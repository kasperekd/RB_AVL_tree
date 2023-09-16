﻿// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#include <iostream>
#include "RB.h"
#include "IO.h"

//https://www.geeksforgeeks.org/tree-traversals-inorder-preorder-and-postorder/
//https://www.cs.usfca.edu/~galles/visualization/RedBlack.html
//https://github.com/ocornut/imgui

using namespace std;

const char NAME_OF_DIC[] = "words.txt";
int AMOUNT_TO_READ = 50000;

int main()
{
	int dic_count;
	char **dictionary = nullptr;

	if (dictionary = readDictionary(NAME_OF_DIC, &dic_count, AMOUNT_TO_READ)) // Reading the original dictionary
	{
		cout << "Number of items read: " << dic_count << endl;
	}
	else
	{
		cout<< "Dictionary reading error";
		return 1;
	}

	struct rbtree *RBroot = RB_NULL;
	
	rbtree_add(&RBroot, dictionary[0], (int)dictionary[0]);
	for (size_t i = 1; i < dic_count; i++)
	{
		rbtree_add(&RBroot, dictionary[i], (int)dictionary[i]);
	}

	fTree("rb1.txt", RBroot);

	char for_delete[] = "aaaa";
	char for_delete2[] = "aa";
	char for_delete3[] = "aaa";
	char for_delete4[] = "aaaa";

	RBroot = rbtree_delete(RBroot, for_delete);
	//RBroot = rbtree_delete(RBroot, for_delete2);
	//RBroot = rbtree_delete(RBroot, for_delete3);
	//RBroot = rbtree_delete(RBroot, for_delete4);

	//rbtree_add(&RBroot, for_delete, (int)dictionary[0]);

	if (dic_count < 500) // output tree to file
	{
		fTree("rb.txt", RBroot);
	}
	else
	{
		cout << "The tree contains too many items to display. Trees with no more than 500 elements are supported for display\n";
	}
	
	rbtree_free(&RBroot);

	if (dictionary) // clear dictionary
	{
		for (int i = 0; i < dic_count; i++)
		{
			delete[] dictionary[i];
		}
		delete[] dictionary;
	}

	return 0;
}

