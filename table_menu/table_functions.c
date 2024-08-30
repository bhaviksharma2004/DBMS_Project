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
    char name[33];
    printf("Enter name of the table 1-32 characters: ");
    scanf("%32s", name);
    while (getchar() != '\n');


    if(num_table == 0 || !tableExist(name, *table_head)) {
        printf("Table does not exist\n\n");
        return;
    }
    num_table--;

    if(strcmp((*table_head)->name, name) == 0) {
        table *temp = *table_head;
        *table_head = (*table_head)->next;
        free(temp->name);
        free(temp->primaryKey);
        free(temp);
        printf("Table '%s' removed successfully.\n\n", name);
        return;
    }

    table *table_node = *table_head;
    table *prev = NULL;
    while(table_node) {
        if(strcmp(table_node->name, name) == 0) {
            prev->next = table_node->next;
            free(table_node->name);
            free(table_node->primaryKey);
            free(table_node);
            printf("Table '%s' removed successfully.\n\n", name);
            return;
        }
        prev = table_node;
        table_node = table_node->next;
    }
    printf("Table '%s' not found.\n\n", name);
}

void selectTable(table **table_head) {
    char name[33];
    printf("Enter name of the table 1-32 characters: ");
    scanf("%32s", name);
    while (getchar() != '\n');


    // Check if the table exists
    if (!tableExist(name, *table_head)) {
        printf("Table '%s' does not exist\n\n", name);
        return;
    }

    table *table_node = *table_head;
    while (table_node) {
        if (strcmp(table_node->name, name) == 0) {
            printf("Selected table '%s'.\n\n", name);
            cellMenu(table_node->topLeft, table_node->bottomLeft, table_node->primaryKey);
            return;
        }
        table_node = table_node->next;
    }
    printf("Table '%s' not found.\n\n", name);
}