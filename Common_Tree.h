#pragma once
#include<iostream>
#include<algorithm>
#include<vector>
#include<queue>//层次遍历时使用
#include<functional>

//此头文件为普通树的实现，用vector存储子树
//基于树的结构为递归的，所以在这里将数据结构和对其的操作分开封装
//当创建了一个Tree,必须最后销毁Tree,Tree类不负责空间分配和销毁

template<class T>
struct Tree
{
public:
	T data;//数据域
	Tree<T>* parent;//父节点
	std::vector<Tree<T>*>child_Tree;//子树  


	Tree() = default;

	Tree(T e)
	{
		parent = nullptr;
		this->data = e;
	}

	~Tree() = default;

	//树结点的的连接

	void AddChild(Tree<T>* child)//添加子树
	{
		if (!child||child==this)//空树或者自身
		{
			return;
		}

		//认父
		child->parent = this;

		//未添加过
		auto it = std::find(child_Tree.begin(),child_Tree.end(),child);
		if (it == child_Tree.end())
		{
			child_Tree.push_back(child);
		}

	}

	//连接父节点
	void AddParent(Tree<T>* parent)
	{
		if (parent&&parent!=this)//非空并且不是自身
		{
			parent->AddChild(this);
		}
	}
	
	//删除连接

	//删除子树
	void DeleteChild(Tree<T>* child)
	{
		if (!child)//空树
		{
			return;
		}

		//寻找子树
		auto it = std::find(child_Tree.begin(), child_Tree.end(), child);
		if (it != child_Tree.end())//找到
		{
			(*it)->parent = nullptr;//脱离
			this->child_Tree.erase(it);
		}

	}

	//脱离父节点
	void DeleteParent()
	{
		//有父节点
		if (this->parent)
		{
			parent->DeleteChild(this);
		}
	}

	
	//所有空间释放由上层管理,因此舍弃此操作
	////释放所有子树空间
	//void Clear_ChildTree()
	//{
	//	//遍历释放空间并且置空
	//	for (auto it = this->child_Tree.begin(); it != this->child_Tree.end(); it++)
	//	{
	//		auto p = *it;
	//		*it = nullptr;

	//		delete p;
	//	}
	//	//清空Child_Tree
	//	this->child_Tree.clear();

	//}

	//注意树的根节点由上层析构

};


template<class T>
class Tree_Manager//管理树的类，即包含对树的操作
{
public:
	
	//创建一个data为e的树节点
	Tree<T>* CreatTree(T e)
	{
		return new Tree<T>(e);
	}

	//以一个数组创造一棵树，并类似于二叉树
	Tree<T>* CreatTree(T a[], int begin, int number)//begin即数组起始位置
	{
		if (begin < 0 || begin >= number)
		{
			return nullptr;
		}

		//根节点
		Tree<T>* tree = new Tree<T>(a[begin]);

		//子树
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

	//不考虑一个不存任何数据的节点，认为此节点为空树无意义
	//此函数只负责tree节点及其子树
	//不负责创建树节点
	void InitTree(Tree<T>* tree,T e)//以e初始化或重置tree,覆盖原Tree,但如果有父节点不切断与父节点联系。
	{
		if (tree != nullptr)
		{
			//清空子树
			for (auto it = tree->child_Tree.begin(); it != tree->child_Tree.end(); it++)
			{
				ClearTree(*it);
			}
			tree->child_Tree.clear();

			tree->data = e;//改变数据

			return;
		}

		//tree为空，即空树时,操作无意义
	}

	//释放整棵树为空树，如果有父节点则切断联系
	void ClearTree(Tree<T>* tree)
	{
		//空节点直接返回
		if (tree == nullptr)
		{
			return; 
		}

		//（如果有）切断与父节点联系
		tree->DeleteParent();

		
		//有子树时递归销毁销毁子树
		if (tree->child_Tree.size() != 0)
		{
			while (!tree->child_Tree.empty())
			{
				auto it = tree->child_Tree.begin();
				ClearTree((*it));
			}
		}

		//销毁此节点
		delete tree;


		return;

	}


	//判断是否为空树
	bool TreeEmpty(Tree<T>* tree)
	{
		if (tree)
		{
			return false;
		}

		return true;
	}

	//返回Tree的深度
	int TreeDepth(Tree<T>* tree)
	{
		//空树
		if (!tree)
		{
			return 0;
		}

		//只有根节点
		if (tree->child_Tree.empty())
		{
			return 1;
		}

		//递归找子树深度
		std::vector<int> depth;
		for (int i = 0; i < tree->child_Tree.size(); i++)
		{
			depth.push_back(TreeDepth(tree->child_Tree[i]));
		}

		//找最大值即子树最大深度
		auto max = std::max_element(depth.begin(), depth.end());

		return *max + 1;

	}

	//返回根节点
	Tree<T>* RootTree(Tree<T>* tree)
	{
		//空树
		if (!tree)
		{
			return nullptr;
		}

		//为根节点
		if (tree->parent == nullptr)
		{
			return tree;
		}

		//不是根节点则向上递归
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
			//为空时
			return NULL;
		}
	}

