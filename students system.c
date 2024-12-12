#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_STUDENTS 100
#define MAX_NAME_LENGTH 50
#define FAIL_SCORE 60

// 定义学生结构体
typedef struct {
  char name[MAX_NAME_LENGTH];
  int score;
} Student;

// 函数声明
int enterStudentsInformation(Student students[]);
void displayFailedStudents(const Student students[], int count);
void displayAllStudents(const Student students[], int count);
void modifyStudentInformation(Student students[], int count);
void displayMenu();
void clearInputBuffer();

int main()
{
  int choice;
  Student students[MAX_STUDENTS];
  int count = 0;

  displayMenu();

  do
  {
    printf("\n请选择你的选项：");
    if (scanf("%d", &choice) != 1)
    {
      printf("输入无效，请输入一个整数。\n");
      clearInputBuffer();
      continue;
    }
    clearInputBuffer();

    switch (choice)
    {
    case 1:
      count = enterStudentsInformation(students);
      break;
    case 2:
      displayFailedStudents(students, count);
      break;
    case 3:
      displayAllStudents(students, count);
      break;
    case 4:
      modifyStudentInformation(students, count);
      break;
    case 5:
#ifdef _WIN32
      system("cls");
#else
      system("clear");
#endif
      displayMenu();
      break;
    case 0:
      printf("退出程序\n");
      break;
    default:
      printf("无效的选择，请重新输入。\n");
      break;
    }

  } while (choice != 0);

  return 0;
}

// 显示菜单
void displayMenu()
{
  printf("****************************************\n");
  printf("************** 学生管理系统 **************\n");
  printf("********** 0、退出                ********\n");
  printf("********** 1、录入学生成绩        ********\n");
  printf("********** 2、查看所有挂科学生信息 ********\n");
  printf("********** 3、查看所有学生信息    ********\n");
  printf("********** 4、修改学生信息        ********\n");
  printf("********** 5、清屏                ********\n");
  printf("****************************************\n");
}

// 清理输入缓冲区
void clearInputBuffer()
{
  int c;
  while ((c = getchar()) != '\n' && c != EOF);
}

// 录入学生信息
int enterStudentsInformation(Student students[])
{
  int count;
  printf("请输入学生数量（最多 %d 名）：", MAX_STUDENTS);
  if (scanf("%d", &count) != 1 || count < 1 || count > MAX_STUDENTS)
  {
    printf("输入无效，请输入一个1到%d之间的整数。\n", MAX_STUDENTS);
    clearInputBuffer();
    return 0;
  }
  clearInputBuffer();

  for (int i = 0; i < count; i++)
  {
    printf("输入第 %d 个学生的姓名：", i + 1);
    if (fgets(students[i].name, sizeof(students[i].name), stdin) != NULL)
    {
      // 去除换行符
      size_t len = strlen(students[i].name);
      if (len > 0 && students[i].name[len - 1] == '\n')
      {
        students[i].name[len - 1] = '\0';
      }
    }
    else
    {
      printf("读取姓名失败。\n");
      students[i].name[0] = '\0';
    }

    printf("输入 %s 的成绩：", students[i].name);
    if (scanf("%d", &students[i].score) != 1)
    {
      printf("输入无效，默认成绩为0。\n");
      students[i].score = 0;
    }
    clearInputBuffer();
  }

  printf("成功录入 %d 名学生的信息。\n", count);
  return count;
}

// 显示挂科学生信息
void displayFailedStudents(const Student students[], int count)
{
  if (count == 0)
  {
    printf("当前没有学生信息。\n");
    return;
  }

  int found = 0;
  printf("挂科学生名单（成绩低于 %d 分）：\n", FAIL_SCORE);
  for (int i = 0; i < count; i++)
  {
    if (students[i].score < FAIL_SCORE)
    {
      printf("姓名：%s, 成绩：%d\n", students[i].name, students[i].score);
      found = 1;
    }
  }

  if (!found)
  {
    printf("没有挂科的学生。\n");
  }
}

// 显示所有学生信息
void displayAllStudents(const Student students[], int count)
{
  if (count == 0)
  {
    printf("当前没有学生信息。\n");
    return;
  }

  printf("所有学生的信息如下：\n");
  for (int i = 0; i < count; i++)
  {
    printf("第 %d 个学生 - 姓名：%s, 成绩：%d\n", i + 1, students[i].name, students[i].score);
  }
}

// 修改学生信息
void modifyStudentInformation(Student students[], int count)
{
  if (count == 0)
  {
    printf("当前没有学生信息可修改。\n");
    return;
  }

  int index;
  printf("请输入要修改的学生编号（1 到 %d）：", count);
  if (scanf("%d", &index) != 1 || index < 1 || index > count)
  {
    printf("输入无效，请输入一个1到 %d 之间的整数。\n", count);
    clearInputBuffer();
    return;
  }
  clearInputBuffer();

  printf("当前第 %d 个学生的信息：\n", index);
  printf("姓名：%s, 成绩：%d\n", students[index - 1].name, students[index - 1].score);

  printf("输入新的姓名（留空则不修改）：");
  char newName[MAX_NAME_LENGTH];
  if (fgets(newName, sizeof(newName), stdin) != NULL)
  {
    // 去除换行符
    size_t len = strlen(newName);
    if (len > 0 && newName[len - 1] == '\n')
    {
      newName[len - 1] = '\0';
    }
    if (strlen(newName) > 0)
    {
      strncpy(students[index - 1].name, newName, MAX_NAME_LENGTH - 1);
      students[index - 1].name[MAX_NAME_LENGTH - 1] = '\0'; // 确保以 null 结尾
    }
  }

  printf("输入新的成绩（-1 表示不修改）：");
  int newScore;
  if (scanf("%d", &newScore) == 1)
  {
    if (newScore >= 0)
    {
      students[index - 1].score = newScore;
    }
  }
  else
  {
    printf("输入无效，成绩不修改。\n");
  }
  clearInputBuffer();

  printf("更新后的第 %d 个学生的信息：\n", index);
  printf("姓名：%s, 成绩：%d\n", students[index - 1].name, students[index - 1].score);
}
