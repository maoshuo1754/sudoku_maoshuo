#include<stdlib.h>
#include<iostream>
#include<string.h>
using namespace std;
int SUM;
int a[10][10];
int sum = 0;
int N;//代表输出的数独矩阵个数 
void Input(int a[][10]);
void Output(int a[][10]);
int check_num(int a[][10], int i, int j, int num);
void TraceBack(int n);

int main(int   argc, char*   argv[])
{

	memset(a, 0, sizeof(a));

	if (strcmp(argv[1], "-c") == 0)
	{
		if (argc != 3)
		{
			cout << "命令输入错误" << endl;
			return 0;
		}
		else
		{
			for (int i = 0; i<int(strlen(argv[2])); i++)
			{
				if (argv[2][i]<'0' || argv[2][i]>'9')
				{
					cout << "命令输入错误" << endl;
					return 0;
				}
			}
		}
		cout << "数独生成成功" << endl;
		freopen("sudoku.txt", "w", stdout);
		SUM = atoi(argv[2]);
		a[0][0] = (5 + 4) % 9 + 1;//学号后两位54 
		TraceBack(1);//

		Output(a);
	}
	else
		if (strcmp(argv[1], "-s") == 0)
		{
			SUM = 1;
			cout << "数独解决成功" << endl;
			freopen(argv[2], "r", stdin);
			freopen("sudoku.txt", "w", stdout);
			Input(a);
			TraceBack(0);
			Output(a);
		}
		else
		{
			cout << "命令输入错误" << endl;
		}

	system("PAUSE");

}

void Input(int a[][10])
{
	for (int i = 0; i<9; i++)
		for (int j = 0; j<9; j++)
		{
			cin >> a[i][j];
			if (check_num(a, i, j, a[i][j]) == 0)
			{
				cout << "9*9初始输入有误" << endl;
				exit(0);
			}
		}
}
void Output(int a[][10])
{

	for (int i = 0; i<9; i++)
	{
		for (int j = 0; j<8; j++)
		{
			cout << a[i][j] << " ";
		}
		cout << a[i][8] << endl;
	}
	cout << endl;

}

int check_num(int a[][10], int i, int j, int num)
{
	if (num == 0)
	{
		return 1;
	}

	for (int k = 0; k<9; k++) //本行 
	{
		if (a[i][k] == num&&k != j&&a[i][k] != 0)
			return 0;
	}

	for (int k = 0; k<9; k++) //本列 
	{
		if (a[k][j] == num&&k != i&&a[k][j] != 0)
			return 0;
	}

	for (int k = i / 3 * 3; k<i / 3 * 3 + 3; k++)//九宫格 
		for (int l = j / 3 * 3; l < j / 3 * 3 + 3; l++)
		{
			if (a[k][l] == num && !(k == i&&l == j))
				return 0;
		}

	return 1;
}

void TraceBack(int n)
{
	if (sum>SUM - 1)
	{
		exit(0);
	}

	if (n>80)
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











