#include <iostream>
//reverse linked list
//repeatedly insert next element to the head node 

using namespace std;

typedef struct Node
{
	Node* next;
	int val;
	Node() : val(0), next(NULL) {}
}*LLNode;


LLNode CreateLLNode(int len)
{
	LLNode head = (LLNode)(malloc(sizeof(Node)));
	head->next = NULL;
	head->val = -1;

	LLNode  q, p;
	q = head;
	while (len)
	{
		p = new Node;
		p->val = len;
		q->next = p;
		q = p;
		len--;
	}
	return  head;
}

void ReverseLLNode(LLNode &p)
{
	LLNode head = p;
	LLNode q, r, tmp;
	q = head->next;
	if (q == NULL) return;
	else r = q->next;
	q->next = NULL;
	while (r)
	{
		tmp = r->next;
		head->next = r;
		r->next = q;
		q = r;
		r = tmp;
	}
}
int main() {
	LLNode lk;
	lk = CreateLLNode(5);
	LLNode p = lk->next;
	
	cout << "original" << endl;
	while (p)
	{
		cout << p->val << endl;
		p = p->next;
	}

	ReverseLLNode(lk);

	cout << "reversed" << endl;
	lk = lk->next;
	while (lk)
	{
		cout << lk->val << endl;
		lk = lk->next;
	}

	getchar();
	return 0;
}