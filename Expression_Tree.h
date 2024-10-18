#pragma once
#include<iostream>
#include"Link_BiTree.h"

//由中缀表达式创建表达式树
//假设运算符均为双目运算符，则表达式对应的表达式树中叶子结点均为操作数，分支结点均为运算符。
//并且不考虑表达式的正确性,并且数都为正整数

class Expression_Tree
{
public:
	//判断运算符
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

	//转换优先级，默认只有加减乘除和幂运算
	int precedence(char c)
	{
		if (c == '+' || c == '-')return 1;
		else if (c == '/' || c == '*' || c == '%')return 2;
		else if (c == '^')return 3;
		else if (c == '(' || c == ')')return 0;
		else return -1;
	}

	//exp为表达式
	BiTree<char>* InitExpTree(std::string exp)
	{
		//BiTree管理
		BiTree_Manager<char> bitree;

		std::vector<BiTree<char>*> expt;//暂存已建立好的表达式树的根结点。
		std::vector<char> optr;//暂存运算符

		auto address = [&]()->void {
			//弹出optr栈顶运算符
			char theta = optr.back();
			optr.pop_back();

			//弹出两个操作数，a为右操作数，b为左操作数
			auto a = expt.back();
			expt.pop_back();

			auto b = expt.back();
			expt.pop_back();

			//以theta为根， a为左子树， b为右子树，创建一棵二叉树
			auto newnode = bitree.CreatTree(theta);
			newnode->AddleftChild(a);
			newnode->AddrightChild(b);

			//重新放入栈中
			expt.push_back(newnode);
		};

		int i = 0;
		for (int i = 0; i < exp.size(); i++)
		{
			if (exp[i] == ' ')
			{
				continue;
			}

			//如果不是运算符
			if (!Isoperate(exp[i]))
			{
				//以exp[i]为根创建一棵只有根结点的二叉树
				BiTree<char>* T = bitree.CreatTree(exp[i]);

				//将二叉树根结点 T 进 EXPT栈
				expt.push_back(T);
			}
			else//为运算符
			{
				//栈为空直接入栈
				if (optr.empty())
				{
					optr.push_back(exp[i]);
				}
				else if (exp[i] == '(')//左括号直接压入
				{
					optr.push_back(exp[i]);
				}
				else if (exp[i] == ')')
				{
					while (exp.back() != '(')
					{
						address();
					}
					exp.pop_back();//删除左括号
				}
				else if (optr.empty() || optr.back() == '(')
				{
					optr.push_back(exp[i]);
				}
				//比较OPTR的栈顶元素和ch的优先级
				else if (precedence(optr.back()) < precedence(exp[i]))//OPTR的栈顶元素小于ch的优先级
				{
					//当前字符压入OPTR栈， 读入下一字符
					optr.push_back(exp[i]);
				}
				else if(precedence(optr.back())>= precedence(exp[i]))//OPTR的栈顶元素大于等于ch的优先级
				{
					address();
					//压入当前字符
					optr.push_back(exp[i]);
				}
				


			}
		}

		//此时optr不一定为空,可能剩下括号
		while (!optr.empty()&&optr.back()!=')')
		{
			address();
		}

		//返回树
		auto tree = expt.back();
		return tree;
	}

	//计算
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

	//遍历表达式进行求值的过程实际上是一个后序遍历二叉树的过程，因此时间和空间复杂度均为O(n)。
	//遍历表达式树进行表达式求值
	int EvaluateExpTree(BiTree<char>* tree)
	{
		//空树
		if (!tree)
		{
			return -1;
		}

		//记录左右子树运算值
		int lvalue = 0;
		int rvalue = 0;

		//左右子树为空，即为操作数
		if (!tree->leftChild && !tree->rightChild)
		{
			return tree->data - '0';
		}
		else
		{
			//左子树存放右操作数，反之右子树存放左操作数,所以反过来计算
			lvalue = EvaluateExpTree(tree->rightChild);
			rvalue = EvaluateExpTree(tree->leftChild);

			//返回运算结果
			return calculate(lvalue, rvalue, tree->data);

		}

	}
};
