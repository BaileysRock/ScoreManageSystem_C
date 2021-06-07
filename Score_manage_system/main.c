#pragma warning (disable:4996)
#include<stdio.h>
#include<ctype.h>
#include<stdlib.h>
#include<string.h>
#define N 30                                     //最大学生数
#define name_max 13                              //设置姓名最大长度
#define id_number  13                            //设置学号长度
#define course_num 3                             //考试科目
struct link                                      //学生信息录入
{
	char number[id_number];                     //学号  用字符串的方式对输入数据进行检查，若输入不为0-9的数，提示错误。增强代码健壮性
	char name[name_max];                        //姓名
	int score[course_num];                      //各科分数
	int score_all;                              //总分
	float score_average;                        //平均分
	struct link* next;                          //指向下一节的头指针
};
void choice();                                  //输出用户选项
struct link* AppendNode_data(struct link* head);//对新添加的节点写入数据
struct link* AppendNode(struct link* head);     //新建一个节点加到链表末尾，返回添加节点后的链表头指针
struct link* delete_one_node(struct link* head);//删除某个指定的节点
void prefix_table(char pattern[], int prefix[]);//KMP的前缀表
void move_prefix_table(int prefix[], int n);    //移位后的prefix table
int kmp_search(char text[], char pattern[]);    //KMP_search
struct link* alter(struct link* head);          //修改数据
void delete_all_link(struct link* head);        //释放所有节点
void Show_score_init(struct link* head);        //输出成绩
void Show_score(struct link* head);             //输出含平均分和总分的成绩
void score_average_all(struct link* head);      //计算每个学生平均分和总分
void each_course(struct link* head);            //计算每科的平均分和总分
struct link* Sortlink_ascending(struct link* head);         //按总分升序 返回将head中元素排序后链表的地址
struct link* Sortlink_descending(struct link* head);        //按总分降序 返回将head中元素排序后链表的地址
struct link* Sortlink_number_descending(struct link* head); //学号降序排列  返回将head中元素排序后链表的地址
struct link* Sortlink_name_dictionary(struct link* head);   //名字按字典顺序 由小到大输出
void swapdata(struct link* p1, struct link* p2);//交换链表，方便对链表排序
void Search_number(struct link* head);          //搜索学号 （模糊匹配）查询学生排名和考试成绩
void Search_name(struct link* head);            //搜索姓名 （模糊匹配）查询学生排名和考试成绩
void Statistic_link(struct link* head);         //分析链表  按优秀（90~100）、良好（80~89）、中等（70~79）、及格（60~69）、不及格（0~59）5个类别
												//同时分课程统计每个类别的人数以及所占的百分比，并统计得分为100分的人数和所占的百分比；
