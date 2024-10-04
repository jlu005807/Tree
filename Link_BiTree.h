#pragma once
//��ʽ������
#include<iostream>


//ͬCommon_Treeһ��
//�������ĽṹΪ�ݹ�ģ����������ｫ���ݽṹ�Ͷ���Ĳ����ֿ���װ
//��������һ��BiTree,�����������BiTree,BiTree�಻����ռ���������

template<class T>
class BiTree
{
public:
	T data;//����

	BiTree<T>* parent;//���ڵ�
	BiTree<T>* leftChild;//������
	BiTree<T>* rightChild;//������

	//���������Ƿ�Ϊ����
	bool leftTag;
	bool rightTag;

	BiTree() = default;

	BiTree(T e) :parent(nullptr), leftChild(nullptr), rightChild(nullptr), leftTag(false), rightTag(false);

	~BiTree() = default;

	void AddleftChild(Tree<T>* child)//�������,������ԭ�����������˲���Ϊ�ϲ㸺�������������
	{
		if (!child||child == this)//������������
		{
			return;
		}

		//�ϸ�,�˴�Ϊ���ݽṹ���������Ƿ�������ԭ���ڵ㣬�˲���Ϊ�ϲ㸺��
		child->parent = this;

		this->leftChild = child;

	}

	

};