// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#include "RB.h"

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
	temp->left = nullptr;
	temp->right = nullptr;

	return temp;
}

void rbtree_left_rotate(rbtree **root, rbtree *current)
{
	rbtree *y = current->right;
	current->right = y->left;
	if (y->left != nullptr) 
	{ 
		y->left->parent = current;
	}
	y->parent = current->parent;
	if (current->parent == nullptr) 
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
	if (y->right != nullptr) 
	{ 
		y->right->parent = current;
	}
	y->parent = current->parent;
	if (current->parent == nullptr)
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
			if (uncle != nullptr && uncle->color == 'R')
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
			if (uncle != nullptr && uncle->color == 'R') 
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
				if (current->parent->parent != nullptr) 
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
	struct rbtree *parent = nullptr; 

	while (current != nullptr)
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

	if (parent == nullptr) 
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
	while (tree != nullptr)
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

//void rbtree_transplant(rbtree *root, rbtree *u, rbtree *v)
//{
//	if (u->parent == nullptr)
//	{
//		root = v;
//	}
//	else if (u == u->parent->left) 
//	{
//		u->parent->left = v;
//	}
//	else 
//	{
//		u->parent->right = v;
//	}
//	if (v != nullptr && v->parent != nullptr)
//	{
//		v->parent = u->parent;
//	}	
//}

void rbtree_transplant(struct rbtree **root, struct rbtree *u, struct rbtree *v)
{
	if (u->parent == NULL)
		*root = v;
	else if (u == u->parent->left)
		u->parent->left = v;
	else
		u->parent->right = v;
	if (v != NULL)
		v->parent = u->parent;
}

struct rbtree *rbtree_min(struct rbtree *tree)
{
	if (tree == nullptr) 
	{
		return nullptr;
	}
	while (tree->left != nullptr) 
	{ 
		tree = tree->left;
	}
	return tree;
}

struct rbtree *rbtree_max(struct rbtree *tree)
{
	if (tree == nullptr) 
	{ 
		return nullptr;
	}
	while (tree->right != nullptr) 
	{ 
		tree = tree->right;
	}
	return tree;
}

//void rbtree_deletefixup(rbtree *root, rbtree *x)
//{
//	while (x != root && x->color == 'B')
//	{
//		if (x == x->parent->left)
//		{
//			rbtree *w = x->parent->right;
//			if (w->color == 'R')
//			{
//				w->color = 'B';
//				x->parent->color = 'R';
//				rbtree_left_rotate(&root, x->parent);
//				w = x->parent->right;
//			}
//			if (w->left->color == 'B' && w->right->color == 'B')
//			{
//				w->color = 'R';
//				x = x->parent;
//			}
//			else
//			{
//				if (w->right->color == 'B')
//				{
//					w->left->color = 'B';
//					w->color = 'R';
//					rbtree_right_rotate(&root, w);
//					w = x->parent->right;
//				}
//				w->color = x->parent->color;
//				x->parent->color = 'B';
//				w->right->color = 'B';
//				rbtree_left_rotate(&root, x->parent);
//				x = root;
//			}
//		}
//		else
//		{
//			rbtree *w = x->parent->left;
//			if (w->color == 'R')
//			{
//				w->color = 'B';
//				x->parent->color = 'R';
//				rbtree_right_rotate(&root, x->parent);
//				w = x->parent->left;
//			}
//			if (w->right->color == 'B' && w->left->color == 'B')
//			{
//				w->color = 'R';
//				x = x->parent;
//			}
//			else
//			{
//				if (w->left->color == 'B')
//				{
//					w->right->color = 'B';
//					w->color = 'R';
//					rbtree_left_rotate(&root, w);
//					w = x->parent->left;
//				}
//				w->color = x->parent->color;
//				x->parent->color = 'B';
//				w->left->color = 'B';
//				rbtree_right_rotate(&root, x->parent);
//				x = root;
//			}
//		}
//	}
//	x->color = 'B';
//}

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
				w->left->color = 'B';
				rbtree_right_rotate(root, x->parent);
				x = *root;
			}
		}
	}
	x->color = 'B';
}

