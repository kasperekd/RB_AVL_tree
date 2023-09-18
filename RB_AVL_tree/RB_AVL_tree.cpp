// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#include <iostream>
#include <chrono>
#include "RB.h"
#include "IO.h"

//https://www.geeksforgeeks.org/tree-traversals-inorder-preorder-and-postorder/
//https://www.cs.usfca.edu/~galles/visualization/RedBlack.html
//https://github.com/ocornut/imgui

using namespace std;

const char NAME_OF_DIC[] = "words.txt";
const char NAME_OF_EXP[] = "lookup.txt";
int STEP = 2500;
int AMOUNT_TO_READ = 500000;

int main()
{
	int dic_count;
	char **dictionary = nullptr;
	struct rbtree *RBroot;

	if (dictionary = readDictionary(NAME_OF_DIC, &dic_count, AMOUNT_TO_READ)) // Reading the original dictionary
	{
		cout << "Number of items read: " << dic_count << endl;
	}
	else
	{
		cout<< "Dictionary reading error";
		return 1;
	}

	//========EXP DELETE========//
	if (dic_count >= 10)
	{
		char forDelete[] = "aaberg";
		RBroot = RB_NULL;

		rbtree_add(&RBroot, dictionary[0], (int)dictionary[0]);
		for (int i = 1; i < 10; i++)
		{
			rbtree_add(&RBroot, dictionary[i], (int)dictionary[i]);
		}

		fTree("preDelete.txt", RBroot);
		rbtree_delete(RBroot, forDelete);
		fTree("postDelete.txt", RBroot);
		rbtree_free(&RBroot);
	}
	
	//========EXP DELETE========//

	//========EXP LOOLUP========//
	RBroot = RB_NULL;
	ofstream out;
	out.open(NAME_OF_EXP);
	out.precision(8);
	

	if (!out)
	{
		cout << "\nFailed to create file for EXP5\n";
	}
	else
	{
		rbtree_add(&RBroot, dictionary[0], (int)dictionary[0]);
		for (int i = 2; i < dic_count && i + STEP - 2 <= dic_count; i += STEP)
		{
			for (int j = i; j < i + STEP; j++)
			{
				rbtree_add(&RBroot, dictionary[j], (int)dictionary[j]);
			}
			char *word = dictionary[i];
			auto begin = chrono::steady_clock::now();
			struct rbtree *finded = rbtree_lookup(RBroot, word);
			auto end_t = std::chrono::steady_clock::now();
			auto elapsed_us = chrono::duration_cast<chrono::nanoseconds>(end_t - begin);
			out << fixed << i + STEP - 2 << ": " << elapsed_us.count() / 1000000000.0 << '\t'<< finded->key << endl;
		}
		out.close();
	}
	//========EXP LOOLUP========//

	fTree("rb1.txt", RBroot);

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

