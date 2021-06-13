struct avl_node {
	int key ;
	int height ;
	int n_l_nodes, n_r_nodes ;
	avl_node* left ;
	avl_node* right ;
} ;

class avl_tree {
	avl_node* p_insert_node(int, avl_node*) ;
	avl_node* p_delete_node(int, avl_node*) ;
	void inorder_t(avl_node*) ;
	void preorder_t(avl_node*) ;
	int node_height(avl_node*) ;
	int node_height_force(avl_node*);
	avl_node* rebalance_tree(avl_node*) ;
	avl_node* ll_rotate(avl_node*) ;
	avl_node* rr_rotate(avl_node*) ;
	avl_node* lr_rotate(avl_node*) ;
	avl_node* rl_rotate(avl_node*) ;
	avl_node* inorder_successor(avl_node*) ;
	avl_node* inorder_predecessor(avl_node*) ;
	int p_get_kth_smallest(int, avl_node*) ;
	int get_num_nodes(avl_node*) ;
	avl_node* find_parent(avl_node*, avl_node*) ;
	int p_get_node_order(int, avl_node*) ;
	avl_node* find_min(avl_node*);
	avl_node* find_max(avl_node*);
public:
	avl_node* tree_root ; 
	avl_node* find_element(int, avl_node* node) ;
	avl_tree() {
		tree_root = nullptr ;
	}
	void inorder_traversal();
	void preorder_traversal();
	void insert_key(int) ;
	int get_tree_height() ;
	void delete_key(int) ;
	int get_next_element(avl_node*) ;
	int get_prev_element(avl_node*) ;
	int get_kth_largest(int) ;
	int get_kth_smallest(int) ;
	int get_node_order(int) ;
	int elements_in_range(int, int) ;
	int closest_element(int) ;
};

int avl_tree::closest_element(int key) {
	avl_node* node = find_element(key, tree_root) ;
	avl_node* parent = find_parent(node, tree_root) ;
	avl_node* v1 = find_max(node->left) ;
	avl_node* v2 = find_min(node->right) ;
	int d1 = (parent == node ? INT_MAX : abs(parent->key - key)) ;
	int d2 = (v1 != NULL ? abs(v1->key - key) : INT_MAX) ;
	int d3 = (v2 != NULL ? abs(v2->key - key) : INT_MAX) ;
	if(key < parent->key) {
		if(d3 <= d1 && d3 <= d2) {
			return v2->key ;
		}
		if(d2 <= d1)
			return v1->key ;
		return parent->key ;
	} else {
		if(d1 <= d2 && d1 <= d3) {
			return parent->key ;
		}
		if(d2 <= d3) {
			return v1->key ;
		}
		return v2->key ;
	}
}

avl_node* avl_tree::find_min(avl_node* node) {
	if(node == NULL) return NULL ;
	avl_node* temp = node ;
	while(temp->left != NULL) {
		temp = temp->left ;
	}
	return temp ;
}

avl_node* avl_tree::find_max(avl_node* node) {
	if(node == NULL) return NULL ;
	avl_node* temp = node ;
	while(temp->right != NULL) {
		temp = temp->right ;
	}
	return temp ;
}



int avl_tree::elements_in_range(int low, int high) {
	int l_order = get_node_order(low);
	int h_order = get_node_order(high);
	
	return h_order - l_order + (l_order > 0 && find_element(low, tree_root) != NULL ? 1 : 0) ;
}

int avl_tree::p_get_node_order(int key, avl_node* node) {
	if(node == NULL) {
		return 0 ;
	}
	if(key == node->key) {
		return 1 + node->n_l_nodes ;
	} else if(key < node->key) {
		return p_get_node_order(key, node->left) ;
	} else {
		return node->n_l_nodes + 1 + p_get_node_order(key, node->right);
	}
}

int avl_tree::get_node_order(int key) {
	return p_get_node_order(key, tree_root) ;
}

