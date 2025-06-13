/******************************************************************
 * Lab1. Linked Lists (TDRK12 Spring 2023)
 * This header file includes signatures of the functions and 
 * declaration of a structure to be implemenetd in your solution.
 * Written by Vladimir Tarasov, Spring 2023
 * Modified by He Tan, Spring 2025
********************************************************************/

#ifndef LAB_LISTS_H  /* Include guard */
#define LAB_LISTS_H

/*
 * A structure implementing a linked list node for the phone directory
 * Every linked list node shall contain:
 * - A phone number, e.g. as a string of digits. 
 *   The phone no. also functions as the ID of a record.
 * - The name of a person having this phone number.
 *   (it can be first name, last name or both names)
 * - A pointer to the next node of a list.
 */
struct node;

/*
 * Displays all records in the telephone directory.
 * Input:
 * - the pointer to the start node of the list
 * Otput for each record:
 * - the ordinal number of the record in the directory
 * - the phone no.
 * - the name
 */
void display(struct node *start);

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
int insert_record(struct node **start);

/*
 * Deletes a record with the given phone no. from user.
 * If the record does not exist, the deletion is unsuccessful.
 * Inputs:
 * - the pointer to the pointer to the first list node
 * Returns:
 *  0 if successful,
 *  -1 otherwise.
 */
int delete_record(struct node **start);

/*
 * Queries the directory by the given phone no. or name from user.
 * Inputs:
 * - the pointer to the first list node
 * - option flag that is set to 1 to search by phone 
 *                           or 2 to search by name
 * Returns
 * - the pointer to the found record or NULL if not found
 */
struct node *query_directory(struct node *start, int option);

/*
 * Deletes all records in the telephone directory
 * and sets the start pointer to NULL.
 * It is supposed to be called before exiting.
 * Input:
 * - the pointer to the pointer to the first list node
 */
void delete_directory(struct node **start);

#endif  // LAB_LISTS_H
