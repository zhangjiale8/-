#include<stdio.h>
#define GET_ARRAY_LENGTH(array,length){length = sizeof(array)/sizeof(array[0]);} //获取数组长度函数 C语言中指能这么写 

/******************获取数组长度函数 C++语言中可以这么写 **************************************/
template <class T> 
int getLength(T &array){
	int length = sizeof(array)/sizeof(array[0]);
	return length;
}