int avl_tree::p_get_kth_smallest(int K, avl_node* node) {
	if(node == NULL)
		return -1 ;
	if(K <= node->n_l_nodes) {
		//node in the left subtree.
		return p_get_kth_smallest(K, node->left);
	} else if(K == (node->n_l_nodes + 1)) {
		//node is the root.
		return node->key ;
	} else {
		return p_get_kth_smallest(K-node->n_l_nodes-1, node->right);
	}
}

int avl_tree::get_kth_smallest(int K) {
	return p_get_kth_smallest(K, tree_root) ;
}

int avl_tree::get_kth_largest(int K) {
	return get_kth_smallest(tree_root->n_l_nodes + tree_root->n_r_nodes - K + 2);
}

avl_node* avl_tree::find_element(int key, avl_node* node) {
	if(node == NULL) {
		return NULL ;
	}
	if(node->key == key)
		return node ;
	if(key < node->key)
		return find_element(key, node->left);
	return find_element(key, node->right);
}

avl_node* avl_tree::find_parent(avl_node* node, avl_node* curr) {
	if(curr == NULL) {
		return NULL ;
	}
	if(node->key < curr->key) {
		if(curr->left == node)
			return curr ;
		return find_parent(node, curr->left);
	} 
	if(node->key > curr->key) {
		if(curr->right == node)
			return curr;
		return find_parent(node, curr->right);
	}
	return node ;
}

int avl_tree::get_next_element(avl_node* node) {
	if(node->right != NULL)
		return inorder_successor(node)->key;
	return find_parent(node, tree_root)->key ;
}	

int avl_tree::get_num_nodes(avl_node* node) {
	if(node == NULL) return 0;
	return 1 + node->n_l_nodes + node->n_r_nodes ;
}

avl_node* avl_tree::inorder_successor(avl_node* node) {
	avl_node* temp = node -> right ;
	while(temp -> left != NULL) {
		temp = temp -> left ;
	}
	return temp ;
}

avl_node* avl_tree::inorder_predecessor(avl_node* node) {
	avl_node* temp = node -> left ;
	while(temp -> right != NULL) {
		temp = temp -> right ;
	}
	return temp ;
}

void avl_tree::delete_key(int key) {
	tree_root = p_delete_node(key, tree_root);
}

avl_node* avl_tree::p_delete_node(int key, avl_node* node) {
	if(node == NULL) { return NULL ;}
	avl_node* ret_val = node;
	if(key < node->key) {
		node->left = p_delete_node(key, node->left);
		node->height = 1 + max(node_height(node->left), node_height(node->right)) ;
		node->n_l_nodes = get_num_nodes(node->left) ;
		node = rebalance_tree(node) ;
		ret_val = node ;
	}else if(key > node->key) {
		node->right = p_delete_node(key, node->right);
		node->height = 1 + max(node_height(node->left), node_height(node->right)) ;
		node->n_r_nodes = get_num_nodes(node->right);
		node = rebalance_tree(node) ;
		ret_val = node ;
	} else if(key == node->key){
		if(node->left == NULL && node->right == NULL) {
			//leaf node case.
			delete node ;
			ret_val = NULL ;
		} else if(node->left != NULL && node->right != NULL) {
			//both child.
			avl_node* inord_succ = inorder_successor(node) ;
			node->key = inord_succ->key ;
			node->right = p_delete_node(node->key, node->right);
			node->n_r_nodes = get_num_nodes(node->right) ;
			ret_val = node ;
			//rebalance_tree(node) ;
		} else{
			if(node->left != NULL) {
				//only left child
				avl_node* temp = node->left ;
				delete node ;
				ret_val = temp ;
			} else {
				//only right child
				avl_node *temp = node->right ;

				delete node ;
				ret_val = temp ;	
			}
		}
	}
	return ret_val ;
}

void avl_tree::preorder_t(avl_node* node) {
	if(node == NULL) return ;
	cout << node->key << ", " ;
	preorder_t(node->left) ;
	preorder_t(node->right) ;
}

void avl_tree::preorder_traversal() {
	preorder_t(tree_root) ;
	cout << endl ;
}

int avl_tree::get_tree_height() {
	return node_height(tree_root);
}

