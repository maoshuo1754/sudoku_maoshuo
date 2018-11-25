#include<stdlib.h>
#include<iostream>
#include<string.h>
using namespace std;
int SUM;
int a[10][10];
int sum = 0;
int N;//代表输出的数独矩阵个数 
FILE* fp1, *fp2;
void Input(int a[][10]);
void Output(int a[][10]);
int check_num(int a[][10], int i, int j, int num);
void TraceBack(int n);

int main(int   argc, char*   argv[])
{
	
	errno_t err1 , err2;
	memset(a, 0, sizeof(a));

	if (strcmp(argv[1], "-c") == 0)
	{
		if (argc != 3)
		{
			cout << "命令输入错误，请输入想要的终局数" << endl;
			return 0;
		}
		else
		{
			for (int i = 0; i<int(strlen(argv[2])); i++)
			{
				if (argv[2][i]<'0' || argv[2][i]>'9')
				{
					cout << "命令输入错误，请输入想要的终局数" << endl;
					return 0;
				}
			}
		}
		err2 = fopen_s(&fp2, "sudoku.txt", "w");
		SUM = atoi(argv[2]);
		a[0][0] = (5 + 4) % 9 + 1;//学号后两位54 
		TraceBack(1);//
		Output(a);
		cout << "终局生成完毕" << endl;
		if (fp2 != 0)
		{
			fclose(fp2);
		}
	}
	else
		if (strcmp(argv[1], "-s") == 0)
		{
			if (argc != 3)
			{
				cout << "命令输入错误，请输入输出路径" << endl;
				return 0;
			}

			SUM = 1;
			err1 = fopen_s(&fp1, argv[2], "r");
			if (err1 != 0)
			{
				cout << "路径错误" << endl;
				return 0;
			}
			err2 = fopen_s(&fp2, "sudoku.txt", "w");
			Input(a);
			TraceBack(0);
			Output(a);
			cout << "解数独完成" << endl;
			if (fp1 != 0)
			{
				fclose(fp1);
			}
			if (fp2 != 0)
			{
				fclose(fp2);
			}
		}
		else
		{
			cout << "命令输入错误，只能是-c或-s" << endl;
			return 0;
		}

	system("PAUSE");
	return 0;
}

void Input(int a[][10])
{
	char temp;
	for (int i = 0; i < 9; i++)
		for (int j = 0; j < 9; j++)
		{
			temp = fgetc(fp1);
			if (temp == ' ' || temp == '\n')
			{
				temp = fgetc(fp1);
			}
			a[i][j] = temp - '0';
			if (check_num(a, i, j, a[i][j]) == 0)
			{
				cout << "9*9初始输入有误" << endl;
				exit(0);
			}
		}
}
void Output(int a[][10])
{

	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			fputc(a[i][j]+'0', fp2);
			fputc(' ', fp2);
		}
		fputc(a[i][8] + '0', fp2);
		fputc('\n', fp2);
	}
	fputc('\n', fp2);

}

int check_num(int a[][10], int i, int j, int num)
{
	if (num == 0)
	{
		return 1;
	}

	for (int k = 0; k < 9; k++) //本行 
	{
		if (a[i][k] == num&&k != j&&a[i][k] != 0)
			return 0;
	}

	for (int k = 0; k < 9; k++) //本列 
	{
		if (a[k][j] == num&&k != i&&a[k][j] != 0)
			return 0;
	}

	for (int k = i / 3 * 3; k < i / 3 * 3 + 3; k++)//九宫格 
		for (int l = j / 3 * 3; l < j / 3 * 3 + 3; l++)
		{
			if (a[k][l] == num && !(k == i&&l == j))
				return 0;
		}

	return 1;
}

void TraceBack(int n)
{
	if (sum > SUM - 1)
	{
		exit(0);
	}

	if (n > 80)
	{
		sum++;
		Output(a);
		return;
	}

	if (a[n / 9][n % 9] != 0)
	{
		TraceBack(n + 1);
	}
	else
	{
		for (int i = 1; i <= 9; i++)
		{
			int temp = a[n / 9][n % 9];
			if (check_num(a, n / 9, n % 9, i))
			{
				a[n / 9][n % 9] = i;
				TraceBack(n + 1);
			}
			a[n / 9][n % 9] = temp;
		}
	}
}

