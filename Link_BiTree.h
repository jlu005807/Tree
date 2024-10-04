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

	BiTree(T e) :parent(nullptr), leftChild(nullptr), rightChild(nullptr), leftTag(false), rightTag(false);

	~BiTree() = default;

	void AddleftChild(Tree<T>* child)//添加子树,不考虑原本左子树，此操作为上层负责，则操作无意义
	{
		if (!child||child == this)//空树或者自身
		{
			return;
		}

		//认父,此处为数据结构，不考虑是否子树有原父节点，此操作为上层负责
		child->parent = this;

		this->leftChild = child;

	}

	

};