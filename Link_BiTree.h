#pragma once
//��ʽ������
#include<iostream>
#include<functional>
#include<queue>

//ͬCommon_Treeһ��
//�������ĽṹΪ�ݹ�ģ����������ｫ���ݽṹ�Ͷ���Ĳ����ֿ���װ
//��������һ��BiTree,�����������BiTree,BiTree�಻����ռ���������

template<class T>
class BiTree
{
public:
	T data;//����

	BiTree<T>* parent;//���ڵ�
	BiTree<T>* leftChild;//������
	BiTree<T>* rightChild;//������

	//���������Ƿ�Ϊ����
	bool leftTag;
	bool rightTag;

	BiTree() = default;

	BiTree(T e) :parent(nullptr), leftChild(nullptr), rightChild(nullptr), leftTag(false), rightTag(false), data(e)
	{

	}

	~BiTree() = default;

	void AddleftChild(BiTree<T>* child)//�������,������ԭ�����������˲���Ϊ�ϲ㸺�������������
	{
		if (!child||child == this)//������������
		{
			return;
		}

		//�ϸ�,�˴�Ϊ���ݽṹ���������Ƿ�������ԭ���ڵ㣬�˲���Ϊ�ϲ㸺��
		child->parent = this;

		this->leftChild = child;

	}

	void AddrightChild(BiTree<T>* child)//�������,������ԭ�����������˲���Ϊ�ϲ㸺�������������
	{
		if (!child || child == this)//������������
		{
			return;
		}

		//�ϸ�,�˴�Ϊ���ݽṹ���������Ƿ�������ԭ���ڵ㣬�˲���Ϊ�ϲ㸺��
		child->parent = this;

		this->rightChild = child;

	}

	void AddChild(BiTree<T>* tree,int pos)//posΪ0ʱ������������Ϊ1ʱ����������,��������������
	{
		if (pos == 0)
		{
			AddleftChild(tree);
		}
		else if (pos == 1)
		{
			AddrightChild(tree);
		}
	}

	//���Ӹ��ڵ�
	void AddParent(BiTree<T>* parent,int pos)//posΪ0ʱ������������Ϊ1ʱ����������,��������������
	{
		if (!parent||parent==this)
		{
			return;
		}

		parent->AddChild(this, pos);
	}

	//ɾ��������
	void DeleteleftChild()
	{
		//�������������Ҳ�������
		if (this->leftChild && !this->leftTag)
		{
			this->leftChild->parent = nullptr;
			this->leftChild = nullptr;
		}
		return;
	}

	//ɾ��������
	void DeleterightChild()
	{
		//�������������Ҳ�������
		if (this->rightChild && !this->rightTag)
		{
			this->rightChild->parent = nullptr;
			this->rightChild = nullptr;
		}
		return;
	}

	//ɾ������
	void DeleteChild(int pos)
	{
		//�����ǿռ�����
		if (pos == 0)
		{
			DeleteleftChild();
		}
		else if (pos == 1)
		{
			DeleterightChild();
		}
	}

	//ɾ�����ڵ�
	void DeleteParent()
	{
			
		if (parent&&parent->leftChild == this)
		{			parent->DeleteChild(0);
		}

		if (parent&&parent->rightChild == this)
		{
			parent->DeleteChild(1);
		}

		return;
	}
	
};

template<class T>
class BiTree_Manager
{
public:
	//����һ��dataΪe�����ڵ�
	BiTree<T>* CreatTree(T e)
	{
		return new BiTree<T>(e);
	}

	//��һ�����鴴��һ����,û��������
	BiTree<T>* CreatTree(T a[], int begin, int number)//begin��������ʼλ��
	{
		if (begin < 0 || begin >= number)
		{
			return nullptr;
		}

		//���ڵ�
		BiTree<T>* tree = new BiTree<T>(a[begin]);

		//����
		BiTree<T>* left = CreatTree(a, begin * 2 + 1, number);
		BiTree<T>* right = CreatTree(a, begin * 2 + 2, number);

		if (left != nullptr)
		{
			tree->AddChild(left,0);
		}

		if (right != nullptr)
		{
			tree->AddChild(right,1);
		}

		return tree;

	}

	//����һ����,�������Ϊ�ղ��������壬�����������ཻ
	BiTree<T>* CreatTree(BiTree<T>* tree)
	{
		//����
		if (!tree)
		{
			return nullptr;
		}

		BiTree<T>* new_tree = new BiTree<T>(tree->data);

		//����������
		BiTree<T>* p;
		if (tree->leftChild && !tree->leftTag)
		{
			p = CreatTree(tree->leftChild);
		}

		//����������
		BiTree<T>* q;
		if (tree->rightChild && !tree->rightTag)
		{
		     q = CreatTree(tree->rightChild);
		}

		new_tree->AddleftChild(p);

		new_tree->AddrightChild(q);

		return new_tree;


	}

