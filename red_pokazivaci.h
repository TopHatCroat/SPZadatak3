#include <iostream>
using namespace std;

struct r {
	element popis;
	r *next;
};

struct red {
	r *front;
	r *rear;
};

bool IsEmptyQ(red *Q){
	return Q->rear == Q->front;
}

element FrontQ(red *Q){
	if (IsEmptyQ(Q)){
		cout << "(FrontQ) - Red je prazan" << endl;
	}	
	else return Q->front->next->popis;
}

void EnQueueQ(element x, red *Q){
	r *n = new r;
	n->next = NULL;
	n->popis = x;
	Q->rear->next = n;
	Q->rear = n;
	
}

void DeQueueQ(red *Q){
	r *d = new r;
	d = Q->front;
	Q->front = Q->front->next;
	delete d;
}

red *InitQ(){
	red *n = new red;
	r *novi = new r;
	n->front = novi;
	n->rear = novi;
	return n;
}
