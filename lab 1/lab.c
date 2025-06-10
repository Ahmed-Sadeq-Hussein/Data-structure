//lab.c (Fixed Version)
// Ahmed Hussein 2025
#include "lab_lists.h"
#include <stdio.h>     
#include <stdlib.h>     
#include <string.h>    

int main() {
    struct node* directory = NULL;
    int choice;

    while (1) {
        printf("\n\n\nTelephone Directory\n");
        printf("1. Display records\n");
        printf("2. Insert record\n");
        printf("3. Delete record\n");
        printf("4. Search record\n");
        printf("5. Delete all records\n");
        printf("6. Exit\n");
        printf("Enter choice: ");

        //FIX:Input validation
        if (scanf("%d", &choice) != 1) {
            printf("Invalid input. Please enter a number.\n");
            while (getchar() != '\n'); 
            continue;
        }

        switch (choice) {
            case 1: display(directory); break;
            case 2: insert_record(&directory); break;
            case 3: delete_record(&directory); break;
            case 4:
                printf("Search by: 1 - Name, 2 - Phone Number: ");
                int opt;
                if (scanf("%d", &opt) != 1 || (opt != 1 && opt != 2)) {
                    printf("Invalid search option.\n");
                    break;
                }
                query_directory(directory, opt);
                break;
            case 5: delete_directory(&directory); break;
            case 6:
                delete_directory(&directory);
                printf("Exiting...\n");
                return 0;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }
}
// 2025 Ahmed Hussein
