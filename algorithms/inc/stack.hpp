/*
 * stack.hpp
 *
 *  Created on: 2016年4月27日
 *      Author: Hawrk
 *        Desc:栈的基本操作
 */

#ifndef ALGORITHMS_INC_STACK_HPP_
#define ALGORITHMS_INC_STACK_HPP_
#include <string>
#include <exception>

#define MAXLEN  500

namespace hal
{
//	struct Data
//	{
//		std::string name;
//		int age;
//	};

	template <class T>
	struct StackType
	{
		T data[MAXLEN];    //用数组实现一个栈
		int top;
	};

	template <class T>
	class Stack
	{
	public:
		//初始化栈
		StackType *init();

		//判断栈是否为空
		bool isempty() const ;

		//判断是否满栈
		bool isfull() const;

		//元素压栈
		bool push(const T& data);

		//栈弹出
		T& pop();

		//栈的长度
		size_t size();

	private:
		StackType *_stack;
	};

}



#endif /* ALGORITHMS_INC_STACK_HPP_ */
