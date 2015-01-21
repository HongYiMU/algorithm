#ifndef COMMON_H
#define COMMON_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <malloc.h>
#define TRUE 1
#define FALSE 0
#define OK 1
#ifndef ERROR
#define ERROR -1
#endif
#define OVERFLOW -2

typedef char ElemType;
typedef char status;

#define STACK_INIT_SIZE 100
#define	STACK_INCREMENT 10

typedef struct _SqSTACK{
	ElemType *base;
	ElemType *top;
	int stackSize;
}SqSTACK;


#endif 