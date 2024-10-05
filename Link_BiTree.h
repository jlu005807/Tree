#pragma once
//链式二叉树
#include<iostream>


//同Common_Tree一般
//基于树的结构为递归的，所以在这里将数据结构和对其的操作分开封装
//当创建了一个BiTree,必须最后销毁BiTree,BiTree类不负责空间分配和销毁

template<class T>
class BiTree
{
public:
	T data;//数据

	BiTree<T>* parent;//父节点
	BiTree<T>* leftChild;//左子树
	BiTree<T>* rightChild;//右子树

	//左右子树是否为线索
	bool leftTag;
	bool rightTag;

	BiTree() = default;

	BiTree(T e) :parent(nullptr), leftChild(nullptr), rightChild(nullptr), leftTag(false), rightTag(false), data(e)
	{

	}

	~BiTree() = default;

	void AddleftChild(BiTree<T>* child)//添加子树,不考虑原本左子树，此操作为上层负责，则操作无意义
	{
		if (!child||child == this)//空树或者自身
		{
			return;
		}

		//认父,此处为数据结构，不考虑是否子树有原父节点，此操作为上层负责
		child->parent = this;

		this->leftChild = child;

	}

	void AddrightChild(BiTree<T>* child)//添加子树,不考虑原本左子树，此操作为上层负责，则操作无意义
	{
		if (!child || child == this)//空树或者自身
		{
			return;
		}

		//认父,此处为数据结构，不考虑是否子树有原父节点，此操作为上层负责
		child->parent = this;

		this->rightChild = child;

	}

	void AddChild(BiTree<T>* tree,int pos)//pos为0时增加左子树，为1时增加右子树,其他操作无意义
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

	//增加父节点
	void AddParent(BiTree<T>* parent,int pos)//pos为0时增加左子树，为1时增加右子树,其他操作无意义
	{
		if (!parent||parent==this)
		{
			return;
		}

		parent->AddChild(this, pos);
	}

	//删除子树
	void DeleteChild(int pos)
	{
		//不考虑空间问题
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

	//删除父节点
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
	//创建一个data为e的树节点
	BiTree<T>* CreatTree(T e)
	{
		return new BiTree<T>(e);
	}

	//不考虑一个不存任何数据的节点，认为此节点为空树无意义
	//此函数只负责tree节点及其子树
	//不负责创建树节点
	void InitTree(BiTree<T>* tree, T e)//以e初始化或重置tree,覆盖原Tree,但如果有父节点不切断与父节点联系。
	{
		if (tree != nullptr)
		{
			//清空子树
			//有子树时递归销毁销毁子树
			if (tree->leftChild)
			{
				ClearTree(tree->leftChild);
			}

			if (tree->rightChild)
			{
				ClearTree(tree->rightChild)l
			}
	

			tree->data = e;//改变数据

			return;
		}

		//tree为空，即空树时,操作无意义
	}

	//释放整棵树为空树，如果有父节点则切断联系
	void ClearTree(BiTree<T>* tree)
	{
		//空节点直接返回
		if (tree == nullptr)
		{
			return;
		}

		//（如果有）切断与父节点联系
		tree->DeleteParent();


		//有子树时递归销毁销毁子树
		if (tree->leftChild)
		{
			ClearTree(tree->leftChild);
		}

		if (tree->rightChild)
		{
			ClearTree(tree->rightChild)l
		}

		//销毁此节点
		delete tree;

		//置空
		tree = nullptr;

		return;

	}
};