#pragma warning (disable:4996)
#include<stdio.h>
#include<ctype.h>
#include<stdlib.h>
#include<string.h>
#define N 30                                     //���ѧ����
#define name_max 13                              //����������󳤶�
#define id_number  13                            //����ѧ�ų���
#define course_num 3                             //���Կ�Ŀ
struct link                                      //ѧ����Ϣ¼��
{
	char number[id_number];                     //ѧ��  ���ַ����ķ�ʽ���������ݽ��м�飬�����벻Ϊ0-9��������ʾ������ǿ���뽡׳��
	char name[name_max];                        //����
	int score[course_num];                      //���Ʒ���
	int score_all;                              //�ܷ�
	float score_average;                        //ƽ����
	struct link* next;                          //ָ����һ�ڵ�ͷָ��
};
void choice();                                  //����û�ѡ��
struct link* AppendNode_data(struct link* head);//������ӵĽڵ�д������
struct link* AppendNode(struct link* head);     //�½�һ���ڵ�ӵ�����ĩβ��������ӽڵ�������ͷָ��
struct link* delete_one_node(struct link* head);//ɾ��ĳ��ָ���Ľڵ�
void prefix_table(char pattern[], int prefix[]);//KMP��ǰ׺��
void move_prefix_table(int prefix[], int n);    //��λ���prefix table
int kmp_search(char text[], char pattern[]);    //KMP_search
struct link* alter(struct link* head);          //�޸�����
void delete_all_link(struct link* head);        //�ͷ����нڵ�
void Show_score_init(struct link* head);        //����ɼ�
void Show_score(struct link* head);             //�����ƽ���ֺ��ֵܷĳɼ�
void score_average_all(struct link* head);      //����ÿ��ѧ��ƽ���ֺ��ܷ�
void each_course(struct link* head);            //����ÿ�Ƶ�ƽ���ֺ��ܷ�
struct link* Sortlink_ascending(struct link* head);         //���ܷ����� ���ؽ�head��Ԫ�����������ĵ�ַ
struct link* Sortlink_descending(struct link* head);        //���ֽܷ��� ���ؽ�head��Ԫ�����������ĵ�ַ
struct link* Sortlink_number_descending(struct link* head); //ѧ�Ž�������  ���ؽ�head��Ԫ�����������ĵ�ַ
struct link* Sortlink_name_dictionary(struct link* head);   //���ְ��ֵ�˳�� ��С�������
void swapdata(struct link* p1, struct link* p2);//���������������������
void Search_number(struct link* head);          //����ѧ�� ��ģ��ƥ�䣩��ѯѧ�������Ϳ��Գɼ�
void Search_name(struct link* head);            //�������� ��ģ��ƥ�䣩��ѯѧ�������Ϳ��Գɼ�
void Statistic_link(struct link* head);         //��������  �����㣨90~100�������ã�80~89�����еȣ�70~79��������60~69����������0~59��5�����
												//ͬʱ�ֿγ�ͳ��ÿ�����������Լ���ռ�İٷֱȣ���ͳ�Ƶ÷�Ϊ100�ֵ���������ռ�İٷֱȣ�
void list_link(struct link* head);              //�б���ʾ����
void WritetoFile(struct link* head);            //д���ļ�
struct link* ReadfromFile(struct link* head);   //���ļ���ȡ
int main()
{
	int choice1;                                //choice1���û�ѡ���ѡ��
	int n = 0;                                  //���ڼ�¼�༶����
	int i;                                      //��¼ÿ��¼���ѧ����
	char c;
	struct link* head = NULL;
	struct link* pr = NULL;
	system("color F9");
	choice();                                   //����û��ɲ�����ѡ��
	printf("\n                        Please enter your choice:\n");
	while (1)                                   //ѭ��ʹ�û�����ִ����ѡ����������
	{

		scanf("%d", &choice1);                  // ¼���û�ѡ��
		while (getchar() != '\n');
		switch (choice1)
		{
		case 0:                                 //while��1)ѭ���ĳ���
			delete_all_link(head);              //�ͷ������ڴ�
			printf("\n�����ѽ�����");
			choice1 = -1;
			return 0;
		case 1:                                 //�û�ѡ��Ϊ1ʱ��¼���û�ѡ�� //���⽫ָ���ͷţ������˹���дΪ������������¼��������׽�ָ���ͷţ�

			c = 'Y';

			i = 0;                             //���ڼ�¼����λѧ�����ձ��ɹ�¼��
			while (c == 'y' || c == 'Y')
			{
				head = AppendNode(head);       //����½ڵ�󷵻������ͷָ��
				head = AppendNode_data(head);  //���½ڵ�д������  ͨ���ݹ�ķ�ʽ����AppendNode(head)������������ڵ㣬���ɹ���������ʱ�򣬲Ż����ִ����һ��

				printf("Do you want to append a student's information(�����밴'y'��'Y'���ص����˵��밴��������):");
				scanf(" %c", &c);
				while (getchar() != '\n');
			}

			Show_score_init(head);             //����ɼ�
			pr = head;
			while (pr != NULL)
			{
				i++;
				pr = pr->next;
			}
			printf("%d new students have been apended !\n", i);
			printf("\n                        Please enter your choice:\n");
			choice1 = -1;
			break;
		case 2:

			head = delete_one_node(head);     //ɾ��һ���ڵ�
			printf("\n                        Please enter your choice:\n");
			choice1 = -1;
			break;
		case 3:
			head = alter(head);              //�ı�ĳһ�ڵ��ֵ
			printf("\n                        Please enter your choice:\n");
			choice1 = -1;
			break;
		case 4:                                //�û�ѡ��Ϊ4ʱ
			each_course(head);
			printf("\n                        Please enter your choice:\n");
			choice1 = -1;
			break;
		case 5:
			score_average_all(head);           //�����ֺܷ�ƽ����
			Show_score(head);                  //����������ֺܷ�ƽ���ֵĳɼ�
			printf("\n                        Please enter your choice:\n");
			choice1 = -1;
			break;
		case 6:
			head = Sortlink_descending(head);   //��������
			Show_score(head);
			printf("\n                        Please enter your choice:\n");
			choice1 = -1;
			break;
		case 7:
			head = Sortlink_ascending(head);    //��������
			Show_score(head);
			printf("\n                        Please enter your choice:\n");
			choice1 = -1;
			break;
		case 8:                                 //��ѧ������
			head = Sortlink_number_descending(head);
			Show_score(head);
			printf("\n                        Please enter your choice:\n");
			choice1 = -1;
			break;
		case 9:
			head = Sortlink_name_dictionary(head);//������������
			Show_score(head);
			printf("\n                        Please enter your choice:\n");
			choice1 = -1;
			break;
		case 10:
			Search_number(head);                 //����ѧ������
			printf("\n                        Please enter your choice:\n");
			choice1 = -1;
			break;
		case 11:
			Search_name(head);                  //������������
			printf("\n                        Please enter your choice:\n");
			choice1 = -1;
			break;
		case 12:
			Statistic_link(head);               //��������
			printf("\n                        Please enter your choice:\n");
			choice1 = -1;
			break;
		case 13:
			list_link(head);                   //Ϊ�����˳ɼ��б�
			printf("\n                        Please enter your choice:\n");
			choice1 = -1;
			break;
		case 14:
			WritetoFile(head);                 //д���ļ�
			printf("\n                        Please enter your choice:\n");
			choice1 = -1;
			break;
		case 15:

			head = ReadfromFile(head);         //���ļ���ȡ
			Show_score(head);                  //չʾ�ɼ�
			printf("\n                        Please enter your choice:\n");
			choice1 = -1;
			break;
		default:
			printf("������������!\n����������!\n����������ѡ��:");

			continue;
		}

	}
}

