// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#include <iostream>
#include "IO.h"

using namespace std;

const char NAME_OF_DIC[] = "words.txt";
int AMOUNT_TO_READ = 50000;

int main()
{
	int dic_count;

	if (char** dictionary = readDictionary(NAME_OF_DIC, &dic_count, AMOUNT_TO_READ)) // Reading the original dictionary
	{
		for (int i = 0; i < dic_count; i++)
		{
			cout << dictionary[i] << endl;
		}		
	}
	else
	{
		cout<< "Dictionary reading error";
		exit;
	}
}

