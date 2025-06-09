/******************************************************************
 * Lab 4. Multi-way Trees (TDRK12 Spring 2023)
 * This header file includes signatures of the functions and 
 * declaration of a structure to be implemented in your solution.
 * Written by Vladimir Tarasov, Spring 2023
********************************************************************/


/*
 * A structure implementing a node of a B-tree. 
 * The definition is provided in ex_btree_3.c, just reuse it in your file.
 * Every node contains:
 * - An array of pointers to M sub-trees.
 * - An integer array of M-1 keys
 * - An integer number of keys 
 */
struct node;


/* Creates a new node of a B-tree.
 * The implementation is provided in ex_btree_3.c
 * Input:
 * - an array of keys,
 * - the number of the keys
 * - an array of pointers to the children
 * Returns:
 * - the pointer to the created node 
*/
struct node *createNode(int keys[], int count, struct node *children[]);


/* Traverses A B-tree using "inorder".
 * The implementation is provided in ex_btree_3.c
 * Input:
 * - the pointer to the start node of the current sub-tree
 * - the level counter used to indent levels of the tree during output.
 */
void traverse(struct node *tree, int level);


/* Searches a B-tree for a key.
 * You have to implement this function yourself.
 * Input:
 * - the pointer to the tree to search
 * - the key to search for
 * Returns:
 * - pointer to the node where the key is found, 
 * - otherwise NULL (if the key is not found)
*/
struct node *search(struct node *tree, int val);