//�������Ǻ�������
void choice()                       //�����е�ѡ��
{
	printf("***********************************************************************************************************\n");
	printf("**********************                                                               **********************\n");
	printf("**********************                                                               **********************\n");
	printf("**********************                    ��ӭ����ѧ���ɼ�����ϵͳ                   **********************\n");
	printf("**********************                                                               **********************\n");
	printf("**********************                                                               **********************\n");
	printf("***********************************************************************************************************\n");
	printf("**************                              Management for Students' scores                  **************\n");
	printf("**************          1.Input record                                                       **************\n"); //¼��ÿ��ѧ����ѧ�š������͸��ƿ��Գɼ�
	printf("**************          2.Delete a node                                                      **************\n"); //ɾ��ָ���Ľڵ�
	printf("**************          3.Alter data                                                         **************\n"); //�ı�ڵ��е�ĳ��ֵ
	printf("**************          4.Calculate total and average score of every course                  **************\n"); //����ÿ�ſγ̵��ֺܷ�ƽ����
	printf("**************          5.Calculate total and average score of every student                 **************\n"); //����ÿ��ѧ�����ֺܷ�ƽ����
	printf("**************          6.Sort in descending order by total score of every student           **************\n"); //��ÿ��ѧ�����ܷ��ɸߵ����ų����α�
	printf("**************          7.Sort in ascending order by total score of every student            **************\n"); //��ÿ��ѧ�����ܷ��ɵ͵����ų����α�
	printf("**************          8.Sort in ascending order by number                                  **************\n"); //��ѧ����С�����ų��ɼ���
	printf("**************          9.Sort in dictionary order by name                                   **************\n"); //���������ֵ�˳���ų��ɼ���
	printf("**************         10.Search by number                                                   **************\n"); //��ѧ�Ų�ѯѧ���������俼�Գɼ�
	printf("**************         11.Search by name                                                     **************\n"); //��������ѯѧ���������俼�Գɼ�
	printf("**************         12.Statistic analysis for every course                                **************\n"); //�����㣨90~100�������ã�80~89�����еȣ�70~79��
																															 //������60~69����������0~59��5����𣬶�ÿ��
																															 //�γ̷ֱ�ͳ��ÿ�����������Լ���ռ�İٷֱȣ���
																															 //ͳ�Ƶ÷�Ϊ100�ֵ���������ռ�İٷֱȣ�
	printf("**************         13.List reccord                                                       **************\n"); //���ÿ��ѧ����ѧ�š����������ƿ��Գɼ����Լ�ÿ�ſγ̵��ֺܷ�ƽ����
	printf("**************         14.Write to a file                                                    **************\n"); //��ÿ��ѧ���ļ�¼��Ϣд���ļ�
	printf("**************         15.Read from a file                                                   **************\n"); //���ļ��ж���ÿ��ѧ���ļ�¼��Ϣ����ʾ
	printf("**************          0.Exit                                                               **************\n"); //�˳�
	printf("***********************************************************************************************************\n");
	printf("***********************************************************************************************************\n");
	printf("***********************************************************************************************************\n");

}

