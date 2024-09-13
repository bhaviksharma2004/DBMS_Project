#include <stdlib.h>
#include <string.h>
#include "table.h"
#include "../utils/utils.h"
#include "../cell_menu/cell.h"


int num_table = 0;

// Helper functions
void freeTableResources(table *tbl) {
    if (tbl == NULL) return;

    if (tbl->topLeft) {
        freeCells(tbl->topLeft);
    }
    
    if (tbl->name) {
        free(tbl->name);
    }
    
    if (tbl->primaryKey) {
        free(tbl->primaryKey);
    }    
    free(tbl);
}

table* findAndRemoveTable(table **table_head, const char *name) {
    table *current = *table_head;
    table *prev = NULL;

    while (current) {
        if (strcmp(current->name, name) == 0) {
            if (prev == NULL) {  // Removing head table
                *table_head = current->next;
            } else {
                prev->next = current->next;
            }
            return current;
        }
        prev = current;
        current = current->next;
    }
    return NULL;
}

// Menu functions
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

    if (*table_tail == NULL) { 
        *table_head = new_table;
    }
    else{ 
        (*table_tail)->next = new_table;
    }
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


    if(!tableExist(name, *table_head)) {
        printf("Table does not exist\n\n");
        return;
    }

    table *table_to_remove = findAndRemoveTable(table_head, name);
    if (table_to_remove) {
        // Free Table Resources
        freeTableResources(table_to_remove);
        num_table--;
        printf("Table '%s' removed successfully.\n\n", name);
    } 
    else {
        printf("Table '%s' not found.\n\n", name);
    }
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