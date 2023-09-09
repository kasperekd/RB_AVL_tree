// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#include "IO.h"

using namespace std;

char **readDictionary(const char DIC_NAME[], int *SIZE_OF_DIC, int amount)
{
	ifstream fread;
	fread.open(DIC_NAME, ios::in);

	if (!fread) return nullptr;

	string buffer;
	int max_size = 0;
	*SIZE_OF_DIC = 0;

	while (fread >> buffer && *SIZE_OF_DIC < amount)
	{
		if (buffer.length() >= max_size) max_size = buffer.length()+1;
		*SIZE_OF_DIC = *SIZE_OF_DIC + 1;
	}

	fread.clear();
	fread.seekg(0);

	char **out = new char *[*SIZE_OF_DIC];
	for (int i = 0; i < *SIZE_OF_DIC; i++)
	{
		out[i] = new char[max_size];
	}

	for (int i = 0; i < *SIZE_OF_DIC; i++)
	{
		fread.getline(out[i], max_size);
	}
	fread.close();

	return out;
}