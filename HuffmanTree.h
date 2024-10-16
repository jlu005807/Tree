#pragma once
#include<iostream>
#include<climits>
#include<vector>

//哈夫曼(Huffman)树又称最优树，是一类带权路径长度最短的树。
//在哈夫曼树中，权值越大的结点离根结点越近。

template<class T>
class HuffmanTree
{
public:

	T weight;//结点的权值
	int parent, lchild, rchild;//结点的双亲、左孩子、右孩子的下标

	HuffmanTree() = default;

	//以一个值初始化weight,并且其他置零
	HuffmanTree(T weight) :weight(weight), parent(0), lchild(0), rchild(0)
	{

	}

	~HuffmanTree() = default;
};


//哈夫曼树的各结点存储在由 HuffmanTree 定义的动态分配的数组中
//为了实现方便，数组的0号单元不使用，从1号单元开始使用，所以数组的大小为 2n。
template<class T>
class HuffmanTree_manager
{
public:
	//用n个元素的数组代替叶子结点的权值构造HuffmanTree,返回一个数组指针
	HuffmanTree<T>* CreatTree(T a[], int num)
	{
		//数组为空,返回空树
		if (num < 1)
		{
			return nullptr;
		}
		//只有一个节点时
		if (num == 1)
		{
			//0号单元不存数据
			HuffmanTree<T>* HT = new HuffmanTree<T>[3] {};
			//构建叶子节点,并指向根节点tree[2]
			HT[1].weight = a[0];
			HT[1].parent = 2;
			//根节点的左子树指向叶子,根节点的权值就是叶子权值
			HT[2].lchild = 1;
			HT[2].weight = HT[1].weight;

			return HT;

		}

		//初始化
		int m = 2 * num - 1;//节点数

		//0 号单元未用，所以需要动态分配 m+l 个单元， HT[m]表示根结点
		HuffmanTree<T>* HT = new HuffmanTree<T>[m + 1] {};

		//输入权值到叶子节点
		for (int i = 1; i <= num; i++)
		{
			HT[i].weight = a[i - 1];
		}


		/*－ －－－－ －－－－－ －初始化工作结束， 下面开始创建哈夫曼树－ － － － －－－－－－ */

		//构造选择函数Select
		//在 HT[k]中选择两个其双亲域为0 且权值最小的结点，并返回它们在 HT 中的序号 sl和 s2
		auto Select = [&](int pos, int& s1, int& s2)->void
		{

			//表示没找到
			/*s1 = 0;
			s2 = 0;*/

			// 初始化最小值
			int minWeight1 = INT_MAX;
			int minWeight2 = INT_MAX;

			// 遍历数组寻找两个权值最小的节点
			for (int i = 1; i <= pos; i++)
			{
				if (HT[i].parent == 0 && HT[i].weight < minWeight1) {
					minWeight2 = minWeight1;
					s2 = s1;
					minWeight1 = HT[i].weight;
					s1 = i;
				}
				else if (HT[i].parent == 0 && HT[i].weight <= minWeight2) {
					minWeight2 = HT[i].weight;
					s2 = i;
				}
			}

		};

		//归并
		for (int i = num + 1; i <= m; i++)
		{
			//通过 n-1 次的选择、删除 、 合并来创建哈夫曼树
			int s1=0, s2=0;

			Select(i - 1, s1, s2);

			if(s1!=0)
			{
				HT[s1].parent = i;
			}

			if(s2!=0)
			{
				HT[s2].parent = i;
			}

		    //得到新结点i, 从森林中删除sl, s2, 将sl和s2的双亲域由0改为i
			HT[i].lchild = s1;
			HT[i].rchild = s2;

			//i的权值为左右孩子权值之和
			HT[i].weight = HT[s1].weight + HT[s2].weight;
		}

		return HT;
	}

	//在构造哈夫曼树之后，求哈夫曼编码的主要思想是：依次以叶子为出发点，向上回溯至根结点为止。 
	//回溯时走左分支则生成代码 0, 走右分支则生成代码l
	//建立哈夫曼编码，将哈夫曼树的n个叶子节点逆向到根节点编码，存在vector中
	void HuffmanTreeCode(HuffmanTree<int>* HT, std::vector<std::string>& codes, int n)
	{
		//空树
		if (!HT)
		{
			return;
		}

		//清空codes
		codes.clear();
	
		for (int i = 1; i <= n; i++)
		{
			std::string v;//存放当前结点的前缀编码

			int k = i;
			int index = HT[i].parent;//index指向k的父节点

			while (index != 0)
			{
				//结点c是f的左孩子， 则生成代码0
				if (HT[index].lchild == k)
				{
					v = "0" + v;
				}
				else //结点c是f的右孩子， 则生成代码1
				{
					v = "1" + v;
				}

				//往上回溯
				k = index;
				index = HT[index].parent;
			}

			//将当前结点编码v放入codes
			codes.push_back(v);

		}
	}

};