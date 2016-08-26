/*
 * stack.hpp
 *
 *  Created on: 2016��4��27��
 *      Author: Hawrk
 *        Desc:ջ�Ļ�������
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
		T data[MAXLEN];    //������ʵ��һ��ջ
		int top;
	};

	template <class T>
	class Stack
	{
	public:
		//��ʼ��ջ
		StackType *init();

		//�ж�ջ�Ƿ�Ϊ��
		bool isempty() const ;

		//�ж��Ƿ���ջ
		bool isfull() const;

		//Ԫ��ѹջ
		bool push(const T& data);

		//ջ����
		T& pop();

		//ջ�ĳ���
		size_t size();

	private:
		StackType *_stack;
	};

}



#endif /* ALGORITHMS_INC_STACK_HPP_ */
