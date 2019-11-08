#include <stdio.h>
#include <malloc.h>
#include <iostream>
#include "common/statusDefine.h"
#include "common/sizeDefine.h"

using namespace std;

typedef struct
{
	int *elem;					//�洢�ռ��ַ��ָ���һ������ָ�룩 
	int length;							//��ǰ˳����� 
	int listsize;						//��ǰ����Ĵ洢���� 
}SqList;

//int InitList_Sq(SqList *L);								//˳���0�ŵ�Ԫ����ʹ�� 
/*************************************��ʼ��˳���**********************************************/
int initsequencelist(SqList *L){
	(*L).elem = (int *)malloc(LIST_INIT_SIZE*sizeof(int));
	if(!(*L).elem){
		exit(OVERFLOW); //�����ڴ�ʧ���˳� 
	}
	(*L).length = 0; //��ʼ��˳�����Ϊ0 
	(*L).listsize = LIST_INIT_SIZE; //˳����ʼ�ڴ������
	return OK; 
} 
/*************************************˳����п�**********************************************/
int  isempty(SqList L){
	int length = L.length;
	if(0 == length){
		return FALSE;
	}else{ 
		return TRUE; 
	}
} 

/*************************************˳������Ԫ��**********************************************/
int  insertElem(SqList *L,int i,int value){
	int *newbase;
	int *p,*q;
	//У��������±�i�Ƿ�Ϸ� 
	if(i <1 || i > (*L).length+1){
		return ERROR;
	}
	//��������洢�ռ��򿪱��µĿռ�
	if((*L).length >= (*L).listsize){
		newbase = (int *)realloc((*L).elem,((*L).listsize +LIST_INCREAMENT_SIZE)*sizeof(int));
		if(!newbase){
			exit(OVERFLOW); //�����ڴ�ʧ���˳� 
		}else{
			(*L).elem = newbase;
			(*L).listsize += LIST_INCREAMENT_SIZE;
		}
	} 
	
	q = &(*L).elem[i-1];  //qΪ˳���Ĳ���λ�� 
	for(p=&(*L).elem[(*L).length-1]; p>=q; --p){
		*(p+1) = *p;
	} 
	*q = value;
	(*L).length++;
	return OK; 
} 
/**************************visit���ʺ���********************************/ 
void coutelem(int e){
	cout<<e<<endl;
}
/**************************ʹ��visit����˳���********************************/ 
int traverse(SqList L,void(coutelem)(int)){
	for(int i=0;i<L.length;i++){
		coutelem(L.elem[i]);
	}
	return OK;
}

/**************************��ȡ˳�����********************************/
int getlength(SqList L){
	int length = L.length;
	return length;
}

/**************************ɾ��˳�����Ԫ��********************************/
int deleteElem(SqList *L,int i,int *e){
	int *p,*q;
	if(i< 1 || i >(*L).length){
		return ERROR;
	}
	
	p = &(*L).elem[i-1]; //��Ҫ��ɾ����Ԫ��λ��
	*e = *p;
	q = (*L).elem +(*L).length -1;
	
	for(++p;p<=q;++p){
		*(p-1) = *p; //��ɾԪ��֮���Ԫ������ 
	}
	(*L).length --;

	return OK; 	 
	
} 


/**************************��ȡ˳�����Ԫ��********************************/
int getElem(SqList L,int i,int *e){
	if(i< 1 || i >L.length){
		return ERROR;
	}
	
	*e = L.elem[i-1];


	return OK; 	 
	
} 

/**************************�Ƚ�Ԫ�ش�С********************************/
int elemCompare(int e,int data){
	if(e>data){
		return TRUE;
	}else{
		return FALSE;
	}	 
	
}

/**************************�Ƚ�Ԫ���Ƿ�********************************/
int equal(int e,int data){
	if(e == data){
		return TRUE;
	}else{
		return FALSE;
	}	 
	
}  

/**************************��ȡ˳����е�һ������ĳ��ֵ��λ��********************************/
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


/**************************��ȡ˳�����ĳ��Ԫ�ص�ǰ��********************************/
int priorElem(SqList L,int elem,int *e){
	int i = 1;
	
	if(L.elem[0]!=elem)				//��һ�������ǰ�� 
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

/**************************��ȡ˳�����ĳ��Ԫ�صĺ��********************************/
int nextElem(SqList L,int elem,int *e){
	int i = 1;
	
	if(L.elem[L.length-1]!=elem)				//������޺�� 
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


/**************************���˳�����Ԫ��********************************/
void clear(SqList *L){
	(*L).length = 0;
}


/**************************����˳���********************************/
void destroy(SqList *L){
	(*L).elem = NULL; 
	(*L).length = 0;
	(*L).listsize = 0;
}

/**************************����˳���ϲ�ȡ����********************************/
void listunion(SqList *leftList,SqList rightList){
	int leftLength, rightLength;
	int i;
	int e;
	
	leftLength = getlength(*leftList);			//��˳����� 
	rightLength = getlength(rightList);
	
	for(i=1; i<=rightLength; i++)
	{
		getElem(rightList, i, &e);				//ȡrightList�е�i��Ԫ�ظ���e 
		int flg = locateElem(*leftList, e, equal);
		if(!flg){ 	//��e����leftList�������
			insertElem(leftList, ++leftLength, e);	
		} 
	}
}
