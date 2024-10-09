#pragma once
#include<iostream>


//哈夫曼(Huffman)树又称最优树，是一类带权路径长度最短的树。
//在哈夫曼树中，权值越大的结点离根结点越近。

template<class T>
class HuffmanTree
{
public:
	T weight;//结点的权值
	int parent, lchild, rchild;//结点的双亲、左孩子、右孩子的下标
};
