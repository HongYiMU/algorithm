#include <iostream>
#include <vector>
#include <stdio.h>
#include <string>
using namespace std;

void print(char*,int);
void InsertIntoVector(char*,int);
void PrintVector();
void Insertion(char c,int start, int end);
vector<char>VecChar;

int main(int argc, char* argv[])
{
    char str[1000];
    int len;
    VecChar.clear();
    while(1)
    {
            cout<<endl;
            fgets(str,sizeof(str),stdin);
            len = strlen(str);
            print(str,len);
            InsertIntoVector(str,len);
            PrintVector();
            
    }
    return 0;    
}

void InsertIntoVector(char* str,int n)
{
	vector<char>iterator::it;
	it = VecChar.begin();
	int begin=0,end=n,mid;
	for(int i=0; i<n; i++)
	{
		while(begin != end)
		{
			mid = (begin+end)/2;
			if(*(it+mid) <= str[i])
			{
				end = mid;
			}
			else
			{
				begin = mid;
			}
		}
		printf("%d",begin);
	}
}
void Insertion(char c,int start, int end)
{

}
void print(char* str,int n)
{
     for(int i=0; i<n; i++)
     {
          cout<<str[i];
     }
}
void PrintVector()
{
     int size = VecChar.size();
     cout << size <<endl;
     cout <<"print vector" <<endl;
     for(int i=0; i<size; i++)
     {
        cout<<VecChar[i];
     } 
     //cout <<endl<<" +++++==++++=" <<endl;
}





/*
void InsertIntoVector(char* str,int n)
{
     int VectorSize;
     //cout << str <<endl;
     for(int i=0; i<n; i++)
     {
             VectorSize = VecChar.size();
             //cout<< VectorSize <<endl;
             if(VectorSize <1)
             {
                  VecChar.push_back(str[i]);
             }
             else if(str[i] <= VecChar[VectorSize/2])
             {
                  Insertion(str[i],0,VectorSize/2);
             }
             else
             {
                 Insertion(str[i],VectorSize/2+1,VectorSize);                 
             }
     }
}

void Insertion(char c,int start, int end)
{
     //cout <<"start:"<<start<<"end:"<<end<<endl;
     if(start == end)
     {
      
         vector<char>::iterator it;
         it = VecChar.begin()+start;
            VecChar.insert(it,c);

         return;     
     }
     int mid = (start+end)/2;
     if(c <= VecChar[mid])
     {
          Insertion(c,start,mid);
     }
     else
     {
         Insertion(c,mid+1,end);
     }
}
*/
