#include <selene.h>
#include <iostream>
using namespace std;
int main() {
	sel::State state;
	state.Load("helloworld.lua");
	string s = state["bar"][3];
	cout << s << endl;
	char a;
	cin >> a;
}