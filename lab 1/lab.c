// Ahmed Hussein 2025
#include "lab_lists.c"
#include <stdio.h>     
#include <stdlib.h>     
#include <string.h>     
//test array for testing purposes only
void insert_test_entries(struct node** directory) {
    // Array of test entries {name, phone}
    const char* test_entries[][2] = {
        {"John Doe", "1234567890"},
        {"Alice Smith", "9876543210"},
        {"Bob Johnson", "5551234567"},
        {"Emma Watson", "1112223333"},
        {"Michael Brown", "4445556666"}
    };
    
    for (int i = 0; i < 5; i++) {
        struct node* new_node = (struct node*)malloc(sizeof(struct node));
        if (!new_node) {
            printf("Memory allocation failed for test entry %d\n", i+1);
            continue;
        }
        
        strncpy(new_node->name, test_entries[i][0], 63);
        new_node->name[63] = '\0';
        strncpy(new_node->phonenumber, test_entries[i][1], 15);
        new_node->phonenumber[15] = '\0';
        
        new_node->next = *directory;
        *directory = new_node;
    }
    printf("Inserted 5 test entries successfully\n");
}
//Made a print for easier readablility
void print_menu() {
    printf("\n\nTelephone Directory\n");
    printf("1. Display records\n");
    printf("2. Insert record\n");
    printf("3. Delete record\n");
    printf("4. Search record\n");
    printf("5. Delete all records\n");
    printf("6. Insert test entries\n");  
    printf("7. Exit\n\n|");
}

//Asks which option to choose
int get_valid_choice() {
    int choice;
    while (1) {
        printf("Enter choice (1-7): ");
        if (scanf("%d", &choice) != 1) {
            printf("Invalid input. Please enter a number.\n");
            while (getchar() != '\n');
            continue;
        }
        if (choice < 1 || choice > 7) {
            printf("Choice must be between 1 and 7\n");
            continue;
        }
        return choice;
    }
}
//the main program.
int main() {
    struct node* directory = NULL;
    int choice;

    while (1) {
        print_menu();
        choice = get_valid_choice();

        switch (choice) {
            case 1: 
                display(directory); 
                break;
                
            case 2: 
                insert_record(&directory); 
                break;
                
            case 3: 
                delete_record(&directory); 
                break;
                
            case 4: {
                printf("Search by: 1 - Name, 2 - Phone Number: ");
                int opt;
                if (scanf("%d", &opt) != 1 || (opt != 1 && opt != 2)) {
                    printf("Invalid search option.\n");
                    while (getchar() != '\n');
                    break;
                }
                query_directory(directory, opt);
                break;
            }
                
            case 5: 
                delete_directory(&directory); 
                break;
                
            case 6: 
                insert_test_entries(&directory);
                break;
                
            case 7:
                delete_directory(&directory);
                printf("Exiting...\n");
                return 0;
        }
    }
}
// 2025 Ahmed Hussein