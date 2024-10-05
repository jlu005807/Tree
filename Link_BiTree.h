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

	BiTree(T e) :parent(nullptr), leftChild(nullptr), rightChild(nullptr), leftTag(false), rightTag(false), data(e)
	{

	}

	~BiTree() = default;

	void AddleftChild(BiTree<T>* child)//�������,������ԭ�����������˲���Ϊ�ϲ㸺�������������
	{
		if (!child||child == this)//������������
		{
			return;
		}

		//�ϸ�,�˴�Ϊ���ݽṹ���������Ƿ�������ԭ���ڵ㣬�˲���Ϊ�ϲ㸺��
		child->parent = this;

		this->leftChild = child;

	}

	void AddrightChild(BiTree<T>* child)//�������,������ԭ�����������˲���Ϊ�ϲ㸺�������������
	{
		if (!child || child == this)//������������
		{
			return;
		}

		//�ϸ�,�˴�Ϊ���ݽṹ���������Ƿ�������ԭ���ڵ㣬�˲���Ϊ�ϲ㸺��
		child->parent = this;

		this->rightChild = child;

	}

	void AddChild(BiTree<T>* tree,int pos)//posΪ0ʱ������������Ϊ1ʱ����������,��������������
	{
		if (pos == 0)
		{
			AddleftChild(tree);
		}
		else if (pos == 1)
		{
			AddrightChild(tree);
		}
	}

	//���Ӹ��ڵ�
	void AddParent(BiTree<T>* parent,int pos)//posΪ0ʱ������������Ϊ1ʱ����������,��������������
	{
		if (!parent||parent==this)
		{
			return;
		}

		parent->AddChild(this, pos);
	}

	//ɾ������
	void DeleteChild(int pos)
	{
		//�����ǿռ�����
		if (pos == 0)
		{
			if (this->leftChild)
				this->leftChild->parent = nullptr;
			this->leftChild = nullptr;
		}
		else if (pos == 1)
		{
			if (this->rightChild)
				this->rightChild->parent = nullptr;
			this->rightChild = nullptr;
		}
	}

	//ɾ�����ڵ�
	void DeleteParent()
	{
		if (!parent)
		{
			return;
		}
		
		if (parent->leftChild == this)
		{
			parent->DeleteChild(0);
		}

		if (parent->rightChild == this)
		{
			parent->DeleteChild(1);
		}

		return;
	}
	
};

template<class T>
class BiTree_Manager
{
	//����һ��dataΪe�����ڵ�
	BiTree<T>* CreatTree(T e)
	{
		return new BiTree<T>(e);
	}

	//������һ�������κ����ݵĽڵ㣬��Ϊ�˽ڵ�Ϊ����������
	//�˺���ֻ����tree�ڵ㼰������
	//�����𴴽����ڵ�
	void InitTree(BiTree<T>* tree, T e)//��e��ʼ��������tree,����ԭTree,������и��ڵ㲻�ж��븸�ڵ���ϵ��
	{
		if (tree != nullptr)
		{
			//�������
			//������ʱ�ݹ�������������
			if (tree->leftChild)
			{
				ClearTree(tree->leftChild);
			}

			if (tree->rightChild)
			{
				ClearTree(tree->rightChild)l
			}
	

			tree->data = e;//�ı�����

			return;
		}

		//treeΪ�գ�������ʱ,����������
	}

	//�ͷ�������Ϊ����������и��ڵ����ж���ϵ
	void ClearTree(BiTree<T>* tree)
	{
		//�սڵ�ֱ�ӷ���
		if (tree == nullptr)
		{
			return;
		}

		//������У��ж��븸�ڵ���ϵ
		tree->DeleteParent();


		//������ʱ�ݹ�������������
		if (tree->leftChild)
		{
			ClearTree(tree->leftChild);
		}

		if (tree->rightChild)
		{
			ClearTree(tree->rightChild)l
		}

		//���ٴ˽ڵ�
		delete tree;

		//�ÿ�
		tree = nullptr;

		return;

	}
};