#include<stdio.h>
#define GET_ARRAY_LENGTH(array,length){length = sizeof(array)/sizeof(array[0]);} //��ȡ���鳤�Ⱥ��� C������ָ����ôд 

/******************��ȡ���鳤�Ⱥ��� C++�����п�����ôд **************************************/
template <class T> 
int getLength(T &array){
	int length = sizeof(array)/sizeof(array[0]);
	return length;
}
