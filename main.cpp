#include "calc_exp.h"
#include <iostream>
using namespace std;
#include <stdio.h>
int main() {

	//freopen("35.in","r",stdin);
	//freopen("111.out","w",stdout);
    try {
		for (COmplex *res;;) {
		//COmplex *res;
			res = calc_exp();
			res -> print();
		}
	}
	catch(int){cerr<<"Wrong";}
	//system("pause");
    return 0;
}