void list_link(struct link* head);              //列表显示数据
void WritetoFile(struct link* head);            //写入文件
struct link* ReadfromFile(struct link* head);   //从文件读取
int main()
{
	int choice1;                                //choice1是用户选择的选项
	int n = 0;                                  //用于记录班级人数
	int i;                                      //记录每次录入的学生数
	char c;
	struct link* head = NULL;
	struct link* pr = NULL;
	system("color F9");
	choice();                                   //输出用户可操作的选项
	printf("\n                        Please enter your choice:\n");
	while (1)                                   //循环使用户可以执行完选项后继续操作
	{

		scanf("%d", &choice1);                  // 录入用户选项
		while (getchar() != '\n');
		switch (choice1)
		{
		case 0:                                 //while（1)循环的出口
			delete_all_link(head);              //释放链表内存
			printf("\n程序已结束！");
			choice1 = -1;
			return 0;
		case 1:                                 //用户选择为1时，录入用户选项 //避免将指针释放，不将此过程写为函数。（例如录入操作，易将指针释放）

			c = 'Y';

			i = 0;                             //用于记录多少位学生最终被成功录入
			while (c == 'y' || c == 'Y')
			{
				head = AppendNode(head);       //添加新节点后返回链表的头指针
				head = AppendNode_data(head);  //对新节点写入数据  通过递归的方式避免AppendNode(head)函数创建过多节点，当成功输入数据时候，才会继续执行下一步

				printf("Do you want to append a student's information(继续请按'y'或'Y'，回到主菜单请按其他键！):");
				scanf(" %c", &c);
				while (getchar() != '\n');
			}

			Show_score_init(head);             //输出成绩
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

			head = delete_one_node(head);     //删除一个节点
			printf("\n                        Please enter your choice:\n");
			choice1 = -1;
			break;
		case 3:
			head = alter(head);              //改变某一节点的值
			printf("\n                        Please enter your choice:\n");
			choice1 = -1;
			break;
		case 4:                                //用户选择为4时
			each_course(head);
			printf("\n                        Please enter your choice:\n");
			choice1 = -1;
			break;
		case 5:
			score_average_all(head);           //计算总分和平均分
			Show_score(head);                  //输出计算完总分和平均分的成绩
			printf("\n                        Please enter your choice:\n");
			choice1 = -1;
			break;
		case 6:
			head = Sortlink_descending(head);   //降序排列
			Show_score(head);
			printf("\n                        Please enter your choice:\n");
			choice1 = -1;
			break;
		case 7:
			head = Sortlink_ascending(head);    //升序排列
			Show_score(head);
			printf("\n                        Please enter your choice:\n");
			choice1 = -1;
			break;
		case 8:                                 //按学号排列
			head = Sortlink_number_descending(head);
			Show_score(head);
			printf("\n                        Please enter your choice:\n");
			choice1 = -1;
			break;
		case 9:
			head = Sortlink_name_dictionary(head);//按照姓名排列
			Show_score(head);
			printf("\n                        Please enter your choice:\n");
			choice1 = -1;
			break;
		case 10:
			Search_number(head);                 //按照学号搜索
			printf("\n                        Please enter your choice:\n");
			choice1 = -1;
			break;
		case 11:
			Search_name(head);                  //按照姓名搜索
			printf("\n                        Please enter your choice:\n");
			choice1 = -1;
			break;
		case 12:
			Statistic_link(head);               //分析数据
			printf("\n                        Please enter your choice:\n");
			choice1 = -1;
			break;
		case 13:
			list_link(head);                   //为所有人成绩列表
			printf("\n                        Please enter your choice:\n");
			choice1 = -1;
			break;
		case 14:
			WritetoFile(head);                 //写入文件
			printf("\n                        Please enter your choice:\n");
			choice1 = -1;
			break;
		case 15:

			head = ReadfromFile(head);         //从文件读取
			Show_score(head);                  //展示成绩
			printf("\n                        Please enter your choice:\n");
			choice1 = -1;
			break;
		default:
			printf("您的输入有误!\n请重新输入!\n请输入您的选项:");

			continue;
		}

	}
}

