#include<stdio.h>
#include "sequenceListUtil.cpp"
#include "arrayUtil.cpp"

int main(){
	SqList leftList,rightList;
	int firstArr[] = {6,5,9,1,8,6};
	int secondArr[] ={3,8,9,12,5,7,4,2,9};
	int i;
	initsequencelist(&leftList);
	int firstLength;
	GET_ARRAY_LENGTH(firstArr,firstLength);
	int secondLength;
	GET_ARRAY_LENGTH(secondArr,secondLength);
	firstLength = getLength(firstArr);
	cout<<"��һ�����鳤�ȣ�"<<firstLength<<endl;
	cout<<"�ڶ������鳤�ȣ�"<<secondLength<<endl;
	cout<<"leftList ��ʼ��"<<endl;
	for(i = 1;i<=firstLength;i++){
		insertElem(&leftList,i,firstArr[i-1]);
	} 
	cout<<"rightList ��ʼ��"<<endl;
	for(i = 1;i<=secondLength;i++){
		insertElem(&rightList,i,secondArr[i-1]);
	} 
	cout<<"���leftList"<<endl;
	traverse(leftList,coutelem); //�о��൱�ڻص����� 
	cout<<"���rightList"<<endl;
	traverse(rightList,coutelem); //�о��൱�ڻص����� 
	cout<<"leftList U rightList"<<endl;
	listunion(&leftList,rightList);
	cout<<"��� leftList U rightList"<<endl;
	traverse(leftList,coutelem); 
	
	return 0;
} 
