#pragma once
#include<iostream>
#include<vector>

//���鼯��һ�����ڹ���Ԫ���������ϵ����ݽṹ��ʵ��Ϊһ��ɭ�֣�
//����ÿ������ʾһ�����ϣ����еĽڵ��ʾ��Ӧ�����е�Ԫ�ء�

class dsu
{
public:
	std::vector<size_t> pa;//��Ÿ������

	std::vector<size_t> size;//�����ڵ������

	dsu() = default;

	explicit dsu(size_t size_):size(size_,1)
	{
		for (auto i = 0; i <= size_; i++)
		{
			pa.push_back(i);//��ʼʱ��ÿ���ڵ㶼��һ���������ڵ�ָ���Լ�
		}
	}

	//��ѯ��Find������ѯĳ��Ԫ���������ϣ���ѯ��Ӧ�����ĸ��ڵ㣩
	//����������ж�����Ԫ���Ƿ�����ͬһ����
	//ͬʱ����·��ѹ������ѯ�����о�����ÿ��Ԫ�ض����ڸü���
	//���ǿ��Խ���ֱ���������ڵ��Լӿ������ѯ��
	

	size_t find(size_t x)
	{
		return pa[x] == x ? x : pa[x]=find(pa[x]);
	}

	//�ϲ���Union�����ϲ�����Ԫ���������ϣ��ϲ���Ӧ������
	//�ϲ�ʱ��ѡ���Ŀ����ĸ��ڵ���Ϊ�����ĸ��ڵ��Ӱ��δ�������ĸ��Ӷȡ�
	// ���ǿ��Խ��ڵ���ٻ���Ƚ�С����������һ�ã����ⷢ���˻���

	size_t unite(size_t x, size_t y)
	{
		x = find(x);
		y = find(y);

		if (x == y)return;//�Ѿ��ϲ�

		//��������С��
		if (size[x] < size[y])
		{
			std::swap(x, y);
		}

		pa[y] = x;

		size[x] += size[y];

	}

	//��ʱ������ɾ�����ƶ�


};