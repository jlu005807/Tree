#pragma once
//因为利用顺序表存放数据结构树局限过多，并且仅仅适用于完全二叉树，仅仅实现简陋完全二叉树的顺序实现，不考虑内存扩展和拷贝赋值,清理树
#include<iostream>
#include<vector>
#include<functional>
#include<cmath>

template<class T>
class Complete_BiTree
{
public:
	std::vector<T> tree;

	Complete_BiTree() = default;

	Complete_BiTree(T a[], int n)
	{
		InitBiTree(a,n);
	}

	//因为是完全二叉树，只插入最后
	void InsertTree(T value)
	{
		tree.push_back(value);
	}

	//因为是完全二叉树，只删除最后
	void DeleteTree()
	{
		tree.pop_back();
	}

	//判断索引
	bool IsIndex(int index)
	{
		if (index < 0 || index >= tree.size())
		{
			return false;
		}
		return true;
	}

	//获得节点值,默认树的索引从零开始
	T GetTreeValue(int index)const
	{
		
		if (!IsIndex(index))
		{
			throw std::out_of_range("Index is out of range");
		}

		return tree[index];
	}

	//父节点索引，不检查错误，即不检查是否为求根节点的父节点
	int ParentTree(int index)
	{
		return (index-1)/2; 
	}


	//左子树索引
	int LeftChild(int index)
	{
		return 2 * index + 1;
	}

	//右子树索引
	int RightChild(int index)
	{
		return 2 * index + 2;
	}

	//树的深度
	int TreeDepth()
	{
		if (tree.empty())
			return 0;
		else return static_cast<int>((std::log2(tree.size()) + 1));
	}

	//后序遍历
	void PostOrderTraverseTree(int index,/*处理函数*/std::function<void(T&)> address = [](T& e)->void {std::cout << e; })
	{
		//开始索引错误
		if (!IsIndex(index))
		{
			return;
		}
		
		//遍历左子树
		PostOrderTraverseTree(index * 2 + 1,address);

		//遍历右子树
		PostOrderTraverseTree(index * 2 + 2,address);

		//根节点
		address(tree[index]);

		return;
	}

	//前序遍历
	void PreOrderTraverseTree(int index,/*处理函数*/std::function<void(T&)> address = [](T& e)->void {std::cout << e; })
	{
		//开始索引错误
		if (!IsIndex(index))
		{
			return;
		}

		//根节点
		address(tree[index]);

		//遍历左子树
		PreOrderTraverseTree(index * 2 + 1,address);

		//遍历右子树
		PreOrderTraverseTree(index * 2 + 2,address);

		return;
	}

	//中序遍历
	void InOrderTraverseTree(int index,/*处理函数*/std::function<void(T&)> address = [](T& e)->void {std::cout << e; })
	{
		//开始索引错误
		if (!IsIndex(index))
		{
			return;
		}

		//遍历左子树
		InOrderTraverseTree(index * 2 + 1,address);

		//根节点
		address(tree[index]);

		//遍历右子树
		InOrderTraverseTree(index * 2 + 2,address);

		return;
	}

	//层次遍历
	void LevelOrderTraverseTree(int index,/*处理函数*/std::function<void(T&)> address = [](T& e)->void {std::cout << e; })
	{
		for (int i = 0; i < tree.size(); i++)
		{
			address(tree[i]);
		}
	}


private:

	//初始化
	void InitBiTree()
	{
		if(!tree.empty())
		{
			tree.clear();
		}
	}
	//以数组初始化
	void InitBiTree(T a[],int n)
	{
		if (!tree.empty())
		{
			tree.clear();
		}
		for (int i = 0; i < n; i++)
		{
			tree.push_back(a[i]);
		}
		return;
	}
};