struct link* AppendNode_data(struct link* head)                                  // head Ϊ����ͷָ�� iΪ�����ڽṹ��ĸ���
{
	int  m, j;
	int i;                                                              //i Ϊѧ�ų��ȷ����������ѧ�ŵļ���
	int flag1 = 0;
	int flag2 = 0;
	char id_number1[id_number];
	char name1[name_max];
	char score1[course_num][10];                                        //��������ĳɼ����Ϊ10λ��������Գɼ�����Ƿ���0-100֮��
																		//����Ϊ�ַ�����ֹ������ĸ����ǿ��׳��
	struct link* p;
	struct link* p1 = head;
	struct link* p2 = head;
	printf("Input student number(�����볤��С��10��ѧ��):");
	scanf("%s", id_number1);
	i = strlen(id_number1);
	for (j = 0; j < i; j++)
	{
		if (id_number1[j] > '9' || id_number1[j] < '0' )
		{
			printf("�������ѧ������!\n");
			return AppendNode_data(head);
		}
	}
	while (p1 != NULL)
	{
		if (strcmp(p1->number, id_number1) == 0)
		{
			printf("�������ѧ���ظ���\n");
			return AppendNode_data(head);
		}
		p1 = p1->next;
	}
	printf("Input student name:(�����볤��С��10������)");
	scanf("%s", name1);
	while (getchar() != '\n');
	while (p2 != NULL)
	{
		if (strcmp(p2->name, name1) == 0)
		{
			printf("������������ظ���\n");
			return AppendNode_data(head);
		}
		p2 = p2->next;
	}
	printf("Input the student score:(�밴 MT EN PH ˳�����뿼�Գɼ�,ÿ����һ�ųɼ��󰴻س�������һ��Ŀ�ɼ���)\n");
	for (i = 0; i < course_num; i++)
	{
		scanf("%s", &score1[i]);
		while (getchar() != '\n');
	}
	for (i = 0; i < course_num; i++)
	{
		if (strlen(score1[i]) >= 3 || strlen(score1[i]) == 0)
		{
			if (strlen(score1[i]) == 3 && score1[i][0] == '1' && score1[i][1] == '0' && score1[i][2] == '0')
			{
				continue;
			}
			else
			{
				printf("�����������󣡣��������ڣ�0-100���ĳɼ���\n");
				return AppendNode_data(head);
			}
		}
		if (strlen(score1[i]) == 2)
		{
			if (score1[i][0] < '0' || score1[i][0] > '9' || score1[i][1] < '0' || score1[i][1] > '9')
			{
				printf("�����������󣡣��������ڣ�0-100���ĳɼ���\n");
				return AppendNode_data(head);
			}
		}
		if (strlen(score1[i]) == 1)
		{
			if (score1[i][0] < '0' || score1[i][0] > '9')
			{
				printf("�����������󣡣��������ڣ�0-100���ĳɼ���\n");
				return AppendNode_data(head);
			}
		}
	}
	p = head;
	while (p->next != NULL)
	{
		p = p->next;
	}
	strcpy(p->number, id_number1);
	strcpy(p->name, name1);
	for (m = 0; m < course_num; m++)
	{
		if (strlen(score1[m]) == 3)
		{
			p->score[m] = 100;
		}
		else if (strlen(score1[m]) == 2)
		{
			p->score[m] = (score1[m][0] - '0') * 10 + (score1[m][1] - '0');
		}
		else if (strlen(score1[m]) == 1)
		{
			p->score[m] = (score1[m][0] - '0');
		}
	}
	return head;
}

struct link* AppendNode(struct link* head)     //��ԭ����β�����һ���ڵ�
{
	struct link* p = NULL, * pr = head;
	p = (struct link*)malloc(sizeof(struct link));
	if (p == NULL)
	{
		printf("No enough memory to allocate!\n");
		exit(0);
	}
	if (head == NULL)
	{
		head = p;
	}
	else
	{
		while (pr->next != NULL)
		{
			pr = pr->next;
		}
		pr->next = p;
	}
	p->next = NULL;
	return head;
}

struct link* delete_one_node(struct link* head)            //ɾ��ĳһ���ڵ�
{
	struct link* p = head;
	struct link* pr = head;
	int i;
	char name1[name_max];
	char number1[id_number];
	int flag1 = 0;
	int flag2 = 0;
	char choice1;
	char choice2;
	if (head == NULL)                               //headΪ��ʱ
	{
		printf("��ǰ����Ϊ�գ��޷�ɾ����\n");
		return head;
	}
	else
	{
		printf("�������ɾ����ѧ����ѧ�Ż�������\n");
		printf("����������ɾ��������1��\n");
		printf("��ѧ�Ų���ɾ��������2��\n");
		scanf("%d", &i);
		while (getchar() != '\n');
		switch (i)
		{
		case 1:                                                         //����������
			printf("�������ɾ��ѧ����������\n");
			gets(name1);
			while (strcmp(name1, p->name) != 0 && p->next != NULL)
			{
				pr = p;
				p = p->next;
			}
			if (strcmp(name1, p->name) == 0)
			{
				flag1 = 1;
				printf("���ҵ�����Ϊ%s��ѧ��,�Ƿ�ȷ��ɾ�����������롮y'��Y��ȷ��ɾ����", name1);
				scanf(" %c", &choice1);
				while (getchar() != '\n');
				if (choice1 == 'y' || choice1 == 'Y')
				{

					if (p == head)
					{
						head = head->next;
					}
					else
					{
						pr->next = p->next;
					}
					free(p);
					printf("��������ѧ����Ϣ�ѱ�ɾ����\n");
					return head;
				}
				else
				{
					printf("��ѧ���ɼ�δɾ����");
					return head;
				}
			}

			if (flag1 == 0)
			{
				printf("��ǰδ�ҵ���ȫƥ���ѧ�����Ƿ����ģ��ƥ�䣨������'y'��n')");
				scanf(" %c", &choice2);
				while (getchar() != '\n');
				if (choice2 == 'y' || choice2 == 'Y')
				{
					p = head;
					while (p != NULL)
					{
						if (kmp_search(p->name, name1) == 1)
						{

							printf("���ҵ���������%s��ѧ��,��ѧ������Ϊ%s,�Ƿ�ȷ��ɾ�����������롮y'��Y��ȷ��ɾ����", name1, p->name);
							scanf(" %c", &choice1);
							while (getchar() != '\n');
							if (choice1 == 'y' || choice1 == 'Y')
							{
								flag2 = 1;
								if (p == head)
								{
									head = head->next;
								}
								else
								{
									pr->next = p->next;
								}
								free(p);
								printf("��������ѧ����Ϣ�ѱ�ɾ����\n");
								return head;
							}

						}
						pr = p;
						p = p->next;
					}
				}
			}
			if (flag1 == 0 && flag2 == 0)
			{
				printf("��ǰδɾ����һѧ���ɼ���\n");
			}
			return head;
		case 2:                                                   //��ѧ�Ų���
			printf("�������ɾ��ѧ����ѧ�ţ�\n");
			gets(number1);
			while (strcmp(number1, p->number) != 0 && p->next != NULL)
			{
				pr = p;
				p = p->next;
			}
			if (strcmp(number1, p->number) == 0)
			{
				flag1 = 1;
				printf("���ҵ�ѧ��Ϊ%s��ѧ��,�Ƿ�ȷ��ɾ�����������롮y'��Y��ȷ��ɾ����", number1);
				scanf(" %c", &choice1);
				while (getchar() != '\n');
				if (choice1 == 'y' || choice1 == 'Y')
				{

					if (p == head)
					{
						head = head->next;
					}
					else
					{
						pr->next = p->next;
					}
					free(p);
					printf("��������ѧ����Ϣ�ѱ�ɾ����\n");
					return head;
				}
				else
				{
					printf("��ѧ���ɼ�δɾ����");
					return head;
				}
			}

			if (flag1 == 0)
			{
				printf("��ǰδ�ҵ���ȫƥ���ѧ�����Ƿ����ģ��ƥ�䣨������'y'��n')");
				scanf(" %c", &choice2);
				while (getchar() != '\n');
				if (choice2 == 'y' || choice2 == 'Y')
				{
					p = head;
					while (p != NULL)
					{
						if (kmp_search(p->number, number1) == 1)
						{

							printf("���ҵ�ѧ�ź���%s��ѧ��,��ѧ��ѧ��Ϊ%s,�Ƿ�ȷ��ɾ�����������롮y'��Y��ȷ��ɾ����", number1, p->number);
							scanf(" %c", &choice1);
							while (getchar() != '\n');
							if (choice1 == 'y' || choice1 == 'Y')
							{
								flag2 = 1;
								if (p == head)
								{
									head = head->next;
								}
								else
								{
									pr->next = p->next;
								}
								free(p);
								printf("��������ѧ����Ϣ�ѱ�ɾ����\n");
								return head;
							}

						}
						pr = p;
						p = p->next;
					}
				}
			}
			if (flag1 == 0 && flag2 == 0)
			{
				printf("��ǰδɾ����һѧ���ɼ���\n");
			}
			return head;
		default:
			printf("������������\n");
			return head;
		}
	}

}

