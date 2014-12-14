
#include <iostream>
using namespace std;

struct red {
	element popis[10000];
	int front;
	int rear;
};

int AddOne(int n){
	return ((n+1) % 10000);
}

bool IsEmptyQ(red *Q){
	if(AddOne(Q->rear) == Q->front) return true;
	return false;
}

element FrontQ(red *Q){
	if (IsEmptyQ(Q)){
		cout << "(FrontQ) - Red je prazan" << endl;
	}
	else return Q->popis[Q->front];
}

void EnQueueQ(element x, red *Q){
	Q->rear = AddOne(Q->rear);
	Q->popis[Q->rear] = x;
}

void DeQueueQ(red *Q){
	if(IsEmptyQ(Q)) return;
//	if(Q->front == 9999) Q->front = 0;
//	Q->front++;
	Q->front = AddOne(Q->front);
}

red *InitQ(){
	red *n = new red;
	n->front=0;
	n->rear=9999;
	return n;
}

