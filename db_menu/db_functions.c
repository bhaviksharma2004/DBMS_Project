#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "database.h"
#include "../table_menu/table.h"
#include "../utils/utils.h"

#define MAX_LINE_LENGTH 256
#define MAX_NAME_LENGTH 33

// Helper functions
void printColumnData(FILE *file, cell *columnCell) {
    while (columnCell) {
        fprintf(file, "%s %s\n", columnCell->colName, columnCell->dataType);
        columnCell = columnCell->right;
    }
}

void printRowData(FILE *file, cell *rowCell) {
    while (rowCell) {
        if (strcmp(rowCell->dataType, "INTEGER") == 0) {
            fprintf(file, "%d\n", *((int *)rowCell->data));
        } 
        else if (strcmp(rowCell->dataType, "FLOAT") == 0) {
            fprintf(file, "%.2f\n", *((float *)rowCell->data));
        } 
        else if (strcmp(rowCell->dataType, "STRING") == 0 || strcmp(rowCell->dataType, "DATE") == 0) {
            fprintf(file, "%s\n", (char *)rowCell->data);
        }
        rowCell = rowCell->right;
    }
}

// Menu functions
void createDatabase(db **db_head, db **db_tail) {
    char name[MAX_NAME_LENGTH];
    printf("Enter name of the database 1-32 characters: ");
    scanf("%32s", name);
    while (getchar() != '\n');

    if(dbExist(name, *db_head)) {
        printf("Database name already exists\n\n");
        return;
    }

    db *new_db = (db *) malloc(sizeof(db));
    new_db->name = strdup(name);
    new_db->table_head = NULL;
    new_db->table_tail = NULL;
    new_db->next = NULL;

    if (*db_tail == NULL){ 
        *db_head = new_db;
    }
    else{ 
        (*db_tail)->next = new_db;
    }

    *db_tail = new_db;

    printf("Database '%s' created successfully.\n\n", name);
    createTable(&((*db_tail)->table_head), &((*db_tail)->table_tail));
}

