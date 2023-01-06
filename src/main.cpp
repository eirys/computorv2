#include<string>
#include<iostream>

int main() {
	using namespace std;

	string s = "2.26 ";
	size_t i;

	long double d = stold(s, &i);

	cout << d << endl;
	cout << i << endl;
}