/******************************************************************
 * Lab1. Linked Lists (TDRK12 Spring 2023)
 * This header file includes signatures of the functions and 
 * declaration of a structure to be implemenetd in your solution.
 * Written by Vladimir Tarasov, Spring 2023
 * Modified by He Tan, Spring 2025
********************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#ifndef LAB_LISTS_H  /* Include guard */
#define LAB_LISTS_H
struct node *query_directory_plus(struct node *start, char *text, int choice);

/*
 * A structure implementing a linked list node for the phone directory
 * Every linked list node shall contain:
 * - A phone number, e.g. as a string of digits. 
 *   The phone no. also functions as the ID of a record.
 * - The name of a person having this phone number.
 *   (it can be first name, last name or both names)
 * - A pointer to the next node of a list.
 */
struct node{
    char phonenumber [16] ;
    char name[64] ;
    struct node* next;
};

/*
 * Displays all records in the telephone directory.
 * Input:
 * - the pointer to the start node of the list
 * Otput for each record:
 * - the ordinal number of the record in the directory
 * - the phone no.
 * - the name
 */
void display(struct node *start) 
{
    if(start == NULL) 
    {
        printf("The directory is empty\n");
        return;
    }
    
    struct node *current = start;
    int count = 1;
    
    while (current != NULL)
    {
        printf("%d : %s : %s\n", count++, current->name, current->phonenumber);
        current = current->next;
    }
    printf("=== Finished the list ===\n");
}




/*
 * Inserts a new record at the beginning of the directory.
 * Fist checks that the record already exists -
 * duplicates are not allowed.
 * Input:
 * - the pointer to the pointer to the first list node
 * Returns:
 * 0 if the insertion is successful,
 * -1 if the node already exists in the directory
 */
int insert_record(struct node **start) 
{
    struct node* newNode = (struct node*)malloc(sizeof(struct node));
    if (!newNode) {
        printf("Memory allocation failed\n");
        return -1;
    }

    // Flush buffer to prevent input issues
    while (getchar() != '\n');

    printf("Write name: ");
    fgets(newNode->name, sizeof(newNode->name), stdin);
    newNode->name[strcspn(newNode->name, "\n")] = '\0';

    if (query_directory_plus(*start, newNode->name, 1)) {
        printf("Error: Name already exists\n");
        free(newNode);
        return -1;
    }

    printf("Write phone number: ");
    fgets(newNode->phonenumber, sizeof(newNode->phonenumber), stdin);
    newNode->phonenumber[strcspn(newNode->phonenumber, "\n")] = '\0';

    if (query_directory_plus(*start, newNode->phonenumber, 2)) {
        printf("Error: Phone number already exists\n");
        free(newNode);
        return -1;
    }

    newNode->next = *start;
    *start = newNode;

    printf("Inserted successfully\n");
    return 0;
}

/*
 * Deletes a record with the given phone no. from user.
 * If the record does not exist, the deletion is unsuccessful.
 * Inputs:
 * - the pointer to the pointer to the first list node
 * Returns:
 *  0 if successful,
 *  -1 otherwise.
 */
int delete_record(struct node **start)
{
    if(*start == NULL) {
        printf("Directory is empty!\n");
        return -1;
    }

    char tempnum[16];
    printf("Write the number you want deleted: ");
    scanf("%s", tempnum);

    struct node *temp = *start, *previous = NULL;

    while (temp != NULL)
    {
        if(strcmp(temp->phonenumber, tempnum) == 0) {
            if(previous == NULL) {
                *start = temp->next;
            }
            else {previous->next = temp->next;}
            free(temp);
            printf("Record deleted :c\n");
            return 0;
        }
        previous = temp;
        temp = temp->next;
    }
    printf("Record not found :c so sad\n");
    return -1;
}

/*
 * Queries the directory by the given phone no. or name from user.
 * Inputs:
 * - the pointer to the first list node
 * - option flag that is set to 1 to search by phone 
 *                           or 2 to search by name
 * Returns
 * - the pointer to the found record or NULL if not found
 */
struct node *query_directory(struct node *start, int option)
{
    struct node* temp = start;
    char tempstr[64];
    
    switch (option)
    {
    case 1:
        printf("Write name: ");
        break;
    case 2:
        printf("Write number: ");
        break;
    default:
        printf("Invalid option, try again\n");
        return NULL;
    }
    scanf("%s", tempstr);

    while(temp != NULL) {
        if ((option == 1 && strcmp(temp->name, tempstr) == 0) ||
            (option == 2 && strcmp(temp->phonenumber, tempstr) == 0)) {
            printf("Found record: %s : %s\n", temp->name, temp->phonenumber);
            return temp;
        }
        temp = temp->next;
    }
    return NULL;
}

/*
CUSTOM. For private use. Query to find if there is a number or name duplicate .abort
1. struct node *start 
2. char text{64}
3. int choice  , 1 name , 2 number .  Returns node of it. 
*/

struct node *query_directory_plus(struct node *start, char *text, int choice) {
    struct node* temp = start;

    while (temp != NULL) {
        if ((choice == 1 && strcmp(temp->name, text) == 0) ||
            (choice == 2 && strcmp(temp->phonenumber, text) == 0)) {
            return temp; // Found record
        }
        temp = temp->next;
    }
    return NULL; // Not found
}




/*
 * Deletes all records in the telephone directory
 * and sets the start pointer to NULL.
 * It is supposed to be called before exiting.
 * Input:
 * - the pointer to the pointer to the first list node
 */
void delete_directory(struct node **start)
{
    if(*start == NULL) {
        printf("Directory is already empty\n");
        return;
    }

    struct node* current = *start;
    struct node *next;

    while (current != NULL)
    {
        next = current->next;
        free(current);
        current = next;
    }
    *start = NULL;
    printf("All records deleted successfully\n");
}

#endif  // LAB_LISTS_H
// 2025 Ahmed Hussein