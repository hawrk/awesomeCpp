/*
 * stack.cpp
 *
 *  Created on: 2016年4月27日
 *      Author: Hawrk
 *        Desc:
 */
#include "stack.hpp"

using namespace hal;

template <class T>
StackType Stack<T>::*init()
{
	StackType *p;
	p = new StackType;
	if(NULL != p)
	{
		//p->T = "";
		p->top = 0;
		return p;
	}
	return NULL;
}

template <class T>
bool Stack<T>::isempty() const
{
	return _stack->top == 0;
}

template <class T>
bool Stack<T>::isfull() const
{
	return _stack->top == MAXLEN - 1;
}

template <class T>
bool Stack<T>::push(const T& data)
{
	//是否满栈
	if(isfull())
	{
		std::cout<<"stack full.."<<std::endl;
		return false;
	}
	//未满，则stack->top +1,并且把data元素赋进去
	//++_stack->top;
	//_stack->data[_stack->top] = data;
	//合并
	_stack->T[++_stack->top] = data;
	return true;
}

//弹出栈顶元素
template <class T>
T& Stack<T>::pop()
{
	//判断空栈
	if(isempty())
	{
		std::cout<<"stack is empty.."<<std::endl;
		throw std::exception;
	}

	return _stack->T[_stack->top--];
}

template <class T>
size_t Stack<T>::size()
{
	return _stack->top+1;
}
