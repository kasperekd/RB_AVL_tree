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

	//temp = RB_NULL;

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
			if (uncle != RB_NULL && uncle->color == 'R')
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
			if (uncle != RB_NULL && uncle->color == 'R')
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
		return nullptr;
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
		return nullptr;
	}
	while (tree->right != RB_NULL)
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

void swap_char(char *x, char *y)
{
	char t = *x; *x = *y; *y = t;
}

/** helpers for delete: swap node pointers */
void swap_np(rbtree **x, rbtree **y)
{
	rbtree *t = *x; *x = *y; *y = t;
}

/** Update parent pointers of child trees of 'parent' */
void change_parent_ptr(rbtree *tree, rbtree *parent, rbtree *old, rbtree *newer)
{
	if (parent == RB_NULL)
	{
		if (tree == old) tree = newer;
		return;
	}
	if (parent->left == old) parent->left = newer;
	if (parent->right == old) parent->right = newer;
}
/** Update parent pointer of a node 'child' */
void change_child_ptr(rbtree *child, rbtree *old, rbtree *newer)
{
	if (child == RB_NULL) return;
	
	if (child->parent == old) child->parent = newer;
}

void rbtree_delete_fixup(rbtree *tree, rbtree *child, rbtree *child_parent)
{
	rbtree *sibling;
	int go_up = 1;

	/* determine sibling to the node that is one-black short */
	if (child_parent->right && child_parent->left && child_parent->right == child) sibling = child_parent->left;
	else sibling = child_parent->right;

	while (sibling && go_up)
	{
		if (child_parent == RB_NULL)
		{
			/* removed parent==black from root, every path, so ok */
			return;
		}

		if (sibling->color == 'R')
		{	/* rotate to get a black sibling */
			child_parent->color = 'R';
			sibling->color = 'B';
			if (child_parent->right == child)
				rbtree_right_rotate(&tree, child_parent);
			else	rbtree_left_rotate(&tree, child_parent);
			/* new sibling after rotation */
			if (child_parent->right == child) sibling = child_parent->left;
			else sibling = child_parent->right;
		}

		if (child_parent->color == 'B'
			&& sibling->color == 'B'
			&& sibling->left->color == 'B'
			&& sibling->right->color == 'B')
		{	/* fixup local with recolor of sibling */
			if (sibling != RB_NULL)
				sibling->color = 'R';

			child = child_parent;
			child_parent = child_parent->parent;
			/* prepare to go up, new sibling */
			if (child_parent->right == child) sibling = child_parent->left;
			else sibling = child_parent->right;
		}
		else go_up = 0;
	}

	if (child_parent->color == 'R'
		&& sibling->color == 'B'
		&& sibling->left->color == 'B'
		&& sibling->right->color == 'B')
	{
		/* move red to sibling to rebalance */
		if (sibling != RB_NULL)
			sibling->color = 'R';
		child_parent->color = 'B';
		return;
	}

	/* get a new sibling, by rotating at sibling. See which child
	   of sibling is red */
	if (child_parent->right == child
		&& sibling->color == 'B'
		&& sibling->right->color == 'R'
		&& sibling->left->color == 'B')
	{
		sibling->color = 'R';
		sibling->right->color = 'B';
		rbtree_left_rotate(&tree, sibling);
		/* new sibling after rotation */
		if (child_parent->right == child) sibling = child_parent->left;
		else sibling = child_parent->right;
	}
	else if (child_parent->left == child
			 && sibling->color == 'B'
			 && sibling->left->color == 'R'
			 && sibling->right->color == 'B')
	{
		sibling->color = 'R';
		sibling->left->color = 'B';
		rbtree_right_rotate(&tree, sibling);
		/* new sibling after rotation */
		if (child_parent->right == child) sibling = child_parent->left;
		else sibling = child_parent->right;
	}

	/* now we have a black sibling with a red child. rotate and exchange colors. */
	sibling->color = child_parent->color;
	child_parent->color = 'B';
	if (child_parent->right == child)
	{
		sibling->left->color = 'B';
		rbtree_right_rotate(&tree, child_parent);
	}
	else
	{
		sibling->right->color = 'B';
		rbtree_left_rotate(&tree, child_parent);
	}
}

