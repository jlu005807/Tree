#pragma once
#include<iostream>
#include<vector>

//并查集是一种用于管理元素所属集合的数据结构，实现为一个森林，
//其中每棵树表示一个集合，树中的节点表示对应集合中的元素。

class dsu
{
public:
	std::vector<size_t> pa;//存放各个结点

	std::vector<size_t> size;//各个节点的数量

	dsu() = default;

	explicit dsu(size_t size_):size(size_,1)
	{
		for (auto i = 0; i <= size_; i++)
		{
			pa.push_back(i);//开始时，每个节点都是一棵树，根节点指向自己
		}
	}

	//查询（Find）：查询某个元素所属集合（查询对应的树的根节点）
	//这可以用于判断两个元素是否属于同一集合
	//同时进行路径压缩，查询过程中经过的每个元素都属于该集合
	//我们可以将其直接连到根节点以加快后续查询。
	

	size_t find(size_t x)
	{
		return pa[x] == x ? x : pa[x]=find(pa[x]);
	}

	//合并（Union）：合并两个元素所属集合（合并对应的树）
	//合并时，选择哪棵树的根节点作为新树的根节点会影响未来操作的复杂度。
	// 我们可以将节点较少或深度较小的树连到另一棵，以免发生退化。

	size_t unite(size_t x, size_t y)
	{
		x = find(x);
		y = find(y);

		if (x == y)return;//已经合并

		//大树并向小树
		if (size[x] < size[y])
		{
			std::swap(x, y);
		}

		pa[y] = x;

		size[x] += size[y];

	}

	//暂时不考虑删除和移动


};