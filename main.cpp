#include"Common_Tree.h"
#include"Seq_BiTree.h"


int main()
{
	//Complete_Tree
	//int a[9] = { 1,2,3,4,5,6,7,8,9 };
	//Complete_BiTree<int> bitree(a, 9);
	//bitree.LevelOrderTraverseTree(0);
	//system("Pause");

	//Common_Tree
	Tree_Manager<int> manager;
	int b[9] = { 1,2,3,4,5,6,7,8,9 };
	Tree<int>* root=manager.CreatTree(b,0,9);
	manager.LevelOrderTraverseTree(root);
	system("Pause");

	manager.DeleteChildTree(root, 2);
	manager.LevelOrderTraverseTree(root);
	system("Pause");

	Tree<int>* p = manager.CreatTree(b, 2, 9);
	manager.InsertChildTree(root, p);
	manager.LevelOrderTraverseTree(root);
	std::cout << std::endl << manager.TreeNumber(root);
	system("Pause");
	

}