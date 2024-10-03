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

	~Tree()
	{
		
	}

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



};


template<class T>
class Tree_Manager//管理树的类，即包含对树的操作
{
public:

	void InitTree(Tree<T>* tree)//初始化一个不存任何数据的节点，但不切断与父节点联系
	{
		if (!tree)//为空
		{
			tree = new Tree<T>();
			return;
		}
		
		delete
	}
	
	void InitTree(Tree<T>* tree,T e)//以e初始化tree一个节点,覆盖原Tree,但不切断与父节点联系
	{
		if (tree != nullptr)
		{

		}


		return std::make_unique<Tree<T>>(new Tree(e));
	}


	void ClearTree(Tree<T>* tree)
	{
		//空节点直接返回
		if (tree == nullptr)
		{
			return;
		}

		//切断与父节点联系
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
		return;

	}

};