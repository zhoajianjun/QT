#include <iostream>

using namespace std;

#include "MyString.h"

int main(){
	CMyString test1("babc");
	CMyString test2("abababcdefb");
	cout << test2.Find(test1) << endl;
	cout << test2(2, 3) << endl;

	if (test1 < test2){
		cout << test1 << "<" << test2 << endl;
	}
	else{
		if (test1 == test2){
			cout << test1 << "==" << test2 << endl;
		}
		else{
			if (test1 > test2){
				cout << test1 << ">" << test2 << endl;
			}
		}
	}

	int length = test2.Length();
	for (int i = 0; i < length; i++){
		cout << test2[i];
	}
	cout << endl;

	test1 += test2;
	cout << test1 << endl;

	test1 = test2;
	cout << test1 << endl;

	cin.get();
	return 0;
}
