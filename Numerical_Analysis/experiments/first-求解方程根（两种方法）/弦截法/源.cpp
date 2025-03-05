#include<iostream>
#include<cmath>

using namespace std;

double f(double x)
{
	return x * x * x + 2 * x * x + 3 * x - 4;
}

double fai(double x0, double x1)
{
	return x1 - (f(x1) * (x1 - x0)) / (f(x1) - f(x0));
}

int main()
{
	double x[100] = {};
	double accuracy = 0;
	cout << "请输入X0，X1以及精度" << endl;
	cin >> x[0] >>x[1]>> accuracy;
	x[2] = fai(x[0], x[1]);
	cout << "x[0] = " << x[0] << endl << "x[1] = " << x[1] << endl;

	int i = 2;
	while (abs(x[i] - x[i - 1]) > accuracy)
	{
		cout <<"x["<<i<<"] = " <<x[i]<<endl;
		i++;
		x[i] = fai(x[i - 2], x[i - 1]);
	}
	cout << "x[" << i << "] = " << x[i]<<endl;
	cout << "故根为：" <<x[i] << endl;

	return 0;
}