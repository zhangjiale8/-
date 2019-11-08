#include <stdio.h>
#include <malloc.h>
#include <iostream>
#include "common/statusDefine.h"
#include "common/sizeDefine.h"

using namespace std;

typedef struct
{
	int *elem;					//存储空间基址（指向第一个结点的指针） 
	int length;							//当前顺序表长度 
	int listsize;						//当前分配的存储容量 
}SqList;

//int InitList_Sq(SqList *L);								//顺序表0号单元正常使用 
/*************************************初始化顺序表**********************************************/
int initsequencelist(SqList *L){
	(*L).elem = (int *)malloc(LIST_INIT_SIZE*sizeof(int));
	if(!(*L).elem){
		exit(OVERFLOW); //分配内存失败退出 
	}
	(*L).length = 0; //初始化顺序表长度为0 
	(*L).listsize = LIST_INIT_SIZE; //顺序表初始内存分配量
	return OK; 
} 
/*************************************顺序表判空**********************************************/
int  isempty(SqList L){
	int length = L.length;
	if(0 == length){
		return FALSE;
	}else{ 
		return TRUE; 
	}
} 

/*************************************顺序表插入元素**********************************************/
int  insertElem(SqList *L,int i,int value){
	int *newbase;
	int *p,*q;
	//校验输入的下标i是否合法 
	if(i <1 || i > (*L).length+1){
		return ERROR;
	}
	//如果超出存储空间则开辟新的空间
	if((*L).length >= (*L).listsize){
		newbase = (int *)realloc((*L).elem,((*L).listsize +LIST_INCREAMENT_SIZE)*sizeof(int));
		if(!newbase){
			exit(OVERFLOW); //分配内存失败退出 
		}else{
			(*L).elem = newbase;
			(*L).listsize += LIST_INCREAMENT_SIZE;
		}
	} 
	
	q = &(*L).elem[i-1];  //q为顺序表的插入位置 
	for(p=&(*L).elem[(*L).length-1]; p>=q; --p){
		*(p+1) = *p;
	} 
	*q = value;
	(*L).length++;
	return OK; 
} 
/**************************visit访问函数********************************/ 
void coutelem(int e){
	cout<<e<<endl;
}
/**************************使用visit访问顺序表********************************/ 
int traverse(SqList L,void(coutelem)(int)){
	for(int i=0;i<L.length;i++){
		coutelem(L.elem[i]);
	}
	return OK;
}

/**************************获取顺序表长度********************************/
int getlength(SqList L){
	int length = L.length;
	return length;
}

/**************************删除顺序表中元素********************************/
int deleteElem(SqList *L,int i,int *e){
	int *p,*q;
	if(i< 1 || i >(*L).length){
		return ERROR;
	}
	
	p = &(*L).elem[i-1]; //需要被删除的元素位置
	*e = *p;
	q = (*L).elem +(*L).length -1;
	
	for(++p;p<=q;++p){
		*(p-1) = *p; //被删元素之后的元素左移 
	}
	(*L).length --;

	return OK; 	 
	
} 


/**************************获取顺序表中元素********************************/
int getElem(SqList L,int i,int *e){
	if(i< 1 || i >L.length){
		return ERROR;
	}
	
	*e = L.elem[i-1];


	return OK; 	 
	
} 

/**************************比较元素大小********************************/
int elemCompare(int e,int data){
	if(e>data){
		return TRUE;
	}else{
		return FALSE;
	}	 
	
}

/**************************比较元素是否********************************/
int equal(int e,int data){
	if(e == data){
		return TRUE;
	}else{
		return FALSE;
	}	 
	
}  

/**************************获取顺序表中第一个大于某个值的位置********************************/
int locateElem(SqList L,int e,int elemCompare(int,int)){
	int i = 1;
	while(i<=L.length && !elemCompare(e,L.elem[i-1])){
		i++;
	}
	
	if(i<=L.length){
		return i;
	}else{
		return 0;
	}
	
}


/**************************获取顺序表中某个元素的前驱********************************/
int priorElem(SqList L,int elem,int *e){
	int i = 1;
	
	if(L.elem[0]!=elem)				//第一个结点无前驱 
	{
		while(i<L.length && L.elem[i]!=elem)
			++i;
		
		if(i<L.length)
		{
			*e = L.elem[i-1];
			return OK;
		}	
	} 	 
	
	return FALSE; 
} 

/**************************获取顺序表中某个元素的后继********************************/
int nextElem(SqList L,int elem,int *e){
	int i = 1;
	
	if(L.elem[L.length-1]!=elem)				//最后结点无后继 
	{
		while(i<L.length && L.elem[i]!=elem)
			++i;
		
		if(i<L.length-1)
		{
			*e = L.elem[i+1];
			return OK;
		}	
	} 	 
	
	return FALSE; 
} 


/**************************清空顺序表中元素********************************/
void clear(SqList *L){
	(*L).length = 0;
}


/**************************销毁顺序表********************************/
void destroy(SqList *L){
	(*L).elem = NULL; 
	(*L).length = 0;
	(*L).listsize = 0;
}

/**************************两个顺序表合并取并集********************************/
void listunion(SqList *leftList,SqList rightList){
	int leftLength, rightLength;
	int i;
	int e;
	
	leftLength = getlength(*leftList);			//求顺序表长度 
	rightLength = getlength(rightList);
	
	for(i=1; i<=rightLength; i++)
	{
		getElem(rightList, i, &e);				//取rightList中第i个元素赋给e 
		int flg = locateElem(*leftList, e, equal);
		if(!flg){ 	//若e不在leftList中则插入
			insertElem(leftList, ++leftLength, e);	
		} 
	}
}