	//������һ�������κ����ݵĽڵ㣬��Ϊ�˽ڵ�Ϊ����������
	//�˺���ֻ����tree�ڵ㼰������
	//�����𴴽����ڵ�
	void InitTree(BiTree<T>* tree, T e)//��e��ʼ��������tree,����ԭTree,������и��ڵ㲻�ж��븸�ڵ���ϵ��
	{
		if (tree != nullptr)
		{
			//�������
			//������ʱ���Ҳ��������ݹ�������������
			if (tree->leftChild && !tree->leftTag)
			{
				ClearTree(tree->leftChild);
			}

			if (tree->rightChild && !tree->rightTag)
			{
				ClearTree(tree->rightChild);
			}
	

			tree->data = e;//�ı�����

			return;
		}

		//treeΪ�գ�������ʱ,����������
	}

	//�ͷ�������Ϊ����������и��ڵ����ж���ϵ
	void ClearTree(BiTree<T>* tree)
	{
		//�սڵ�ֱ�ӷ���
		if (tree == nullptr)
		{
			return;
		}

		//������У��ж��븸�ڵ���ϵ
		tree->DeleteParent();


		//������ʱ�ݹ�������������
		if (tree->leftChild && !tree->leftTag)
		{
			ClearTree(tree->leftChild);
		}

		if (tree->rightChild && !tree->rightTag)
		{
			ClearTree(tree->rightChild);
		}

		//���ٴ˽ڵ�
		delete tree;

		//�ÿ�
		tree = nullptr;

		return;

	}

	//�ж��Ƿ�Ϊ����
	bool TreeEmpty(BiTree<T>* tree)
	{
		if (tree)
		{
			return false;
		}

		return true;
	}

	//����Tree�����
	int TreeDepth(BiTree<T>* tree)
	{
		//����
		if (!tree)
		{
			return 0;
		}

		//������
		int left=0, right=0;//���������������

		if (!tree->leftTag)
		{
			left = TreeDepth(tree->leftChild);
		}

		if (!tree->rightTag)
		{
			right = TreeDepth(tree->rightChild);
		}
		
		return left > right ? left+1 : right+1;
	}

	//���ظ��ڵ�
	BiTree<T>* RootTree(BiTree<T>* tree)
	{
		//����
		if (!tree)
		{
			return nullptr;
		}

		//Ϊ���ڵ�
		if (tree->parent == nullptr)
		{
			return tree;
		}

		//���Ǹ��ڵ������ϵݹ�
		return RootTree(tree->parent);
	}

	T ValueTree(BiTree<T>* tree)
	{
		if (tree)
		{
			return tree->data;
		}
		else
		{
			//Ϊ��ʱ
			return NULL;
		}
	}

	//��������
	void AssignTree(BiTree<T>* tree, T e)
	{
		//����
		if (!tree)
		{
			return;
		}

		tree->data = e;

		return;
	}

	//���ظ��ڵ�
	BiTree<T>* ParentTree(BiTree<T>* tree)
	{
		//����
		if (!tree)
		{
			return nullptr;
		}

		//Ϊ���ڵ�ʱ����nullptr
		return tree->parent;
	}

	BiTree<T>* LeftChild(BiTree<T>* tree)
	{
		//����
		if (!tree)
		{
			return nullptr;
		}

		//��Ϊ����
		if (!tree->leftTag)
		{
			//����Ϊ��
			return tree->leftChild;
		}

		//������Ϊ��
		return nullptr;
	}

	BiTree<T>* RightChild(BiTree<T>* tree)
	{
		//����
		if (!tree)
		{
			return nullptr;
		}

		//��Ϊ����
		if (!tree->rightTag)
		{
			//����Ϊ��
			return tree->rightChild;
		}

		//������Ϊ��
		return nullptr;
	}

	//����tree�����ֵܡ���tree��parent�����ӻ������ֵܣ��򷵻ؿ�
	BiTree<T>* LeftSibling(BiTree<T>* tree)
	{
		//���������޸��ڵ���߸��ڵ�������Ϊ����
		if (!tree||tree->parent||tree->parent->leftTag)
		{
			return nullptr;
		}

		//treeΪ������,parent������Ϊ��
		if (tree->parent->leftChild==tree||!tree->parent->leftChild)
		{
			//����Ϊ��
			return nullptr;
		}

		//���ظ��ڵ������������tree�����ֵ�
		return tree->parent->leftChild;
	}