void prefix_table(char pattern[], int prefix[])            //KMP�㷨����λǰ��ǰ׺��
{
	int n = strlen(pattern);
	prefix[0] = 0;
	int len = 0;
	int i = 1;              //�Ƚ� �ӵڶ�����ĸ��ʼ  ��һ����ĸһ��Ϊ0
	while (i < n)
	{
		if (pattern[i] == pattern[len])
		{
			len++;
			prefix[i] = len;
			i++;
		}
		else
		{
			if (len > 0)
			{
				len = prefix[len - 1];
			}
			else
			{
				prefix[i] = len;
				i++;
			}
		}
	}
}

void move_prefix_table(int prefix[], int n)                  //�ƶ����ǰ׺��
{
	int i;
	for (i = n - 1; i > 0; i--)
	{
		prefix[i] = prefix[i - 1];

	}
	prefix[0] = -1;
}

int kmp_search(char text[], char pattern[])                //kmp����
{
	int i = 0, j = 0;
	int m = strlen(text);
	int n = strlen(pattern);
	int* prefix = (int*)malloc(n * sizeof(int));
	prefix_table(pattern, prefix);
	move_prefix_table(prefix, n);
	if (strlen(pattern) > strlen(text))
	{
		return 0;
	}
	while (i < m)
	{
		if (j == n - 1 && text[i] == pattern[j])
		{
			return 1;
			j = prefix[j];

		}
		if (text[i] == pattern[j])
		{
			i++;
			j++;
		}
		else
		{
			j = prefix[j];
			if (j == -1)
			{
				i++;
				j++;
			}
		}
	}
	free(prefix);
	return 0;
}

struct link* alter(struct link* head)                   //�ı�ڵ����ֵ
{
	struct link* p;
	struct link* pr;
	char a;