	//更改数据
	void AssignTree(Tree<T>* tree, T e)
	{
		//空树
		if (!tree)
		{
			return;
		}

		tree->data = e;
		return;
	}

	//返回父节点
	Tree<T>* ParentTree(Tree<T>* tree)
	{
		//空树
		if (!tree)
		{
			return nullptr;
		}

		//为根节点时返回nullptr
		return tree->parent;
	}

	//返回最左子树
	Tree<T>* LeftChildTree(Tree<T>* tree)
	{
		//空树
		if (!tree)
		{
			return nullptr;
		}

		//无子树
		if (tree->child_Tree.empty())
		{
			return nullptr;
		}

		return tree->child_Tree[0];
	}

	//返回最右子树，注意最左最右子树可能相同
	Tree<T>* RightChildTree(Tree<T>* tree)
	{
		//空树
		if (!tree)
		{
			return nullptr;
		}

		//无子树
		if (tree->child_Tree.empty())
		{
			return nullptr;
		}

		return tree->child_Tree[tree->child_Tree.size()-1];
	}

	//插入子树，插入最右边,两棵树不相交
	void InsertChildTree(Tree<T>* parent, Tree<T>* child)
	{
		//判断父节点和子树是否为空
		if (!parent || !child)
		{
			return;
		}

		//pos判断

		//如果子树有父节点需要移除
		child->DeleteParent();
		parent->AddChild(child);
	}
	
	//删除第pos棵子树，如果pos不在parent子树范围内，则操作无意义
	void DeleteChildTree(Tree<T>* parent, int pos)
	{
		//空树
		if (!parent)
		{
			return;
		}

		//在范围内
		if (pos > 0 && pos <= parent->child_Tree.size())
		{
			//此操作只是将子树释放置空,并脱离父节点
			ClearTree(parent->child_Tree[pos - 1]);
		}

	}

	//前序遍历
	//这里function不一定返回空，具体视情况而立,默认为输出data
	void PreOrderTraverseTree(Tree<T>* tree,/*处理函数*/std::function<void(T&)> address = [](T& e)->void {std::cout << e; })
	{
		//空树
		if (!tree)
		{
			return;
		}

		//根节点
		address(tree->data);

		//递归遍历子树
		for (auto it = tree->child_Tree.begin(); it != tree->child_Tree.end(); it++)
		{
			PreOrderTraverseTree(*it);
		}

		return;

	}

	//后序遍历
	void PostOrderTraverseTree(Tree<T>* tree,/*处理函数*/std::function<void(T&)> address = [](T& e)->void {std::cout << e; })
	{
		//空树
		if (!tree)
		{
			return;
		}

	
		//递归遍历子树
		for (auto it = tree->child_Tree.begin(); it != tree->child_Tree.end(); it++)
		{
			PostOrderTraverseTree(*it,address);
		}

		//根节点
		address(tree->data);


		return;

	}

	//普通树没有中序遍历
	void InOrderTraverseTree(Tree<T>* tree) = delete;

	//层序遍历
	void LevelOrderTraverseTree(Tree<T>* tree,/*处理函数*/std::function<void(T&)> address = [](T& e)->void {std::cout << e; })
	{
		//空树
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
			//处理当前节点
			address(now_tree->data);
			//吧当前节点的子树放入队列
			for (auto it = now_tree->child_Tree.begin(); it != now_tree->child_Tree.end(); it++)
			{
				trees.push(*it);
			}
		}
		return;
	}

	//找到第一个值为e的节点
	Tree<T>* FindTree(Tree<T>* tree, T e)
	{
		if (!tree)
		{
			return nullptr;
		}

		//此节点
		if (tree->data == e)
		{
			return tree;
		}

		for (auto it = tree->child_Tree.begin(); it != tree->child_Tree.end(); it++)
		{
			//从子树找
			Tree<T>* node = FindTree(*it,e);
			if (node)
			{
				return node;
			}
		}

		//找不到
		return nullptr;
	}

	//返回树节点数量
	int TreeNumber(Tree<T>* tree)
	{
		//空树
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