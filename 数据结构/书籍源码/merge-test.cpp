#include<stdio.h>
#include "sequenceListUtil.cpp"
#include "arrayUtil.cpp"

int main(){
	SqList leftList,rightList,threeList,fourList;
	int firstArr[] = {3, 5, 8, 11};
	int secondArr[] ={2, 6, 8, 9, 11, 15, 20};
	int i;
	initsequencelist(&leftList);
	int firstLength;
	GET_ARRAY_LENGTH(firstArr,firstLength);
	int secondLength;
	GET_ARRAY_LENGTH(secondArr,secondLength);
	firstLength = getLength(firstArr);
	cout<<"第一个数组长度："<<firstLength<<endl;
	cout<<"第二个数组长度："<<secondLength<<endl;
	cout<<"leftList 初始化"<<endl;
	for(i = 1;i<=firstLength;i++){
		insertElem(&leftList,i,firstArr[i-1]);
	} 
	cout<<"rightList 初始化"<<endl;
	for(i = 1;i<=secondLength;i++){
		insertElem(&rightList,i,secondArr[i-1]);
	} 
	
	cout<<"输出leftList"<<endl;
	traverse(leftList,coutelem); //感觉相当于回调函数 
	cout<<"输出rightList"<<endl;
	traverse(rightList,coutelem); //感觉相当于回调函数 
	
	cout<<"leftList Merge rightList"<<endl;
	listmerge(leftList,rightList,&threeList);
	cout<<"输出 leftList Merge rightList"<<endl;
	traverse(leftList,coutelem); 
	
	return 0;
} 
