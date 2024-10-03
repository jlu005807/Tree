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

	~Tree() = default;

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

	
	//���пռ��ͷ����ϲ����,��������˲���
	////�ͷ����������ռ�
	//void Clear_ChildTree()
	//{
	//	//�����ͷſռ䲢���ÿ�
	//	for (auto it = this->child_Tree.begin(); it != this->child_Tree.end(); it++)
	//	{
	//		auto p = *it;
	//		*it = nullptr;

	//		delete p;
	//	}
	//	//���Child_Tree
	//	this->child_Tree.clear();

	//}

	//ע�����ĸ��ڵ����ϲ�����

};


template<class T>
class Tree_Manager//���������࣬�����������Ĳ���
{
public:

	//������һ�������κ����ݵĽڵ㣬��Ϊ�˽ڵ�Ϊ����������
	//�˺���ֻ����tree�ڵ㼰������
	void InitTree(Tree<T>* tree,T e)//��e��ʼ��������tree,����ԭTree,������и��ڵ㲻�ж��븸�ڵ���ϵ��
	{
		if (tree != nullptr)
		{
			tree->Clear_ChildTree();//�������
			tree->data = e;//�ı�����
		}

		//treeΪ�գ�������ʱ,�������ڵ�
		tree = new Tree<T>(e);
	}

	//�ͷ�������Ϊ����������и��ڵ����ж���ϵ
	void ClearTree(Tree<T>* tree)
	{
		//�սڵ�ֱ�ӷ���
		if (tree == nullptr)
		{
			return;
		}

		//������У��ж��븸�ڵ���ϵ
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

		//�ÿ�
		tree = nullptr;

		return;

	}


	//�ж��Ƿ�Ϊ����
	bool TreeEmpty(Tree<T>* tree)
	{
		if (tree)
		{
			return false;
		}

		return true;
	}

	//����Tree�����
	int TreeDepth(Tree<T>* tree)
	{
		//����
		if (!tree)
		{
			return 0;
		}

		//ֻ�и��ڵ�
		if (tree->child_Tree.empty())
		{
			return 1;
		}

		//�ݹ����������
		std::vector<int> depth;
		for (int i = 0; i < tree->child_Tree.size(); i++)
		{
			depth.push_back(TreeDepth(tree->child_Tree[i]));
		}

		//�����ֵ������������
		auto max = std::max_element(depth.begin(), depth.end());

		return *max + 1;

	}

	//���ظ��ڵ�
	Tree<T>* RootTree(Tree<T>* tree)
	{
		//����
		if (!tree)
		{
			return nullptr;
		}

		//Ϊ���ڵ�
		if (tree->parent == nullptr)
		{
			return tree;
		}

		//���Ǹ��ڵ������ϵݹ�
		return RootTree(tree->parent);

	}

	T ValueTree(Tree<T>* tree)
	{
		if (tree)
		{
			return tree->data;
		}
		else
		{
			//Ϊ��ʱ
			return NULL;
		}
	}

	//��������
	void AssignTree(Tree<T>* tree, T e)
	{
		//����
		if (!tree)
		{
			return;
		}

		tree->data = e;
		return;
	}

	//���ظ��ڵ�
	Tree<T>* ParentTree(Tree<T>* tree)
	{
		//����
		if (!tree)
		{
			return nullptr;
		}

		//Ϊ���ڵ�ʱ����nullptr
		return tree->parent;
	}

	//������������
	Tree<T>* LeftChildTree(Tree<T>* tree)
	{
		//����
		if (!tree)
		{
			return nullptr;
		}

		//������
		if (tree->child_Tree.empty())
		{
			return nullptr;
		}

		return tree->child_Tree[0];
	}

	//��������������ע��������������������ͬ
	Tree<T>* RightChildTree(Tree<T>* tree)
	{
		//����
		if (!tree)
		{
			return nullptr;
		}

		//������
		if (tree->child_Tree.empty())
		{
			return nullptr;
		}

		return tree->child_Tree[tree->child_Tree.size()-1];
	}

	//�����pos�����������pos����parent������Χ�ڣ���������ұ�
	void InsertChildTree(Tree<T>* parent, Tree<T>* child, int pos)
	{
		//�жϸ��ڵ�������Ƿ�Ϊ��
		if (!parent || !child)
		{
			return;
		}

		//pos�ж�
		if (pos<1 || pos>parent->child_Tree.size())//�������ұ�
		{
			parent->AddChild(child);
		}

		child->parent = parent;

		//����ԭλ������
		ClearTree(parent->child_Tree[pos]);
		parent->child_Tree[pos] = child;
	}
	
	//ɾ����pos�����������pos����parent������Χ�ڣ������������
	void DeleteChildTree(Tree<T>* parent, int pos)
	{
		//����
		if (!tree)
		{
			return;
		}

		//�ڷ�Χ��
		if (pos > 0 && pos <= parent->child_Tree.size())
		{
			//�˲���ֻ�ǽ������ͷ��ÿ�
			ClearTree(parent->child_Tree[pos - 1]);
			//��Child_Tree��ɾ��
			auto it = parent->child_Tree.begin() + pos - 1;
			parent->child_Tree.erase(it);
		}

	}
};