#include <stdio.h>
#include "sequenceListUtil.cpp"
using namespace std;


int main(){
	SqList L;
	int i;
	int e;
	cout<<"˳���������..."<<endl;
	cout<<"��ʼ��˳����� initsequencelist ��������������������"<<endl;
	int flg = initsequencelist(&L);
	cout<<flg<<endl;
	
	cout<<"�ж�˳����Ƿ�Ϊ�պ��� isempty ����..."<<endl;
	flg =  isempty(L);
	cout<<flg<<endl;
	
	cout<<"˳������Ԫ�غ��� insertElem ����..."<<endl;
	for(int k= 1;k < 6;k++){
		//����һ��λ�ò������� 
		flg =  insertElem(&L,k,2*k);
	} 
	
	cout<<"˳���ʹ��visit()�������ʲ���..."<<endl;
	traverse(L,coutelem); //�о��൱�ڻص����� 
	
	cout<<"��ȡ˳����� length ����..."<<endl;
	int length =  getlength(L);
	cout<<length<<endl;
	
	cout<<"ɾ��˳�����ĳ��Ԫ��"<<endl;
	deleteElem(&L,3,&e);
	traverse(L,coutelem);
	
	cout<<"��ȡ˳�����ĳ��Ԫ��"<<endl;
	getElem(L, 2, &e);
	cout<<"��Ԫ��ֵ:"<<e<<endl;
	
	cout<<"��ȡ˳����е�һ������ĳ��ֵ��8����λ��"<<endl;
	i = locateElem(L, 8, elemCompare);
	cout<<"��Ԫ��λ��:"<<i<<endl;
	
	cout<<"��ȡ˳�����ĳ��Ԫ�ص�ǰ��"<<endl;
	priorElem(L, 8, &e);
	cout<<"��Ԫ��λ��:"<<e<<endl;
	
	cout<<"��ȡ˳�����ĳ��Ԫ�صĺ��"<<endl;
	nextElem(L, 8, &e);
	cout<<"��Ԫ��λ��:"<<e<<endl;
	
	cout<<"���˳�����Ԫ��"<<endl;
	cout<<"���˳�����Ԫ��ǰ"<<endl;
	flg =  isempty(L);
	cout<<flg<<endl;
	clear(&L); 
	cout<<"���˳�����Ԫ�غ�"<<endl;
	flg =  isempty(L);
	cout<<flg<<endl;
	
	cout<<"����˳���ǰ"<<endl;
	cout<< (L.elem ? "����":"������")<<endl;
	
	destroy(&L);
	
	cout<<"����˳����"<<endl;
	cout<< (L.elem ? "����":"������")<<endl; 
	return 0; 
}





