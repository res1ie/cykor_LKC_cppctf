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
	EC(field xx,field yy):is_O(false),x(xx),y(yy){} // it must tested that is element of curve when emplementing cryptosystem, but we wont test it since it is for CTF
	bool isLegal(){
		return is_O || y*y == x*x*x + a*x + b;
	}
	EC(const EC& o):is_O(o.is_O),x(o.x),y(o.y){}
	EC operator+(const EC&o) const{
		if(is_O)
			return o;
		if(o.is_O)
			return *this;
		field m;
		if(x==o.x){
			if(y==o.x){
				field x2=x*x;
				m=(x2+x2+x2+a)/(y+y);
			}
			else
				return EC();
		}
		else
			m = (o.y-y) / (o.x-x);
		field newx = m*m - x - o.x;
		field newy = y + (newx-x)*m;
		return EC(newx,-newy);
	}
	EC operator-() const{
		if(is_O)
			return EC();
		return EC(x,-y);
	}
	EC operator-(const EC& o) const{
		return *this+(-o);
	}
	template<typename int_t>
	EC operator*(int_t oo) const{
		EC a=*this,b;
		while(oo){
			if(oo&1)b=b+a;
			a=a+a;
			oo>>=1;
		}
		return b;
	}
};

template<class field,int code_num>
field EC<field,code_num>::a;
template<class field,int code_num>
field EC<field,code_num>::b;

int main(){
	typedef MF<int,7> mf;
	typedef EC<mf,1> ec;
	ec::a=0;
	ec::b=7;
	ec x,y;
	x=x+y;
	x=x-y;
	x=y*15;
}