	char name[name_max];
	char number[id_number];
	char choice;
	char choice1;
	char choice3;
	char choice4;
	int choice5;
	int mark;
	int flag = 0;
	int flag1 = 0;
	if (head == NULL)
	{
		printf("��ǰ����Ϊ�գ���");
		return head;
	}
	else
	{
		printf("����������Ҫ�޸ĵ�ѧ����������ѧ�ţ�\n");
		printf("�������޸�������a��\n");
		printf("��ѧ���޸�������b��\n");
		scanf("%c", &a);
		while (getchar() != '\n');
		switch (a)
		{
		case 'a':
			printf("�������޸ĳɼ���ѧ��������");
			scanf("%s", name);
			while (getchar() != '\n');
			p = head;
			while (p->next != NULL && strcmp(p->name, name) != 0)
			{
				pr = p;
				p = p->next;
			}
			if (strcmp(p->name, name) == 0)
			{
				flag = 1;
				printf("���޸ĵ�ѧ���������ǣ�%s\n", name);
				printf("��ȷ��Ҫ�޸���(ȷ�������롮y')\n");
				scanf("%c", &choice);
				while (getchar() != '\n');
				while (choice == 'y' || choice == 'Y')
				{
					printf("���޸�ѧ��\n����:%s\nѧ��:%s\n", p->name, p->number);
					printf("��ǰ�ɼ�Ϊ��MT:%d EN:%d PH:%d\n", p->score[0], p->score[1], p->score[2]);
					printf("����������Ҫ�޸ĵ�ֵ���ֺܷ�ƽ���ֻ����޸����Ƴɼ����Զ��޸ģ�:\n");
					printf("�޸�MT������m\n");
					printf("�޸�EN������E\n");
					printf("�޸�PH������P\n");
					printf("�����������ݽ��᷵����һ��:�������˳��޸Ĺ�����������������");
					scanf("%c", &choice1);
					while (getchar() != '\n');
					if (choice1 == 'm' || choice1 == 'M')
					{
						printf("����ǰ���޸�%s�� MT ����\n", p->name);
						printf("��������Ҫ�޸ĵķ�����");
						scanf("%d", &mark);
						while (getchar() != '\n');
						p->score[0] = mark;
						p->score_all = p->score[0] + p->score[1] + p->score[2];
					}
					else if (choice1 == 'e' || choice1 == 'E')
					{
						printf("����ǰ���޸�%s�� EN ����\n", p->name);
						printf("��������Ҫ�޸ĵķ�����");
						scanf("%d", &mark);
						while (getchar() != '\n');
						p->score[1] = mark;
						p->score_all = p->score[0] + p->score[1] + p->score[2];
					}
					else if (choice1 == 'p' || choice1 == 'P')
					{
						printf("����ǰ���޸�%s�� PH ����\n", p->name);
						printf("��������Ҫ�޸ĵķ�����");
						scanf("%d", &mark);
						while (getchar() != '\n');
						p->score[2] = mark;
						p->score_all = p->score[0] + p->score[1] + p->score[2];
					}
					else
					{
						return head;
					}
				}
			}

			if (flag == 0)                                  //����������û����ȫ��ͬ������
			{
				printf("��ǰδ�ҵ���ȫƥ���ѧ�����Ƿ����ģ��ƥ�䣨������'y'��n')");
				scanf(" %c", &choice3);
				while (getchar() != '\n');
				if (choice3 == 'y' || choice3 == 'Y')
				{
					p = head;
					while (p != NULL)
					{
						if (kmp_search(p->name, name) == 1)
						{
							printf("��Ҫ�ҵ���%s��?\n", p->name);
							printf("��ȷ��������1");
							scanf("%d", &choice5);
							while (getchar() != '\n');
							if (choice5 != 1)
							{
								if (p->next != NULL)
								{
									p = p->next;
									continue;
								}
								else
								{
									return head;
								}
							}
							while (1)
							{
								flag1 = 1;
								printf("���޸�ѧ��\n����:%s\nѧ��:%s\n", p->name, p->number);
								printf("��ǰ�ɼ�Ϊ��MT:%d EN:%d PH:%d\n", p->score[0], p->score[1], p->score[2]);
								printf("����������Ҫ�޸ĵ�ֵ���ֺܷ�ƽ���ֻ����޸����Ƴɼ����Զ��޸ģ�:\n");
								printf("�޸�MT������m\n");
								printf("�޸�EN������E\n");
								printf("�޸�PH������P\n");
								printf("�����������ݽ��᷵����һ��:�������˳��޸Ĺ�����������������");
								scanf("%c", &choice4);
								while (getchar() != '\n');
								if (choice4 == 'm' || choice4 == 'M')
								{
									printf("����ǰ���޸�%s�� MT ����\n", p->name);
									printf("��������Ҫ�޸ĵķ�����");
									scanf("%d", &mark);
									while (getchar() != '\n');
									p->score[0] = mark;
								}
								else if (choice4 == 'e' || choice4 == 'E')
								{
									printf("����ǰ���޸�%s�� EN ����\n", p->name);
									printf("��������Ҫ�޸ĵķ�����");
									scanf("%d", &mark);
									while (getchar() != '\n');
									p->score[1] = mark;
								}
								else if (choice4 == 'p' || choice4 == 'P')
								{
									printf("����ǰ���޸�%s�� PH ����\n", p->name);
									printf("��������Ҫ�޸ĵķ�����");
									scanf("%d", &mark);
									while (getchar() != '\n');
									p->score[2] = mark;
								}
								else
								{
									return head;
								}
							}

						}
						p = p->next;
					}
				}

			}
			if (flag == 0 && flag1 == 0)
			{
				printf("δ�ҵ�������%s��ص�ѧ��", name);
				return head;
			}
			return head;
		case 'b':
			printf("�������޸ĳɼ���ѧ��ѧ�ţ�");
			scanf("%s", number);
			while (getchar() != '\n');
			p = head;
			while (p->next != NULL && strcmp(p->number, number) != 0)
			{
				pr = p;
				p = p->next;
			}
			if (strcmp(p->number, number) == 0)
			{
				flag = 1;
				printf("���޸ĵ�ѧ����ѧ���ǣ�%s\n", number);
				printf("��ȷ��Ҫ�޸���(ȷ�������롮y')\n");
				scanf("%c", &choice);
				while (getchar() != '\n');
				while (choice == 'y' || choice == 'Y')
				{
					printf("���޸�ѧ��\n����:%s\nѧ��:%s\n", p->name, p->number);
					printf("��ǰ�ɼ�Ϊ��MT:%d EN:%d PH:%d\n", p->score[0], p->score[1], p->score[2]);
					printf("����������Ҫ�޸ĵ�ֵ���ֺܷ�ƽ���ֻ����޸����Ƴɼ����Զ��޸ģ�:\n");
					printf("�޸�MT������m\n");
					printf("�޸�EN������E\n");
					printf("�޸�PH������P\n");
					printf("�����������ݽ��᷵����һ��:�������˳��޸Ĺ�����������������");
					scanf("%c", &choice1);
					while (getchar() != '\n');
					if (choice1 == 'm' || choice1 == 'M')
					{
						printf("����ǰ���޸�%s�� MT ����\n", p->name);
						printf("��������Ҫ�޸ĵķ�����");
						scanf("%d", &mark);
						while (getchar() != '\n');
						p->score[0] = mark;
						p->score_all = p->score[0] + p->score[1] + p->score[2];
					}
					else if (choice1 == 'e' || choice1 == 'E')
					{
						printf("����ǰ���޸�%s�� EN ����\n", p->name);
						printf("��������Ҫ�޸ĵķ�����");
						scanf("%d", &mark);
						while (getchar() != '\n');
						p->score[1] = mark;
						p->score_all = p->score[0] + p->score[1] + p->score[2];
					}
					else if (choice1 == 'p' || choice1 == 'P')
					{
						printf("����ǰ���޸�%s�� PH ����\n", p->name);
						printf("��������Ҫ�޸ĵķ�����");
						scanf("%d", &mark);
						while (getchar() != '\n');
						p->score[2] = mark;
						p->score_all = p->score[0] + p->score[1] + p->score[2];
					}
					else
					{
						return head;
					}
				}
			}

			if (flag == 0)
			{
				printf("��ǰδ�ҵ���ȫƥ���ѧ�����Ƿ����ģ��ƥ�䣨������'y'��n')");
				scanf(" %c", &choice3);
				while (getchar() != '\n');
				if (choice3 == 'y' || choice3 == 'Y')
				{
					p = head;
					while (p != NULL)
					{
						if (kmp_search(p->number, number) == 1)
						{
							printf("��Ҫ�ҵ���%s��?\n", p->number);
							printf("��ȷ��������1");
							scanf("%d", &choice5);
							while (getchar() != '\n');
							if (choice5 != 1)
							{
								if (p->next != NULL)
								{
									p = p->next;
									continue;
								}
								else
								{
									return head;
								}
							}
							while (1)
							{
								flag1 = 1;
								printf("���޸�ѧ��\n����:%s\nѧ��:%s\n", p->name, p->number);
								printf("��ǰ�ɼ�Ϊ��MT:%d EN:%d PH:%d\n", p->score[0], p->score[1], p->score[2]);
								printf("����������Ҫ�޸ĵ�ֵ���ֺܷ�ƽ���ֻ����޸����Ƴɼ����Զ��޸ģ�:\n");
								printf("�޸�MT������m\n");
								printf("�޸�EN������E\n");
								printf("�޸�PH������P\n");
								printf("�����������ݽ��᷵����һ��:�������˳��޸Ĺ�����������������");
								scanf("%c", &choice4);
								while (getchar() != '\n');
								if (choice4 == 'm' || choice4 == 'M')
								{
									printf("����ǰ���޸�%s�� MT ����\n", p->name);
									printf("��������Ҫ�޸ĵķ�����");
									scanf("%d", &mark);
									while (getchar() != '\n');
									p->score[0] = mark;
								}
								else if (choice4 == 'e' || choice4 == 'E')
								{
									printf("����ǰ���޸�%s�� EN ����\n", p->name);
									printf("��������Ҫ�޸ĵķ�����");
									scanf("%d", &mark);
									while (getchar() != '\n');
									p->score[1] = mark;
								}
								else if (choice4 == 'p' || choice4 == 'P')
								{
									printf("����ǰ���޸�%s�� PH ����\n", p->name);
									printf("��������Ҫ�޸ĵķ�����");
									scanf("%d", &mark);
									while (getchar() != '\n');
									p->score[2] = mark;
								}
								else
								{
									return head;
								}
							}

						}
						p = p->next;
					}
				}

			}
			if (flag == 0 && flag1 == 0)
			{
				printf("δ�ҵ�������%s��ص�ѧ��", number);
				return head;
			}
			return head;

		default:
			printf("������������\n");
			return head;

		}
	}
}

