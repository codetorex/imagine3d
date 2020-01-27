
#ifndef STACK_H
#define STACK_H
#include <stdio.h>
#include <memory.h>
#include "array.h"

template <class Ty>
class istack
{
private:
	carray<Ty,0> mstack;

public:
	void push(Ty data)
	{
		mstack.AddElement(data);
	};
	Ty pop()
	{
		return mstack[mstack.GetCount()];
	};
	void de(int i)
	{
		mstack.RemoveElement(i);		
	};
	void get(int i)
	{
		return mstack[i];
	};

};

#endif
