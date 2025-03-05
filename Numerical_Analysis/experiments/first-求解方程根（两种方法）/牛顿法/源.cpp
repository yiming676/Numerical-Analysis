#include<iostream>
#include<cmath>

using namespace std;

int main()
{
	double x[50] = {};
	double accuracy;
	cin >> x[0]>>accuracy;

	x[1] =(2* x[0] * x[0] * x[0] + 2 * x[0] * x[0] + 4)/(3 * x[0] * x[0] + 4 * x[0]+3);
	
	int i = 0;
	while (abs(x[i + 1] - x[i]) > accuracy)
	{
		i++;
		cout <<"x["<<i<<"] = "<< x[i] << endl;
		x[i+1]= (2 * x[i] * x[i] * x[i] + 2 * x[i] * x[i] + 4) / (3 * x[i] * x[i] + 4 * x[i] + 3);
	}
	cout << "x[" << i+1 << "] = "<< x[i + 1]<<endl;
	cout << "¸ùÎª£º " << x[i + 1];

	return 0;
}
	
