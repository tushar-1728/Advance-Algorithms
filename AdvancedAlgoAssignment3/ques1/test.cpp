#include<iostream>
#include <string.h>
#include<list>
using namespace std;

int main(){
	string txt = "apple\0";
	string sub = txt.substr(2);
	cout << sub << endl;
}