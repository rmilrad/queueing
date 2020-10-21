#include <iostream>
#include <iomanip>
#include <string>
#include <ostream>
#include <string.h>
using namespace std;

class node {
public:
	int priority;
	node* prev, * next;
};

class queue {
public:
	queue();
	~queue();
	queue(const queue& q);
	void enqueue(int);
	void dequeue();
	void print();
private:
	node* front;
};

queue::queue() {
	front = 0;
}

queue::~queue() {
	node* p = front;	
	while (p != front) {
		p = p->next;
	}

	while (p != front) {
		p->next = front->next;
		delete front;
		front = p->next;
	}

	if (p == front) {
		delete front;
		front = nullptr;
	}
}

queue::queue(const queue& q) {
	front = 0;
	if (q.front == NULL) {
		return;
	}
	
	node* helper = q.front;
	node* temp = new node;

	temp->priority = q.front->priority;
	front = temp;
	front->next = front;
	front->prev = front;
	helper = helper->next;
	if (helper == q.front) {
		return;
	}
	node* current = front;
	while (helper != q.front) {
		node* p = new node;
		p->priority = helper->priority;
		p->next = front;
		p->prev = current;
		current->next = p;
		front->prev = p;
		current = p;
		helper = helper->next;
	}
}

void queue::enqueue(int num) {
	if (front == 0) {
		node* temp = new node;
		temp->priority = num;
		temp->next = temp;
		temp->prev = temp;
		front = temp;
	}
	else {
		node* temp = new node;
		temp->priority = num;
		temp->next = front;
		front->prev->next = temp;
		temp->prev = front->prev;
		front->prev = temp;
	}
}

void queue::dequeue() {
	if (front == 0) {
		cout << "no nodes left to dequeue" << endl;
		front = 0;
		return;
	}
	if (front->next == front) {
		delete front;
		front = 0;
		return;
	}
	node* temp = front;
	front->next->prev = front->prev;
	front->prev->next = front->next;
	front = front->next;
	delete temp;
}

void queue::print() {
	node* current = front;
	if (front == 0) {
		cout << "No nodes left in queue" << endl;
		return;
	}
	if (front->next == front) {
		cout << front->priority << endl;
		return;
	}
	else {
		cout << front->priority << " ";
		current = current->next;
		while (current != front) {
			cout << current->priority << " ";
			current = current->next;
		}
	}
	cout << endl;
}

int main()
{
	queue k;
	k.enqueue(60);
	k.print();
	k.enqueue(20);
	k.enqueue(30);
	k.print();
	k.enqueue(10);
	k.print();
	k.enqueue(50);
	k.enqueue(40);
	k.print();
	queue j = k;
	j.dequeue();
	j.print();
	j.dequeue();
	j.dequeue();
	j.dequeue();
	j.print();
	j.dequeue();
	j.dequeue();
	j.print();
	j.dequeue();
	j.dequeue();
	return 0;
}