	//����tree�����ֵܡ���tree��parent���Һ��ӻ������ֵܣ��򷵻ؿ�
	BiTree<T>* RightSibling(BiTree<T>* tree)
	{
		//���������޸��ڵ���߸��ڵ�������Ϊ����
		if (!tree || tree->parent||tree->parent->rightTag)
		{
			return nullptr;
		}

		//treeΪ������,parent������Ϊ��
		if (tree->parent->rightChild == tree || !tree->parent->rightChild)
		{
			//����Ϊ��
			return nullptr;
		}

		//���ظ��ڵ������������tree�����ֵ�
		return tree->parent->rightChild;
	}

	//���������ʧЧ����Ҫ��������
	//��child����Ϊparent����ڵ㣬���������ཻ�������ԭ�����������Ϊchild������������
	void InsertleftChild(BiTree<T>* parent, BiTree<T>* child)
	{
		//һ��Ϊ�ջ���������ͬ
		if (!parent || !child || parent == child)
		{
			return;
		}

		//�����������Ҳ�Ϊ����
		BiTree<T>* p = nullptr;
		if (parent->leftChild && !parent->leftTag)
		{
			p = parent->leftChild;//��¼����
		}

		//����
		parent->AddleftChild(child);

		BiTree<T>* q = child->rightChild;
		while (q->rightChild && !q->rightTag)
		{
			q = q->rightChild;
		}
		//�ҵ�child����������
		q->AddrightChild(p);
	}

	//��child����Ϊparent����ڵ㣬���������ཻ�������ԭ�����������Ϊchild������������
	void InsertRightChild(BiTree<T>* parent, BiTree<T>* child)
	{
		//һ��Ϊ�ջ���������ͬ
		if (!parent || !child || parent == child)
		{
			return;
		}

		//�����������Ҳ�Ϊ����
		BiTree<T>* p = nullptr;
		if (parent->rightChild && !parent->rightTag)
		{
			p = parent->rightChild;//��¼����
		}

		//����
		parent->AddrightChild(child);

		BiTree<T>* q = child->rightChild;
		while (q->rightChild && !q->rightTag)
		{
			q = q->rightChild;
		}
		//�ҵ�child����������
		q->AddrightChild(p);
	}

	//posΪ0������������1����������������������
	void InsertChild(BiTree<T>* parent,BiTree<T>* child,int pos)
	{
		if (pos == 0)
		{
			InsertleftChild(parent, child);
		}
		else if (pos == 1)
		{
			InsertRightChild(parent, child);
		}
	}

	//ɾ��������ʧЧ
	//treeɾ�����������������������������ͷſռ�
	BiTree<T>* DeleteLeftChild(BiTree<T>* tree)
	{
		//��������������Ϊ�ջ���Ϊ����
		if (!tree || !tree->leftChild || tree->leftTag)
		{
			return nullptr;
		}

		//��¼������
		BiTree<T>* p = tree->leftChild;

		tree->DeleteleftChild();

		return p;
	}

	//treeɾ�����������������������������ͷſռ�
	BiTree<T>* DeleteRightChild(BiTree<T>* tree)
	{
		//��������������Ϊ�ջ���Ϊ����
		if (!tree || !tree->rightChild || tree->rightTag)
		{
			return nullptr;
		}

		//��¼������
		BiTree<T>* p = tree->rightChild;

		tree->DeleterightChild();

		return p;
	}

	//posΪ0ɾ����������1ɾ��������������������
	BiTree<T>* DeleteChild(BiTree<T>* parent, int pos)
	{
		if (pos == 0)
		{
			return DeleteLeftChild(parent);
		}
		else if (pos == 1)
		{
			return DeleteRightChild(parent);
		}

		return nullptr;
	}

	//ǰ�����
	//����function��һ�����ؿգ��������������,Ĭ��Ϊ���data
	void PreOrderTraverseTree(BiTree<T>* tree,/*������*/std::function<void(T&)> address = [](T& e)->void {std::cout << e; })
	{
		//����
		if (!tree)
		{
			return;
		}

		//���ڵ�
		address(tree->data);

		//����������
		if (tree->leftChild && !tree->leftTag)
		{
			PreOrderTraverseTree(tree->leftChild, address);
		}

		//����������
		if (tree->rightChild && !tree->rightTag)
		{
			PreOrderTraverseTree(tree->rightChild, address);
		}

		return;

	}

	//�������
	void InOrderTraverseTree(BiTree<T>* tree,/*������*/std::function<void(T&)> address = [](T& e)->void {std::cout << e; })
	{
		//����
		if (!tree)
		{
			return;
		}

		//����������
		if (tree->leftChild && !tree->leftTag)
		{
			InOrderTraverseTree(tree->leftChild, address);
		}

		//���ڵ�
		address(tree->data);

		//����������
		if (tree->rightChild && !tree->rightTag)
		{
			InOrderTraverseTree(tree->rightChild, address);
		}

		return;

	}

