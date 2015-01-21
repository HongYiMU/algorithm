#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef UCHAR
#define UCHAR unsigned char 
#endif

const char* base64="ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
static UCHAR FindPos(char c);
char* Base64Encode(char* s, int len);
char* Base64Decode(char* code);

int main(int argc, char* argv[])
{
	char msg[] = "Xue1234";
	char *encode,*decode;
	encode = Base64Encode(msg,strlen(msg));
	printf("encode:%s-><%s>\n",msg,encode);
	decode = Base64Decode(encode);
	printf("\ndecode:%s-><%s>\n",encode,decode);
	free(encode);
	free(decode);
	system("pause");
	return 0;
}
static UCHAR FindPos(char c)
{
	UCHAR p;
	for(p=0; p<strlen(base64); p++)
	{
		if(c == base64[p])
		{
			break;
		}
	}
	return p;
}


char* Base64Decode(char* s)
{
	UCHAR* decode = NULL;
	int len;
	int i,j;
	UCHAR ch;
	int unit;
	int td;
	char* pch;
	int itemp;
	len	= strlen(s);
	unit = len/4;
	//printf("---=>%s<=>%d<=>%d<---\n",s,len,unit);
	
	decode = (UCHAR*)malloc(len+1);
	
	memset(decode,'\0',len+1);
	for(i=0; i<len; i++)
	{
		ch = FindPos(s[i]);
		//printf("%d ",ch);
		decode[i]=ch;
	}
	for(i=0;i<unit; i++)
	{
		itemp = *(int*)(decode+i*4);
		//printf("\n###<%d>###\n",itemp);
		pch = (UCHAR*)&itemp;
		for(j=0;j<4;j++)
		{
			//printf("<%d>",*pch);
			*((char*)&td) = (*pch & 0x3f) << 2;
			td = td << 6;
			pch++;
		}
		td = td >> 8;
		for(j=0;j<3;j++)
		{
			decode[i*3+2-j] = td & 0xff;
			//printf("<%d>",decode[i*3+2-j]);
			td = td >> 8;
		}
	}
	decode[i*3] = '\0';
	return decode;
}

char* Base64Encode(char* s, int dataLen)
{
	char *encode;
	int dataCount;
	int codeSize = 0,unit;
	int i,j,temp,p=0,index,t;
	int precode=0;
	if(dataLen<1)
		{return NULL;}
	unit = dataLen/3;
	dataCount = dataLen*8/6;
	if(dataLen%3)
		{unit += 1;dataCount += 1;}
	codeSize = unit*4;
	encode = (char*)malloc(codeSize+1);
	memset(encode,'\0',codeSize+1);
	for(i=0; i<unit; i++)
	{
		temp = 0;
		temp = *(int*)(s+i*3) & ~(0xff<<24);
		//printf("-=-=%c-%c-%c-=%d=-=\n",*(char*)&temp,*(((char*)&temp)+1),*(((char*)&temp)+2),temp);

		for(t=0; t<3; t++)
		{
			precode = precode | (temp & 0xff);
			precode = precode << 8;
			temp = temp>>8;
		}
		for(j=0;j<4;j++)
		{
			if(p<dataCount)
			{
				index = (precode<<6*j) & 0xfc000000;
				//printf("-=%d=%x-=\n",precode,(index>>26)&0x3f);
				encode[p] = base64[(index>>26)&0x3f];
				p++;
			}
			else
			{
				encode[p] = '=';
				p++;
			}
		}
	}
	encode[codeSize] = '\0';
	return encode;
}