void delete_all_link(struct link* head)                 //�ͷŴ��������������нڵ�ռ�õ��ڴ�
{
	struct link* p = head, * pr = NULL;
	if (head != NULL)
	{
		while (p->next != NULL)
		{
			pr = p;
			p = p->next;
			free(pr);
		}
		free(p->next);
	}
}

void each_course(struct link* head)               //���㲢���ÿ�ſε����۷ֺ��ܷ� //head Ϊͷָ��,nΪָ�����
{
	int i, k;
	int j = 0;
	struct link* p = head;
	int all_score[course_num];
	float aver_score[course_num];
	if (head == NULL)                             //�ж������Ƿ�Ϊ��
	{
		printf("��ǰѧ������Ϊ�գ�\n");
	}
	else
	{
		for (i = 0; i < course_num; i++)
		{
			all_score[i] = 0;
			aver_score[i] = 0;
		}
		while (p != NULL)
		{
			for (k = 0; k < course_num; k++)
			{
				all_score[k] += p->score[k];                         //����ÿһ���ܷ�
			}
			p = p->next;
			j++;
		}
		for (i = 0; i < course_num; i++)
		{
			aver_score[i] = (float)all_score[i] / j;              //����ƽ����
		}
		printf("            MT       EN      PH\n");
		printf("�ܷ�:");
		for (i = 0; i < course_num; i++)
		{
			printf("%9d ", all_score[i]);
		}
		printf("\nƽ����:");
		for (i = 0; i < course_num; i++)
		{
			printf("%9.1f", aver_score[i]);
		}
	}
}

void score_average_all(struct link* head)                               //��ƽ���ɼ����ܳɼ�
{
	if (head != NULL)
	{
		struct link* p = head;
		int all_score;
		int i;
		while (p != NULL)
		{
			all_score = 0;
			for (i = 0; i < course_num; i++)
			{
				all_score += p->score[i];
			}
			p->score_all = all_score;
			p->score_average = (float)all_score / course_num;
			p = p->next;
		}
	}
}

void Show_score_init(struct link* head)                                      //����ɼ�������
{
	int i = 1;
	struct link* p = head;

	if (head != NULL)
	{
		printf("  ���         ѧ��         ѧ������    MT        EN        PH    \n");
		while (p != NULL)
		{
			printf("%4d    %14s%12s     %3d       %3d       %3d\n", i, p->number, p->name, p->score[0], p->score[1], p->score[2]);
			p = p->next;
			i++;
		}
	}
}

void Show_score(struct link* head)                                      //�����ƽ���ֺ��ֵܷĳɼ�������
{
	int i = 1;
	struct link* p = head;
	if (head == NULL)
	{
		printf("��ǰѧ������Ϊ��!!");
	}
	else
	{
		printf("   ���      ѧ��           ����       MT        EN        PH       �ܷ�     ƽ����\n");
		while (p != NULL)
		{
			printf("%5d%14s%12s%10d%10d%10d%10d       %.1f\n", i, p->number, p->name, p->score[0], p->score[1], p->score[2], p->score_all, p->score_average);
			p = p->next;
			i++;
		}
	}
}

struct link* Sortlink_ascending(struct link* head)                //�ɼ���������
{
	if (head == NULL)
	{
		printf("Ŀǰû�����ݿ�������\n");
		return head;
	}
	else
	{
		score_average_all(head);                                   //����ƽ���ֺ��ܷ�
		struct link* p = NULL, * pr = NULL;
		p = head;
		while (p->next != NULL)
		{
			pr = p->next;
			while (pr != NULL)
			{
				if (p->score_all > pr->score_all)
				{
					swapdata(pr, p);
				}
				pr = pr->next;
			}
			p = p->next;
		}
		return head;
	}
}

struct link* Sortlink_descending(struct link* head)              //�ɼ���������
{
	if (head == NULL)
	{
		printf("Ŀǰû�����ݿ�������\n");
		return head;
	}
	else
	{
		score_average_all(head);                                   //����ƽ���ֺ��ܷ�
		struct link* p = NULL, * pr = NULL;
		p = head;
		while (p->next != NULL)
		{
			pr = p->next;
			while (pr != NULL)
			{
				if (p->score_all < pr->score_all)
				{
					swapdata(pr, p);
				}
				pr = pr->next;
			}
			p = p->next;
		}
		return head;
	}
}

