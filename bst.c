/*
 * This file is where you should implement your binary search tree.  It already
 * contains skeletons of the functions you need to implement (along with
 * documentation for each function).  Feel free to implement any additional
 * functions you might need.  Also, don't forget to include your name and
 * @oregonstate.edu email address below.
 *
 * Name: Oscar Abelanet
 * Email: abelaneo@oregonstate.edu
 */

#include <stdlib.h>

#include "bst.h"

/*
 * This structure represents a single node in a BST.  In addition to containing
 * pointers to its two child nodes (i.e. `left` and `right`), it contains two
 * fields representing the data stored at this node.  The `key` field is an
 * integer value that should be used as an identifier for the data in this
 * node.  Nodes in the BST should be ordered based on this `key` field.  The
 * `value` field stores data associated with the key.
 *
 * You should not modify this structure.
 */
struct bst_node {
  int key;
  void* value;
  struct bst_node* left;
  struct bst_node* right;
};


/*
 * This structure represents an entire BST.  It specifically contains a
 * reference to the root node of the tree.
 *
 * You should not modify this structure.
 */
struct bst {
  struct bst_node* root;
};

/*
 * This function should allocate and initialize a new, empty, BST and return
 * a pointer to it.
 */
struct bst* bst_create() {
	struct bst* new_tree = malloc(sizeof(struct bst));
	new_tree->root = NULL;
	return new_tree;
}

void root_free(struct bst_node* root) {
	if (root == NULL) {
		return;
	} else {
		root_free(root->left);
		root_free(root->right);
	}
	free(root);
}

/*
 * This function should free the memory associated with a BST.  While this
 * function should up all memory used in the BST itself, it should not free
 * any memory allocated to the pointer values stored in the BST.  This is the
 * responsibility of the caller.
 *
 * Params:
 *   bst - the BST to be destroyed.  May not be NULL.
 */
void bst_free(struct bst* bst) {
	if (bst->root != NULL) {
		root_free(bst->root);
	}
	free(bst);
}


int root_size(struct bst_node* root) {
	if (root == NULL) {
		return 0;
	} else {
		return root_size(root->left) + root_size(root->right) + 1;
	}
}

/*
 * This function should return the total number of elements stored in a given
 * BST.
 *
 * Params:
 *   bst - the BST whose elements are to be counted.  May not be NULL.
 */
int bst_size(struct bst* bst) {
	if (bst->root == NULL) {
		return 0;
	} else {
		return root_size(bst->root);
	}
}



/*
 * This function should insert a new key/value pair into the BST.  The key
 * should be used to order the key/value pair with respect to the other data
 * stored in the BST.  The value should be stored along with the key, once the
 * right location in the tree is found.
 *
 * Params:
 *   bst - the BST into which a new key/value pair is to be inserted.  May not
 *     be NULL.
 *   key - an integer value that should be used to order the key/value pair
 *     being inserted with respect to the other data in the BST.
 *   value - the value being inserted into the BST.  This should be stored in
 *     the BST alongside the key.  Note that this parameter has type void*,
 *     which means that a pointer of any type can be passed.
 */
void bst_insert(struct bst* bst, int key, void* value) {
	struct bst_node* new_node = malloc(sizeof(struct bst_node));
	new_node->key = key;
	new_node->value = value;
	new_node->left = NULL;
	new_node->right = NULL;

	if (bst->root == NULL) {
		bst->root = new_node;
		return;
	}

	struct bst_node* cur = bst->root;
	while (1 == 1) {
		if (key > cur->key) {
			if (cur->right == NULL) {
				cur->right = new_node;
				return;
			} else {
				cur = cur->right;
			}
		} else {
			if (cur->left == NULL) {
				cur->left = new_node;
				return;
			} else {
				cur = cur->left;
			}
		}
	}
}

/*
 * This function should remove a key/value pair with a specified key from a
 * given BST.  If multiple values with the same key exist in the tree, this
 * function should remove the first one it encounters (i.e. the one closest to
 * the root of the tree).
 *
 * Params:
 *   bst - the BST from which a key/value pair is to be removed.  May not
 *     be NULL.
 *   key - the key of the key/value pair to be removed from the BST.
 */
