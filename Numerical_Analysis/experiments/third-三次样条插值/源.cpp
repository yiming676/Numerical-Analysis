#define _CRT_SECURE_NO_WARNINGS  1
#pragma warning(disable:6031)
#include<iostream>
#include<stdio.h>
#include<malloc.h>

using namespace std;

void Gaussian(double B[20][21], int len,double answer[20])     //高斯消去法，下三角矩阵的增广矩阵  行len 列len+1
{
	double tmp = 0;
	for (int ii = 0; ii <= len; ii++)  B[0][ii] /= B[0][0];         
	for (int ii = 1; ii <= len - 1; ii++)
		for (int jj = ii; jj <= len; jj++)
		{
			B[ii][jj] /= B[ii][ii - 1];
			B[ii][ii - 1] = 1;
		}
			

	for (int kk = 1; kk <= len - 1; kk++)
	{	
		for (int jj = kk - 1; jj <= len; jj++)
			B[kk][jj] -= B[kk - 1][jj];

		tmp = B[kk][kk];
		for (int ii = kk; ii <= len; ii++)
			B[kk][ii] /= tmp;
	}

	answer[len - 1] = B[len - 1][len];
	for (int ii = len -2; ii >= 0; ii--)
		answer[ii] = B[ii][len] - B[ii][ii + 1] * answer[ii + 1];
}


