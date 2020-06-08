#include "function.h"

//��ʼ������
void InitQueue(LinkQueue& Q) {
	Q.front = Q.rear = (LinkNode*)malloc(sizeof(LinkNode));
	Q.front->next = NULL;
}

//�����п�
bool IsEmpty(LinkQueue Q) {
	if (Q.front == Q.rear)
		return true;
	else
		return false;
}

//�����
void EnQueue(LinkQueue& Q, ElemType x) {
	LinkNode* s = (LinkNode*)malloc(sizeof(LinkNode));
	s->data = x; //β�巨��������һ������
	s->next = NULL;
	Q.rear->next = s;
	Q.rear = s;
}

//������(ͷ��ɾ����)
bool DeQueue(LinkQueue& Q, ElemType& x) {
	if (Q.front == Q.rear) {
		return false; //ͷβָ�����ʱ������Ϊ��
	}
	LinkNode* p = Q.front->next; //�¶���һ��ָ��pָ��ͷ�����һ����ͷ���û�д����ݣ���һ�����У�
	x = p->data;
	Q.front->next = p->next; //����
	if (p == Q.rear) { //��p��Q.rearָ��ͬһλ�õ�ʱ��˵���ӿգ���Ҫ��front��rear��ʼ��
		Q.rear = Q.front;
	}
	free(p);
	return true;
}