struct link* Sortlink_number_descending(struct link* head)              //ѧ�Ž�������
{
	if (head == NULL)
	{
		printf("Ŀǰû�����ݿ�������\n");
		return head;
	}
	else
	{
		score_average_all(head);                                   //����ƽ���ֺ��ܷ�
		struct link* p = NULL, * pr = NULL;
		p = head;
		while (p->next != NULL)
		{
			pr = p->next;
			while (pr != NULL)
			{
				if (strcmp(p->number, pr->number) < 0)
				{
					swapdata(pr, p);
				}
				pr = pr->next;
			}
			p = p->next;
		}
		return head;
	}
}

struct link* Sortlink_name_dictionary(struct link* head)
{
	if (head == NULL)
	{
		printf("Ŀǰû�����ݿ�������\n");
		return head;
	}
	else
	{
		score_average_all(head);                                   //����ƽ���ֺ��ܷ�
		struct link* p = NULL, * pr = NULL;
		p = head;
		while (p->next != NULL)
		{
			pr = p->next;
			while (pr != NULL)
			{
				if (strcmp(p->name, pr->name) > 0)
				{
					swapdata(pr, p);
				}
				pr = pr->next;
			}
			p = p->next;
		}
		return head;
	}
}

void swapdata(struct link* p1, struct link* p2)    //ʹ�����ýڵ��������Խ�������  ��������
{
	int i = 0;

	char number1[id_number];
	char name1[name_max];
	int score[course_num];
	int score_all;
	float score_average;

	strcpy(number1, p1->number);
	strcpy(name1, p1->name);
	score_all = p1->score_all;
	score_average = p1->score_average;
	for (i = 0; i < course_num; i++)
	{
		score[i] = p1->score[i];
	}

	strcpy(p1->number, p2->number);
	strcpy(p1->name, p2->name);
	p1->score_all = p2->score_all;
	p1->score_average = p2->score_average;
	for (i = 0; i < course_num; i++)
	{
		p1->score[i] = p2->score[i];
	}

	strcpy(p2->number, number1);
	strcpy(p2->name, name1);
	p2->score_all = score_all;
	p2->score_average = score_average;
	for (i = 0; i < course_num; i++)
	{
		p2->score[i] = score[i];
	}
}

void Search_number(struct link* head)         //����ѧ������
{
	int i = 0;
	int flag1 = 0;                           //����Ƿ�������
	int flag2 = 0;
	char number[id_number];
	char choice1;
	char choice2;
	if (head == NULL)
	{
		printf("��ǰ�����ݿ�������");
	}
	else
	{
		printf("��������Ҫ������ѧ����ѧ�ţ�");
		scanf("%s", number);
		while (getchar() != '\n');
		score_average_all(head);
		Sortlink_descending(head);
		struct link* p;
		struct link* pr;
		p = head;
		while (p != NULL)
		{
			i++;
			if (strcmp(number, p->number) == 0)
			{
				printf("ѧ��������%s\nѧ��ѧ�ţ�%s\n��������%d��!\n", p->name, p->number, i);
				printf("MT�ɼ���%d\nEN�ɼ���%d\nPH�ɼ���%d\n�ܷ֣�%d\nƽ���֣�%.1f\n", p->score[0], p->score[1], p->score[2], p->score_all, p->score_average);
				flag1 = 1;
				break;
			}
			p = p->next;
		}

		if (flag1 == 0)                    //����ȫƥ���ѧ��
		{
			printf("��ǰ����ȫƥ���ѧ��,�Ƿ����ģ��ƥ��?(����������'y'��'Y')");
			scanf("%c", &choice1);
			while (getchar() != '\n');
			if (choice1 == 'y' || choice1 == 'Y')
			{
				p = head;
				i = 0;
				while (p != NULL)
				{
					i++;
					if (kmp_search(p->number, number) == 1)
					{
						flag2 = 1;
						printf("��Ҫ�ҵ���ѧ��Ϊ%s��ѧ����(������'y'��'n')", p->number);
						scanf("%c", &choice2);
						while (getchar() != '\n');
						if (choice2 == 'y' || choice2 == 'Y')
						{
							printf("ѧ��������%s\nѧ��ѧ�ţ�%s\n��������%d��!\n", p->name, p->number, i);
							printf("MT�ɼ���%d\nEN�ɼ���%d\nPH�ɼ���%d\n�ܷ֣�%d\nƽ���֣�%.1f\n", p->score[0], p->score[1], p->score[2], p->score_all, p->score_average);
							break;
						}
					}
					pr = p;
					p = p->next;
				}
			}
		}
		if (flag1 == 0 && flag2 == 0)
		{
			printf("δ�ҵ�����ѧ��Ϊ%s��ѧ������Ϣ��\n", number);
		}

	}
}

void Search_name(struct link* head)        //������������
{
	int i = 0;
	int flag1 = 0;
	int flag2 = 0;
	char name[name_max];
	char choice1;
	char choice2;

	if (head == NULL)
	{
		printf("��ǰ�����ݿ�������");
	}
	else
	{
		printf("��������Ҫ������ѧ����������");
		scanf("%s", name);
		while (getchar() != '\n');
		score_average_all(head);
		Sortlink_descending(head);
		struct link* p;
		struct link* pr;
		p = head;
		while (p != NULL)
		{
			i++;
			if (strcmp(name, p->name) == 0)                               //�ַ�����ͬ
			{
				printf("ѧ��������%s\nѧ��ѧ�ţ�%s\n��������%d��!\n", p->name, p->number, i);
				printf("MT�ɼ���%d\nEN�ɼ���%d\nPH�ɼ���%d\n�ܷ֣�%d\nƽ���֣�%.1f\n", p->score[0], p->score[1], p->score[2], p->score_all, p->score_average);
				flag1 = 1;
				break;
			}
			p = p->next;
		}

		if (flag1 == 0)                                                  //�ַ�������ȫ��ͬ
		{
			printf("��ǰ����ȫƥ���ѧ��,�Ƿ����ģ��ƥ��?(����������'y'��'Y')");
			scanf("%c", &choice1);
			while (getchar() != '\n');
			if (choice1 == 'y' || choice1 == 'Y')
			{
				p = head;
				i = 0;
				while (p != NULL)
				{
					i++;
					if (kmp_search(p->name, name) == 1)
					{
						flag2 = 1;
						printf("��Ҫ�ҵ�������Ϊ%s��ѧ����(������'y'��'n')", p->name);
						scanf("%c", &choice2);
						while (getchar() != '\n');
						if (choice2 == 'y' || choice2 == 'Y')
						{
							printf("ѧ��������%s\nѧ��ѧ�ţ�%s\n��������%d��!\n", p->name, p->number, i);
							printf("MT�ɼ���%d\nEN�ɼ���%d\nPH�ɼ���%d\n�ܷ֣�%d\nƽ���֣�%.1f\n", p->score[0], p->score[1], p->score[2], p->score_all, p->score_average);
							break;
						}
					}
					pr = p;
					p = p->next;
				}
			}
		}
		if (flag1 == 0 && flag2 == 0)                                 //��δ��������
		{
			printf("δ�ҵ���������Ϊ%sѧ������Ϣ��\n", name);
		}
	}
}