void bst_remove(struct bst* bst, int key) {
  	struct bst_node* cur = bst->root;
	struct bst_node* parent = cur;
	int d;
	
	if (cur == NULL) {
		return;
	}
	
	// Checks if the root is to be removed
	if (cur->key == key) {
		struct bst_node* tbr = cur;

		// If node to be removed is a leaf
		if (tbr->left == NULL && tbr->right == NULL) {
			bst->root = NULL;
			free(tbr);
			return;	

		// Else if to be removed node has 2 children
		} else if (tbr->left != NULL && tbr->right != NULL) {
			struct bst_node* suc = tbr->right;
			struct bst_node* suc_parent;
			int N_is_suc_p;

			if (suc->left == NULL) {
				N_is_suc_p = 1;
			} else {
				N_is_suc_p = 0;
			}	

			while (suc->left != NULL) {
				suc_parent = suc;
				suc = suc->left;
			}
		
			suc->left = tbr->left;
			if (N_is_suc_p == 0) {
				suc_parent->left = suc->right;
				suc->right = tbr->right;
			}
	
			bst->root = suc;
			free(tbr);
			return;

		// Else if tbr has one child
		} else {	
			struct bst_node* tbr_child;
			if (tbr->left != NULL) {
				tbr_child = tbr->left;
			} else {
				tbr_child = tbr->right;
			}

			bst->root = tbr_child;
			free(tbr);
			return;
		}
	}
	

	// Iterates through to find the node to be removed and its parent
	while (cur->key != key) {
		if (cur->key < key) {
			if (cur->right != NULL) {
				parent = cur;
				cur = cur->right;
				d = 1;
			} else {
				return;
			}
		} else {
			if (cur->left != NULL) {
				parent = cur;
				cur = cur->left;
				d = -1;
			} else {
				return;
			}
		}
	}

	struct bst_node* tbr = cur;
	struct bst_node* tbr_parent = parent;

	// If node to be removed is a leaf
	if (tbr->left == NULL && tbr->right == NULL) {
		if (d == 1) {
			tbr_parent->right = NULL;
		} else {
			tbr_parent->left = NULL;
		}

	// Else if to be removed node has 2 children
	} else if (tbr->left != NULL && tbr->right != NULL) {
		struct bst_node* suc = tbr->right;
		struct bst_node* suc_parent;
		int N_is_suc_p;

		if (suc->left == NULL) {
			N_is_suc_p = 1;
		} else {
			N_is_suc_p = 0;
		}

		while (suc->left != NULL) {
			suc_parent = suc;
			suc = suc->left;
		}
		
		suc->left = tbr->left;
		if (N_is_suc_p == 0) {
			suc_parent->left = suc->right;
			suc->right = tbr->right;
		}

		if (d == 1) {
			tbr_parent->right = suc;
		} else {
			tbr_parent->left = suc;
		}

	// Else if to be removed node has one child
	} else {	
		struct bst_node* tbr_child;
		if (tbr->left != NULL) {
			tbr_child = tbr->left;
		} else {
			tbr_child = tbr->right;
		}

		if (d = 1) {
			tbr_parent->right = tbr_child;
		} else {
			tbr_parent->left = tbr_child;
		}
	}

	free(tbr);
	return;
}

/*
 * This function should return the value associated with a specified key in a
 * given BST.  If multiple values with the same key exist in the tree, this
 * function should return the first one it encounters (i.e. the one closest to
 * the root of the tree).  If the BST does not contain the specified key, this
 * function should return NULL.
 *
 * Params:
 *   bst - the BST from which a key/value pair is to be removed.  May not
 *     be NULL.
 *   key - the key of the key/value pair whose value is to be returned.
 *
 * Return:
 *   Should return the value associated with the key `key` in `bst` or NULL,
 *   if the key `key` was not found in `bst`.
 */
void* bst_get(struct bst* bst, int key) {
  	if (bst->root == NULL) {
		return NULL;
	}

	struct bst_node* cur = bst->root;

	while (1 == 1) {
		if (cur->key < key) {
			if (cur->right != NULL) {
				cur = cur->right;
			} else {
				return NULL;
			}
		} else if (cur->key > key) {
			if (cur->left != NULL) {
				cur = cur->left;
			} else {
				return NULL;
			}
		} else {
			return cur->value;
		}
	}
}

