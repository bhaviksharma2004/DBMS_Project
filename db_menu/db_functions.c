#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "database.h"
#include "../table_menu/table.h"
#include "../utils/utils.h"


int num_db = 0;

void createDatabase(db **db_head, db **db_tail) {
    char name[33];
    printf("Enter name of the database 1-32 characters: ");
    scanf("%32s", name);
    while (getchar() != '\n');

    if(dbExist(name, *db_head)) {
        printf("Database name already exists\n\n");
        return;
    }

    num_db++;

    db *new_db = (db *) malloc(sizeof(db));
    new_db->name = strdup(name);
    new_db->table_head = NULL;
    new_db->table_tail = NULL;
    new_db->next = NULL;

    if(*db_tail == NULL) *db_head = new_db;
    else (*db_tail)->next = new_db;

    *db_tail = new_db;

    printf("Database '%s' created successfully.\n\n", name);
    createTable(&((*db_tail)->table_head), &((*db_tail)->table_tail));
}

void removeDatabase(db **db_head) {
    char name[33];
    printf("Enter name of database 1-32 characters: ");
    scanf("%32s", name);
    while (getchar() != '\n'); 


    if(num_db == 0 || !dbExist(name, *db_head)) {
        printf("Database does not exist\n\n");
        return;
    }
    num_db--;

    if(strcmp((*db_head)->name, name) == 0) {
        db *temp = *db_head;
        *db_head = (*db_head)->next;
        free(temp->name);
        free(temp);
        printf("Database '%s' removed successfully.\n\n", name);
        return;
    }

    db *db_node = *db_head;
    db *prev = NULL;
    while(db_node) {
        if(strcmp(db_node->name, name) == 0) {
            prev->next = db_node->next;
            free(db_node->name);
            free(db_node);
            printf("Database '%s' removed successfully.\n\n", name);
            return;
        }
        prev = db_node;
        db_node = db_node->next;
    }
    printf("Database '%s' not found.\n\n", name);
}

void selectDatabase(db **db_head) {
    char name[33];
    printf("Enter name of the database 1-32 characters: ");
    scanf("%32s", name);
    while (getchar() != '\n'); 


    if(!dbExist(name, *db_head)) {
        printf("Database '%s' does not exist\n\n", name);
        return;
    }

    db *db_node = *db_head;
    while(db_node) {
        if(strcmp(db_node->name, name) == 0) {
            printf("Inside '%s' database.\n\n", name);
            tableMenu(&db_node->table_head, &db_node->table_tail);
            return;
        }
        db_node = db_node->next;
    }
}

void saveDatabase() {
    // Write Logic to save database
}