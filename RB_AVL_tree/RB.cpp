// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#include "RB.h"

struct rbtree *TNULL = nullptr; // Для проверки без ошибок

struct rbtree *create_node(char *key, int value)
{
	struct rbtree *temp = new(std::nothrow) rbtree[sizeof(struct rbtree)];

	if (temp == nullptr) 
	{
		return nullptr;
	}

	temp->key = key;
	temp->value = value;
	temp->color = 'R';
	temp->parent = nullptr;
	temp->left = TNULL;
	temp->right = TNULL;

	return temp;
}

void rbtree_left_rotate(rbtree **root, rbtree *current)
{
	rbtree *y = current->right;
	current->right = y->left;
	if (y->left != TNULL) 
	{ 
		y->left->parent = current;
	}
	y->parent = current->parent;
	if (current->parent == TNULL) 
	{
		*root = y;
	}
	else if (current == current->parent->left)
	{
		current->parent->left = y;
	}
	else 
	{
		current->parent->right = y;
	}
	y->left = current;
	current->parent = y;
}

void rbtree_right_rotate(rbtree **root, rbtree *current)
{
	rbtree *y = current->left;
	current->left = y->right;
	if (y->right != TNULL) 
	{ 
		y->right->parent = current;
	}
	y->parent = current->parent;
	if (current->parent == TNULL)
	{
		*root = y;
	}
	else if (current == current->parent->right)
	{
		current->parent->right = y;
	}
	else 
	{
		current->parent->left = y;
	}
	y->right = current;
	current->parent = y;
}

void rbtree_fix(rbtree **root, rbtree *current)
{
	while (current != *root && current->parent->color == 'R')
	{
		if (current->parent == current->parent->parent->left)
		{
			rbtree *uncle = current->parent->parent->right;
			if (uncle != TNULL && uncle->color == 'R') 
			{ 
				current->parent->color = 'B';
				uncle->color = 'B';
				current->parent->parent->color = 'R';
				current = current->parent->parent;
			}
			else
			{
				if (current == current->parent->right)
				{
					current = current->parent;
					rbtree_left_rotate(&*root, current);
				}
				current->parent->color = 'B';
				current->parent->parent->color = 'R';
				rbtree_right_rotate(&*root, current->parent->parent);
			}
		}
		else
		{
			rbtree *uncle = current->parent->parent->left;
			if (uncle != TNULL && uncle->color == 'R') 
			{
				current->parent->color = 'B';
				uncle->color = 'B';
				current->parent->parent->color = 'R';
				current = current->parent->parent;
			}
			else
			{
				if (current == current->parent->left)
				{
					current = current->parent;
					rbtree_right_rotate(&*root, current);
				}
				current->parent->color = 'B';
				if (current->parent->parent != TNULL) 
				{ 
					current->parent->parent->color = 'R';
					rbtree_left_rotate(&*root, current->parent->parent);
				}
			}
		}
	}
	rbtree *temp = *root;
	temp->color = 'B';
}

void rbtree_add(struct rbtree **root, char *key, int value)
{
	struct rbtree *current = *root;
	struct rbtree *parent = TNULL; 

	while (current != TNULL)
	{
		parent = current;
		if (strcmp(key, current->key) < 0)
		{
			current = current->left;
		}
		else if (strcmp(key, current->key) > 0)
		{
			current = current->right;
		}
		else
		{
			current->value = value;
			return;
		}
	}

	struct rbtree *new_node = create_node(key, value);

	if (new_node == nullptr)
	{
		return;
	}

	new_node->parent = parent;

	if (parent == TNULL) 
	{
		*root = new_node;
	}
	else if (strcmp(key, parent->key) < 0)
	{
		parent->left = new_node;
	}
	else
	{
		parent->right = new_node;
	}

	rbtree_fix(&*root, new_node);
}

void printTree(std::ostream &stream, rbtree *tree, int space)
{
	if (!tree)
		return;
	int count = 2;
	space += count;
	printTree(stream, tree->right, space);
	for (int i = count; i < space; ++i)
		stream << "  ";
	stream << tree->key << "(" << tree->color << ")" << std::endl;
	printTree(stream, tree->left, space);
}

void fTree(const char NAME_TREE[], rbtree *root)
{
	std::ofstream fout;
	fout.open(NAME_TREE);
	if (!fout)
	{
		std::cout << "\nFailed to create file for Tree\n";
		return;
	}

	printTree(fout, root);
	fout.close();
}


void rbtree_free(rbtree **tree)
{
	if (tree == nullptr)
	{
		return;
	}
	std::stack<rbtree *> stack;
	rbtree *current = *tree;
	while (current != nullptr || !stack.empty())
	{
		while (current != nullptr)
		{
			stack.push(current);
			current = current->left;
		}
		current = stack.top();
		stack.pop();
		rbtree *temp = current;
		current = current->right;
		delete temp;
	}
	*tree = nullptr;
}