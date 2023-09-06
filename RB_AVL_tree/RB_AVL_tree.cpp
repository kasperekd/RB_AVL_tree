// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#include <iostream>
#include "RB.h"
#include "IO.h"

//https://www.geeksforgeeks.org/tree-traversals-inorder-preorder-and-postorder/
//https://www.cs.usfca.edu/~galles/visualization/RedBlack.html
//https://github.com/ocornut/imgui

using namespace std;

const char NAME_OF_DIC[] = "words.txt";
int AMOUNT_TO_READ = 20;

int main()
{
	int dic_count;
	char **dictionary = NULL;

	if (dictionary = readDictionary(NAME_OF_DIC, &dic_count, AMOUNT_TO_READ)) // Reading the original dictionary
	{
		cout << "Number of items read: " << dic_count << endl;
	}
	else
	{
		cout<< "Dictionary reading error";
		return 1;
	}

	struct rbtree *RBroot = NULL;
	
	rbtree_add(&RBroot, dictionary[0], (int)dictionary[0]);
	for (size_t i = 1; i < dic_count; i++)
	{
		rbtree_add(&RBroot, dictionary[i], (int)dictionary[i]);
	}

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

