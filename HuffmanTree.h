#pragma once
#include<iostream>


//������(Huffman)���ֳ�����������һ���Ȩ·��������̵�����
//�ڹ��������У�ȨֵԽ��Ľ��������Խ����

template<class T>
class HuffmanTree
{
public:
	T weight;//����Ȩֵ
	int parent, lchild, rchild;//����˫�ס����ӡ��Һ��ӵ��±�
};
