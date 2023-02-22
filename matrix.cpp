#include <iostream>
using std::cout;
using std::endl;
template<int siz,class zm=int>
struct matrix{
    zm **m;
    matrix(zm x=0){
        m=new zm*[siz];
        for(int i=0;i<siz;i++){
            m[i]=new zm[siz];
            for(int j=0;j<siz;j++)
            	m[i][j]=0;
            m[i][i]=x;
        }
    }
    matrix(const matrix&y){
        m=new zm*[siz];
        for(int i=0;i<siz;i++){
            m[i]=new zm[siz];
            memcpy(m[i],y.m[i],siz*sizeof(zm));
        }
    }
    ~matrix(){
        for(int i=0;i<siz;i++)
            delete[]m[i];
        delete[]m;
    }
   	void operator=(const matrix& y){
    	for(int i=0;i<siz;i++)
            memcpy(m[i],y.m[i],siz*sizeof(zm));
	}
    zm* operator[](int i){
        return m[i];
    }
    matrix operator+(matrix y){
        matrix z=*this;
        for(int i=0;i<siz;i++)
            for(int j=0;j<siz;j++)
                z[i][j]=z[i][j]+y[i][j];
        return z;
    }
    matrix operator-(matrix y){
        matrix z=*this;
        for(int i=0;i<siz;i++)
            for(int j=0;j<siz;j++)
                z[i][j]=z[i][j]-y[i][j];
        return z;
    }
    matrix operator*(matrix y){
        matrix z;
        for(int i=0;i<siz;i++)
            for(int j=0;j<siz;j++)
                for(int k=0;k<siz;k++)
                    z[i][j]=z[i][j]+m[i][k]*y[k][j];
        return z;
    }
    void prn(){
        for(int i=0;i<siz;i++){
            for(int j=0;j<siz;j++)
                cout<<m[i][j]<<' ';
            cout<<'\n';
        }
        cout<<"---"<<endl;
    }
};
