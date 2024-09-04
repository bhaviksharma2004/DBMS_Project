#include <stdlib.h>
#include <string.h>
#include "table.h"
#include "../utils/utils.h"
#include "../cell_menu/cell.h"


int num_table = 0;

void createTable(table **table_head, table **table_tail) {
    char name[33];
    printf("Enter name of the table 1-32 characters: ");
    scanf("%32s", name);
    while (getchar() != '\n');


    if(tableExist(name, *table_head)) {
	    printf("Table name already exists\n\n");
	    return;
    }
    num_table++;

    table *new_table = (table *) malloc(sizeof(table));
    new_table->name = strdup(name);
    new_table->topLeft= NULL;
    new_table->bottomLeft= NULL;
    new_table->next = NULL;

    if(*table_tail == NULL) *table_head = new_table;
    else (*table_tail)->next = new_table;

    *table_tail = new_table;

    printf("Table '%s' created successfully.\n\n", name);
    addRow(&((*table_tail)->bottomLeft), &((*table_tail)->topLeft), &(new_table->primaryKey));
}

void removeTable(table **table_head) {
    if (*table_head == NULL) {
        printf("No tables available to remove.\n\n");
        return;
    }

    char name[33];
    printf("Enter name of the table 1-32 characters: ");
    scanf("%32s", name);
    while (getchar() != '\n');


    if(num_table == 0 || !tableExist(name, *table_head)) {
        printf("Table does not exist\n\n");
        return;
    }

    table *current = *table_head;
    table *prev = NULL;
    while(current) {
        if(strcmp(current->name, name) == 0) {
            if (prev == NULL) {     // Removing head table
                *table_head = current->next;
            }
            else {
                prev->next = current->next;
            }

            freeCells(current->topLeft);  // MOST IMP. TO CLEAN UP WHOLE MEMORY INSIDE THE TABLE

            prev->next = current->next;
            free(current->name);
            free(current->primaryKey);
            free(current);

            num_table--;
            printf("Table '%s' removed successfully.\n\n", name);
            return;
        }
        prev = current;
        current = current->next;
    }
    printf("Table '%s' not found.\n\n", name);
}

void selectTable(table **table_head) {
    if (*table_head == NULL) {
        printf("No tables available to select.\n\n");
        return;
    }
     
    char name[33];
    printf("Enter name of the table 1-32 characters: ");
    scanf("%32s", name);
    while (getchar() != '\n');


    table *current = *table_head;
    while (current) {
        if (strcmp(current->name, name) == 0) {
            printf("Selected table '%s'.\n\n", name);
            cellMenu(current->topLeft, current->bottomLeft, current->primaryKey);
            return;
        }
        current = current->next;
    }
    printf("Table '%s' not found.\n\n", name);
}

void listTables(table *table_head){
    if(table_head == NULL){ 
        printf("\nNo table to print\n\n");
        return;
    }

    printf("\n");
    table *curr = table_head;
    while(curr){
        printf("%s\n", curr->name);
        curr = curr->next;
    }
    printf("\n\n");
}