#include "bigInt.h"
#include "p_int.h"
#include <iostream>
using namespace std;

int main() {
	BigInt i(-59), j(-58);
	cout << boolalpha << (i < j) << endl;
	return 0;
}
