#pragma once
//链式二叉树
#include<iostream>
#include<functional>
#include<queue>

//同Common_Tree一般
//基于树的结构为递归的，所以在这里将数据结构和对其的操作分开封装
//当创建了一个BiTree,必须最后销毁BiTree,BiTree类不负责空间分配和销毁

template<class T>
class BiTree
{
public:
	T data;//数据

	BiTree<T>* parent;//父节点
	BiTree<T>* leftChild;//左子树
	BiTree<T>* rightChild;//右子树

	//左右子树是否为线索
	bool leftTag;
	bool rightTag;

	BiTree() = default;

	BiTree(T e) :parent(nullptr), leftChild(nullptr), rightChild(nullptr), leftTag(false), rightTag(false), data(e)
	{

	}

	~BiTree() = default;

	void AddleftChild(BiTree<T>* child)//添加子树,不考虑原本左子树，此操作为上层负责，则操作无意义
	{
		if (!child||child == this)//空树或者自身
		{
			return;
		}

		//认父,此处为数据结构，不考虑是否子树有原父节点，此操作为上层负责
		child->parent = this;

		this->leftChild = child;

	}

	void AddrightChild(BiTree<T>* child)//添加子树,不考虑原本左子树，此操作为上层负责，则操作无意义
	{
		if (!child || child == this)//空树或者自身
		{
			return;
		}

		//认父,此处为数据结构，不考虑是否子树有原父节点，此操作为上层负责
		child->parent = this;

		this->rightChild = child;

	}

	void AddChild(BiTree<T>* tree,int pos)//pos为0时增加左子树，为1时增加右子树,其他操作无意义
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

	//增加父节点
	void AddParent(BiTree<T>* parent,int pos)//pos为0时增加左子树，为1时增加右子树,其他操作无意义
	{
		if (!parent||parent==this)
		{
			return;
		}

		parent->AddChild(this, pos);
	}

	//删除左子树
	void DeleteleftChild()
	{
		//有左子树，并且不是线索
		if (this->leftChild && !this->leftTag)
		{
			this->leftChild->parent = nullptr;
			this->leftChild = nullptr;
		}
		return;
	}

	//删除右子树
	void DeleterightChild()
	{
		//有右子树，并且不是线索
		if (this->rightChild && !this->rightTag)
		{
			this->rightChild->parent = nullptr;
			this->rightChild = nullptr;
		}
		return;
	}

	//删除子树
	void DeleteChild(int pos)
	{
		//不考虑空间问题
		if (pos == 0)
		{
			DeleteleftChild();
		}
		else if (pos == 1)
		{
			DeleterightChild();
		}
	}

	//删除父节点
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
	//创建一个data为e的树节点
	BiTree<T>* CreatTree(T e)
	{
		return new BiTree<T>(e);
	}

