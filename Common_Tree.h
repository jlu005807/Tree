#pragma once
#include<iostream>
#include<algorithm>
#include<vector>

//��ͷ�ļ�Ϊ��ͨ����ʵ�֣���vector�洢����
//�������ĽṹΪ�ݹ�ģ����������ｫ���ݽṹ�Ͷ���Ĳ����ֿ���װ
//��������һ��Tree,�����������Tree

template<class T>
struct Tree
{
public:
	T data;//������
	Tree<T>* parent;//���ڵ�
	std::vector<Tree<T>*>child_Tree;//����  


	Tree() = default;

	Tree(T e)
	{
		parent = nullptr;
		this->data = e;
	}

	~Tree()
	{
		
	}

	//�����ĵ�����

	void AddChild(Tree<T>* child)//�������
	{
		if (!child&&child==this)//������������
		{
			return;
		}

		//�ϸ�
		child->parent = this;

		//δ��ӹ�
		auto it = std::find(child_Tree.begin(),child_Tree.end(),child);
		if (it == child_Tree.end())
		{
			child_Tree.push_back(child);
		}

	}

	//���Ӹ��ڵ�
	void AddParent(Tree<T>* parent)
	{
		if (parent&&parent!=this)//�ǿղ��Ҳ�������
		{
			parent->AddChild(this);
		}
	}
	
	//ɾ������

	//ɾ������
	void DeleteChild(Tree<T>* child)
	{
		if (!child)//����
		{
			return;
		}

		//Ѱ������
		auto it = this->child_Tree.std::find(child_Tree.begin(), child_Tree.end(), child);
		if (it != child_Tree.end())//�ҵ�
		{
			*it->parent = nullptr;//����
			this->child_Tree.erase(it);
		}

	}

	//���븸�ڵ�
	void DeleteParent()
	{
		//�и��ڵ�
		if (this->parent)
		{
			parent->DeleteChild(this);
		}
	}



};


template<class T>
class Tree_Manager//���������࣬�����������Ĳ���
{
public:

	void InitTree(Tree<T>* tree)//��ʼ��һ�������κ����ݵĽڵ㣬�����ж��븸�ڵ���ϵ
	{
		if (!tree)//Ϊ��
		{
			tree = new Tree<T>();
			return;
		}
		
		delete
	}
	
	void InitTree(Tree<T>* tree,T e)//��e��ʼ��treeһ���ڵ�,����ԭTree,�����ж��븸�ڵ���ϵ
	{
		if (tree != nullptr)
		{

		}


		return std::make_unique<Tree<T>>(new Tree(e));
	}


	void ClearTree(Tree<T>* tree)
	{
		//�սڵ�ֱ�ӷ���
		if (tree == nullptr)
		{
			return;
		}

		//�ж��븸�ڵ���ϵ
		if (tree->parent)
		{
			tree->parent->child_Tree.std::remove(tree->parent->child_Tree.begin(), tree->parent->child_Tree.end(), tree);
		}

		
		//������ʱ�ݹ�������������
		if (tree->child_Tree.size() ��= 0)
		{
			for (int i = 0; i < tree->child_Tree.size(); i++)
			{
				ClearTree(tree->child_Tree[i]);
			}
		}

		//���ٴ˽ڵ�
		delete tree;
		return;

	}

};