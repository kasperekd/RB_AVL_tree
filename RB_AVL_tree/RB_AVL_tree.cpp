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

int main(int argc, char **argv)
{
	int dic_count;
	char **dictionary = nullptr;
	struct rbtree *RBroot;

	if (argc > 1)
	{
		AMOUNT_TO_READ = atoi(argv[1]);
		if (argc > 2)
		{
			STEP = atoi(argv[2]);
			if (STEP < 1)
			{
				STEP = 1;
			}
		}
	}

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
		char forDelete[] = "aa";
		RBroot = RB_NULL;

		rbtree_add(&RBroot, dictionary[0], 0);
		for (int i = 1; i < 10; i++)
		{
			rbtree_add(&RBroot, dictionary[i], i);
		}

		if (RBroot != RB_NULL || !RBroot)
		{
			fTree("preDelete.txt", RBroot);
			rbtree_delete(&RBroot, forDelete);
			fTree("postDelete.txt", RBroot);
			rbtree_free(&RBroot);

			if (!RBroot)
			{
				cout << "Removal experiment is done\n";
			}
		}
		
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
		if (STEP > dic_count)
		{
			cout << "dictionary size(" << dic_count << ") less than step(" << STEP <<")\n";
		}
		else
		{
			rbtree_add(&RBroot, dictionary[0], 0);
			for (int i = 1; i < dic_count && i + STEP - 1 <= dic_count; i += STEP)
			{
				for (int j = i; j < i + STEP; j++)
				{
					rbtree_add(&RBroot, dictionary[j - 1], j - 1);
				}
				char *word = dictionary[i - 1];
				auto begin = chrono::steady_clock::now();
				struct rbtree *finded = rbtree_lookup(RBroot, word);
				auto end_t = std::chrono::steady_clock::now();
				auto elapsed_us = chrono::duration_cast<chrono::nanoseconds>(end_t - begin);
				out << fixed << i + STEP - 1 << " " << elapsed_us.count() / 1000000000.0 << '\t' << finded->key << endl;
			}
			out.close();
			rbtree_free(&RBroot);
			cout << "Lookup experiment is done\n";
		}
	}
	//========EXP LOOLUP========//

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

