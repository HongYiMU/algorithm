#include <iostream>
#include <string>
using namespace std;
#define template_t template <typename T>

template <typename T>
int compare(const T &T1, const T &T2)
{
	if(T1 < T2){return -1;}
	if(T1 > T2){return 1;}

	return 0;
}
template <typename T>
T mins(const T &T1, const T &T2)
 {
 	if(T1<=T2){return T1;} 
 	return T2;
 }
template <class T>
T sum(const T& T1, const T& T2)
{
	return T1+T2;
}
//非类型模板形参size_t 
void test(size_t ii)
{
	cout<< "test" <<endl;	
}

template <class T>
class Queue
{
 public:
      T a;
      Queue(){};
      ~Queue(){};
      
};


int main(void)
{
	string str1="123",str2="234";
	cout << "int " <<compare(1,2)<<endl;
	cout <<"string "<<compare(str1,str2)<<endl;
	
	cout << "int " << min(1,2) <<endl;
	cout <<"string "<< min(str1,str2) <<endl;
	
	cout << "sum" << sum(str1, str2)<<endl;
	cout << "sum 1+2=" << sum(1,2)<<endl;
	
    Queue<char> qc;
    
	test(1);

	system("pause");
}

