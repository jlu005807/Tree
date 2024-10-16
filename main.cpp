#include"Common_Tree.h"
#include"Seq_BiTree.h"
#include"Link_BiTree.h"
#include"HuffmanTree.h"
#include"Expression_Tree.h"

int main()
{
	//Complete_Tree
	//int a[9] = { 1,2,3,4,5,6,7,8,9 };
	//Complete_BiTree<int> bitree(a, 9);
	//bitree.PreOrderTraverseTree(0);
	//system("Pause");

	//Common_Tree
	//Tree_Manager<int> manager;
	//int b[9] = { 1,2,3,4,5,6,7,8,9 };
	//Tree<int>* root=manager.CreatTree(b,0,9);
	//manager.LevelOrderTraverseTree(root);
	//system("Pause");

	//manager.DeleteChildTree(root, 2);
	//manager.LevelOrderTraverseTree(root);
	//system("Pause");

	//Tree<int>* p = manager.CreatTree(b, 2, 9);
	//manager.LevelOrderTraverseTree(p);
	//system("pause");

	//manager.InsertChildTree(root, p);
	//manager.LevelOrderTraverseTree(root);
	//std::cout << std::endl << manager.TreeNumber(root);
	//system("Pause");

	//manager.ClearTree(root);

	////Link_BiTree
	//BiTree_Manager<int> bimanager;
	//int c[9] = { 1,2,3,4,5,6,7,8,9 };
	//BiTree<int>* root1 = bimanager.CreatTree(c, 0, 9);
	//bimanager.PreOrderTraverseTree(root1);
	//system("Pause");

	//bimanager.DeleteChild(root1, 1);
	//bimanager.LevelOrderTraverseTree(root1);
	//system("Pause");

	//BiTree<int>* p1 = bimanager.CreatTree(c, 2, 9);
	//bimanager.LevelOrderTraverseTree(p1);
	//system("Pause");

	//bimanager.InsertChild(root1, p1, 1);
	//bimanager.PostOrderTraverseTree(root1);
	//system("Pause");

	//bimanager.Non_Recursive_PostOrderTraverseTree(root1);
	//system("Pause");

	//bimanager.InOrderThreading(root1);

	//bimanager.DeleteThreading(root1);

	//bimanager.ClearTree(root1);

	//HuffamanTree
	//HuffmanTree_manager<int> human;

	//int a[8] = {5,28,7,8,14,23,3,11};

	//HuffmanTree<int>* tree = human.CreatTree(a, 8);

	//for (int i = 1; i <= 2 * 8 - 1; i++)
	//{
	//	std::cout << i <<" "<< tree[i].weight << " " << tree[i].parent << " " << tree[i].lchild << " " << tree[i].rchild << std::endl;
	//}

	//std::vector<std::string> v;

	//human.HuffmanTreeCode(tree, v, 8);

	//Expression_Tree
	//Expression_Tree expt;

	//std::string  v("(1+1)*2-4");

	//auto tree = expt.InitExpTree(v);
	//
	//std::cout << expt.EvaluateExpTree(tree);

}