//rbtree *rbtree_delete(rbtree *root, char *key)
//{
//	rbtree *z;
//	if (!(z = rbtree_lookup(root, key)))
//	{
//		return nullptr;
//	}
//	rbtree *x;
//	rbtree *y = z;
//	char ycolor = y->color;
//	
//	if (z->left == nullptr)
//	{
//		x = z->right;
//		rbtree_transplant(root, z, z->right);
//	}
//	else if (z->right == nullptr)
//	{
//		x = z->left;
//		rbtree_transplant(root, z, z->left);
//	}
//	else
//	{
//		y = rbtree_min(z->right);
//		ycolor = y->color;
//		x = y->right;
//
//		if (y->parent == z)
//		{
//			x->parent = y;
//		}
//		else
//		{
//			rbtree_transplant(root, y, y->right);
//			y->right = z->right;
//			y->right->parent = y;
//		}
//
//		rbtree_transplant(root, z, y);
//		y->left = z->left;
//		y->left->parent = y;
//		y->color = z->color;
//	}
//
//	delete z;
//
//	if (ycolor == 'B') 
//	{
//		rbtree_deletefixup(root, x);
//	}
//}

rbtree *rbtree_delete(rbtree *root, char *key)
{
	rbtree *z;
	if (!(z = rbtree_lookup(root, key)))
	{
		return root;
	}
	if (z == root && z->left == nullptr && z->right == nullptr) // проверка на корень дерева
	{
		delete z;
		return nullptr;
	}
	rbtree *x;
	rbtree *y = z;
	char ycolor = y->color;

	if (z->left == nullptr && z->right == nullptr) // проверка на лист
	{
		x = nullptr;
		rbtree_transplant(&root, z, nullptr);
	}
	else if (z->left == nullptr)
	{
		x = z->right;
		rbtree_transplant(&root, z, z->right);
	}
	else if (z->right == nullptr)
	{
		x = z->left;
		rbtree_transplant(&root, z, z->left);
	}
	else
	{
		y = rbtree_min(z->right);
		ycolor = y->color;
		x = y->right;

		if (y->parent != z)
		{
			rbtree_transplant(&root, y, y->right);
			y->right = z->right;
			y->right->parent = y;
		}

		rbtree_transplant(&root, z, y);
		y->left = z->left;
		y->left->parent = y;
		y->color = z->color;
	}

	delete z;

	if (ycolor == 'B' && x != nullptr) // проверка на существование родителя и потомков
	{
		rbtree_delete_fixup(&root, x);
	}

	return root;
}

//struct rbtree *rbtree_delete(struct rbtree *root, char *key)
//{
//	struct rbtree *z = rbtree_lookup(root, key);
//	if (z == NULL)
//		return root;
//	struct rbtree *y = z;
//	char y_original_color = y->color;
//	struct rbtree *x;
//	if (z->left == NULL)
//	{
//		x = z->right;
//		rbtree_transplant(&root, z, z->right);
//	}
//	else if (z->right == NULL)
//	{
//		x = z->left;
//		rbtree_transplant(&root, z, z->left);
//	}
//	else
//	{
//		y = rbtree_min(z->right);
//		y_original_color = y->color;
//		x = y->right;
//		if (y->parent == z)
//			x->parent = y;
//		else
//		{
//			rbtree_transplant(&root, y, y->right);
//			y->right = z->right;
//			y->right->parent = y;
//		}
//		rbtree_transplant(&root, z, y);
//		y->left = z->left;
//		y->left->parent = y;
//		y->color = z->color;
//	}
//	if (y_original_color == 'B')
//		rbtree_delete_fixup(&root, x);
//	return root;
//}

//struct rbtree *rbtree_delete(struct rbtree *root, char *key)
//{
//	struct rbtree *z = rbtree_lookup(root, key);
//	if (z == NULL)
//		return root;
//	struct rbtree *y = z;
//	char y_original_color = y->color;
//	struct rbtree *x;
//	if (z->left == NULL)
//	{
//		x = z->right;
//		rbtree_transplant(&root, z, z->right);
//	}
//	else if (z->right == NULL)
//	{
//		x = z->left;
//		rbtree_transplant(&root, z, z->left);
//	}
//	else
//	{
//		y = rbtree_min(z->right);
//		y_original_color = y->color;
//		x = y->right;
//		if (y->parent == z)
//			x->parent = y;
//		else
//		{
//			rbtree_transplant(&root, y, y->right);
//			y->right = z->right;
//			y->right->parent = y;
//		}
//		rbtree_transplant(&root, z, y);
//		y->left = z->left;
//		y->left->parent = y;
//		y->color = z->color;
//	}
//	if (y_original_color == 'B' && x != nullptr)
//		rbtree_delete_fixup(&root, x);
//	return root;
//}

//struct rbtree *create_node(char *key, int value)
//{
//	struct rbtree *node = new struct rbtree;
//	node->parent = NULL;
//	node->left = NULL;
//	node->right = NULL;
//	node->color = 'R';
//	node->key = new char[strlen(key) + 1];
//	strcpy(node->key, key);
//	node->value = value;
//	return node;
//}

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