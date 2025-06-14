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

// Function to create a node (implementation from ex_btree_3.c)
struct node *createNode(int keys[], int count, struct node *children[]) {
    struct node *newNode = (struct node *)malloc(sizeof(struct node));
    newNode->keys = (int *)malloc(count * sizeof(int));
    newNode->children = (struct node **)malloc((count + 1) * sizeof(struct node *));
    
    for (int i = 0; i < count; i++) {
        newNode->keys[i] = keys[i];
    }
    
    for (int i = 0; i <= count; i++) {
        newNode->children[i] = children[i];
    }
    
    newNode->key_count = count;
    newNode->is_leaf = 1; // Assume leaf by default
    return newNode;
}

// Function to traverse B-tree in-order (implementation from ex_btree_3.c)
void traverse(struct node *tree, int level) {
    if (tree == NULL) return;
    
    for (int i = 0; i < tree->key_count; i++) {
        traverse(tree->children[i], level + 1);
        for (int j = 0; j < level; j++) printf("   ");
        printf("%d\n", tree->keys[i]);
    }
    traverse(tree->children[tree->key_count], level + 1);
}

// Function to search for a key in B-tree
struct node *search(struct node *tree, int val) {
    if (tree == NULL) {
        return NULL;
    }
    
    int i = 0;
    while (i < tree->key_count && val > tree->keys[i]) {
        i++;
    }
    
    if (i < tree->key_count && val == tree->keys[i]) {
        return tree;
    }
    
    if (tree->is_leaf) {
        return NULL;
    }
    
    return search(tree->children[i], val);
}

int main() {
    // Build the test B-tree (order 4) from Figure 1
    // Leaf nodes
    int leaf1_keys[] = {18, 29};
    int leaf2_keys[] = {45};
    int leaf3_keys[] = {49};
    int leaf4_keys[] = {63, 72};
    int leaf5_keys[] = {59};
    
    struct node *leaf1 = createNode(leaf1_keys, 2, (struct node *[]){NULL, NULL, NULL});
    struct node *leaf2 = createNode(leaf2_keys, 1, (struct node *[]){NULL, NULL});
    struct node *leaf3 = createNode(leaf3_keys, 1, (struct node *[]){NULL, NULL});
    struct node *leaf4 = createNode(leaf4_keys, 2, (struct node *[]){NULL, NULL, NULL});
    struct node *leaf5 = createNode(leaf5_keys, 1, (struct node *[]){NULL, NULL});
    
    // Internal nodes
    int int1_keys[] = {30, 45};
    int int2_keys[] = {49, 63};
    
    struct node *int1 = createNode(int1_keys, 2, (struct node *[]){leaf1, leaf2, NULL});
    struct node *int2 = createNode(int2_keys, 2, (struct node *[]){leaf3, leaf4, leaf5});
    
    // Root node
    int root_keys[] = {45};
    struct node *root = createNode(root_keys, 1, (struct node *[]){int1, int2});
    
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