avl_node* avl_tree::ll_rotate(avl_node* root) {
	avl_node* node1 = root ;
	avl_node* node2 = root->left ;
	//avl_node* node3 = node2->left ;
	
	//make node2 the root.
	root = node2;
	//make root the right child of node2 but before that make right child of node2 the left child of older root.
	node1->left = node2 -> right ;
	node2->right = node1 ;	

	node1->height = 1 + max(node_height(node1->left), node_height(node1->right));
	node2->height = 1 + max(node_height(node2->left), node_height(node2->right));
	node1->n_l_nodes = get_num_nodes(node1->left);
	node2->n_r_nodes = get_num_nodes(node1);
	return root ;
}

avl_node* avl_tree::rr_rotate(avl_node* root) {
	avl_node* node1 = root ;
	avl_node* node2 = root->right ;

	//make node2 the root of the tree
	root = node2 ;
	//make node1 the left child of node 2. before that make left child of node2 the right child of node1.
	node1 -> right = node2 -> left ;
	node2 -> left  = node1 ;

	node1->height = 1 + max(node_height(node1->left), node_height(node1->right));
	node2->height = 1 + max(node_height(node2->left), node_height(node2->right));
	node1->n_r_nodes = get_num_nodes(node1->right);
	node2->n_l_nodes = get_num_nodes(node1);
	return root ;
}

avl_node* avl_tree::lr_rotate(avl_node* root) {
	//avl_node* node2 = root->left ;
	//avl_node* node3 = node2->right ;
	root->left = rr_rotate(root->left);
	root = ll_rotate(root);
	return root;
}

avl_node* avl_tree::rl_rotate(avl_node* root) {
	root->right = ll_rotate(root->right);
	root = rr_rotate(root);
	return root;
}

avl_node* avl_tree::rebalance_tree(avl_node* node) {
	int balance_factor = node_height(node->right) - node_height(node->left) ;
	if(balance_factor == -2) {
		//tree is heavier on the left.
		if(node_height(node->left->left) > node_height(node->left->right)) {
			//rotation to the right is needed.
			return ll_rotate(node);
		} else {
			//rotate left then rotate right is needed.
			return lr_rotate(node);
		}		
	} else if(balance_factor == 2) {
		//tree is heavier on the right.
		if(node_height(node->right->right) > node_height(node->right->left)) {
			//rotation to the left is needed.
			return rr_rotate(node) ;
		} else {
			return rl_rotate(node) ;
		}
	}
	return node ;
}

void avl_tree::insert_key(int key) {
	tree_root = p_insert_node(key, tree_root) ;
}

int avl_tree::node_height(avl_node* node) {
	if(node == NULL) return 0 ;
	return node->height ;
}

int avl_tree::node_height_force(avl_node* node) {
	if(node == NULL) return 0 ;
	int height = 1+max(node_height_force(node->left), node_height_force(node->right)) ;
	node->height = height ;
	return height ;
}

avl_node* avl_tree::p_insert_node(int key, avl_node* node) {
	if(node == NULL) {
		avl_node *new_node = new avl_node();
		new_node -> key = key ;
		new_node -> height = 1 ;
		new_node -> n_l_nodes = new_node -> n_r_nodes = 0 ;
		new_node -> left = new_node -> right = NULL ;
		return new_node ;
	}
	if(key < node->key) {
		node->left = p_insert_node(key, node->left) ;
		node->height = 1 + max(node_height(node->left), node_height(node->right)) ;
		node->n_l_nodes = get_num_nodes(node->left);
	}
	if(key > node->key) {
		node->right = p_insert_node(key, node->right) ;
		node->height = 1 + max(node_height(node->left), node_height(node->right)) ;
		node->n_r_nodes = get_num_nodes(node->right) ;
	}

	node = rebalance_tree(node) ;

	return node ;
}

void avl_tree::inorder_traversal() {
	inorder_t(tree_root) ;
	cout << endl ;
}

void avl_tree::inorder_t(avl_node* node) {
	if(node == NULL) return ;
	inorder_t(node->left) ;
	cout << node->key << ", " ;
	inorder_t(node->right) ;
}