//接下来是函数部分
void choice()                       //界面中的选项
{
	printf("***********************************************************************************************************\n");
	printf("**********************                                                               **********************\n");
	printf("**********************                                                               **********************\n");
	printf("**********************                    欢迎来到学生成绩管理系统                   **********************\n");
	printf("**********************                                                               **********************\n");
	printf("**********************                                                               **********************\n");
	printf("***********************************************************************************************************\n");
	printf("**************                              Management for Students' scores                  **************\n");
	printf("**************          1.Input record                                                       **************\n"); //录入每个学生的学号、姓名和各科考试成绩
	printf("**************          2.Delete a node                                                      **************\n"); //删除指定的节点
	printf("**************          3.Alter data                                                         **************\n"); //改变节点中的某个值
	printf("**************          4.Calculate total and average score of every course                  **************\n"); //计算每门课程的总分和平均分
	printf("**************          5.Calculate total and average score of every student                 **************\n"); //计算每个学生的总分和平均分
	printf("**************          6.Sort in descending order by total score of every student           **************\n"); //按每个学生的总分由高到低排出名次表
	printf("**************          7.Sort in ascending order by total score of every student            **************\n"); //按每个学生的总分由低到高排出名次表
	printf("**************          8.Sort in ascending order by number                                  **************\n"); //按学号由小到大排出成绩表
	printf("**************          9.Sort in dictionary order by name                                   **************\n"); //按姓名的字典顺序排出成绩表
	printf("**************         10.Search by number                                                   **************\n"); //按学号查询学生排名及其考试成绩
	printf("**************         11.Search by name                                                     **************\n"); //按姓名查询学生排名及其考试成绩
	printf("**************         12.Statistic analysis for every course                                **************\n"); //按优秀（90~100）、良好（80~89）、中等（70~79）
																															 //、及格（60~69）、不及格（0~59）5个类别，对每门
																															 //课程分别统计每个类别的人数以及所占的百分比，并
																															 //统计得分为100分的人数和所占的百分比；
	printf("**************         13.List reccord                                                       **************\n"); //输出每个学生的学号、姓名、各科考试成绩，以及每门课程的总分和平均分
	printf("**************         14.Write to a file                                                    **************\n"); //将每个学生的记录信息写入文件
	printf("**************         15.Read from a file                                                   **************\n"); //从文件中读出每个学生的记录信息并显示
	printf("**************          0.Exit                                                               **************\n"); //退出
	printf("***********************************************************************************************************\n");
	printf("***********************************************************************************************************\n");
	printf("***********************************************************************************************************\n");

}

