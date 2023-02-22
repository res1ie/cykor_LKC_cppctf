#include "GFv2.cpp"
#include "matrix.cpp"
#include <iostream>
int main(){
	GF<8,1>::base=0x11b;
	matrix<2,GF<8,1>> a(2);
	a=a*a*a;
	a.prn();
}
