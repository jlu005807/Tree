#pragma once
//��Ϊ����˳��������ݽṹ�����޹��࣬���ҽ�����������ȫ������������ʵ�ּ�ª��ȫ��������˳��ʵ�֣��������ڴ���չ�Ϳ�����ֵ,������
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

	//��Ϊ����ȫ��������ֻ�������
	void InsertTree(T value)
	{
		tree.push_back(value);
	}

	//��Ϊ����ȫ��������ֻɾ�����
	void DeleteTree()
	{
		tree.pop_back();
	}

	//�ж�����
	bool IsIndex(int index)
	{
		if (index < 0 || index >= tree.size())
		{
			return false;
		}
		return true;
	}

	//��ýڵ�ֵ,Ĭ�������������㿪ʼ
	T GetTreeValue(int index)const
	{
		
		if (!IsIndex(index))
		{
			throw std::out_of_range("Index is out of range");
		}

		return tree[index];
	}

	//���ڵ��������������󣬼�������Ƿ�Ϊ����ڵ�ĸ��ڵ�
	int ParentTree(int index)
	{
		return (index-1)/2; 
	}


	//����������
	int LeftChild(int index)
	{
		return 2 * index + 1;
	}

	//����������
	int RightChild(int index)
	{
		return 2 * index + 2;
	}

	//�������
	int TreeDepth()
	{
		if (tree.empty())
			return 0;
		else return static_cast<int>((std::log2(tree.size()) + 1));
	}

	//�������
	void PostOrderTraverseTree(int index,/*������*/std::function<void(T&)> address = [](T& e)->void {std::cout << e; })
	{
		//��ʼ��������
		if (!IsIndex(index))
		{
			return;
		}
		
		//����������
		PostOrderTraverseTree(index * 2 + 1,address);

		//����������
		PostOrderTraverseTree(index * 2 + 2,address);

		//���ڵ�
		address(tree[index]);

		return;
	}

	//ǰ�����
	void PreOrderTraverseTree(int index,/*������*/std::function<void(T&)> address = [](T& e)->void {std::cout << e; })
	{
		//��ʼ��������
		if (!IsIndex(index))
		{
			return;
		}

		//���ڵ�
		address(tree[index]);

		//����������
		PreOrderTraverseTree(index * 2 + 1,address);

		//����������
		PreOrderTraverseTree(index * 2 + 2,address);

		return;
	}

	//�������
	void InOrderTraverseTree(int index,/*������*/std::function<void(T&)> address = [](T& e)->void {std::cout << e; })
	{
		//��ʼ��������
		if (!IsIndex(index))
		{
			return;
		}

		//����������
		InOrderTraverseTree(index * 2 + 1,address);

		//���ڵ�
		address(tree[index]);

		//����������
		InOrderTraverseTree(index * 2 + 2,address);

		return;
	}

	//��α���
	void LevelOrderTraverseTree(int index,/*������*/std::function<void(T&)> address = [](T& e)->void {std::cout << e; })
	{
		for (int i = 0; i < tree.size(); i++)
		{
			address(tree[i]);
		}
	}


private:

	//��ʼ��
	void InitBiTree()
	{
		if(!tree.empty())
		{
			tree.clear();
		}
	}
	//�������ʼ��
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