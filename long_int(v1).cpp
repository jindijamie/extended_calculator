#include "long_int.h"
#include <iostream>
#include <cmath>

#include <cassert>
#include <cstdio>
#include <string>
using namespace std;

LongInt::LongInt(int number) {
	if(number<0) symbol=1,number=-number;
	else symbol=0;
	int n=number,i;
	for (i=0;n!=0;i++) n/=10;
	if(number==0) i=1;
	string num(i,'0');
	number_=num;
    n=number;
    for (i=0;i<num.length();i++) number_[num.length()-i-1]=n%10+'0',n/=10; 
}

LongInt::LongInt(long double number) {
	if(number<0) symbol=1,number=-number;
	else symbol=0;
	long double n=number;
	int i;
	for (i=0;n>=1.0;i++) n/=10;
	if(number==0.0) i=1;
	string num(i,'0');
	number_=num;
    n=number;
    for (i=0;i<num.length();i++) number_[num.length()-i-1]=int(n-floor(n/10)*10)+'0',n/=10; 
}



LongInt::LongInt(const LongInt &long_int2) : number_(long_int2.number_),symbol(long_int2.symbol){
	
}

LongInt::~LongInt(){
	
}

LongInt::LongInt(const string Int)
{
	string Int2=Int;
	if(Int[0]=='-') symbol=1,Int2=Int.substr(1,Int.length());
	else symbol=0;
	string num(Int2);
	number_=num;
	this->cancelz();
}

void LongInt::cancelz()
{
	if(number_[0]!='0') return;
	int n=0;
	while(number_[n]=='0' && n<number_.length()) n++;
	
	if(n==number_.length()) n--;
	number_=number_.substr(n,number_.length());
	
}

LongInt::operator bool(){
	for(int i=0;i<number_.length();i++) 
		if(number_[i]!='0') return 1;
	return 0;
}

LongInt::operator long double(){
	long double db=0;
	for (int i=0;i<number_.length();i++) db=10*db+number_[i]-'0';
	if(symbol==1) return -db;
	return db;
}

LongInt::operator int(){
	int db=0;
	for (int i=0;i<number_.length();i++) db=10*db+number_[i]-'0';
	if(symbol==1) return -db;
	return db;
}


bool LongInt::operator!=(const LongInt &long_int2) const{
	if(number_.length()!=long_int2.number_.length()) return 1;
	for (int i=0;i<number_.length();i++)
		if(number_[i]!=long_int2.number_[i]) return 1;
	return 0;
}

bool LongInt::operator<(const LongInt &long_int2) const{
	if(symbol!=long_int2.symbol) return symbol;
	if(symbol==0)
	{
		if(number_.length()!=long_int2.number_.length()) return number_.length()<long_int2.number_.length();
		for (int i=0;i<number_.length();i++)
			if(number_[i]!=long_int2.number_[i]) return number_[i]<long_int2.number_[i];
		return 0;
	}
	else
	{
		if(number_.length()!=long_int2.number_.length()) return number_.length()>long_int2.number_.length();
		for (int i=0;i<number_.length();i++)
			if(number_[i]!=long_int2.number_[i]) return number_[i]>long_int2.number_[i];
		return 0;
	}

}


LongInt &LongInt::operator=(const LongInt &long_int2){
	symbol = long_int2.symbol;
	number_= long_int2.number_;
}

LongInt LongInt::operator+(const LongInt &long_int2) const{
	int l=MIN(number_.length(),long_int2.number_.length()),l2=MAX(number_.length(),long_int2.number_.length());
	int now=0,next=0;
	string bn;
	bn=max(*this,long_int2).number_;
	LongInt sum;
	string su(l2+1,'0');
	sum.number_=su;
	if(symbol==long_int2.symbol)
	{
		sum.symbol=symbol;
		for (int i=0;i<l;i++) 
		{
			now=next+number_[number_.length()-1-i]-'0'+long_int2.number_[long_int2.number_.length()-1-i]-'0';
			sum.number_[l2-i]=now%10+'0'; 
			next=now/10;
			//cout<<l2-i<<" "<<sum.number_[l2-i]<<endl;
		}
		for (int i=l;i<l2;i++)
		{
			now=next+bn[l2-1-i]-'0';
			sum.number_[l2-i]=now%10+'0'; 
			next=now/10;
			//cout<<l2-i<<" "<<sum.number_[l2-i]<<endl;
			
		}
		sum.symbol=symbol;
		sum.number_[0]=next+'0';
		sum.cancelz();
		//cout<<sum.number_;
	}
	else
	{
		LongInt long_int3=long_int2;
		long_int3.symbol=!long_int3.symbol;
		sum=*this-long_int3;
	 } 
	return sum;
}

