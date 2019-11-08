#include <stdio.h>
#include "sequenceListUtil.cpp"
using namespace std;


int main(){
	SqList L;
	int i;
	int e;
	cout<<"顺序表函数测试..."<<endl;
	cout<<"初始化顺序表函数 initsequencelist 。。。。。。。。。。"<<endl;
	int flg = initsequencelist(&L);
	cout<<flg<<endl;
	
	cout<<"判断顺序表是否为空函数 isempty 测试..."<<endl;
	flg =  isempty(L);
	cout<<flg<<endl;
	
	cout<<"顺序表插入元素函数 insertElem 测试..."<<endl;
	for(int k= 1;k < 6;k++){
		//在哪一个位置插入数据 
		flg =  insertElem(&L,k,2*k);
	} 
	
	cout<<"顺序表使用visit()函数访问测试..."<<endl;
	traverse(L,coutelem); //感觉相当于回调函数 
	
	cout<<"获取顺序表长度 length 测试..."<<endl;
	int length =  getlength(L);
	cout<<length<<endl;
	
	cout<<"删除顺序表中某个元素"<<endl;
	deleteElem(&L,3,&e);
	traverse(L,coutelem);
	
	cout<<"获取顺序表中某个元素"<<endl;
	getElem(L, 2, &e);
	cout<<"该元素值:"<<e<<endl;
	
	cout<<"获取顺序表中第一个大于某个值（8）的位置"<<endl;
	i = locateElem(L, 8, elemCompare);
	cout<<"该元素位置:"<<i<<endl;
	
	cout<<"获取顺序表中某个元素的前驱"<<endl;
	priorElem(L, 8, &e);
	cout<<"该元素位置:"<<e<<endl;
	
	cout<<"获取顺序表中某个元素的后继"<<endl;
	nextElem(L, 8, &e);
	cout<<"该元素位置:"<<e<<endl;
	
	cout<<"清空顺序表中元素"<<endl;
	cout<<"清空顺序表中元素前"<<endl;
	flg =  isempty(L);
	cout<<flg<<endl;
	clear(&L); 
	cout<<"清空顺序表中元素后"<<endl;
	flg =  isempty(L);
	cout<<flg<<endl;
	
	cout<<"销毁顺序表前"<<endl;
	cout<< (L.elem ? "存在":"不存在")<<endl;
	
	destroy(&L);
	
	cout<<"销毁顺序表后"<<endl;
	cout<< (L.elem ? "存在":"不存在")<<endl; 
	return 0; 
}





