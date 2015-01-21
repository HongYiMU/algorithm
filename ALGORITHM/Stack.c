//#include "common.h"
#include "Stack.h"

status StackInit(SqSTACK* stack)
{
	stack->base = (SElemType*)malloc(STACK_INIT_SIZE * sizeof(SElemType));
	if(!stack->base)
	{
		return ERROR;
	}
	stack->top = stack->base;
	stack->stackSize = STACK_INIT_SIZE;
	return OK;
}

status Push(SqSTACK* stack,SElemType e)
{
	if(stack->top - stack->base >= stack->stackSize)
	{
		SElemType* preBase = stack->base;
		printf("over flow! top = %p memory reallocing ...\n",stack->top);
		stack->base = (SElemType*)realloc(stack->base,(stack->stackSize + STACK_INCREMENT)*sizeof(SElemType));

		if(!stack->base)
		{
			perror("realloc");
			return ERROR;
		}
		stack->stackSize += STACK_INCREMENT;
		stack->top = stack->base + (stack->top - preBase);
	}

	*(stack->top) = e;
	stack->top += 1;
	return OK;
}


SElemType Pop(SqSTACK* stack)
{
	SElemType pop;
	if(stack->base == stack->top)
	{
		printf("error:stack empty!\n");
		return 0;
	}

	pop = *( -- stack->top);
	return pop;
}

status StackDestroy(SqSTACK* stack)
{
	free(stack->base);
	return 0;
}
status StackIsEmpty(SqSTACK* stack)
{
	if(stack->base >= stack->top)
	{
		return TRUE;
	}
	return FALSE;
}

SElemType StackGetTop(SqSTACK* stack)
{
	if(stack->top == stack->base)
	{
		return ERROR;
	}
	return *(stack->top-1);
}