LongInt LongInt::operator-(const LongInt &long_int2) const{
	LongInt b,s,*r;
	int now=0,next=0;
	if(symbol==long_int2.symbol)
	{
		b=max(*this,long_int2);
		s=min(*this,long_int2);
		LongInt result(b);
		for(int i=0;i<s.number_.length();i++)
		{
			now=b.number_[b.number_.length()-1-i]-s.number_[s.number_.length()-1-i]-next;
			next=0;
			while (now<0) next++, now+=10;
			result.number_[b.number_.length()-1-i]=now+'0';
			//cout<<result.number_[b.number_.length()-1-i];
		}
		for(int i=s.number_.length();i<b.number_.length() && next!=0;i++)
		{
			now=b.number_[b.number_.length()-1-i]-'0'-next;
			next=0;
			while (now<0) next++, now+=10;
			result.number_[b.number_.length()-1-i]=now+'0';
			//cout<<result.number_[b.number_.length()-1-i]<<"now"<<now<<endl;
		}
		
		result.cancelz();
		if(*this<long_int2) result.symbol=1;
		else result.symbol=0;
		return result;
	}
	else
	{
		LongInt long_int3=long_int2;
		long_int3.symbol=!long_int3.symbol;
		LongInt result=*this+long_int3;
		return result;
	}
	
}

LongInt LongInt::operator*(const LongInt &long_int2) const{
	int n,next=0;
	string a="0",b="";
	string mid="";
	int i=number_.length()-1,j=long_int2.number_.length()-1,k=0,f=0;
	LongInt result;
	for (int k=i;k>=0;k--)
	{
		mid="";
		for(int l=j;l>=0;l--)
		{
			n=(number_[k]-'0')*(long_int2.number_[l]-'0')+next;
			a[0]=n%10+'0';
			next=n/10;
			mid=a+mid;
		}
		while (next!=0)
		{
			a[0]=next%10+'0';
			next/=10;
			mid=a+mid;
		}
		result=LongInt(mid+b)+result;
		b=b+"0";
	}

	if(symbol==long_int2.symbol) result.symbol=0;
	else result.symbol=1;
	result.cancelz();
	return result;
}



LongInt LongInt::operator/(const LongInt &long_int2) const{
	if(!bool(LongInt(long_int2))) assert(1);
	LongInt aa(*this),bb(long_int2);
	aa.symbol=bb.symbol=0;
	if(aa<bb) return LongInt(0);
	string res="";
	string t="0";
	LongInt result;
	int next,now;
	string a="0"+number_,b="0"+long_int2.number_;
	for(int i=0;i<a.length()-b.length()+1;i++)
	{
		t="0";
		while(a.compare(i,b.length(),b)>=0)
		{
			t[0]+=1;
			next=0;
			for(int k=1;k<=b.length();k++)
			{
				now=a[i+b.length()-k]-b[b.length()-k]-next;
				next=0;
				while(now<0) now+=10,next++;
				a[i+b.length()-k]=now+'0';
			}
		}
		//cout<<"a="<<a<<"t="<<t<<endl;
		res=res+t;
	}
	result.number_=res;
	result.cancelz();
	if(symbol==long_int2.symbol) result.symbol=0;
	else result.symbol=1;
	return result;
}
LongInt LongInt::operator%(const LongInt &long_int2) const{

	if(!bool(LongInt(long_int2))) assert(1);
	LongInt a=*this/long_int2; 
	//cout<<"a(";
	//a.print();
	//cout<<")";
	LongInt c=a*long_int2;
	LongInt result=*this-c;
	return result;
}


LongInt LongInt::operator-=(const LongInt &long_int2) {
	*this=*this-long_int2;
	return *this;
}

LongInt max(const LongInt &long_int1, const LongInt &long_int2){
	LongInt a(long_int1),b(long_int2);
	a.symbol=b.symbol=0;
	if(a<b) return b;
	return a;
}

LongInt min(const LongInt &long_int1, const LongInt &long_int2){
	LongInt a(long_int1),b(long_int2);
	a.symbol=b.symbol=0;
	if(a<b) return a;
	return b;
}

void LongInt::print(){
	if(symbol && number_!="0") cout<<"-";
	cout<<number_;
}


