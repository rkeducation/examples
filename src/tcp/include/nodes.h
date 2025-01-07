//
//  tree.h
//  SysHealth
//
//  Created by Ramesh Kumar on 25/12/24.
//

#ifndef tree_h
#define tree_h

template < class Type >
struct Node {
	Type value;
	Node *left;
	Node *right;
	Node ( Type val, Node *l = nullptr, Node *r = nullptr ) : value(val), left(l), right(r) {}
};

template < class Type >
Node<Type> * createTree( Type arr[], int N, int curr ) {
	if (curr >= N)
		return NULL;
	
	Node<Type> * n = new Node<Type>(arr[curr]);
	
	n->left = createTree(arr, N, curr*2+1);
	n->right = createTree(arr, N, curr*2+2);
	
	return n;
}

template < class T >
void deleteNodes( Node<T> * root ) {
	if (!root)
		return;
	deleteNodes(root->left);
	deleteNodes(root->right);
	printf("Deleted Node : %d \n", root->value);
	delete root;
}

template < class Type >
void printNodes( Node<Type> *root, int lvl = 0 ) {
	if (!root)
		return;
	for (int i=0; i < lvl; i++)
		printf("-->");
	printf("%d\n", root->value);
	printNodes(root->left, lvl+1);
	printNodes(root->right, lvl+1);
}

#endif /* tree_h */