rbtree *rbtree_delete(rbtree *tree, char *key)
{
	rbtree *to_delete;
	rbtree *child;
	if ((to_delete = rbtree_lookup(tree, key)) == RB_NULL) return 0;

	/* make sure we have at most one non-leaf child */
	if (to_delete->left != RB_NULL && to_delete->right != RB_NULL)
	{
		/* swap with smallest from right subtree (or largest from left) */
		rbtree *smright = to_delete->right;
		while (smright->left != RB_NULL)
			smright = smright->left;
		/* swap the smright and to_delete elements in the tree,
		 * but the rbnode_t is first part of user data struct
		 * so cannot just swap the keys and data pointers. Instead
		 * readjust the pointers left,right,parent */

		 /* swap colors - colors are tied to the position in the tree */
		swap_char(&to_delete->color, &smright->color);

		/* swap child pointers in parents of smright/to_delete */
		change_parent_ptr(tree, to_delete->parent, to_delete, smright);
		if (to_delete->right != smright)
			change_parent_ptr(tree, smright->parent, smright, to_delete);

		/* swap parent pointers in children of smright/to_delete */
		change_child_ptr(smright->left, smright, to_delete);
		change_child_ptr(smright->left, smright, to_delete);
		change_child_ptr(smright->right, smright, to_delete);
		change_child_ptr(smright->right, smright, to_delete);
		change_child_ptr(to_delete->left, to_delete, smright);
		if (to_delete->right != smright)
			change_child_ptr(to_delete->right, to_delete, smright);
		if (to_delete->right == smright)
		{
			/* set up so after swap they work */
			to_delete->right = to_delete;
			smright->parent = smright;
		}

		/* swap pointers in to_delete/smright nodes */
		swap_np(&to_delete->parent, &smright->parent);
		swap_np(&to_delete->left, &smright->left);
		swap_np(&to_delete->right, &smright->right);

		/* now delete to_delete (which is at the location where the smright previously was) */
	}

	if (to_delete->left != RB_NULL) child = to_delete->left;
	else child = to_delete->right;

	/* unlink to_delete from the tree, replace to_delete with child */
	change_parent_ptr(tree, to_delete->parent, to_delete, child);
	change_child_ptr(child, to_delete, to_delete->parent);

	if (to_delete->color == 'R')
	{
		/* if node is red then the child (black) can be swapped in */
	}
	else if (child && child->color == 'R')
	{
		/* change child to BLACK, removing a RED node is no problem */
		if (child != RB_NULL) child->color = 'B';
	}
	else
	{
		rbtree_delete_fixup(tree, child, to_delete->parent);
	}
	
	/* unlink completely */
	to_delete->parent = RB_NULL;
	to_delete->left = RB_NULL;
	to_delete->right = RB_NULL;
	to_delete->color = 'B';
	return to_delete;
}




//void rbtree_delete_fixup(struct rbtree **root, struct rbtree *x)
//{
//	while (x != *root && x->color == 'B')
//	{
//		if (x == x->parent->left)
//		{
//			struct rbtree *w = x->parent->right;
//			if (w->color == 'R')
//			{
//				w->color = 'B';
//				x->parent->color = 'R';
//				rbtree_left_rotate(root, x->parent);
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
//					rbtree_right_rotate(root, w);
//					w = x->parent->right;
//				}
//				w->color = x->parent->color;
//				x->parent->color = 'B';
//				w->right->color = 'B';
//				rbtree_left_rotate(root, x->parent);
//				x = *root;
//			}
//		}
//		else
//		{
//			struct rbtree *w = x->parent->left;
//			if (w->color == 'R')
//			{
//				w->color = 'B';
//				x->parent->color = 'R';
//				rbtree_right_rotate(root, x->parent);
//				w = x->parent->left;
//			}
//			if (w->left->color == 'B' && w->right->color == 'B')
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
//					rbtree_left_rotate(root, w);
//					w = x->parent->left;
//				}
//				w->color = x->parent->color;
//				x->parent->color = 'B';
//				w->left->color = 'B';
//				rbtree_right_rotate(root, x->parent);
//				x = *root;
//			}
//		}
//	}
//	x->color = 'B';
//}

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

