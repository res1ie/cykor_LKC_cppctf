#include <iostream>
using std::cout;
using std::endl;
#include <bitset>
#include <cassert>
#include <algorithm>
#include <vector>
#include <array>
using std::array;
using std::vector;
using std::bitset;
/*
modular field, partialy works when p is not prime
*/
template<class int_t,int_t p> // p may be nonprime, but...
class MF{ // modular arithmetic
	int_t x;
public:
	MF(int_t a=0):x(a%p){}
	MF(const MF& o):x(o.x){}
	MF& operator=(const MF& o){
		x=o.x;
		return *this;
	}
	MF operator+(const MF o) const{
		return MF(x+o.x);
	}
	MF operator-(const MF o) const{
		return MF(p+x-o.x);
	}
	MF operator*(const MF o) const{
		return MF(x*o.x);
	}
	template<class int2_t>
	MF operator^(int2_t o) const{
		MF x=*this,y(1);
		while(o){
			if(o&1)y=y*x;
			x=x*x;
			o>>=1;
		}
		return y;
	}
	MF inv() const{
		int_t a=x,b=p; 
		int_t c=1,d=0;
		while(a!=0){
			d=d-(b/a)*c;
			b%=a;
			std::swap(a,b);
			std::swap(c,d);
		}
		return MF((d%p+p)%p);
	}
	MF operator/(const MF o) const{
		return MF(*this*o.inv());
	}
};
/*
general GF , looking for some good naming 
*/
template<class int_t,int_t p,int n> // here p need to be prime
class GGF:public array<MF<int_t,p>,n+1>{
	const array<MF<int_t,p>,n+1>& base;
public:
	GGF(const array<MF<int_t,p>,n+1>& m,array<MF<int_t,p>,n+1> x=array<MF<int_t,p>,n+1>()):array<MF<int_t,p>,n+1>(x),base(m){}
	GGF(const GGF& o):array<MF<int_t,p>,n+1>(o),base(o.base){}
	GGF& operator=(const GGF& x){
		*(array<MF<int_t,p>,n+1>*)this=x;
		return *this;
	} 
	GGF operator+(GGF o) const{
		assert(&base==&o.base);
		for(int i=0;i<n;i++)
			o[i]=(o[i]+(*this)[i]);
		return o;
	}
	GGF operator*(GGF o) const{
		assert(&base==&o.base);
		array<MF<int_t,p>,n+1> tmp = *(array<MF<int_t,p>,n+1>*)this;
		array<MF<int_t,p>,n+1> res;
		for(int i=0;i<n;i++){
			for(int j=0;j<n;j++)
				res[j]=res[j]+tmp[j]*o[i];
			//tmp <<= 1;
			memmove(&tmp[1],&tmp[0],n*sizeof(MF<int_t,p>));
			tmp[0]=0;
			MF<int_t,p> d=tmp[n]/base[n];
			for(int i=0;i<=n;i++)
				tmp[i]=tmp[i]-base[i]*d;
		}
		return GGF(base,res);
	}
	GGF operator^(int_t o) const{
		GGF x=*this,y(base);y[0]=1;
		while(o){
			if(o&1)y=y*x;
			x=x*x;
			o>>=1;
		}
		return y;
	}
	GGF inv() const{
		int_t k=1,o=p; //! there need to calc p^n, but there need to be integer type with enough space first ; so this should be fixed
		int m=n;
		while(m){
			if(m&1)k*=o;
			o=o*o;
			m>>=1;
		}
		return *this^(k-2);
	}
	GGF operator/( GGF o) const{
		assert(&base==&o.base);
		return *this*o.inv();
	}
};
/*
GF(2^n) 
*/
template<int n>
class GF:public bitset<n+1>{
	const bitset<n+1>& base;
public:
	GF(const bitset<n+1>& m,bitset<n+1> x=0):bitset<n+1>(x),base(m){}
	GF(const GF& o):bitset<n+1>(o),base(o.base){}
	GF& operator=(const GF& x){
		*(bitset<n+1>*)this=x;
		return *this;
	}
	GF operator+(const GF o) const{
		assert(&base==&o.base);
		return GF(base,*(bitset<n+1>*)this^o);
	}
	GF operator*(const GF o) const{
		assert(&base==&o.base);
		bitset<n+1> tmp = *(bitset<n+1>*)this;
		bitset<n+1> res;
		for(int i=0;i<n;i++){
			if(o.test(i))
				res^=tmp;
			tmp <<= 1;
			if(tmp.test(n))
				tmp^=base;
		}
		return GF(base,res);
	}
	template<typename int_t>
	GF operator^(int_t o) const{
		GF x=*this,y(base,1);
		while(o){
			if(o&1)y=y*x;
			x=x*x;
			o>>=1;
		}
		return y;
	}
	GF inv() const{
		return *this^((1<<n)-2);
	}
	GF operator/( GF o) const{
		assert(&base==&o.base);
		return *this*o.inv();
	}
};
template<class int_t,int_t p,int n>
class GGFgen{
	array<MF<int_t,p>,n+1> base;
public:
	GGFgen(array<MF<int_t,p>,n+1> m):base(m){}
	GGFgen(std::initializer_list<int_t> lst){
		int i=0;
		for(int m:lst){
			base[i]=m;
			i++;
		}
	} 
	GGF<int_t,p,n> operator()(){
		return GGF<int_t,p,n>(base);
	}
	GGF<int_t,p,n> operator()(array<MF<int_t,p>,n+1> x){
		return GGF<int_t,p,n>(base,x);
	}
};
template<int n>
class GFgen{
	bitset<n+1> base;
public:
	GFgen(bitset<n+1> m):base(m){}
	GF<n> operator()(){
		return GF<n>(base);
	}
	GF<n> operator()(bitset<n+1> x){
		return GF<n>(base,x);
	}
};
int main(){
	MF<int,7> x=6;
	x=x+x;
	cout<<*(int*)&x<<'\n';
	GGFgen<int,7,2> g7134({1,3,1});
	auto y=g7134();
	auto z=g7134();
	y[1]=3;
	y=y^47; // n-2
	y=y.inv();
	for(auto k:y)cout<<*(int*)&k;
	
}