	//以一个数组创造一棵树,没有线索化
	BiTree<T>* CreatTree(T a[], int begin, int number)//begin即数组起始位置
	{
		if (begin < 0 || begin >= number)
		{
			return nullptr;
		}

		//根节点
		BiTree<T>* tree = new BiTree<T>(a[begin]);

		//子树
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

	//复制一个树,如果有树为空操作无意义，并且两树不相交
	BiTree<T>* CreatTree(BiTree<T>* tree)
	{
		//空树
		if (!tree)
		{
			return nullptr;
		}

		BiTree<T>* new_tree = new BiTree<T>(tree->data);

		//创建左子树
		BiTree<T>* p;
		if (tree->leftChild && !tree->leftTag)
		{
			p = CreatTree(tree->leftChild);
		}

		//创建右子树
		BiTree<T>* q;
		if (tree->rightChild && !tree->rightTag)
		{
		     q = CreatTree(tree->rightChild);
		}

		new_tree->AddleftChild(p);

		new_tree->AddrightChild(q);

		return new_tree;


	}

	//不考虑一个不存任何数据的节点，认为此节点为空树无意义
	//此函数只负责tree节点及其子树
	//不负责创建树节点
	void InitTree(BiTree<T>* tree, T e)//以e初始化或重置tree,覆盖原Tree,但如果有父节点不切断与父节点联系。
	{
		if (tree != nullptr)
		{
			//清空子树
			//有子树时并且不是线索递归销毁销毁子树
			if (tree->leftChild && !tree->leftTag)
			{
				ClearTree(tree->leftChild);
			}

			if (tree->rightChild && !tree->rightTag)
			{
				ClearTree(tree->rightChild);
			}
	

			tree->data = e;//改变数据

			return;
		}

		//tree为空，即空树时,操作无意义
	}

	//释放整棵树为空树，如果有父节点则切断联系
	void ClearTree(BiTree<T>* tree)
	{
		//空节点直接返回
		if (tree == nullptr)
		{
			return;
		}

		//（如果有）切断与父节点联系
		tree->DeleteParent();


		//有子树时递归销毁销毁子树
		if (tree->leftChild && !tree->leftTag)
		{
			ClearTree(tree->leftChild);
		}

		if (tree->rightChild && !tree->rightTag)
		{
			ClearTree(tree->rightChild);
		}

		//销毁此节点
		delete tree;

		//置空
		tree = nullptr;

		return;

	}

	//判断是否为空树
	bool TreeEmpty(BiTree<T>* tree)
	{
		if (tree)
		{
			return false;
		}

		return true;
	}

	//返回Tree的深度
	int TreeDepth(BiTree<T>* tree)
	{
		//空树
		if (!tree)
		{
			return 0;
		}

		//非线索
		int left=0, right=0;//纪律左右子树深度

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

	//返回根节点
	BiTree<T>* RootTree(BiTree<T>* tree)
	{
		//空树
		if (!tree)
		{
			return nullptr;
		}

		//为根节点
		if (tree->parent == nullptr)
		{
			return tree;
		}

		//不是根节点则向上递归
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
			//为空时
			return NULL;
		}
	}

	//更改数据
	void AssignTree(BiTree<T>* tree, T e)
	{
		//空树
		if (!tree)
		{
			return;
		}

		tree->data = e;

		return;
	}

	//返回父节点
	BiTree<T>* ParentTree(BiTree<T>* tree)
	{
		//空树
		if (!tree)
		{
			return nullptr;
		}

		//为根节点时返回nullptr
		return tree->parent;
	}

	BiTree<T>* LeftChild(BiTree<T>* tree)
	{
		//空树
		if (!tree)
		{
			return nullptr;
		}

		//不为线索
		if (!tree->leftTag)
		{
			//可能为空
			return tree->leftChild;
		}

		//左子树为空
		return nullptr;
	}

	BiTree<T>* RightChild(BiTree<T>* tree)
	{
		//空树
		if (!tree)
		{
			return nullptr;
		}

		//不为线索
		if (!tree->rightTag)
		{
			//可能为空
			return tree->rightChild;
		}

		//右子树为空
		return nullptr;
	}

	//返回tree的左兄弟。若tree是parent的左孩子或无左兄弟，则返回空
	BiTree<T>* LeftSibling(BiTree<T>* tree)
	{
		//空树或者无父节点或者父节点左子树为线索
		if (!tree||tree->parent||tree->parent->leftTag)
		{
			return nullptr;
		}

		//tree为左子树,parent左子树为空
		if (tree->parent->leftChild==tree||!tree->parent->leftChild)
		{
			//可能为空
			return nullptr;
		}

		//返回父节点的左子树，即tree的左兄弟
		return tree->parent->leftChild;
	}

	//返回tree的右兄弟。若tree是parent的右孩子或无右兄弟，则返回空
	BiTree<T>* RightSibling(BiTree<T>* tree)
	{
		//空树或者无父节点或者父节点右子树为线索
		if (!tree || tree->parent||tree->parent->rightTag)
		{
			return nullptr;
		}

		//tree为右子树,parent右子树为空
		if (tree->parent->rightChild == tree || !tree->parent->rightChild)
		{
			//可能为空
			return nullptr;
		}

		//返回父节点的右子树，即tree的右兄弟
		return tree->parent->rightChild;
	}

	//插入后线索失效，需要重新生成
	//将child插入为parent的左节点，两棵树不相交，如果有原左子树，则变为child的最右下子树
	void InsertleftChild(BiTree<T>* parent, BiTree<T>* child)
	{
		//一者为空或者两者相同
		if (!parent || !child || parent == child)
		{
			return;
		}

		//左子树不空且不为线索
		BiTree<T>* p = nullptr;
		if (parent->leftChild && !parent->leftTag)
		{
			p = parent->leftChild;//记录下来
		}

		//插入
		parent->AddleftChild(child);

		BiTree<T>* q = child->rightChild;
		while (q->rightChild && !q->rightTag)
		{
			q = q->rightChild;
		}
		//找到child最右下子树
		q->AddrightChild(p);
	}

	//将child插入为parent的左节点，两棵树不相交，如果有原右子树，则变为child的最右下子树
	void InsertRightChild(BiTree<T>* parent, BiTree<T>* child)
	{
		//一者为空或者两者相同
		if (!parent || !child || parent == child)
		{
			return;
		}

		//右子树不空且不为线索
		BiTree<T>* p = nullptr;
		if (parent->rightChild && !parent->rightTag)
		{
			p = parent->rightChild;//记录下来
		}

		//插入
		parent->AddrightChild(child);

		BiTree<T>* q = child->rightChild;
		while (q->rightChild && !q->rightTag)
		{
			q = q->rightChild;
		}
		//找到child最右下子树
		q->AddrightChild(p);
	}

	//pos为0插入左子树，1插入右子树，其他无意义
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

	//删除后线索失效
	//tree删除左子树，返回左子树，不负责释放空间
	BiTree<T>* DeleteLeftChild(BiTree<T>* tree)
	{
		//空树或者左子树为空或者为线索
		if (!tree || !tree->leftChild || tree->leftTag)
		{
			return nullptr;
		}

		//记录左子树
		BiTree<T>* p = tree->leftChild;

		tree->DeleteleftChild();

		return p;
	}

	//tree删除右子树，返回右子树，不负责释放空间
	BiTree<T>* DeleteRightChild(BiTree<T>* tree)
	{
		//空树或者右子树为空或者为线索
		if (!tree || !tree->rightChild || tree->rightTag)
		{
			return nullptr;
		}

		//记录右子树
		BiTree<T>* p = tree->rightChild;

		tree->DeleterightChild();

		return p;
	}

	//pos为0删除左子树，1删除右子树，其他无意义
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

	//前序遍历
	//这里function不一定返回空，具体视情况而立,默认为输出data
	void PreOrderTraverseTree(BiTree<T>* tree,/*处理函数*/std::function<void(T&)> address = [](T& e)->void {std::cout << e; })
	{
		//空树
		if (!tree)
		{
			return;
		}

		//根节点
		address(tree->data);

		//遍历左子树
		if (tree->leftChild && !tree->leftTag)
		{
			PreOrderTraverseTree(tree->leftChild, address);
		}

		//遍历右子树
		if (tree->rightChild && !tree->rightTag)
		{
			PreOrderTraverseTree(tree->rightChild, address);
		}

		return;

	}

	//中序遍历
	void InOrderTraverseTree(BiTree<T>* tree,/*处理函数*/std::function<void(T&)> address = [](T& e)->void {std::cout << e; })
	{
		//空树
		if (!tree)
		{
			return;
		}

		//遍历左子树
		if (tree->leftChild && !tree->leftTag)
		{
			InOrderTraverseTree(tree->leftChild, address);
		}

		//根节点
		address(tree->data);

		//遍历右子树
		if (tree->rightChild && !tree->rightTag)
		{
			InOrderTraverseTree(tree->rightChild, address);
		}

		return;

	}

	//后序遍历
	void PostOrderTraverseTree(BiTree<T>* tree,/*处理函数*/std::function<void(T&)> address = [](T& e)->void {std::cout << e; })
	{
		//空树
		if (!tree)
		{
			return;
		}

		//遍历左子树
		if (tree->leftChild && !tree->leftTag)
		{
			InOrderTraverseTree(tree->leftChild, address);
		}

		//遍历右子树
		if (tree->rightChild && !tree->rightTag)
		{
			InOrderTraverseTree(tree->rightChild, address);
		}

		//根节点
		address(tree->data);

		return;

	}

	//层次遍历
	void LevelOrderTraverseTree(BiTree<T>* tree,/*处理函数*/std::function<void(T&)> address = [](T& e)->void {std::cout << e; })
	{
		//空树
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

			//左子树
			if (p->leftChild && !p->leftTag)
			{
				trees.push(p->leftChild);
			}

			//遍历右子树
			if (p->rightChild && !p->rightTag)
			{
				trees.push(p->rightChild);
			}

		}

		return;

	}