int main()
{
	int number = 0;
	cout << "请输入离散点个数：";
	cin >> number;
	cout << endl;
	
	double x[20] = { 0 }, y[20] = { 0 }, h[20] = { 0 }, namuda[20] = { 0 }, miu[20] = { 0 }, d[20] = { 0 }, m[20] = { 0 };
	
	double X[20][20]={0};//用于存储众多S(x)中各项的系数；

	memset(x, 0, sizeof(double) * number);
	memset(y, 0, sizeof(double) * number);
	memset(h, 0, sizeof(double) * number);
	memset(namuda, 0, sizeof(double) * number);
	memset(miu, 0, sizeof(double) * number);
	memset(d, 0, sizeof(double) * number);

	double a = 0, b = 0;                       //一阶导数或二阶导数载体

	double A[20][21] = { 0 };
	memset(A, 0, sizeof(A));
	for (int ii = 0; ii < 10; ii++) A[ii][ii] = 2;

	for (int ii = 0; ii < number; ii++)
	{
		cout << "第" << ii+1 << "个点的坐标 ( 以空格分开x，y坐标 )：";
		cin >> x[ii]>>y[ii];
		cout << endl;
	}

	for (int ii = 0; ii <= number-1 ; ii++)  h[ii] = x[ii + 1] - x[ii];

	for (int ii = 1; ii <= number-1 ; ii++)
	{
		namuda[ii] = h[ii] / (h[ii] + h[ii - 1]);
		miu[ii] = 1 - namuda[ii];
		d[ii] = 3 * (((miu[ii] * (y[ii + 1] - y[ii])) / h[ii]) + ((namuda[ii] * (y[ii] - y[ii - 1])) / h[ii - 1]));
	}
	
	int  boundary_condition=0;                                 //选择边界条件

	while (boundary_condition !=2 )
	{
		cout << "请输入初始边界条件 ( 0：已知首尾点一阶导数；1：已知首尾点二阶导数 ；2：退出)：";
		cin >> boundary_condition;
		cout << endl;

		if (boundary_condition == 0)                           //已知 f0' 和 fn'
		{
			cout << "请输入f0' 和 fn'的值（以空格分开）：";
			cin >> a >> b;
			cout << endl;
			d[1] -= namuda[1] * a;
			d[number - 1] -= miu[number - 1] * b;

			for (int ii = 1; ii <= number - 2; ii++)            //增广矩阵
			{
				A[ii - 1][ii] = miu[ii];
				A[ii][ii - 1] = namuda[ii + 1];
			}
			for (int ii = 0; ii <= number - 1; ii++)   A[ii][number - 1] = d[ii + 1];
			Gaussian(A, number - 2, m);

			double t1 = 0, t2 = 0;
			for (int ii = 0; ii < number - 1; ii++)               //三次
			{
				t1 = m[ii] / (h[ii] * h[ii]) + (2 * y[ii]) / (h[ii] * h[ii] * h[ii]);
				t2 = m[ii + 1] / (h[ii] * h[ii]) - (2 * y[ii + 1]) / (h[ii] * h[ii] * h[ii]);
				X[ii][3] = t1 + t2;
				X[ii][2] = -t1 * (x[ii] + 2 * x[ii + 1]) - t2 * (x[ii + 1] + x[ii]);
				X[ii][1] = t1 * (2 * x[ii + 1] * x[ii] + x[ii + 1] * x[ii + 1]) + t2 * (2 * x[ii] * x[ii + 1] + x[ii] * x[ii]);
				X[ii][0] = (y[ii] + y[ii + 1]) / (h[ii] * h[ii]) - t1 * x[ii] * x[ii + 1] * x[ii + 1] - t2 * x[ii + 1] * x[ii] * x[ii];
				cout << "x∈[ " << x[ii] << " , " << x[ii + 1] << " ]  ,  S(x) = ";
				if (X[ii][3] == 1)  cout << "x^3 + ";
				if (X[ii][3] != 1 && X[ii][3] != 0)  cout << X[ii][3] << " x^3 + ";
				if (X[ii][2] == 1)  cout << "x^2 + ";
				if (X[ii][2] != 1 && X[ii][2] != 0)  cout << X[ii][2] << " x^2 + ";
				if (X[ii][1] == 1)  cout << "x + ";
				if (X[ii][1] != 1 && X[ii][1] != 0)  cout << X[ii][1] << " x + ";
				if (X[ii][0] != 0)  cout << X[ii][0];
				cout << endl;
			}
			memset(X, 0, sizeof(X));
		}

		else if (boundary_condition == 1)                      //已知 f0" 和 fn"
		{
			cout << "请输入 f0'' 和 fn'' 的值（以空格分开）：";
			cin >> a >> b;
			cout << endl;
			d[0] = 3 * ((y[1] - y[0]) / h[0]) - (h[0] * a) / 2;
			d[number] = 3 * ((y[number-1] - y[number - 2]) / h[number - 1]) - (h[number - 1] * b) / 2;

			for (int ii = 2; ii <= number; ii++)                     //增广矩阵
			{ 
				A[ii - 1][ii] = miu[ii];
				A[ii][ii - 1] = namuda[ii + 1];
			}
			A[0][1] = 1; A[1][0] = namuda[1];
			
			for (int ii = 0; ii < number; ii++)
				A[ii][number] = d[ii];
			Gaussian(A, number , m);

			double t1 = 0, t2 = 0;
			for (int ii = 0; ii < number - 1; ii++)                  //三次
			{
				t1 = m[ii+1] / (h[ii] * h[ii]) + (2 * y[ii]) / (h[ii] * h[ii] * h[ii]);
				t2 = m[ii + 2] / (h[ii] * h[ii]) - (2 * y[ii + 1]) / (h[ii] * h[ii] * h[ii]);
				X[ii][3] = t1 + t2;
				X[ii][2] = -t1 * (x[ii] + 2 * x[ii + 1]) - t2 * (x[ii + 1] + x[ii]);
				X[ii][1] = t1 * (2 * x[ii + 1] * x[ii] + x[ii + 1] * x[ii + 1]) + t2 * (2 * x[ii] * x[ii + 1] + x[ii] * x[ii]);
				X[ii][0] = (y[ii] + y[ii + 1]) / (h[ii] * h[ii]) - t1 * x[ii] * x[ii + 1] * x[ii + 1] - t2 * x[ii + 1] * x[ii] * x[ii];
				cout << "x∈[ " << x[ii] << " , " << x[ii + 1] << " ]  ,  S(x) = ";
				if (X[ii][3] == 1)  cout << "x^3 + ";
				if (X[ii][3] != 1 && X[ii][3] != 0)  cout << X[ii][3] << " x^3 + ";
				if (X[ii][2] == 1)  cout << "x^2 + ";
				if (X[ii][2] != 1 && X[ii][2] != 0)  cout << X[ii][2] << " x^2 + ";
				if (X[ii][1] == 1)  cout << "x + ";
				if (X[ii][1] != 1 && X[ii][1] != 0)  cout << X[ii][1] << " x + ";
				if (X[ii][0] != 0)  cout <<X[ii][0] ;				
				cout << endl;
			}
			memset(X, 0, sizeof(X));
		}
	}
	return 0;
}