void removeDatabase(db **db_head, db **db_tail) {
    char name[MAX_NAME_LENGTH];
    printf("Enter name of database 1-32 characters: ");
    scanf("%32s", name);
    while (getchar() != '\n'); 

    if(!dbExist(name, *db_head)) {
        printf("Database does not exist\n\n");
        return;
    }

    db *db_node = *db_head;
    db *prev = NULL;    // Will store pointer to previous node

    while (db_node) {
        if (strcmp(db_node->name, name) == 0) {
            if (prev == NULL) { 
                *db_head = db_node->next;  // Remove head node
            }
            else { 
                prev->next = db_node->next;
            }

            if (*db_tail == db_node) { 
                *db_tail = prev;  // If tail node getting removed
            }

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
    char name[MAX_NAME_LENGTH];
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

void listDatabases(db *db_head) {
    if (db_head == NULL) { 
        printf("No Database to print\n");
        return;
    }

    printf("\n");
    db *curr = db_head;
    int i = 0;
    while (curr) {
        printf("%d. %s\n", i++, curr->name);
        curr = curr->next;
    }
    printf("\n\n");
}

void saveDatabase(const char *filePath, db *dbHead) {
    FILE *file = fopen(filePath, "w");
    if (!file) {
        printf("Error opening file for saving");
        return;
    }

    db *currentDB = dbHead;
    while (currentDB) {
        fprintf(file, "DATABASE:%s\n", currentDB->name);

        table *currentTable = currentDB->table_head;
        while (currentTable) {
            fprintf(file, "TABLE:%s %s\n", currentTable->name, currentTable->primaryKey);

            // Print column definitions with types
            printColumnData(file, currentTable->topLeft);

            cell *rowCell = currentTable->topLeft;
            while (rowCell) {
                printRowData(file, rowCell);
                rowCell = rowCell->down;
            }

            fprintf(file, "END_TABLE\n");
            currentTable = currentTable->next;
        }
        fprintf(file, "END_DATABASE\n");
        currentDB = currentDB->next;
    }

    fclose(file);
    printf("Database saved successfully.\n");
}


void loadDatabases(const char *filename, db **db_head, db **db_tail) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Error opening file");
        return;
    }

    db *current_db = NULL;
    table *current_table = NULL;
    cell *current_column = NULL;
    char line[100];
    int col_count = 0;
    int row_count = 0;

    while (fgets(line, sizeof(line), file)) {
        // Trim newline character
        line[strcspn(line, "\n")] = '\0';

        if (strncmp(line, "DATABASE:", 9) == 0) {
            // Process new database
            current_db = (db *)malloc(sizeof(db));
            current_db->name = strdup(line + 9);
            current_db->table_head = NULL;
            current_db->table_tail = NULL;
            current_db->next = NULL;

            if (*db_head == NULL) {
                *db_head = current_db;
                *db_tail = current_db;
            } else {
                (*db_tail)->next = current_db;
                *db_tail = current_db;
            }
        } 
        else if (strncmp(line, "TABLE:", 6) == 0) {
            // Process new table and primary key
            char *table_name = strtok(line + 6, " ");
            char *primary_key = strtok(NULL, " ");

            current_table = (table *)malloc(sizeof(table));
            current_table->name = strdup(table_name);
            current_table->primaryKey = strdup(primary_key);
            current_table->topLeft = NULL;
            current_table->bottomLeft = NULL;
            current_table->next = NULL;

            if (current_db->table_head == NULL) {
                current_db->table_head = current_table;
                current_db->table_tail = current_table;
            } else {
                current_db->table_tail->next = current_table;
                current_db->table_tail = current_table;
            }

            col_count = 0; // Reset count for new table
            row_count = 0; // Reset count for new table
        } 
        else if (strncmp(line, "END_TABLE", 9) == 0) {
            current_table = NULL;
        } 
        else if (strncmp(line, "END_DATABASE", 12) == 0) {
            current_db = NULL;
        } 
        else if (current_table != NULL) {
            if (strchr(line, ' ')) {
                // Process column definition
                char *column_name = strtok(line, " ");
                char *data_type = strtok(NULL, " ");

                cell *column_cell = (cell *)malloc(sizeof(cell));
                column_cell->colName = strdup(column_name);
                column_cell->dataType = strdup(data_type);
                column_cell->data = NULL;
                column_cell->right = NULL;
                column_cell->down = NULL;
                column_cell->top = NULL;

                if (current_table->topLeft == NULL) {
                    current_table->topLeft = column_cell;
                    current_table->bottomLeft = column_cell;
                }
                else {
                    cell *last_column = current_table->topLeft;
                    while (last_column->right != NULL) {
                        last_column = last_column->right;
                    }
                    last_column->right = column_cell;
                }
                current_column = column_cell; // Update current_column for rows
                col_count++;
            } 
            else {
                // Process row data
                cell *column_cell = current_table->topLeft;

                if(row_count == 0){
                    for (int it = 0; it < col_count; it++) {
                        insertCellData(column_cell, line);
                        column_cell = column_cell->right;
                        if (fgets(line, sizeof(line), file)) {
                            line[strcspn(line, "\n")] = '\0'; // Trim newline
                        }
                        else break;
                    }
                    current_table->bottomLeft = current_table->topLeft;
                }
                else{
                    // Store last row_start
                    cell *last_row_start = current_table->bottomLeft;

                    // Create new cell
                    cell *new_row_start = (cell *)malloc(sizeof(cell));
                    new_row_start->top = last_row_start;
                    new_row_start->down = NULL;
                    new_row_start->colName = strdup(current_table->topLeft->colName);
                    new_row_start->dataType = strdup(current_table->topLeft->dataType);
                    new_row_start->data = NULL;
                    new_row_start->right = NULL;

                    last_row_start->down = new_row_start;
                    current_table->bottomLeft = new_row_start;

                    for(int it = 0; it < col_count; it++){
                        insertCellData(column_cell, line);
                        column_cell = column_cell->right;
                        if (fgets(line, sizeof(line), file)) {
                            line[strcspn(line, "\n")] = '\0'; // Trim newline
                        } 
                        else break;
                    }
                }
                row_count++;
            }
        }
    }
    fclose(file);
}