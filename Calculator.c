//这是一个很简单的计算器小程序



#include <stdio.h>

int main()
{
    setbuf(stdout,NULL);
    char opera;
    double num1, num2;
    int continueCalc = 1;

    while (continueCalc)//这个就是创建一个可以循环使用的
    {

        printf("请输入运算符 (+, -, *, /) 或输入 'q' 退出： ");
        scanf(" %c", &opera); // 注意前面的空格用于跳过任何前导空白字符

        if (opera== 'q' || opera== 'Q')
        {
            printf("退出计算器。\n");
            break; // 退出循环
        }

        // 提示用户输入两个操作数
        printf("请输入两个数字： ");
        if (scanf_s("%lf %lf", &num1, &num2) != 2)
          //这里也是把scanf混合一起来写了，
          //输入成功一个返回一，那么输入两个成功了就是返回二了
        {
            printf("输入无效，请输入两个数字。\n");
            // 清除输入缓冲区
            while (getchar() != '\n')
                ;
            continue; // 重新开始循环
        }

        // 执行计算
        switch (opera)
        {
        case '+':
            printf("%.2lf + %.2lf = %.2lf\n", num1, num2, num1 + num2);
            break;
        case '-':
            printf("%.2lf - %.2lf = %.2lf\n", num1, num2, num1 - num2);
            break;
        case '*':
            printf("%.2lf * %.2lf = %.2lf\n", num1, num2, num1 * num2);
            break;
        case '/':
            if (num2 == 0)
            {
                printf("错误：除数不能为零。\n");
            }
            else
            {
                printf("%.2lf / %.2lf = %.2lf\n", num1, num2, num1 / num2);
            }
            break;
        default:
            printf("未知的运算符。\n");
        }

        // 询问用户是否继续
        printf("是否继续计算？(1: 是, 0: 否)： ");
        if (scanf_s("%d", &continueCalc) != 1 || (continueCalc != 0 && continueCalc != 1))
        {
            printf("输入无效，默认退出。\n");
            break;
        }
    }

    printf("感谢使用计算器！\n");

    return 0;
}
