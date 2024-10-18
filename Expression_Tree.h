#pragma once
#include<iostream>
#include"Link_BiTree.h"

//����׺���ʽ�������ʽ��
//�����������Ϊ˫Ŀ�����������ʽ��Ӧ�ı��ʽ����Ҷ�ӽ���Ϊ����������֧����Ϊ�������
//���Ҳ����Ǳ��ʽ����ȷ��,��������Ϊ������

class Expression_Tree
{
public:
	//�ж������
	bool Isoperate(char op)
	{
		if (op=='('||op==')'||op=='^'||op == '-' || op == '+' || op == '*' || op == '/' || op == '%')
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	//ת�����ȼ���Ĭ��ֻ�мӼ��˳���������
	int precedence(char c)
	{
		if (c == '+' || c == '-')return 1;
		else if (c == '/' || c == '*' || c == '%')return 2;
		else if (c == '^')return 3;
		else if (c == '(' || c == ')')return 0;
		else return -1;
	}

	//expΪ���ʽ
	BiTree<char>* InitExpTree(std::string exp)
	{
		//BiTree����
		BiTree_Manager<char> bitree;

		std::vector<BiTree<char>*> expt;//�ݴ��ѽ����õı��ʽ���ĸ���㡣
		std::vector<char> optr;//�ݴ������

		auto address = [&]()->void {
			//����optrջ�������
			char theta = optr.back();
			optr.pop_back();

			//����������������aΪ�Ҳ�������bΪ�������
			auto a = expt.back();
			expt.pop_back();

			auto b = expt.back();
			expt.pop_back();

			//��thetaΪ���� aΪ�������� bΪ������������һ�ö�����
			auto newnode = bitree.CreatTree(theta);
			newnode->AddleftChild(a);
			newnode->AddrightChild(b);

			//���·���ջ��
			expt.push_back(newnode);
		};

		int i = 0;
		for (int i = 0; i < exp.size(); i++)
		{
			if (exp[i] == ' ')
			{
				continue;
			}

			//������������
			if (!Isoperate(exp[i]))
			{
				//��exp[i]Ϊ������һ��ֻ�и����Ķ�����
				BiTree<char>* T = bitree.CreatTree(exp[i]);

				//������������� T �� EXPTջ
				expt.push_back(T);
			}
			else//Ϊ�����
			{
				//ջΪ��ֱ����ջ
				if (optr.empty())
				{
					optr.push_back(exp[i]);
				}
				else if (exp[i] == '(')//������ֱ��ѹ��
				{
					optr.push_back(exp[i]);
				}
				else if (exp[i] == ')')
				{
					while (exp.back() != '(')
					{
						address();
					}
					exp.pop_back();//ɾ��������
				}
				else if (optr.empty() || optr.back() == '(')
				{
					optr.push_back(exp[i]);
				}
				//�Ƚ�OPTR��ջ��Ԫ�غ�ch�����ȼ�
				else if (precedence(optr.back()) < precedence(exp[i]))//OPTR��ջ��Ԫ��С��ch�����ȼ�
				{
					//��ǰ�ַ�ѹ��OPTRջ�� ������һ�ַ�
					optr.push_back(exp[i]);
				}
				else if(precedence(optr.back())>= precedence(exp[i]))//OPTR��ջ��Ԫ�ش��ڵ���ch�����ȼ�
				{
					address();
					//ѹ�뵱ǰ�ַ�
					optr.push_back(exp[i]);
				}
				


			}
		}

		//��ʱoptr��һ��Ϊ��,����ʣ������
		while (!optr.empty()&&optr.back()!=')')
		{
			address();
		}

		//������
		auto tree = expt.back();
		return tree;
	}

	//����
	int calculate(int left, int right, char oper)
	{
		switch (oper)
		{
		case '+':
			return left + right;
		case '-':
			return left - right;
		case '*':
			return left * right;
		case '/':
			return left / right;
		case '%':
			return left % right;
		case '^':
			return pow(left, right);
		default:
			break;
		}
	}

	//�������ʽ������ֵ�Ĺ���ʵ������һ����������������Ĺ��̣����ʱ��Ϳռ临�ӶȾ�ΪO(n)��
	//�������ʽ�����б��ʽ��ֵ
	int EvaluateExpTree(BiTree<char>* tree)
	{
		//����
		if (!tree)
		{
			return -1;
		}

		//��¼������������ֵ
		int lvalue = 0;
		int rvalue = 0;

		//��������Ϊ�գ���Ϊ������
		if (!tree->leftChild && !tree->rightChild)
		{
			return tree->data - '0';
		}
		else
		{
			//����������Ҳ���������֮����������������,���Է���������
			lvalue = EvaluateExpTree(tree->rightChild);
			rvalue = EvaluateExpTree(tree->leftChild);

			//����������
			return calculate(lvalue, rvalue, tree->data);

		}

	}
};