void Statistic_link(struct link* head)  //���������е�����
{
	int category[course_num][5];        //��¼ÿ����� ÿ���γ̶�Ӧ������
	float category1[course_num][5];
	int i, n;
	int j = 0;
	struct link* p = head;
	float category2;
	if (head == NULL)
	{
		printf("��ǰ����Ϊ�գ��޷�������");
	}
	else {

		for (i = 0; i < course_num; i++)
		{
			for (n = 0; n < 5; n++)
			{
				category[i][n] = 0;
			}
		}
		n = 0;
		while (p != NULL)
		{
			for (i = 0; i < course_num; i++)                         //��¼��ͬ�ȼ�
			{
				if (p->score[i] >= 90 && p->score[i] <= 100)
				{
					category[i][0]++;
				}
				if (p->score[i] >= 80 && p->score[i] <= 89)
				{
					category[i][1]++;
				}
				if (p->score[i] >= 70 && p->score[i] <= 79)
				{
					category[i][2]++;
				}
				if (p->score[i] >= 60 && p->score[i] <= 69)
				{
					category[i][3]++;
				}
				if (p->score[i] >= 0 && p->score[i] <= 59)
				{
					category[i][4]++;
				}
			}
			p = p->next;
			j++;
		}
		for (i = 0; i < course_num; i++)
		{
			for (n = 0; n < 5; n++)
			{
				category1[i][n] = (float)category[i][n] / j;
			}
		}
		printf("\t\t\t\t  MT  \t\t  EN  \t\t  PH  \n");
		printf("\t\t\tA:");
		for (i = 0; i < course_num; i++)
		{
			category2 = category1[i][0] * 100;
			printf("\t%d   %4.2f%%", category[i][0], category2);
		}
		printf("\n");
		printf("\t\t\tB:");
		for (i = 0; i < course_num; i++)
		{
			category2 = category1[i][1] * 100;
			printf("\t%d   %4.2f%%", category[i][1], category2);
		}
		printf("\n");
		printf("\t\t\tC:");
		for (i = 0; i < course_num; i++)
		{
			category2 = category1[i][2] * 100;
			printf("\t%d   %4.2f%%", category[i][2], category2);
		}
		printf("\n");
		printf("\t\t\tD:");
		for (i = 0; i < course_num; i++)
		{
			category2 = category1[i][3] * 100;
			printf("\t%d   %4.2f%%", category[i][3], category2);
		}
		printf("\n");
		printf("\t\t\tE:");
		for (i = 0; i < course_num; i++)
		{
			category2 = category1[i][4] * 100;
			printf("\t%d   %4.2f%%", category[i][4], category2);
		}
		printf("\n");
	}

}

void list_link(struct link* head)               //�б���ʾ����
{
	int i = 1;
	struct link* p = head;
	if (head == NULL)
	{
		printf("��ǰѧ������Ϊ��!!");
	}
	else
	{
		score_average_all(head);
		printf("����������������������������������������������������������������������������������������������\n");
		printf("|  ���  |     ѧ��     |  ѧ������  |    MT    |    EN    |    PH    |   �ܷ�   |   ƽ����   |\n");
		printf("����������������������������������������������������������������������������������������������\n");
		while (p != NULL)
		{
			printf("|%4d    |%14s|%12s|   %3d    |   %3d    |   %3d    |   %3d    |   %4.2f    |\n", i, p->number, p->name, p->score[0], p->score[1], p->score[2], p->score_all, p->score_average);
			printf("����������������������������������������������������������������������������������������������\n");
			p = p->next;
			i++;
		}
	}
}

void WritetoFile(struct link* head)              //д���ļ�
{
	struct link* p = head;
	int i = 0;
	FILE* fp = fopen("data.txt", "w");
	score_average_all(head);
	if (fp == NULL)
	{
		printf("Failure to open data.txt!\n");
	}
	else
	{
		while (p != NULL)
		{
			i++;
			fprintf(fp, "%8d  %14s  %12s  %6d  %6d  %6d  %6d  %7.2f\n", i, p->number, p->name, p->score[0], p->score[1], p->score[2], p->score_all, p->score_average);
			p = p->next;
		}
		fclose(fp);
	}
	printf("�ɹ�д���ļ���\n");

}

struct link* ReadfromFile(struct link* head)     //���ļ���ȡ
{
	struct link* p;
	int i = 0;
	FILE* fp = fopen("data.txt", "r");
	score_average_all(head);
	if (fp == NULL)
	{
		printf("Failure to open data.txt!\n");
	}
	else
	{
		struct link temp;   //
		fscanf(fp, "%d  %s  %s  %d  %d  %d  %d  %f", &i, temp.number, temp.name, &temp.score[0], &temp.score[1], &temp.score[2], &temp.score_all, &temp.score_average);
		while (!feof(fp))
		{
			head = AppendNode(head);
			p = head;
			while (p->next != NULL)
			{
				p = p->next;
			}
			i++;
			strcpy(p->number, temp.number);
			strcpy(p->name, temp.name);
			p->score[0] = temp.score[0];
			p->score[1] = temp.score[1];
			p->score[2] = temp.score[2];
			p->score_all = temp.score_all;
			p->score_average = temp.score_average;
			fscanf(fp, "%d  %s  %s  %d  %d  %d  %d  %f", &i, temp.number, temp.name, &temp.score[0], &temp.score[1], &temp.score[2], &temp.score_all, &temp.score_average);
		}
		fclose(fp);
		printf("�ɹ����ļ���ȡ��\n");
	}
	return head;
}
