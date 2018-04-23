#include "bigInt.h"
#include <iostream>
using namespace std;

int main() {
	BigInt i(-123);
	BigInt j(330);
	BigInt k(i);
	cout << i << endl;
	return 0;
}
