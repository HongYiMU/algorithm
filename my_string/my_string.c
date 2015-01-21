#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
size_t my_strlen(const char* s);
char* my_strcat(char* to, const char *from);
char* my_strcpy(char* to, const char *from);
const char* my_strstr(const char* from, const char* str);
int my_atoi(const char* str);


int maintemp(int argc, char* argv[])
{
	//int ret = my_strlen("test");
	//printf("ret = %d\n",ret);
	
	//char to[100] = "test111";
	//char* from = "test222";
	//my_strcpy(to,from);
	
	//char *from = "testABC";
	//char *find = my_strstr(from,"ta");
	//printf("strstr:%s\n",find);
	
	char *str = "000123";
	int i = my_atoi(str);
	printf("atoi %d\n",i);

	system("pause");
	return 0;
}
char* my_strcpy(char* to, const char *from)
{
	char *str = to;
	assert(to != NULL);
	while((*to++ = *from++) != '\0')
	{}
	return str;
}

char* my_strcat(char* to, const char *from)
{
	char *end = to;
	while(*end)
	{end++;}
	while(*from)
	{
		*end = *from++;
		end++;
	}
	*end = '\0';
	return to;
}
size_t my_strlen(const char* s)
{
	const char *p;
	for(p=s; *p; p++)
	{
	}
	return p-s;
}
const char* my_strstr(const char* from, const char* str)
{
	const char* p;
	assert(from != NULL && str != NULL);
	for(p=from; *p; p++)
	{
		const char *frmtemp = p;
		const char *s=str;
		while(*s++ == *frmtemp++)
		{
			if(*s == '\0')
			{
				return p;
			}
		}
	}
	return NULL;
}

int my_atoi(const char* str)
{
	const char* p;
	int dec=0;
	int m=1;
	for(p=str;*p;p++)
	{
		m *= 10;
	}
	m /=10;
	for(p=str;*p>='0' && *p<='9'; p++)
	{
		dec += (*p-'0')*m;
		m /= 10;
	}
	if(*p=='\0')
	{
		return dec;
	}
	return 0;
}


