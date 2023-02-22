#include "GFv2.cpp"

template<class field,int code_num> 
class EC{
public:
	static field a;
	static field b; // y^2 = x^3 + ax + b
	bool is_O;
	field x;
	field y;
	EC():is_O(true),x(),y(){}
	EC(field xx,field yy):is_O(false),x(xx),y(yy){}
	bool isLegal(){
		return is_O || y*y == x*x*x + a*x + b;
	}
	EC(const EC& o){
		return is_o
	}
};

int main(){
	typedef MF<int,7> mf;
	typedef EC<mf,1> ec;
	ec::a=0;
	ec::b=7; 
}
