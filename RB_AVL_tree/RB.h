#include "iostream"

struct rbtree
{
	struct rbtree* parent;
	struct rbtree* left;
	struct rbtree* right;
	char color; // 0 - red; 1 - black
	char* key;
	int value;
};

void rbtree_add(struct rbtree **root, char* key, int value);
struct rbtree *rbtree_lookup(struct rbtree *root, char *key);
struct rbtree *rbtree_delete(struct rbtree *root, char *key);
struct rbtree *rbtree_min(struct rbtree *root);
struct rbtree *rbtree_max(struct rbtree *root);
void rbtree_free(struct rbtree *root);
void rbtree_print_dfs(struct rbtree *root, int level);

struct rbtree *create_node(char* key, int value);