	//返回节点数
	int TreeNumber(BiTree<T>* tree)
	{
		//空树
		if (!tree)
		{
			return 0;
		}

		int number = 1;

		//左子树不空，并且不是线索
		if (tree->leftChild && !tree->leftTag)
		{
			number += TreeNumber(tree->leftChild);
		}

		//右子树不空，并且不是线索
		if (tree->rightChild && !tree->rightTag)
		{
			number += TreeNumber(tree->rightChild);
		}

		return number;
	}
	
	//消除线索化，使得更改过的树重新线索化
	void DeleteThreading(BiTree<T>* tree)
	{
		//空树
		if (!tree)
		{
			return;
		}
		
		//取消左子树线索化
		if (tree->leftTag)
		{
			tree->leftChild = nullptr;
			tree->leftTag = false;
		}
		else
		{
			DeleteThreading(tree->leftChild);
		}

		//取消右子树线索化
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


	//默认tree没有线索化，如果已经线索化需要消除线索化
	//pre是全局变址，初始化时其右孩子指针为空，便于在树的最左点开始建线索
	//二叉树中序线索化
	void InThreading(BiTree<T>* tree, BiTree<T>* pre)
	{
		//非空树
		if (tree)
		{
			InThreading(tree->leftChild, pre);//左子树递归线索化

			//左子树为空,线索化
			if (!tree->leftChild)
			{
				tree->leftTag = true;
				//左子树指向前驱，即pre
				tree->leftChild = pre;
			}
			else
			{
				tree->leftTag = false;
			}

			//前驱右子树为空
			if (!pre->rightChild)
			{
				pre->rightTag = true;
				//右子树指向后继，即tree
				pre->rightChild = tree;
			}
			else
			{
				pre->rightTag = false;
			}

			//前移
			pre = tree;

			InThreading(tree->rightChild, pre);//右子树递归线索化
		
		}
	}

	//返回一个左子树指向根节点的头结点Thrt
	//带头结点的二叉树中序线索化
	BiTree<T>* InOrderThreading(BiTree<T>* tree)
	{
		//中序遍历二叉树，并将其线索化。Thrt指向头结点
		BiTree<T>* Thrt = new BiTree<T>();//创建头结点

		Thrt->leftTag = false;//头结点有左子树，若树非空，则其左子树为树的根节点
		Thrt->rightTag = true;//头结点的右子树指针为右线索
		Thrt->rightChild = Thrt;//初始化右指针指向头结点
		
		if (!tree)
		{
			Thrt->leftChild = Thrt;//如果树为空，左指针也指向头结点
		}
		else
		{
			Thrt->leftChild = tree;//左指针指向根结点
			//pre初值指向头结点
			BiTree<T>* pre = Thrt;
			InThreading(tree, pre);//线索化
			//pre最后为最右结点，pre的右线索指向头结点
			pre->rightChild = Thrt;
			pre->rightTag = true;
			Thrt->rightChild = pre;//头结点的右线索指向pre，即树的最右结点
		}

		return Thrt;//返回头结点
	}




};