	//�������
	void PostOrderTraverseTree(BiTree<T>* tree,/*������*/std::function<void(T&)> address = [](T& e)->void {std::cout << e; })
	{
		//����
		if (!tree)
		{
			return;
		}

		//����������
		if (tree->leftChild && !tree->leftTag)
		{
			InOrderTraverseTree(tree->leftChild, address);
		}

		//����������
		if (tree->rightChild && !tree->rightTag)
		{
			InOrderTraverseTree(tree->rightChild, address);
		}

		//���ڵ�
		address(tree->data);

		return;

	}

	//��α���
	void LevelOrderTraverseTree(BiTree<T>* tree,/*������*/std::function<void(T&)> address = [](T& e)->void {std::cout << e; })
	{
		//����
		if (!tree)
		{
			return;
		}

		std::queue<BiTree<T>*> trees;
		trees.push(tree);

		while (!trees.empty())
		{
			BiTree<T>* p = trees.front();
			trees.pop();

			address(p->data);

			//������
			if (p->leftChild && !p->leftTag)
			{
				trees.push(p->leftChild);
			}

			//����������
			if (p->rightChild && !p->rightTag)
			{
				trees.push(p->rightChild);
			}

		}

		return;

	}

	//���ؽڵ���
	int TreeNumber(BiTree<T>* tree)
	{
		//����
		if (!tree)
		{
			return 0;
		}

		int number = 1;

		//���������գ����Ҳ�������
		if (tree->leftChild && !tree->leftTag)
		{
			number += TreeNumber(tree->leftChild);
		}

		//���������գ����Ҳ�������
		if (tree->rightChild && !tree->rightTag)
		{
			number += TreeNumber(tree->rightChild);
		}

		return number;
	}
	
	//������������ʹ�ø��Ĺ���������������
	void DeleteThreading(BiTree<T>* tree)
	{
		//����
		if (!tree)
		{
			return;
		}
		
		//ȡ��������������
		if (tree->leftTag)
		{
			tree->leftChild = nullptr;
			tree->leftTag = false;
		}
		else
		{
			DeleteThreading(tree->leftChild);
		}

		//ȡ��������������
		if (tree->rightTag)
		{
			tree->rightChild = nullptr;
			tree->rightTag = false;
		}
		else
		{
			DeleteThreading(tree->rightChild);
		}

		return;
	}


	//Ĭ��treeû��������������Ѿ���������Ҫ����������
	//pre��ȫ�ֱ�ַ����ʼ��ʱ���Һ���ָ��Ϊ�գ���������������㿪ʼ������
	//����������������
	void InThreading(BiTree<T>* tree, BiTree<T>* pre)
	{
		//�ǿ���
		if (tree)
		{
			InThreading(tree->leftChild, pre);//�������ݹ�������

			//������Ϊ��,������
			if (!tree->leftChild)
			{
				tree->leftTag = true;
				//������ָ��ǰ������pre
				tree->leftChild = pre;
			}
			else
			{
				tree->leftTag = false;
			}

			//ǰ��������Ϊ��
			if (!pre->rightChild)
			{
				pre->rightTag = true;
				//������ָ���̣���tree
				pre->rightChild = tree;
			}
			else
			{
				pre->rightTag = false;
			}

			//ǰ��
			pre = tree;

			InThreading(tree->rightChild, pre);//�������ݹ�������
		
		}
	}

	//����һ��������ָ����ڵ��ͷ���Thrt
	//��ͷ���Ķ���������������
	BiTree<T>* InOrderThreading(BiTree<T>* tree)
	{
		//�����������������������������Thrtָ��ͷ���
		BiTree<T>* Thrt = new BiTree<T>();//����ͷ���

		Thrt->leftTag = false;//ͷ������������������ǿգ�����������Ϊ���ĸ��ڵ�
		Thrt->rightTag = true;//ͷ����������ָ��Ϊ������
		Thrt->rightChild = Thrt;//��ʼ����ָ��ָ��ͷ���
		
		if (!tree)
		{
			Thrt->leftChild = Thrt;//�����Ϊ�գ���ָ��Ҳָ��ͷ���
		}
		else
		{
			Thrt->leftChild = tree;//��ָ��ָ������
			//pre��ֵָ��ͷ���
			BiTree<T>* pre = Thrt;
			InThreading(tree, pre);//������
			//pre���Ϊ���ҽ�㣬pre��������ָ��ͷ���
			pre->rightChild = Thrt;
			pre->rightTag = true;
			Thrt->rightChild = pre;//ͷ����������ָ��pre�����������ҽ��
		}

		return Thrt;//����ͷ���
	}




};