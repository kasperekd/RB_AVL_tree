// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#include "RB.h"

struct rbtree *create_node(char *key, int value)
{
	struct rbtree *temp = new rbtree[sizeof(struct rbtree)];

	temp->key = key; 
	temp->value = value;
	temp->color = 0;
	temp->parent = NULL;
	temp->left = NULL; 
	temp->right = NULL; 

	return temp;
}

void rbtree_add(struct rbtree **root, char *key, int value)
{
	struct rbtree *current = *root;
	struct rbtree *parent = NULL;

	while (current != NULL) 
	{
		if (strcmp(key, current->key) < 0) // if the key is less than the current nodes key, go left
		{
			parent = current;
			current = current->left;
		}
		else if (strcmp(key, current->key) > 0) // if the key is greater than the current nodes key, go right
		{
			parent = current;
			current = current->right;
		}
		else // if the key already exists in the tree, update the value
		{ 
			current->value = value;
			return;
		}
	}

	struct rbtree *new_node = create_node(key, value); 

	if (parent == NULL) // if the tree was empty, the new node becomes the root
	{ 
		*root = new_node;
	}
	else if (strcmp(key, parent->key) < 0) // if the key is less than the parent nodes key, the new node becomes the left child
	{ 
		parent->left = new_node;
		new_node->parent = parent;
	}
	else //if the key is greater than the parent nodes key, the new node becomes the right child
	{ 
		parent->right = new_node;
		new_node->parent = parent;
	}
}