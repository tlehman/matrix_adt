#include <iostream>
#include "matrix.h"
using namespace std;

int main()
{
	char filename1[] = "a.mtx";
	matrix a(2,2);
	a.identity();
	a.show();
	cout << "det(a) = " << a.det() << endl;

	return 0;
}