/*****************************************************************************
 **
 ** BST puzzle functions
 **
 *****************************************************************************/

/*
 * This function should return the height of a given BST, which is the maximum
 * depth of any node in the tree (i.e. the number of edges in the path from
 * the root to that node).  Note that the height of an empty tree is -1 by
 * convention.
 *
 * Params:
 *   bst - the BST whose height is to be computed
 *
 * Return:
 *   Should return the height of bst.
 */
int bst_height(struct bst* bst) {
	if (bst->root == NULL) {
		return -1;
  	}

	struct bst_node* left = bst->root->left; 
	struct bst_node* right = bst->root->right;
  
	if (left == NULL && right == NULL) {
		return 0;
  	} else if (left == NULL) {
		struct bst rightsub;
		rightsub.root = right;
		return bst_height(&rightsub) + 1;
	} else if (right == NULL) {
		struct bst leftsub;
		leftsub.root = left;
		return bst_height(&leftsub) + 1;
  	} else {
		struct bst rightsub;
		rightsub.root = right;
		struct bst leftsub;
		leftsub.root = left;

		int longleft = 1 + bst_height(&leftsub);
		int longright = 1 + bst_height(&rightsub);
		if (longleft < longright) {
			return longright;
		} else {
			return longleft;
		}
	}
}

/*
 * This function should determine whether a specified value is a valid path
 * sum within a given BST.  In other words, this function should check whether
 * the given BST contains any path from the root to a leaf in which the keys
 * sum to the specified value.
 *
 * Params:
 *   bst - the BST whose paths sums to search
 *   sum - the value to search for among the path sums of `bst`
 *
 * Return:
 *   Should return 1 if `bst` contains any path from the root to a leaf in
 *   which the keys add up to `sum`.  Should return 0 otherwise.
 */
int bst_path_sum(struct bst* bst, int sum) {
	if (bst->root == NULL) {
		return 0;
	}

	if (bst->root->left == NULL && bst->root->right == NULL) {
		if (bst->root->key == sum) {
			return 1;
		}
		else return 0;
	}
	
	int newsum = sum - bst->root->key;

	struct bst leftsub;
	leftsub.root = bst->root->left;
	int left = bst_path_sum(&leftsub, newsum);

	struct bst rightsub;
	rightsub.root = bst->root->right;
	int right = bst_path_sum(&rightsub, newsum);

	if (right == 1 || left == 1) {
		return 1;
	}
	return 0;
}

/*
 * This function should compute a range sum in a given BST.  Specifically, it
 * should compute the sum of all keys in the BST between a given lower bound
 * and a given upper bound.  For full credit, you should not process any subtree
 * whose keys cannot be included in the range sum.
 *
 * Params:
 *   bst - the BST within which to compute a range sum
 *   lower - the lower bound of the range over which to compute a sum; this
 *     should be considered an *inclusive* bound; in other words a key that's
 *     equal to this bound should be included in the sum
 *   upper - the upper bound of the range over which to compute a sum; this
 *     should be considered an *inclusive* bound; in other words a key that's
 *     equal to this bound should be included in the sum
 *
 * Return:
 *   Should return the sum of all keys in `bst` between `lower` and `upper`.
 */
int bst_range_sum(struct bst* bst, int lower, int upper) {
	if (bst->root == NULL) {
		return 0;
	}
	
	int left_sum = 0;
	int right_sum = 0;

	if (bst->root->left != NULL) {
		if (bst->root->key > lower) {
			
			struct bst leftsub;
			leftsub.root = bst->root->left;
			left_sum = bst_range_sum(&leftsub, lower, upper);
		}

	} 
	if (bst->root->right != NULL) {
		if (bst->root->key < upper) {
			
			struct bst rightsub;
			rightsub.root = bst->root->right;
			right_sum = bst_range_sum(&rightsub, lower, upper);
		}
	}
	if (bst->root->key <= upper && bst->root->key >= lower) {
		return right_sum + left_sum + bst->root->key;
	}
	return right_sum + left_sum;
}
