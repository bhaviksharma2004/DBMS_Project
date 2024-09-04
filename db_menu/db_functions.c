#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "database.h"
#include "../table_menu/table.h"
#include "../utils/utils.h"


void createDatabase(db **db_head, db **db_tail) {
    char name[33];
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

    if(*db_tail == NULL) *db_head = new_db;
    else (*db_tail)->next = new_db;

    *db_tail = new_db;

    printf("Database '%s' created successfully.\n\n", name);
    createTable(&((*db_tail)->table_head), &((*db_tail)->table_tail));
}

// ENSURE IT WILL WORK FOR ALL CASES
void removeDatabase(db **db_head, db **db_tail) {
    char name[33];
    printf("Enter name of database 1-32 characters: ");
    scanf("%32s", name);
    while (getchar() != '\n'); 


    if(!dbExist(name, *db_head)) {
        printf("Database does not exist\n\n");
        return;
    }

    db *db_node = *db_head;
    db *prev = NULL;

    // Traverse the list to find the database to remove
    while (db_node) {
        if (strcmp(db_node->name, name) == 0) {
            if (prev) {
                // Remove node from middle or end
                prev->next = db_node->next;
            } else {
                // Removing the head node
                *db_head = db_node->next;
            }

            // Update tail if needed
            if (*db_tail == db_node) {
                *db_tail = prev;
            }

            // Free allocated memory
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

void listDatabases(db *db_head){
    if(db_head == NULL){ 
        printf("No Database to print\n");
        return;
    }

    printf("\n");
    db *curr = db_head;
    int i = 0;
    while(curr){
        printf("%d. %s\n", i++, curr->name);
        curr = curr->next;
    }
    printf("\n\n");
}




// Saving Databases

void saveDatabase(const char *filePath, db *dbHead) {
    FILE *file = fopen(filePath, "w");
    if (!file) {
        perror("Error opening file for saving");
        return;
    }

    db *currentDB = dbHead;
    while (currentDB) {
        fprintf(file, "DATABASE:%s\n", currentDB->name);

        table *currentTable = currentDB->table_head;
        while (currentTable) {
            fprintf(file, "TABLE:%s %s\n", currentTable->name, currentTable->primaryKey);

            cell *currentCell = currentTable->topLeft;
            if (currentCell) {
                // Print column names
                cell *headerCell = currentCell;
                while (headerCell) {
                    fprintf(file, "%s ", headerCell->colName);
                    headerCell = headerCell->right;
                }
                fprintf(file, "\n");

                // Print data
                while (currentCell) {
                    cell *rowHead = currentCell;
                    while (rowHead) {
                        // Determine the data type and print accordingly
                        if (strcmp(rowHead->dataType, "INTEGER") == 0) {
                            fprintf(file, "%d ", *((int *)rowHead->data));
                        }
                        else if (strcmp(rowHead->dataType, "FLOAT") == 0) {
                            fprintf(file, "%.2f ", *((float *)rowHead->data));
                        }
                        else if (strcmp(rowHead->dataType, "STRING") == 0) {
                            fprintf(file, "%s ", (char *)rowHead->data);
                        }
                        else if (strcmp(rowHead->dataType, "DATE") == 0) {
                            fprintf(file, "%s ", (char *)rowHead->data);
                        }
                        else {
                            fprintf(file, "UNKNOWN ");
                        }
                        rowHead = rowHead->right;
                    }
                    fprintf(file, "\n");
                    currentCell = currentCell->down;
                }
            }
            fprintf(file, "END_TABLE\n");
            currentTable = currentTable->next;
        }
        fprintf(file, "END_DATABASE\n");
        currentDB = currentDB->next;
    }

    fclose(file);
    printf("Database saved successfully.\n"); // Debugging statement
}

void loadDatabases(db **db_head, db **db_tail) {
    FILE *file = fopen("databases_metadata.txt", "r");
    if (!file) {
        perror("Error opening file for loading");
        return;
    }

    db *currentDB = NULL;
    table *currentTable = NULL;
    cell *lastCellInRow = NULL;
    char line[256];
    int readingColumnNames = 0;

    while (fgets(line, sizeof(line), file)) {
        if (strncmp(line, "DATABASE:", 9) == 0) {
            char dbName[100];
            sscanf(line + 9, "%s", dbName);

            // Create new database and add to list
            db *newDB = (db *)malloc(sizeof(db));
            newDB->name = strdup(dbName);
            newDB->table_head = NULL;
            newDB->table_tail = NULL;
            newDB->next = NULL;

            if (!*db_head) {
                *db_head = newDB;
                *db_tail = newDB;
            } else {
                (*db_tail)->next = newDB;
                *db_tail = newDB;
            }
            currentDB = newDB;
        } else if (strncmp(line, "TABLE:", 6) == 0) {
            char tableName[100], primaryKey[100];
            sscanf(line + 6, "%s %s", tableName, primaryKey);

            // Create new table and add to database
            table *newTable = (table *)malloc(sizeof(table));
            newTable->name = strdup(tableName);
            newTable->primaryKey = strdup(primaryKey);
            newTable->topLeft = NULL;
            newTable->bottomLeft = NULL;
            newTable->next = NULL;

            if (!currentDB->table_head) {
                currentDB->table_head = newTable;
                currentDB->table_tail = newTable;
            } else {
                currentDB->table_tail->next = newTable;
                currentDB->table_tail = newTable;
            }
            currentTable = newTable;
            readingColumnNames = 1;
        } else if (strcmp(line, "END_TABLE\n") == 0) {
            // End of current table
            currentTable = NULL;
            readingColumnNames = 0;
            lastCellInRow = NULL; // Reset for next table
        } else if (strcmp(line, "END_DATABASE\n") == 0) {
            // End of current database
            currentDB = NULL;
        } else {
            if (readingColumnNames) {
                // Read column names
                char *colName = strtok(line, " \n");
                cell *prevCell = NULL;
                while (colName) {
                    cell *newCell = (cell *)malloc(sizeof(cell));
                    newCell->colName = strdup(colName);
                    newCell->data = NULL;
                    newCell->right = NULL;
                    newCell->down = NULL;

                    if (!currentTable->topLeft) {
                        currentTable->topLeft = newCell;
                        currentTable->bottomLeft = newCell;
                    } else {
                        currentTable->bottomLeft->right = newCell;
                        currentTable->bottomLeft = newCell;
                    }
                    prevCell = newCell;
                    colName = strtok(NULL, " \n");
                }
                lastCellInRow = prevCell; // Keep track of the last cell
            } else {
                // Handle cell data
                char *data = strtok(line, " \n");
                cell *rowHead = NULL;
                cell *prevCell = NULL;
                while (data) {
                    cell *newCell = (cell *)malloc(sizeof(cell));
                    newCell->data = strdup(data); // Adjust based on data type
                    newCell->right = NULL;
                    newCell->down = NULL;

                    if (!rowHead) {
                        rowHead = newCell;
                        lastCellInRow->down = rowHead;
                    } else {
                        prevCell->right = newCell;
                    }
                    prevCell = newCell;
                    data = strtok(NULL, " \n");
                }
                if (currentTable->bottomLeft == NULL) {
                    currentTable->bottomLeft = rowHead;
                }
                lastCellInRow = prevCell; // Update last cell in row
            }
        }
    }
    fclose(file);
}