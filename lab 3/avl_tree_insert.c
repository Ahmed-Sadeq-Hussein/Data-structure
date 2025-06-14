#include <stdio.h>
#include <stdlib.h>
#include "lab_binary_trees.h"

// AVL Tree Node Structure
struct node {
    int data;
    int balance;
    struct node *left;
    struct node *right;
};

// Helper function to get height of a node
int height(struct node *node) {
    if (node == NULL)
        return 0;
    return 1 + (height(node->left) > height(node->right) ? height(node->left) : height(node->right));
}

// Helper function to get balance factor
int getBalance(struct node *node) {
    if (node == NULL)
        return 0;
    return height(node->left) - height(node->right);
}

// Right rotation (LL rotation)
struct node *rightRotate(struct node *y) {
    struct node *x = y->left;
    struct node *T2 = x->right;

    // Perform rotation
    x->right = y;
    y->left = T2;

    // Update balance factors
    y->balance = getBalance(y);
    x->balance = getBalance(x);

    return x;
}

// Left rotation (RR rotation)
struct node *leftRotate(struct node *x) {
    struct node *y = x->right;
    struct node *T2 = y->left;

    // Perform rotation
    y->left = x;
    x->right = T2;

    // Update balance factors
    x->balance = getBalance(x);
    y->balance = getBalance(y);

    return y;
}

// Insert function
struct node *insert(int data, struct node *tree, bool *ht_inc) {
    if (tree == NULL) {
        tree = (struct node *)malloc(sizeof(struct node));
        tree->data = data;
        tree->left = tree->right = NULL;
        tree->balance = 0;
        *ht_inc = TRUE;
        return tree;
    }

    if (data < tree->data) {
        tree->left = insert(data, tree->left, ht_inc);
        if (*ht_inc) {
            switch (tree->balance) {
                case -1:
                    tree->balance = 0;
                    *ht_inc = FALSE;
                    break;
                case 0:
                    tree->balance = 1;
                    break;
                case 1:
                    if (tree->left->balance == 1) {
                        printf("LL Rotation\n");
                        tree = rightRotate(tree);
                    } else {
                        printf("LR Rotation\n");
                        tree->left = leftRotate(tree->left);
                        tree = rightRotate(tree);
                    }
                    tree->balance = 0;
                    *ht_inc = FALSE;
            }
        }
    } else if (data > tree->data) {
        tree->right = insert(data, tree->right, ht_inc);
        if (*ht_inc) {
            switch (tree->balance) {
                case 1:
                    tree->balance = 0;
                    *ht_inc = FALSE;
                    break;
                case 0:
                    tree->balance = -1;
                    break;
                case -1:
                    if (tree->right->balance == -1) {
                        printf("RR Rotation\n");
                        tree = leftRotate(tree);
                    } else {
                        printf("RL Rotation\n");
                        tree->right = rightRotate(tree->right);
                        tree = leftRotate(tree);
                    }
                    tree->balance = 0;
                    *ht_inc = FALSE;
            }
        }
    }
    return tree;
}

// Display function
void display(struct node *ptr, int level) {
    if (ptr != NULL) {
        display(ptr->right, level + 1);
        printf("\n");
        for (int i = 0; i < level; i++)
            printf("    ");
        printf("%d", ptr->data);
        display(ptr->left, level + 1);
    }
}

// Find largest element
struct node *findLargestElement(struct node *tree) {
    if (tree == NULL)
        return NULL;
    while (tree->right != NULL)
        tree = tree->right;
    return tree;
}

// Delete function
struct node *delete(int data, struct node *tree, bool *ht_inc) {
    if (tree == NULL) {
        *ht_inc = FALSE;
        return NULL;
    }

    if (data < tree->data) {
        tree->left = delete(data, tree->left, ht_inc);
        if (*ht_inc) {
            switch (tree->balance) {
                case -1:
                    tree->balance = 0;
                    break;
                case 0:
                    tree->balance = 1;
                    *ht_inc = FALSE;
                    break;
                case 1:
                    if (tree->left->balance >= 0) {
                        printf("R1 Rotation\n");
                        tree = rightRotate(tree);
                    } else {
                        printf("R-1 Rotation\n");
                        tree->left = leftRotate(tree->left);
                        tree = rightRotate(tree);
                    }
                    *ht_inc = FALSE;
            }
        }
    } else if (data > tree->data) {
        tree->right = delete(data, tree->right, ht_inc);
        if (*ht_inc) {
            switch (tree->balance) {
                case 1:
                    tree->balance = 0;
                    break;
                case 0:
                    tree->balance = -1;
                    *ht_inc = FALSE;
                    break;
                case -1:
                    printf("Right Rotation\n");
                    tree = leftRotate(tree);
                    *ht_inc = FALSE;
            }
        }
    } else {
        // Node to delete found
        struct node *temp;
        if (tree->left == NULL || tree->right == NULL) {
            temp = tree->left ? tree->left : tree->right;
            if (temp == NULL) {
                temp = tree;
                tree = NULL;
                *ht_inc = TRUE;
            } else {
                *tree = *temp;
                *ht_inc = TRUE;
            }
            free(temp);
        } else {
            temp = findLargestElement(tree->left);
            tree->data = temp->data;
            tree->left = delete(temp->data, tree->left, ht_inc);
            if (*ht_inc) {
                switch (tree->balance) {
                    case -1:
                        tree->balance = 0;
                        break;
                    case 0:
                        tree->balance = 1;
                        *ht_inc = FALSE;
                        break;
                    case 1:
                        if (tree->left->balance >= 0) {
                            printf("R1 Rotation\n");
                            tree = rightRotate(tree);
                        } else {
                            printf("R-1 Rotation\n");
                            tree->left = leftRotate(tree->left);
                            tree = rightRotate(tree);
                        }
                        *ht_inc = FALSE;
                }
            }
        }
    }
    return tree;
}

// Search function
struct node *search(struct node *ptr, int data) {
    if (ptr == NULL || ptr->data == data)
        return ptr;
    if (ptr->data < data)
        return search(ptr->right, data);
    return search(ptr->left, data);
}

// Inorder traversal
void inorder(struct node *ptr) {
    if (ptr != NULL) {
        inorder(ptr->left);
        printf("%d ", ptr->data);
        inorder(ptr->right);
    }
}

// Main function for testing
int main() {
    struct node *root = NULL;
    bool ht_inc;
    int choice, value;
    
    while (1) {
        printf("\nAVL Tree Operations\n");
        printf("1. Insert\n");
        printf("2. Delete\n");
        printf("3. Display\n");
        printf("4. Search\n");
        printf("5. Inorder Traversal\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        
        switch (choice) {
            case 1:
                printf("Enter value to insert: ");
                scanf("%d", &value);
                root = insert(value, root, &ht_inc);
                break;
            case 2:
                printf("Enter value to delete: ");
                scanf("%d", &value);
                root = delete(value, root, &ht_inc);
                break;
            case 3:
                printf("AVL Tree:\n");
                display(root, 1);
                printf("\n");
                break;
            case 4:
                printf("Enter value to search: ");
                scanf("%d", &value);
                if (search(root, value))
                    printf("Value %d found in tree\n", value);
                else
                    printf("Value %d not found\n", value);
                break;
            case 5:
                printf("Inorder Traversal: ");
                inorder(root);
                printf("\n");
                break;
            case 6:
                exit(0);
            default:
                printf("Invalid choice\n");
        }
    }
    return 0;
}