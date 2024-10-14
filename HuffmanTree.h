#pragma once
#include<iostream>
#include<climits>


//������(Huffman)���ֳ�����������һ���Ȩ·��������̵�����
//�ڹ��������У�ȨֵԽ��Ľ��������Խ����

template<class T>
class HuffmanTree
{
public:

	T weight;//����Ȩֵ
	int parent, lchild, rchild;//����˫�ס����ӡ��Һ��ӵ��±�

	HuffmanTree() = default;

	//��һ��ֵ��ʼ��weight,������������
	HuffmanTree(T weight) :weight(weight), parent(0), lchild(0), rchild(0)
	{

	}

	~HuffmanTree() = default;
};


//���������ĸ����洢���� HuffmanTree ����Ķ�̬�����������
//Ϊ��ʵ�ַ��㣬�����0�ŵ�Ԫ��ʹ�ã���1�ŵ�Ԫ��ʼʹ�ã���������Ĵ�СΪ 2n��
template<class T>
class HuffmanTree_manager
{
public:
	//��n��Ԫ�ص��������Ҷ�ӽ���Ȩֵ����HuffmanTree,����һ������ָ��
	HuffmanTree<T>* CreatTree(T a[], int num)
	{
		//����Ϊ��,���ؿ���
		if (num < 1)
		{
			return nullptr;
		}
		//ֻ��һ���ڵ�ʱ
		if (num == 1)
		{
			//0�ŵ�Ԫ��������
			HuffmanTree<T>* HT = new HuffmanTree<T>[3] {};
			//����Ҷ�ӽڵ�,��ָ����ڵ�tree[2]
			HT[1].weight = a[0];
			HT[1].parent = 2;
			//���ڵ��������ָ��Ҷ��,���ڵ��Ȩֵ����Ҷ��Ȩֵ
			HT[2].lchild = 1;
			HT[2].weight = HT[1].weight;

			return HT;

		}

		//��ʼ��
		int m = 2 * num - 1;//�ڵ���

		//0 �ŵ�Ԫδ�ã�������Ҫ��̬���� m+l ����Ԫ�� HT[m]��ʾ�����
		HuffmanTree<T>* HT = new HuffmanTree<T>[m + 1] {};

		//����Ȩֵ��Ҷ�ӽڵ�
		for (int i = 1; i <= num; i++)
		{
			HT[i].weight = a[i - 1];
		}

		/*�� �������� ���������� ����ʼ������������ ���濪ʼ�������������� �� �� �� ������������ */

		//����ѡ����Select
		//�� HT[k] (l:e;;;k:e;;;i-1) ��ѡ��������˫����Ϊ0 ��Ȩֵ��С�Ľ�㣬������������ HT �е���� sl�� s2
		auto Select = [&](int pos, int& s1, int& s2)->void
		{

			//��ʾû�ҵ�
			s1 = 0;
			s2 = 0;

			// ��ʼ����Сֵ
			int minWeight1 = INT_MAX;
			int minWeight2 = INT_MAX;


			// ��������Ѱ������Ȩֵ��С�Ľڵ�
			for (int i = 0; i < 
				pos; i++)
			{
				if (HT[i].parent == 0 && HT[i].weight < minWeight1) {
					minWeight2 = minWeight1;
					s2 = s1;
					minWeight1 = HT[i].weight;
					s1 = i;
				}
				else if (HT[i].parent == 0 && HT[i].weight < minWeight2 && HT[i].weight != minWeight1) {
					minWeight2 = HT[i].weight;
					s2 = i;
				}
			}
		};

		for (int i = num + 1; i <= m; i++)
		{
			//ͨ�� n-1 �ε�ѡ��ɾ�� �� �ϲ���������������
			int s1, s2;

			Select(i - 1, s1, s2);

			HT[s1].parent = i;
			HT[s2].parent = i;

		    //�õ��½��i, ��ɭ����ɾ��sl, s2, ��sl��s2��˫������0��Ϊi
			HT[i].lchild = s1;
			HT[i].rchild = s2;

			//i��ȨֵΪ���Һ���Ȩֵ֮��
			HT[i].weight = HT[s1].weight + HT[s2].weight;


		}
	}
};