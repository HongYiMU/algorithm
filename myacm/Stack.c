#include "common.h"

extern status StackInit(SqSTACK* stack);
extern status Push(SqSTACK* stack,ElemType e);
extern status Pop(SqSTACK* stack);
extern status StackDestroy(SqSTACK* stack);




status StackInit(SqSTACK* stack)
{
	stack->base = (ElemType*)malloc(STACK_INIT_SIZE * sizeof(int));
	if(!stack->base)
	{
		return ERROR;
	}
	stack->top = stack->base;
	stack->stackSize = STACK_INIT_SIZE;
	return OK;
}
status Push(SqSTACK* stack,ElemType e)
{
	if(stack->top - stack->base >= stack->stackSize)
	{
		ElemType* preBase = stack->base;
		printf("over flow! top = %p memory reallocing ...\n",stack->top);
		stack->base = (ElemType*)realloc(stack->base,(stack->stackSize + STACK_INCREMENT)*sizeof(ElemType));

		if(!stack->base)
		{
			perror("realloc");
			return ERROR;
		}
		stack->stackSize += STACK_INCREMENT;
		stack->top = stack->base + (stack->top - preBase);
	}
	
	*(stack->top) = e;
	stack->top +=1;
	return OK;
}
ElemType Pop(SqSTACK* stack)
{
	ElemType pop;
	if(stack->base == stack->top)
	{
		printf("error:stack empty!\n");
		return (ERROR);
	}
	
	pop = * -- stack->top;
	return pop;
}
status StackDestroy(SqSTACK* stack)
{
	free(stack->base);
	return 0;
}
status StackIsEmpty(SqSTACK* stack)
{
	if(stack->base == stack->top)
	{
		return TRUE;
	}
	return FALSE;
}

ElemType GetTop(SqSTACK* stack)
{
	if(stack->top == stack->base)
	{
		return ERROR;
	}
	return *(stack->top-1);
}

status IsIn(ElemType e)
{
	switch(e)
	{
		case '+':
		case '-': 
		case '*':
		case '/': 
		case '=':
		//case '=':
		case '(':
		case ')':
			return TRUE;
			break;
		default:
			break;
	}
	return FALSE;
}

int GetIndex(ElemType x)
{
	int ret = -1;
	switch(x)
	{
		case '+':ret = 0;break;
		case '-':ret = 1;break;
		case '*':ret = 2;break;
		case '/':ret = 3;break;
		case '(':ret = 4;break;
		case ')':ret = 5;break;
		case '=':ret = 6;break;
		default:
			break;
	}
	return ret;
}

ElemType Precede(ElemType a,ElemType b)
{
	ElemType priority[7][7] = {
			{'>','>','<','<','<','>','>'},{'>','>','<','<','<','>','>'},
			{'>','>','>','>','<','>','>'},{'>','>','>','>','<','>','>'},
			{'<','<','<','<','<','=','/'},{'>','>','>','>','/','>','>'},
			{'<','<','<','<','<','/','='}
	};
	ElemType oprant[] = {'+','-','*','/','(',')','='};
	int ia = 0,ib = 0;
	ia = GetIndex(a);
	ib = GetIndex(b);

	return priority[ia][ib];
}

int DecNotationExchange(int dec,int N)
{
	int ox = 1;
	SqSTACK stack;
	if(dec <1)
	{
		return 0;
	}
	StackInit(&stack);
	
	while(dec)
	{
		Push(&stack,dec%N);
		dec = dec/N;
	}
	if (!StackIsEmpty(&stack))
	{
		ox = Pop(&stack);
	}
	while(!StackIsEmpty(&stack))
	{
		ox = ox *10 + Pop(&stack);
	}
	StackDestroy(&stack);	
	return ox;
}
ElemType OperationSwitch(ElemType a1,ElemType op,ElemType a2)
{
	ElemType ret=0;
	switch(op)
	{
		case '+':ret= a1+a2;	break;
		case '-':ret= a1-a2;	break;
		case '*':ret= a1*a2;	break;
		case '/':ret= a1/a2;	break;
		default:
			break;
	}
	return ret;
}
ElemType EvaluateExpression()
{
	SqSTACK stack_oprand,stack_operator;
	ElemType ch[100],*pch,toprand,toperator1,toperator2,ret;
	StackInit(&stack_oprand);
	StackInit(&stack_operator);
	memset(ch,0,sizeof(ch));
	fgets(ch,100,stdin);
	ch[strlen(ch)-1] = '\0';
	pch = ch;
	Push(&stack_oprand,'=');

	while(1)
	{
		//printf("%c",*pch);
		if( !IsIn(*pch))
		{
			*pch = *pch - '0';
			//printf("=%d ",*pch);
			Push(&stack_operator,*pch); 

		}//operator
		else//operand
		{
			switch(Precede(GetTop(&stack_oprand),*pch))
			{
				case '<':
					Push(&stack_oprand,*pch);	
					break;
				case '=':
					Pop(&stack_oprand);
					break;
				case '>': 
					toprand = Pop(&stack_oprand);
					toperator1 = Pop(&stack_operator);
					toperator2 = Pop(&stack_operator);
					ret = OperationSwitch(toperator1,toprand,toperator2);
					Push(&stack_operator,ret);
					if(*pch != '=' && *pch != ')'){
						Push(&stack_oprand,*pch);
					}
					break;
				case '/':
					Pop(&stack_oprand);
					break;
			}
		}
		if(*pch != '=')	{pch++;	}
		else if(GetTop(&stack_oprand) == '='){break;}
	}

	ret = GetTop(&stack_operator);
	return ret+'0';
}

void StackTest()
{
	while(1){

	//printf("Dec %d to .. is:%d\n",10,DecNotationExchange(10,2));
	ElemType ret = EvaluateExpression();
	
	printf("\n\nret = %c\n",ret);
	}
}

