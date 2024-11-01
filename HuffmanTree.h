#pragma once
#include<iostream>
#include<climits>
#include<vector>

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
		//�� HT[k]��ѡ��������˫����Ϊ0 ��Ȩֵ��С�Ľ�㣬������������ HT �е���� sl�� s2
		auto Select = [&](int pos, int& s1, int& s2)->void
		{

			//��ʾû�ҵ�
			/*s1 = 0;
			s2 = 0;*/

			// ��ʼ����Сֵ
			int minWeight1 = INT_MAX;
			int minWeight2 = INT_MAX;

			// ��������Ѱ������Ȩֵ��С�Ľڵ�
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

		//�鲢
		for (int i = num + 1; i <= m; i++)
		{
			//ͨ�� n-1 �ε�ѡ��ɾ�� �� �ϲ���������������
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

		    //�õ��½��i, ��ɭ����ɾ��sl, s2, ��sl��s2��˫������0��Ϊi
			HT[i].lchild = s1;
			HT[i].rchild = s2;

			//i��ȨֵΪ���Һ���Ȩֵ֮��
			HT[i].weight = HT[s1].weight + HT[s2].weight;
		}

		return HT;
	}

	//�ڹ����������֮����������������Ҫ˼���ǣ�������Ҷ��Ϊ�����㣬���ϻ����������Ϊֹ�� 
	//����ʱ�����֧�����ɴ��� 0, ���ҷ�֧�����ɴ���l
	//�������������룬������������n��Ҷ�ӽڵ����򵽸��ڵ���룬����vector��
	void HuffmanTreeCode(HuffmanTree<int>* HT, std::vector<std::string>& codes, int n)
	{
		//����
		if (!HT)
		{
			return;
		}

		//���codes
		codes.clear();
	
		for (int i = 1; i <= n; i++)
		{
			std::string v;//��ŵ�ǰ����ǰ׺����

			int k = i;
			int index = HT[i].parent;//indexָ��k�ĸ��ڵ�

			while (index != 0)
			{
				//���c��f�����ӣ� �����ɴ���0
				if (HT[index].lchild == k)
				{
					v = "0" + v;
				}
				else //���c��f���Һ��ӣ� �����ɴ���1
				{
					v = "1" + v;
				}

				//���ϻ���
				k = index;
				index = HT[index].parent;
			}

			//����ǰ������v����codes
			codes.push_back(v);

		}
	}


	//��һ�������ƴ���code����Ϊn��HTҶ�ӽڵ��Ӧ�ı��(��һ��ʼ��������Ƿ��򷵻ء�INVALID��
	std::string decode(HuffmanTree<int>* HT, std::string code, int n)
	{
		int k;

		//ֻ��һ���ڵ�ʱ���⿼��
		k = (n == 1) ? 2 : 2 * n - 1;

		std::string postcode;

		int i = 0;

		while (i < code.size())
		{
			//����Ҷ�ӽڵ㣬������
			if (HT[k].lchild == 0 && HT[k].rchild == 0)
			{
				postcode.push_back(k);

				k = (n == 1) ? 2 : 2 * n - 1;
			}
			else
			{
				//Ϊ��ʱ����
				if (code[i] == '0')
				{
					k = HT[k].lchild;
					i++;
				}
				//Ϊһʱ����
				else if (code[i] == '1')
				{

					k = HT[k].rchild;
					i++;
				}

			}
		}

		//���һ���ж��Ƿ�ΪҶ�ӽڵ㣬���պõ�Ҷ�ӽڵ�������룬����Ϊ����Ƿ�����
		if (HT[k].lchild == 0 && HT[k].rchild == 0)
		{
			postcode.push_back(k);
			return postcode;
		}
		else
		{
			return { "INVALID" };
		}
	}

};