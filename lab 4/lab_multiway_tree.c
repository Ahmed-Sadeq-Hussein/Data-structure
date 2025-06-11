// AHMED HUSSEIN 2025
/*
PSEUDO CODE 
function search (node , key)
{
 i = 1
 while i <= node.key-count && key > node.keys[i]
 {
 i = i + 1
 }

 IF i <=key.key-count && key > node.keys[i]
 {
 return node
 }

 ELIF node is a leaf
 {
 return NULL //ergo not found
 }

 else
 {
 return search(node.children[i], key) //This is recursive earch 
 }

}
*/
#include <stdio.h>
#include <stdlib.h>
#include "lab_multiway_trees.h"
struct node {
    int *keys;              // Array of keys
    struct node **children; // Array of child pointers
    int key_count;          // Number of keys currently in node
    int is_leaf;            // Leaf flag (1 if leaf, 0 otherwise)
};

//function to search for a key in B-tree according to the psuedo code written above
struct node *search(struct node *tree, int val) {
    if (tree == NULL) {
        return NULL;
    }
    
    int i = 0;
    //find the first key greater than or equal to val
    while (i < tree->key_count && val > tree->keys[i]) {
        i++;
    }
    
    //If the found key is equal to val, return this node
    if (i < tree->key_count && val == tree->keys[i]) {
        return tree;
    }
    
    //If this is a leaf node, the key is not present
    if (tree->is_leaf) {
        return NULL;
    }
    
    //otherwise, search in the appropriate child. recursive func part
    return search(tree->children[i], val);
}

// Main function to demonstrate search functionality
int main() {
    // Build the test B-tree (order 4) from Figure 1
    // This would normally be in ex_btree_3.c
    
    // Example of building a small part of the tree:
    // Node with keys 45 (root)
    int root_keys[] = {45};
    struct node *root_children[2] = {NULL, NULL}; // Simplified for example
    struct node *root = createNode(root_keys, 1, root_children);
    
    // Add more nodes to build the complete test tree...
    
    printf("==== Output of the B-tree search program====\n");
    printf("The created B-tree:\n");
    traverse(root, 0);
    
    int option;
    do {
        printf("\n1.Search\n2.Quit\nEnter your option: ");
        scanf("%d", &option);
        
        if (option == 1) {
            int search_val;
            printf("Enter the value to search for: ");
            scanf("%d", &search_val);
            
            struct node *result = search(root, search_val);
            if (result != NULL) {
                printf("The key %d is found\n", search_val);
            } else {
                printf("The key %d is NOT found\n", search_val);
            }
        }
    } while (option != 2);
    
    return 0;
}