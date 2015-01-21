#include <iostream>
using namespace std;
class Complex    //定义Complex类
{
	public:
		Complex( ){real=0;imag=0;}   //定义构造函数
		Complex(double r,double i){real=r;imag=i;}    //构造函数重载
		Complex complex_add(Complex &c2);    //声明复数相加函数
		void display( );    //声明输出函数
	private:
			double real; //实部
			double imag; //虚部
};
Complex Complex::complex_add(Complex &c2)
{
	Complex c;
		c.real=real+c2.real;
		c.imag=imag+c2.imag;
	return c;
}
void Complex::display( ) //定义输出函数
{
	cout<<"("<<real<<","<<imag<<"i)"<<endl;
}
int main()
{
	Complex c1(3,4),c2(5,-10),c3;    //定义3个复数对象
	c3=c1.complex_add(c2);         //调用复数相加函数
	cout<<"c1="; c1.display();              //输出c1的值
	cout<<"c2="; c2.display();              //输出c2的值
	cout<<"c1+c2="; c3.display();        //输出c3的值
	return 0;
}
