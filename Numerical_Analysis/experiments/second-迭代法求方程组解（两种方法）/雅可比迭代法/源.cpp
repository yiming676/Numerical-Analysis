#include<iostream>
#include<iomanip>
#include<cmath>

using namespace std;

int main()
{
	double  x[3] = {0,0,0}, y[3] = {0,0,0};
	double C[3][3] = { 0 , -0.4 , -0.2 , 0.25 , 0 , -0.5 , -0.2 , 0.3 , 0 };
	double f[3] = { -2.4 , 5 , 0.3 };
	for (int ii = 0; ii < 3; ii++)
	{
		for (int jj = 0; jj < 3; jj++)
		{
			y[ii] += C[ii][jj] * x[jj];
		}
		y[ii] += f[ii];
		cout << "第1轮迭代：y[" << ii << "] = " << setw(11) <<setfill(' ') << fixed << setprecision(6) << y[ii] << endl;
	}
	cout << endl;

	int time = 2;
	while ((abs(y[0] - x[0]) >= 0.00001) && (abs(y[1] - x[1]) >= 0.00001) && (abs(y[2] - x[2]) >= 0.00001))
	{
		x[0] =y[0], x[1] =y[1], x[2] = y[2];
		y[0] = y[1] = y[2] = 0;
		for (int ii = 0; ii < 3; ii++)
		{
			for (int jj = 0; jj < 3; jj++)
			{
				y[ii] += C[ii][jj] * x[jj];
			}
			y[ii] += f[ii];
			cout << "第"<<time<<"轮迭代：y[" << ii << "] = " << setw(11) << setfill(' ') << fixed << setprecision(6) << y[ii] << endl;
		}
		time++;
		cout << endl;
	}

	return 0;
}