struct link* AppendNode_data(struct link* head)                                  // head 为链表头指针 i为链表内结构体的个数
{
	int  m, j;
	int i;                                                              //i 为学号长度方便下面进行学号的检验
	int flag1 = 0;
	int flag2 = 0;
	char id_number1[id_number];
	char name1[name_max];
	char score1[course_num][10];                                        //设置输入的成绩最大为10位数，方便对成绩检查是否在0-100之内
																		//设置为字符串防止输入字母，增强健壮性
	struct link* p;
	struct link* p1 = head;
	struct link* p2 = head;
	printf("Input student number(请输入长度小于10的学号):");
	scanf("%s", id_number1);
	i = strlen(id_number1);
	for (j = 0; j < i; j++)
	{
		if (id_number1[j] > '9' || id_number1[j] < '0' )
		{
			printf("您输入的学号有误!\n");
			return AppendNode_data(head);
		}
	}
	while (p1 != NULL)
	{
		if (strcmp(p1->number, id_number1) == 0)
		{
			printf("您输入的学号重复！\n");
			return AppendNode_data(head);
		}
		p1 = p1->next;
	}
	printf("Input student name:(请输入长度小于10的姓名)");
	scanf("%s", name1);
	while (getchar() != '\n');
	while (p2 != NULL)
	{
		if (strcmp(p2->name, name1) == 0)
		{
			printf("您输入的姓名重复！\n");
			return AppendNode_data(head);
		}
		p2 = p2->next;
	}
	printf("Input the student score:(请按 MT EN PH 顺序输入考试成绩,每输入一门成绩后按回车输入下一科目成绩！)\n");
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
				printf("您的输入有误！（请输入在（0-100）的成绩）\n");
				return AppendNode_data(head);
			}
		}
		if (strlen(score1[i]) == 2)
		{
			if (score1[i][0] < '0' || score1[i][0] > '9' || score1[i][1] < '0' || score1[i][1] > '9')
			{
				printf("您的输入有误！（请输入在（0-100）的成绩）\n");
				return AppendNode_data(head);
			}
		}
		if (strlen(score1[i]) == 1)
		{
			if (score1[i][0] < '0' || score1[i][0] > '9')
			{
				printf("您的输入有误！（请输入在（0-100）的成绩）\n");
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

struct link* AppendNode(struct link* head)     //在原链表尾后添加一个节点
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

struct link* delete_one_node(struct link* head)            //删除某一个节点
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
	if (head == NULL)                               //head为空时
	{
		printf("当前数据为空，无法删除！\n");
		return head;
	}
	else
	{
		printf("请输入待删除的学生的学号或姓名：\n");
		printf("按姓名查找删除请输入1！\n");
		printf("按学号查找删除请输入2！\n");
		scanf("%d", &i);
		while (getchar() != '\n');
		switch (i)
		{
		case 1:                                                         //按姓名查找
			printf("请输入待删除学生的姓名：\n");
			gets(name1);
			while (strcmp(name1, p->name) != 0 && p->next != NULL)
			{
				pr = p;
				p = p->next;
			}
			if (strcmp(name1, p->name) == 0)
			{
				flag1 = 1;
				printf("已找到姓名为%s该学生,是否确认删除？（请输入‘y'或’Y‘确认删除）", name1);
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
					printf("您搜索的学生信息已被删除！\n");
					return head;
				}
				else
				{
					printf("该学生成绩未删除！");
					return head;
				}
			}

			if (flag1 == 0)
			{
				printf("当前未找到完全匹配的学生！是否进行模糊匹配（请输入'y'或’n')");
				scanf(" %c", &choice2);
				while (getchar() != '\n');
				if (choice2 == 'y' || choice2 == 'Y')
				{
					p = head;
					while (p != NULL)
					{
						if (kmp_search(p->name, name1) == 1)
						{

							printf("已找到姓名含有%s该学生,该学生姓名为%s,是否确认删除？（请输入‘y'或’Y‘确认删除）", name1, p->name);
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
								printf("您搜索的学生信息已被删除！\n");
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
				printf("当前未删除任一学生成绩！\n");
			}
			return head;
		case 2:                                                   //按学号查找
			printf("请输入待删除学生的学号：\n");
			gets(number1);
			while (strcmp(number1, p->number) != 0 && p->next != NULL)
			{
				pr = p;
				p = p->next;
			}
			if (strcmp(number1, p->number) == 0)
			{
				flag1 = 1;
				printf("已找到学号为%s该学生,是否确认删除？（请输入‘y'或’Y‘确认删除）", number1);
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
					printf("您搜索的学生信息已被删除！\n");
					return head;
				}
				else
				{
					printf("该学生成绩未删除！");
					return head;
				}
			}

			if (flag1 == 0)
			{
				printf("当前未找到完全匹配的学生！是否进行模糊匹配（请输入'y'或’n')");
				scanf(" %c", &choice2);
				while (getchar() != '\n');
				if (choice2 == 'y' || choice2 == 'Y')
				{
					p = head;
					while (p != NULL)
					{
						if (kmp_search(p->number, number1) == 1)
						{

							printf("已找到学号含有%s该学生,该学生学号为%s,是否确认删除？（请输入‘y'或’Y‘确认删除）", number1, p->number);
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
								printf("您搜索的学生信息已被删除！\n");
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
				printf("当前未删除任一学生成绩！\n");
			}
			return head;
		default:
			printf("您的输入有误\n");
			return head;
		}
	}

}

void prefix_table(char pattern[], int prefix[])            //KMP算法的移位前的前缀表
{
	int n = strlen(pattern);
	prefix[0] = 0;
	int len = 0;
	int i = 1;              //比较 从第二个字母开始  第一个字母一定为0
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

void move_prefix_table(int prefix[], int n)                  //移动后的前缀表
{
	int i;
	for (i = n - 1; i > 0; i--)
	{
		prefix[i] = prefix[i - 1];

	}
	prefix[0] = -1;
}

int kmp_search(char text[], char pattern[])                //kmp搜索
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

struct link* alter(struct link* head)                   //改变节点的数值
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
		printf("当前数据为空！！");
		return head;
	}
	else
	{
		printf("请输入您需要修改的学生的姓名或学号！\n");
		printf("按姓名修改请输入a！\n");
		printf("按学号修改请输入b！\n");
		scanf("%c", &a);
		while (getchar() != '\n');
		switch (a)
		{
		case 'a':
			printf("请输入修改成绩的学生姓名：");
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
				printf("待修改的学生的姓名是：%s\n", name);
				printf("您确定要修改吗？(确定请输入‘y')\n");
				scanf("%c", &choice);
				while (getchar() != '\n');
				while (choice == 'y' || choice == 'Y')
				{
					printf("待修改学生\n姓名:%s\n学号:%s\n", p->name, p->number);
					printf("当前成绩为：MT:%d EN:%d PH:%d\n", p->score[0], p->score[1], p->score[2]);
					printf("请您输入您要修改的值（总分和平均分会在修改三科成绩后自动修改）:\n");
					printf("修改MT请输入m\n");
					printf("修改EN请输入E\n");
					printf("修改PH请输入P\n");
					printf("输入其他内容将会返回上一级:（如需退出修改过程请输入其他键）");
					scanf("%c", &choice1);
					while (getchar() != '\n');
					if (choice1 == 'm' || choice1 == 'M')
					{
						printf("您当前在修改%s的 MT 分数\n", p->name);
						printf("请输入您要修改的分数：");
						scanf("%d", &mark);
						while (getchar() != '\n');
						p->score[0] = mark;
						p->score_all = p->score[0] + p->score[1] + p->score[2];
					}
					else if (choice1 == 'e' || choice1 == 'E')
					{
						printf("您当前在修改%s的 EN 分数\n", p->name);
						printf("请输入您要修改的分数：");
						scanf("%d", &mark);
						while (getchar() != '\n');
						p->score[1] = mark;
						p->score_all = p->score[0] + p->score[1] + p->score[2];
					}
					else if (choice1 == 'p' || choice1 == 'P')
					{
						printf("您当前在修改%s的 PH 分数\n", p->name);
						printf("请输入您要修改的分数：");
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

			if (flag == 0)                                  //输入与链表没有完全相同的人名
			{
				printf("当前未找到完全匹配的学生！是否进行模糊匹配（请输入'y'或’n')");
				scanf(" %c", &choice3);
				while (getchar() != '\n');
				if (choice3 == 'y' || choice3 == 'Y')
				{
					p = head;
					while (p != NULL)
					{
						if (kmp_search(p->name, name) == 1)
						{
							printf("您要找的是%s吗?\n", p->name);
							printf("正确，请输入1");
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
								printf("待修改学生\n姓名:%s\n学号:%s\n", p->name, p->number);
								printf("当前成绩为：MT:%d EN:%d PH:%d\n", p->score[0], p->score[1], p->score[2]);
								printf("请您输入您要修改的值（总分和平均分会在修改三科成绩后自动修改）:\n");
								printf("修改MT请输入m\n");
								printf("修改EN请输入E\n");
								printf("修改PH请输入P\n");
								printf("输入其他内容将会返回上一级:（如需退出修改过程请输入其他键）");
								scanf("%c", &choice4);
								while (getchar() != '\n');
								if (choice4 == 'm' || choice4 == 'M')
								{
									printf("您当前在修改%s的 MT 分数\n", p->name);
									printf("请输入您要修改的分数：");
									scanf("%d", &mark);
									while (getchar() != '\n');
									p->score[0] = mark;
								}
								else if (choice4 == 'e' || choice4 == 'E')
								{
									printf("您当前在修改%s的 EN 分数\n", p->name);
									printf("请输入您要修改的分数：");
									scanf("%d", &mark);
									while (getchar() != '\n');
									p->score[1] = mark;
								}
								else if (choice4 == 'p' || choice4 == 'P')
								{
									printf("您当前在修改%s的 PH 分数\n", p->name);
									printf("请输入您要修改的分数：");
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
				printf("未找到姓名和%s相关的学生", name);
				return head;
			}
			return head;
		case 'b':
			printf("请输入修改成绩的学生学号：");
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
				printf("待修改的学生的学号是：%s\n", number);
				printf("您确定要修改吗？(确定请输入‘y')\n");
				scanf("%c", &choice);
				while (getchar() != '\n');
				while (choice == 'y' || choice == 'Y')
				{
					printf("待修改学生\n姓名:%s\n学号:%s\n", p->name, p->number);
					printf("当前成绩为：MT:%d EN:%d PH:%d\n", p->score[0], p->score[1], p->score[2]);
					printf("请您输入您要修改的值（总分和平均分会在修改三科成绩后自动修改）:\n");
					printf("修改MT请输入m\n");
					printf("修改EN请输入E\n");
					printf("修改PH请输入P\n");
					printf("输入其他内容将会返回上一级:（如需退出修改过程请输入其他键）");
					scanf("%c", &choice1);
					while (getchar() != '\n');
					if (choice1 == 'm' || choice1 == 'M')
					{
						printf("您当前在修改%s的 MT 分数\n", p->name);
						printf("请输入您要修改的分数：");
						scanf("%d", &mark);
						while (getchar() != '\n');
						p->score[0] = mark;
						p->score_all = p->score[0] + p->score[1] + p->score[2];
					}
					else if (choice1 == 'e' || choice1 == 'E')
					{
						printf("您当前在修改%s的 EN 分数\n", p->name);
						printf("请输入您要修改的分数：");
						scanf("%d", &mark);
						while (getchar() != '\n');
						p->score[1] = mark;
						p->score_all = p->score[0] + p->score[1] + p->score[2];
					}
					else if (choice1 == 'p' || choice1 == 'P')
					{
						printf("您当前在修改%s的 PH 分数\n", p->name);
						printf("请输入您要修改的分数：");
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
				printf("当前未找到完全匹配的学生！是否进行模糊匹配（请输入'y'或’n')");
				scanf(" %c", &choice3);
				while (getchar() != '\n');
				if (choice3 == 'y' || choice3 == 'Y')
				{
					p = head;
					while (p != NULL)
					{
						if (kmp_search(p->number, number) == 1)
						{
							printf("您要找的是%s吗?\n", p->number);
							printf("正确，请输入1");
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
								printf("待修改学生\n姓名:%s\n学号:%s\n", p->name, p->number);
								printf("当前成绩为：MT:%d EN:%d PH:%d\n", p->score[0], p->score[1], p->score[2]);
								printf("请您输入您要修改的值（总分和平均分会在修改三科成绩后自动修改）:\n");
								printf("修改MT请输入m\n");
								printf("修改EN请输入E\n");
								printf("修改PH请输入P\n");
								printf("输入其他内容将会返回上一级:（如需退出修改过程请输入其他键）");
								scanf("%c", &choice4);
								while (getchar() != '\n');
								if (choice4 == 'm' || choice4 == 'M')
								{
									printf("您当前在修改%s的 MT 分数\n", p->name);
									printf("请输入您要修改的分数：");
									scanf("%d", &mark);
									while (getchar() != '\n');
									p->score[0] = mark;
								}
								else if (choice4 == 'e' || choice4 == 'E')
								{
									printf("您当前在修改%s的 EN 分数\n", p->name);
									printf("请输入您要修改的分数：");
									scanf("%d", &mark);
									while (getchar() != '\n');
									p->score[1] = mark;
								}
								else if (choice4 == 'p' || choice4 == 'P')
								{
									printf("您当前在修改%s的 PH 分数\n", p->name);
									printf("请输入您要修改的分数：");
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
				printf("未找到姓名和%s相关的学生", number);
				return head;
			}
			return head;

		default:
			printf("您的输入有误！\n");
			return head;

		}
	}
}

void delete_all_link(struct link* head)                 //释放创建的链表中所有节点占用的内存
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

void each_course(struct link* head)               //计算并输出每门课的评价分和总分 //head 为头指针,n为指针节数
{
	int i, k;
	int j = 0;
	struct link* p = head;
	int all_score[course_num];
	float aver_score[course_num];
	if (head == NULL)                             //判断数据是否为空
	{
		printf("当前学生数据为空！\n");
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
				all_score[k] += p->score[k];                         //计算每一科总分
			}
			p = p->next;
			j++;
		}
		for (i = 0; i < course_num; i++)
		{
			aver_score[i] = (float)all_score[i] / j;              //计算平均分
		}
		printf("            MT       EN      PH\n");
		printf("总分:");
		for (i = 0; i < course_num; i++)
		{
			printf("%9d ", all_score[i]);
		}
		printf("\n平均分:");
		for (i = 0; i < course_num; i++)
		{
			printf("%9.1f", aver_score[i]);
		}
	}
}

void score_average_all(struct link* head)                               //求平均成绩和总成绩
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

void Show_score_init(struct link* head)                                      //输出成绩（链表）
{
	int i = 1;
	struct link* p = head;

	if (head != NULL)
	{
		printf("  序号         学号         学生姓名    MT        EN        PH    \n");
		while (p != NULL)
		{
			printf("%4d    %14s%12s     %3d       %3d       %3d\n", i, p->number, p->name, p->score[0], p->score[1], p->score[2]);
			p = p->next;
			i++;
		}
	}
}

void Show_score(struct link* head)                                      //输出含平均分和总分的成绩的链表
{
	int i = 1;
	struct link* p = head;
	if (head == NULL)
	{
		printf("当前学生数据为空!!");
	}
	else
	{
		printf("   序号      学号           姓名       MT        EN        PH       总分     平均分\n");
		while (p != NULL)
		{
			printf("%5d%14s%12s%10d%10d%10d%10d       %.1f\n", i, p->number, p->name, p->score[0], p->score[1], p->score[2], p->score_all, p->score_average);
			p = p->next;
			i++;
		}
	}
}

struct link* Sortlink_ascending(struct link* head)                //成绩升序排列
{
	if (head == NULL)
	{
		printf("目前没有数据可以排序！\n");
		return head;
	}
	else
	{
		score_average_all(head);                                   //计算平均分和总分
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

struct link* Sortlink_descending(struct link* head)              //成绩降序排列
{
	if (head == NULL)
	{
		printf("目前没有数据可以排序！\n");
		return head;
	}
	else
	{
		score_average_all(head);                                   //计算平均分和总分
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

struct link* Sortlink_number_descending(struct link* head)              //学号降序排列
{
	if (head == NULL)
	{
		printf("目前没有数据可以排序！\n");
		return head;
	}
	else
	{
		score_average_all(head);                                   //计算平均分和总分
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
		printf("目前没有数据可以排序！\n");
		return head;
	}
	else
	{
		score_average_all(head);                                   //计算平均分和总分
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

void swapdata(struct link* p1, struct link* p2)    //使传到该节点的链表可以交换数据  方便排序
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

void Search_number(struct link* head)         //按照学号搜索
{
	int i = 0;
	int flag1 = 0;                           //标记是否被搜索到
	int flag2 = 0;
	char number[id_number];
	char choice1;
	char choice2;
	if (head == NULL)
	{
		printf("当前无数据可搜索！");
	}
	else
	{
		printf("请您输入要搜索的学生的学号：");
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
				printf("学生姓名：%s\n学生学号：%s\n排名：第%d名!\n", p->name, p->number, i);
				printf("MT成绩：%d\nEN成绩：%d\nPH成绩：%d\n总分：%d\n平均分：%.1f\n", p->score[0], p->score[1], p->score[2], p->score_all, p->score_average);
				flag1 = 1;
				break;
			}
			p = p->next;
		}

		if (flag1 == 0)                    //无完全匹配的学生
		{
			printf("当前无完全匹配的学生,是否进行模糊匹配?(继续请输入'y'或'Y')");
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
						printf("您要找的是学号为%s的学生吗？(请输入'y'或'n')", p->number);
						scanf("%c", &choice2);
						while (getchar() != '\n');
						if (choice2 == 'y' || choice2 == 'Y')
						{
							printf("学生姓名：%s\n学生学号：%s\n排名：第%d名!\n", p->name, p->number, i);
							printf("MT成绩：%d\nEN成绩：%d\nPH成绩：%d\n总分：%d\n平均分：%.1f\n", p->score[0], p->score[1], p->score[2], p->score_all, p->score_average);
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
			printf("未找到关于学号为%s的学生的信息！\n", number);
		}

	}
}

void Search_name(struct link* head)        //按照姓名搜索
{
	int i = 0;
	int flag1 = 0;
	int flag2 = 0;
	char name[name_max];
	char choice1;
	char choice2;

	if (head == NULL)
	{
		printf("当前无数据可搜索！");
	}
	else
	{
		printf("请您输入要搜索的学生的姓名：");
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
			if (strcmp(name, p->name) == 0)                               //字符串相同
			{
				printf("学生姓名：%s\n学生学号：%s\n排名：第%d名!\n", p->name, p->number, i);
				printf("MT成绩：%d\nEN成绩：%d\nPH成绩：%d\n总分：%d\n平均分：%.1f\n", p->score[0], p->score[1], p->score[2], p->score_all, p->score_average);
				flag1 = 1;
				break;
			}
			p = p->next;
		}

		if (flag1 == 0)                                                  //字符串不完全相同
		{
			printf("当前无完全匹配的学生,是否进行模糊匹配?(继续请输入'y'或'Y')");
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
						printf("您要找的是姓名为%s的学生吗？(请输入'y'或'n')", p->name);
						scanf("%c", &choice2);
						while (getchar() != '\n');
						if (choice2 == 'y' || choice2 == 'Y')
						{
							printf("学生姓名：%s\n学生学号：%s\n排名：第%d名!\n", p->name, p->number, i);
							printf("MT成绩：%d\nEN成绩：%d\nPH成绩：%d\n总分：%d\n平均分：%.1f\n", p->score[0], p->score[1], p->score[2], p->score_all, p->score_average);
							break;
						}
					}
					pr = p;
					p = p->next;
				}
			}
		}
		if (flag1 == 0 && flag2 == 0)                                 //均未被搜索到
		{
			printf("未找到关于姓名为%s学生的信息！\n", name);
		}
	}
}

void Statistic_link(struct link* head)  //分析链表中的数据
{
	int category[course_num][5];        //记录每个类别 每个课程对应的人数
	float category1[course_num][5];
	int i, n;
	int j = 0;
	struct link* p = head;
	float category2;
	if (head == NULL)
	{
		printf("当前数据为空！无法分析！");
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
			for (i = 0; i < course_num; i++)                         //记录不同等级
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

void list_link(struct link* head)               //列表显示数据
{
	int i = 1;
	struct link* p = head;
	if (head == NULL)
	{
		printf("当前学生数据为空!!");
	}
	else
	{
		score_average_all(head);
		printf("———————————————————————————————————————————————\n");
		printf("|  序号  |     学号     |  学号姓名  |    MT    |    EN    |    PH    |   总分   |   平均分   |\n");
		printf("———————————————————————————————————————————————\n");
		while (p != NULL)
		{
			printf("|%4d    |%14s|%12s|   %3d    |   %3d    |   %3d    |   %3d    |   %4.2f    |\n", i, p->number, p->name, p->score[0], p->score[1], p->score[2], p->score_all, p->score_average);
			printf("———————————————————————————————————————————————\n");
			p = p->next;
			i++;
		}
	}
}

void WritetoFile(struct link* head)              //写入文件
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
	printf("成功写入文件！\n");

}

struct link* ReadfromFile(struct link* head)     //从文件读取
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
		printf("成功从文件读取！\n");
	}
	return head;
}
