#pragma once
#include<iostream>
#include<algorithm>
#include<vector>

//此头文件为普通树的实现，用vector存储子树
//基于树的结构为递归的，所以在这里将数据结构和对其的操作分开封装
//当创建了一个Tree,必须最后销毁Tree

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
		if (!child&&child==this)//空树或者自身
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
		auto it = this->child_Tree.std::find(child_Tree.begin(), child_Tree.end(), child);
		if (it != child_Tree.end())//找到
		{
			*it->parent = nullptr;//脱离
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

	//不考虑一个不存任何数据的节点，认为此节点为空树无意义
	//此函数只负责tree节点及其子树
	void InitTree(Tree<T>* tree,T e)//以e初始化或重置tree,覆盖原Tree,但如果有父节点不切断与父节点联系。
	{
		if (tree != nullptr)
		{
			tree->Clear_ChildTree();//清空子树
			tree->data = e;//改变数据
		}

		//tree为空，即空树时,创建根节点
		tree = new Tree<T>(e);
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
		if (tree->parent)
		{
			tree->parent->child_Tree.std::remove(tree->parent->child_Tree.begin(), tree->parent->child_Tree.end(), tree);
		}

		
		//有子树时递归销毁销毁子树
		if (tree->child_Tree.size() ！= 0)
		{
			for (int i = 0; i < tree->child_Tree.size(); i++)
			{
				ClearTree(tree->child_Tree[i]);
			}
		}

		//销毁此节点
		delete tree;

		//置空
		tree = nullptr;

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

	//插入第pos棵子树，如果pos不在parent子树范围内，则插入最右边
	void InsertChildTree(Tree<T>* parent, Tree<T>* child, int pos)
	{
		//判断父节点和子树是否为空
		if (!parent || !child)
		{
			return;
		}

		//pos判断
		if (pos<1 || pos>parent->child_Tree.size())//插入最右边
		{
			parent->AddChild(child);
		}

		child->parent = parent;

		//覆盖原位置子树
		ClearTree(parent->child_Tree[pos]);
		parent->child_Tree[pos] = child;
	}
	
	//删除第pos棵子树，如果pos不在parent子树范围内，则操作无意义
	void DeleteChildTree(Tree<T>* parent, int pos)
	{
		//空树
		if (!tree)
		{
			return;
		}

		//在范围内
		if (pos > 0 && pos <= parent->child_Tree.size())
		{
			//此操作只是将子树释放置空
			ClearTree(parent->child_Tree[pos - 1]);
			//从Child_Tree中删除
			auto it = parent->child_Tree.begin() + pos - 1;
			parent->child_Tree.erase(it);
		}

	}
};