//rbtree *rbtree_successor(rbtree *node)
//{
//	if (node->right != nullptr)
//		return rbtree_min(node);
//	rbtree *parent = node->parent;
//	if (parent != nullptr && parent->right == node)
//	{
//		node = parent;
//		parent = parent->parent;
//	}
//	return parent;
//}
//
//rbtree *rbtree_predecessor(rbtree *node)
//{
//	if (node->left != nullptr)
//		return rbtree_max(node);
//	rbtree *parent = node->parent;
//	if (parent != nullptr && parent->left == node)
//	{
//		node = parent;
//		parent = parent->parent;
//	}
//	return parent;
//}
//
//
//void rbtree_delete_fixup(rbtree *tree, rbtree *node)
//{
//	while (node != tree && node->color == 'B')
//	{
//		if (node == node->parent->left)
//		{
//			rbtree *brother = node->parent->right;
//			if (brother->color == 'R')
//			{
//				brother->color = 'B';
//				brother->parent->color = 'R';
//				rbtree_left_rotate(&tree, brother->parent);
//				brother = node->parent->right;
//			}
//			if (brother->left->color == 'B' && brother->right->color == 'B')
//			{
//				brother->color = 'R';
//				node = node->parent;
//			}
//			else if (brother->right->color == 'B')
//			{
//				brother->left->color = 'B';
//				brother->color = 'R';
//				rbtree_right_rotate(&tree, brother);
//				brother = node->parent->right;
//			}
//			else
//			{
//				brother->color = node->parent->color;
//				brother->right->color = 'B';
//				node->parent->color = 'B';
//				rbtree_left_rotate(&tree, node->parent);
//				node = tree;
//			}
//		}
//		else
//		{
//			rbtree *brother = node->parent->left;
//			if (brother->color == 'R')
//			{
//				brother->color = 'B';
//				brother->parent->color = 'R';
//				rbtree_right_rotate(&tree, brother->parent);
//				brother = node->parent->left;
//			}
//			if (brother->right->color == 'B' && brother->left->color == 'B')
//			{
//				brother->color = 'r';
//				node = node->parent;
//			}
//			else if (brother->left->color == 'B')
//			{
//				brother->right->color = 'B';
//				brother->color = 'R';
//				rbtree_left_rotate(&tree, brother);
//				brother = node->parent->left;
//			}
//			else
//			{
//				brother->color = node->parent->color;
//				brother->left->color = 'B';
//				node->parent->color = 'B';
//				rbtree_right_rotate(&tree, node->parent);
//				node = tree;
//			}
//		}
//	}
//	node->color = 'B';
//}
//rbtree *rbtree_delete(rbtree **tree, char* key)
//{
//	rbtree *z;
//	if (!(z = rbtree_lookup(*tree, key)))
//	{
//		return *tree;
//	}
//	rbtree *for_delete;
//	rbtree *child = z; 
//	if (z->left == nullptr || z->right == nullptr)
//		for_delete = z;
//	else
//		for_delete = rbtree_successor(z);
//	if (for_delete->left != for_delete)
//		child = for_delete->left;
//	else
//		child = for_delete->right;
//	child->parent = for_delete->parent;
//	if (for_delete->parent == nullptr)
//		*tree = child;
//	else if (for_delete->parent->left == for_delete)
//		for_delete->parent->left = child;
//	else
//		for_delete->parent->right = child;
//	if (z != for_delete)
//		z->key = for_delete->key;
//	if (for_delete->color == 'B')
//		rbtree_delete_fixup(*tree, child);
//	return for_delete;
//}




//rbtree *rbtree_delete(rbtree *root, char *key)
//{
//	rbtree *z;
//	if (!(z = rbtree_lookup(root, key)))
//	{
//		return root;
//	}
//	if (z == root && z->left == nullptr && z->right == nullptr) // проверка на корень дерева
//	{
//		delete z;
//		return nullptr;
//	}
//	rbtree *x;
//	rbtree *y = z;
//	char ycolor = y->color;
//
//	if (z->left == nullptr && z->right == nullptr) // проверка на лист
//	{
//		x = nullptr;
//		rbtree_transplant(&root, z, nullptr);
//	}
//	else if (z->left == nullptr)
//	{
//		x = z->right;
//		rbtree_transplant(&root, z, z->right);
//	}
//	else if (z->right == nullptr)
//	{
//		x = z->left;
//		rbtree_transplant(&root, z, z->left);
//	}
//	else
//	{
//		y = rbtree_min(z->right);
//		ycolor = y->color;
//		x = y->right;
//
//		if (y->parent != z)
//		{
//			rbtree_transplant(&root, y, y->right);
//			y->right = z->right;
//			y->right->parent = y;
//		}
//
//		rbtree_transplant(&root, z, y);
//		y->left = z->left;
//		y->left->parent = y;
//		y->color = z->color;
//	}
//
//	delete z;
//
//	if (ycolor == 'B' && x != nullptr) // проверка на существование родителя и потомков
//	{
//		rbtree_delete_fixup(&root, x);
//	}
//
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