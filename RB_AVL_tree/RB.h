#include <iostream>
#include <fstream>
#include <stack>


struct rbtree
{
	struct rbtree* parent;
	struct rbtree* left;
	struct rbtree* right;
	char color; // R - red; R - black
	char* key;
	int value;
};

#define RB_NULL &rb_null
extern struct rbtree rb_null;

void rbtree_add(struct rbtree **root, char* key, int value);
struct rbtree *rbtree_lookup(struct rbtree *root, char *key);
struct rbtree *rbtree_delete(struct rbtree *root, char *key);
struct rbtree *rbtree_min(struct rbtree *root);
struct rbtree *rbtree_max(struct rbtree *root);
void rbtree_free(struct rbtree **root);
void rbtree_print_dfs(struct rbtree *root, int level);

struct rbtree *create_node(char* key, int value);
void fTree(const char NAME_TREE[], rbtree *root);
void printTree(std::ostream &stream, rbtree *tree, int space = 0);