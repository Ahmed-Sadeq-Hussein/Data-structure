/******************************************************************
 * Lab 3. Binary Trees (TDRK12 Spring 2023)
 * This header file includes signatures of the functions and 
 * declaration of a structure to be implemented in your solution.
 * Written by Vladimir Tarasov, Spring 2023
********************************************************************/
//AHMED HUSSEIN 2025

#ifndef LAB_BINARY_TREES_H  /* iNCLUDE GUARDS */
#define LAB_BINARY_TREES_H

/*
 * An enumeration emulating a boolean type that is used in 
 * the functions insert() and delete().
 * The definition is reused from in avl_tree_insert.c.
 */
typedef enum
{
    FALSE,
    TRUE
} bool;

/*
 * A structure implementing a node of an AVL tree. 
 * The definition is provided in avl_tree_insert.c, just reuse it in your file.
 * Every node contains:
 * - An integer data member. 
 * - An integer balance factor
 * - A pointer to the left sub-tree.
 * - A pointer to the right sub-tree.
 */
struct node;

/* Inserts a new element into an AVL tree.
 * When needed, perfoms a rotation to restore the balance of a tree.
 * The implementation is provided in avl_tree_insert.c
 * Input:
 * - the data to be inserted
 * - the pointer to the start node of the current sub-tree
 * - a variable that controls re-balancing of the tree 
 *   (see more explanation in avl_tree_insert.c)
 * Returns:
 *  - the pointer to the start node of the current sub-tree
 */
struct node *insert(int data, struct node *tree, bool *ht_inc);

/* Displays an AVL tree.
 * The implementation is provided in avl_tree_insert.c
 * Input:
 * - the pointer to the start node of the current sub-tree
 * - the level counter used to indent levels of the tree during output.
 *
 */
void display(struct node *ptr, int level);

/*
 * Finds the largest element in a AVL tree. 
 * The implementation can be reused from the exercise.
 * Input:
 * - the pointer to the start node of the current sub-tree
  * Returns:
 *  - the pointer to the node with largest element in a AVL tree
*/
struct node *findLargestElement(struct node *tree);

/* Deletes an element from an AVL tree.
 * When needed, perfoms a rotation to restore the balance of a tree.
 * You have to implement this function yourself.
 * The general structure of this function should be similar 
 * to the one from the exercise.
 * Input:
 * - the data to be deleted
 * - the pointer to the start node of the current sub-tree
 * - a variable that controls re-balancing of the tree 
 *   (see more explanation in avl_tree_insert.c)
 * Returns:
 *  - the pointer to the start node of the current sub-tree
 */
struct node *delete(int data, struct node *tree, bool *ht_inc);

#endif // LAB_BINARY_TREES_H
