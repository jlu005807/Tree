#pragma once
#include<iostream>
#include<memory>//ʹ��unique_ptr�Զ��ͷ���Դ��һ���ԣ������ݽṹ�Ͳ����ֿ�
#include<vector>

//��ͷ�ļ�Ϊ��ͨ����ʵ�֣���vector�洢����
//�������ĽṹΪ�ݹ�ģ����������ｫ���ݽṹ�Ͷ���Ĳ����ֿ���װ

template<class T>
struct Tree
{
public:
	T data;
	std::vector<std::unique_ptr<Tree>> child_Tree;


	Tree() = default;

	Tree(T e)
	{
		this->data = e;
	}

private:

	Tree(const Tree* other) = delete;

	Tree& operator=(const Tree other) = delete;

};

//�����ǿ�������͸�
template<class T>
class Tree_Manager//���������࣬�����������Ĳ���
{
public:

	std::unique_ptr<Tree> InitTree()//����һ�������κ����ݵĽڵ�
	{
		return std::make_unique<Tree>(new Tree());
	}
	
	void InitTree(T e)//��e����һ���ڵ�
	{
		return std::make_unique<Tree>(new Tree(e));
	}





};