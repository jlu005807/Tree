#pragma once
#include<iostream>
#include<memory>//使用unique_ptr自动释放资源这一特性，将数据结构和操作分开
#include<vector>

//此头文件为普通树的实现，用vector存储子树
//基于树的结构为递归的，所以在这里将数据结构和对其的操作分开封装

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

//不考虑拷贝构造和赋
template<class T>
class Tree_Manager//管理树的类，即包含对树的操作
{
public:

	std::unique_ptr<Tree> InitTree()//返回一个不存任何数据的节点
	{
		return std::make_unique<Tree>(new Tree());
	}
	
	void InitTree(T e)//以e创建一个节点
	{
		return std::make_unique<Tree>(new Tree(e));
	}





};