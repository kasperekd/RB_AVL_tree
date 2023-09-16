// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#include "RB.h"

struct rbtree rb_null = { RB_NULL, RB_NULL, RB_NULL, 'B', nullptr, 0 }; // null node

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
	temp->parent = RB_NULL;
	temp->left = RB_NULL;
	temp->right = RB_NULL;

	return temp;
}

void rbtree_left_rotate(rbtree **root, rbtree *current)
{
	rbtree *y = current->right;
	current->right = y->left;
	if (y->left != RB_NULL)
	{ 
		y->left->parent = current;
	}
	y->parent = current->parent;
	if (current->parent == RB_NULL)
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
	if (y->right != RB_NULL)
	{ 
		y->right->parent = current;
	}
	y->parent = current->parent;
	if (current->parent == RB_NULL)
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
			if (uncle->color == 'R')
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
			if (uncle->color == 'R')
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
				if (current->parent->parent != RB_NULL)
				{ 
					current->parent->parent->color = 'R';
					rbtree_left_rotate(&*root, current->parent->parent);
				}
			}
		}
	}
	(*root)->color = 'B';
	
}

void rbtree_add(struct rbtree **root, char *key, int value)
{
	struct rbtree *current = *root;
	struct rbtree *parent = RB_NULL;

	while (current != RB_NULL)
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

	if (new_node == RB_NULL)
	{
		return;
	}

	new_node->parent = parent;

	if (parent == RB_NULL)
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

struct rbtree *rbtree_lookup(struct rbtree *tree, char *key)
{
	while (tree != RB_NULL)
	{
		if (strcmp(key, tree->key) == 0)
			return tree;
		else if (strcmp(tree->key, key) > 0)
			tree = tree->left;
		else
			tree = tree->right;
	}
	return tree;
}

void rbtree_transplant(struct rbtree **root, struct rbtree *u, struct rbtree *v)
{
	if (u->parent == RB_NULL)
		*root = v;
	else if (u == u->parent->left)
		u->parent->left = v;
	else
		u->parent->right = v;
	if (v != RB_NULL)
		v->parent = u->parent;
}

struct rbtree *rbtree_min(struct rbtree *tree)
{
	if (tree == RB_NULL)
	{
		return RB_NULL;
	}
	while (tree->left != RB_NULL)
	{ 
		tree = tree->left;
	}
	return tree;
}

struct rbtree *rbtree_max(struct rbtree *tree)
{
	if (tree == RB_NULL)
	{ 
		return RB_NULL;
	}
	while (tree->right != RB_NULL)
	{ 
		tree = tree->right;
	}
	return tree;
}

void rbtree_delete_fixup(struct rbtree **root, struct rbtree *x)
{
	while (x != *root && x->color == 'B')
	{
		if (x == x->parent->left)
		{
			struct rbtree *w = x->parent->right;
			if (w->color == 'R')
			{
				w->color = 'B';
				x->parent->color = 'R';
				rbtree_left_rotate(root, x->parent);
				w = x->parent->right;
			}
			if (w->left->color == 'B' && w->right->color == 'B')
			{
				w->color = 'R';
				x = x->parent;
			}
			else
			{
				if (w->right->color == 'B')
				{
					w->left->color = 'B';
					w->color = 'R';
					rbtree_right_rotate(root, w);
					w = x->parent->right;
				}
				w->color = x->parent->color;
				x->parent->color = 'B';
				w->right->color = 'B';
				rbtree_left_rotate(root, x->parent);
				x = *root;
			}
		}
		else
		{
			struct rbtree *w = x->parent->left;
			if (w->color == 'R')
			{
				w->color = 'B';
				x->parent->color = 'R';
				rbtree_right_rotate(root, x->parent);
				w = x->parent->left;
			}
			if (w->left->color == 'B' && w->right->color == 'B')
			{
				w->color = 'R';
				x = x->parent;
			}
			else
			{
				if (w->left->color == 'B')
				{
					w->right->color = 'B';
					w->color = 'R';
					rbtree_left_rotate(root, w);
					w = x->parent->left;
				}
				w->color = x->parent->color;
				x->parent->color = 'B';
				w->left->color = 'B';;
				rbtree_right_rotate(root, x->parent);
				x = *root;
			}
		}
	}
	x->color = 'B';
}

rbtree *rbtree_delete(rbtree *root, char *key)
{
	rbtree *z;
	if (!(z = rbtree_lookup(root, key)))
	{
		return root;
	}
	if (z == root && z->left == RB_NULL && z->right == RB_NULL) // проверка на корень дерева
	{
		delete z;
		return RB_NULL;
	}
	rbtree *x = RB_NULL;
	rbtree *y = z;
	char ycolor = y->color;

	if (z->left == RB_NULL && z->right == RB_NULL) // проверка на лист
	{
		//x = RB_NULL;
		rbtree_transplant(&root, z, RB_NULL);
	}
	else if (z->left == RB_NULL)
	{
		x = z->right;
		rbtree_transplant(&root, z, z->right);
	}
	else if (z->right == RB_NULL)
	{
		x = z->left;
		rbtree_transplant(&root, z, z->left);
	}
	else
	{
		y = rbtree_max(z->left);
		ycolor = y->color;
		x = y->left;

		if (y->parent != z)
		{
			rbtree_transplant(&root, y, y->left);
			y->left = z->left;
			y->left->parent = y;
		}
		rbtree_transplant(&root, z, y);
		y->right = z->right;
		y->right->parent = y;
		y->color = z->color;
	}

	delete z;
	z = RB_NULL;

	rbtree_delete_fixup(&root, x);

	return root;
}

void printTree(std::ostream &stream, rbtree *tree, int space)
{
	if (tree == RB_NULL)
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
	while (current != RB_NULL || !stack.empty())
	{
		while (current != RB_NULL)
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