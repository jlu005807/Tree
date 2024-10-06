#pragma once
#include<iostream>
#include<algorithm>
#include<vector>
#include<queue>//��α���ʱʹ��
#include<functional>

//��ͷ�ļ�Ϊ��ͨ����ʵ�֣���vector�洢����
//�������ĽṹΪ�ݹ�ģ����������ｫ���ݽṹ�Ͷ���Ĳ����ֿ���װ
//��������һ��Tree,�����������Tree,Tree�಻����ռ���������

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
		if (!child||child==this)//������������
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
		auto it = std::find(child_Tree.begin(), child_Tree.end(), child);
		if (it != child_Tree.end())//�ҵ�
		{
			(*it)->parent = nullptr;//����
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
	
	//����һ��dataΪe�����ڵ�
	Tree<T>* CreatTree(T e)
	{
		return new Tree<T>(e);
	}

	//��һ�����鴴��һ�������������ڶ�����
	Tree<T>* CreatTree(T a[], int begin, int number)//begin��������ʼλ��
	{
		if (begin < 0 || begin >= number)
		{
			return nullptr;
		}

		//���ڵ�
		Tree<T>* tree = new Tree<T>(a[begin]);

		//����
		Tree<T>* p = CreatTree(a, begin * 2 + 1, number);
		Tree<T>* q = CreatTree(a, begin * 2 + 2, number);

		if (p != nullptr)
		{
			tree->AddChild(p);
		}

		if (q != nullptr)
		{
			tree->AddChild(q);
		}

		return tree;

	}

	//������һ�������κ����ݵĽڵ㣬��Ϊ�˽ڵ�Ϊ����������
	//�˺���ֻ����tree�ڵ㼰������
	//�����𴴽����ڵ�
	void InitTree(Tree<T>* tree,T e)//��e��ʼ��������tree,����ԭTree,������и��ڵ㲻�ж��븸�ڵ���ϵ��
	{
		if (tree != nullptr)
		{
			//�������
			for (auto it = tree->child_Tree.begin(); it != tree->child_Tree.end(); it++)
			{
				ClearTree(*it);
			}
			tree->child_Tree.clear();

			tree->data = e;//�ı�����

			return;
		}

		//treeΪ�գ�������ʱ,����������
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
		tree->DeleteParent();

		
		//������ʱ�ݹ�������������
		if (tree->child_Tree.size() != 0)
		{
			while (!tree->child_Tree.empty())
			{
				auto it = tree->child_Tree.begin();
				ClearTree((*it));
			}
		}

		//���ٴ˽ڵ�
		delete tree;


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

	//�����������������ұ�,���������ཻ
	void InsertChildTree(Tree<T>* parent, Tree<T>* child)
	{
		//�жϸ��ڵ�������Ƿ�Ϊ��
		if (!parent || !child)
		{
			return;
		}

		//pos�ж�

		//��������и��ڵ���Ҫ�Ƴ�
		child->DeleteParent();
		parent->AddChild(child);
	}
	
	//ɾ����pos�����������pos����parent������Χ�ڣ������������
	void DeleteChildTree(Tree<T>* parent, int pos)
	{
		//����
		if (!parent)
		{
			return;
		}

		//�ڷ�Χ��
		if (pos > 0 && pos <= parent->child_Tree.size())
		{
			//�˲���ֻ�ǽ������ͷ��ÿ�,�����븸�ڵ�
			ClearTree(parent->child_Tree[pos - 1]);
		}

	}

	//ǰ�����
	//����function��һ�����ؿգ��������������,Ĭ��Ϊ���data
	void PreOrderTraverseTree(Tree<T>* tree,/*������*/std::function<void(T&)> address = [](T& e)->void {std::cout << e; })
	{
		//����
		if (!tree)
		{
			return;
		}

		//���ڵ�
		address(tree->data);

		//�ݹ��������
		for (auto it = tree->child_Tree.begin(); it != tree->child_Tree.end(); it++)
		{
			PreOrderTraverseTree(*it);
		}

		return;

	}

	//�������
	void PostOrderTraverseTree(Tree<T>* tree,/*������*/std::function<void(T&)> address = [](T& e)->void {std::cout << e; })
	{
		//����
		if (!tree)
		{
			return;
		}

	
		//�ݹ��������
		for (auto it = tree->child_Tree.begin(); it != tree->child_Tree.end(); it++)
		{
			PostOrderTraverseTree(*it,address);
		}

		//���ڵ�
		address(tree->data);


		return;

	}

	//��ͨ��û���������
	void InOrderTraverseTree(Tree<T>* tree) = delete;

	//�������
	void LevelOrderTraverseTree(Tree<T>* tree,/*������*/std::function<void(T&)> address = [](T& e)->void {std::cout << e; })
	{
		//����
		if (!tree)
		{
			return;
		}

		std::queue<Tree<T>*> trees;
		trees.push(tree);
		while (!trees.empty())
		{
			Tree<T>* now_tree = trees.front();
			trees.pop();
			//����ǰ�ڵ�
			address(now_tree->data);
			//�ɵ�ǰ�ڵ�������������
			for (auto it = now_tree->child_Tree.begin(); it != now_tree->child_Tree.end(); it++)
			{
				trees.push(*it);
			}
		}
		return;
	}

	//�ҵ���һ��ֵΪe�Ľڵ�
	Tree<T>* FindTree(Tree<T>* tree, T e)
	{
		if (!tree)
		{
			return nullptr;
		}

		//�˽ڵ�
		if (tree->data == e)
		{
			return tree;
		}

		for (auto it = tree->child_Tree.begin(); it != tree->child_Tree.end(); it++)
		{
			//��������
			Tree<T>* node = FindTree(*it,e);
			if (node)
			{
				return node;
			}
		}

		//�Ҳ���
		return nullptr;
	}

	//�������ڵ�����
	int TreeNumber(Tree<T>* tree)
	{
		//����
		if (!tree)
		{
			return 0;
		}

		int number = 1;

		for (auto it = tree->child_Tree.begin(); it != tree->child_Tree.end(); it++)
		{
			number += TreeNumber(*it);
		}

		return number;
	}
};