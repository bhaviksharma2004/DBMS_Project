#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "utils.h"

int dbExist(char *name, db *db_head) {
    while(db_head) {
        if(strcmp(db_head->name, name) == 0) return 1;
        db_head = db_head->next;
    }
    return 0;
}

int tableExist(char *name, table *table_head) {
    while(table_head) {
        if(strcmp(table_head->name, name) == 0) return 1;
        table_head = table_head->next;
    }
    return 0;
}

void printCell(cell *cell){
    if(*cell->dataType){
        if (strcmp(cell->dataType, "INTEGER") == 0){
            printf("%-32d", *(int *)cell->data);   // No. in format specifier prints in fixed block whereas '-' represent left padded 
        }
        else if (strcmp(cell->dataType, "FLOAT") == 0){ 
            printf("%-32.2f", *(float *)cell->data);
        }
        else if (strcmp(cell->dataType, "STRING") == 0){ 
            printf("%-32s", (char *)cell->data);
        }
        else if (strcmp(cell->dataType, "DATE") == 0){ 
            printf("%-32s", (char *)cell->data);
        }
    }
}

cell *createCell(char *type) {
    cell *newCell = (cell *) malloc(sizeof(cell));

    newCell->dataType = strdup(type);
    newCell->right = NULL;
    newCell->down = NULL;
    newCell->top = NULL;


    // printf("Enter data in '%s' format: ", newCell->dataType);

    if (strcmp(type, "INTEGER") == 0) {
        char data[10];
        while(1){
            printf("Enter data in INTEGER format: ");
            scanf("%9s", data);

            if(isNum(data)) break;
            else printf("Input is not an Integer\n");
        }

        int val = atoi(data);
        newCell->data = malloc(sizeof(int));
        *(int *)newCell->data = val;
    }
    else if (strcmp(type, "FLOAT") == 0) {
        printf("Enter data in FLOAT format: ");
        float data;
        scanf("%f", &data);
        newCell->data = malloc(sizeof(float));
        *(float *)newCell->data = data;
    }
    else if (strcmp(type, "STRING") == 0) {
        printf("Enter data in STRING format: ");
        char data[33];
        scanf("%s", data);

        newCell->data = malloc(strlen(data) + 1);
        strcpy((char *)newCell->data, data);
    }
    else if (strcmp(type, "DATE") == 0) {
        printf("Enter data in DATE(DD-MM-YYYY) format: ");
        char data[11];
        scanf("%s", data);
        
        newCell->data = malloc(strlen(data) + 1);
        strcpy((char *)newCell->data, data);
    }

    return newCell;
}

int checkInputRange(int a, int b){
    char choice[2];
    while(1){
        printf("\nEnter dataType you want to store in Column\n 1. INTEGER\n 2. FLOAT\n 3. STRING\n 4. DATE\n");

        scanf("%1s", choice);
        while (getchar() != '\n');

        if ('1' <= choice[0] && choice[0] <= '4') break;
        else printf("Invalid choice. Please enter a number between 1 and 4.\n");
    }
    return choice[0] - '0';
}

void deleteRow(cell **topLeft, cell **bottomLeft, cell **head){
    // If there are no rows present in table
    if (*head == NULL) {
        printf("No Rows to delete\n");
        return;
    }   
    // If 1st row need to delete
    if ((*head)->top == NULL) {
        *topLeft = (*topLeft)->down;

        if (*topLeft == NULL) {
            *bottomLeft = NULL; // Update bottomLeft to NULL
        }

        cell *topLeftIterator = *topLeft;

        cell *node = *head;
        while (node) {
            cell *temp = node;
            node = node->right;
            free(temp->data);
            free(temp->dataType);
            free(temp->colName);
            free(temp);

            if(topLeftIterator != NULL){
                topLeftIterator->top = NULL;
                topLeftIterator = topLeftIterator->right;
            }
        }
        *head = NULL;
        return;
    }
    // Handle other than above cases
    *head = (*head)->top;

    if (*bottomLeft == *head) {
        *bottomLeft = (*head)->top;
    }

    cell *node = *head;
    while (node) {
        cell *temp = node->down;   // Node to delete

        node->down = temp->down;
        if (temp->down != NULL) {
            temp->down->top = node;
        }

        free(temp->data);
        free(temp->colName);
        free(temp->dataType);
        free(temp);
        
        node = node->right;
    }
}

void assignPrimaryKey(cell **topLeft, char **primaryKey){
    *primaryKey = (char *)malloc(33 * sizeof(char));

    while(1){
        printf("\nPrimary key column can only be in INTEGER or STRING\n");
        printf("Enter the name of the primary key column: ");
        scanf("%32s", *primaryKey);
        while (getchar() != '\n');

        cell *node = *topLeft;
        while(node){
            if(strcmp(node->dataType, "INTEGER") == 0 || strcmp(node->dataType, "STRING") == 0){
                if(strcmp(node->colName, *primaryKey) == 0){
                    printf("Assigned Primary key : %s\n\n", *primaryKey);
                    return;
                }
            }
            else break;
            node = node->right;
        }
        printf("Either wrong datatype or Column doesn't exist\n");
    }
}

int ifValueExist(cell **topLeft, char *data, char *primaryKey){
    cell *node = *topLeft;
    while (node) {
        if(strcmp(node->colName, primaryKey) == 0){
            while(node){
                if(strcmp(node->data, data) == 0) return 1;

                node = node->down;
            }
            break;
        }
        node = node->right;
    }
    return 0;
}

void createHeaderRow(int numCols, cell **bottomLeft, cell **topLeft) {
    char *type[] = {"INTEGER", "FLOAT", "STRING", "DATE"};
    cell *prev = NULL;

    for (int i = 0; i < numCols; i++) {
        char colName[33];
        int isDuplicate;

        // Loop to ensure unique column name
        printf("\nEnter name of column-%d in 1-32 characters: ", i + 1);
        scanf("%32s", colName);
        while (getchar() != '\n');

        isDuplicate = 0;
        cell *current = *topLeft;
        while (current != NULL) {
            if (strcmp(current->colName, colName) == 0) {
                printf("Column name already exists. Please enter a unique name.\n");
                printf("\nEnter name of column-%d in 1-32 characters: ", i + 1);
                scanf("%32s", colName);
                while (getchar() != '\n');  // Clear input buffer
                
                current = *topLeft; // Reset to start of list for rechecking
                isDuplicate = 1;
                continue; 
            }
            current = current->right;
        }

        int choice = checkInputRange(1, 4);
        cell *newCell = createCell(type[choice - 1]);
        newCell->colName = strdup(colName);

        if (i == 0) {
            *bottomLeft = newCell;
            *topLeft = newCell;
        } 
        else {
            prev->right = newCell;
        }
        prev = newCell;
    }
}

void processRowData(cell **bottomLeft, cell **topLeft, char **primaryKey) {
    cell *node = *bottomLeft;
    cell *prev = NULL;

    while (node) {
        cell *newCell = createCell(node->dataType);
        newCell->colName = strdup(node->colName);

        if (strcmp(newCell->colName, *primaryKey) == 0) {
            if (ifValueExist(topLeft, newCell->data, *primaryKey)) {
                printf("Value already exists\n");

                // Free Cell resources
                free(newCell->colName);
                free(newCell->data);
                free(newCell);

                // Ask user what to do next
                int flag = 0;
                while(1){
                    char choice[2];
                    printf("1. Do you want add new value?\n");
                    printf("2. Exit without saving row?\n");
                    scanf("%1s", choice);

                    if (choice[0] == '1'){
                        flag = 1;
                        break;
                    }
                    else if (choice[0] == '2') return;
                    else printf("Invalid choice. Exiting.\n");
                }
                if(flag) continue;  // continue on the same node
            }
        }

        // Adjust pointer for the newCell
        newCell->top = node;
        if (prev != NULL) {
            prev->right = newCell;
        }
        prev = newCell;
        node->down = newCell;
        node = node->right;
    }

    *bottomLeft = (*bottomLeft)->down;
}

int isNum(char *to_delete){
    while(*to_delete){
        if(*to_delete < '0' || *to_delete > '9') return 0;
        to_delete++;
    }
    return 1;
}

// Clean whole memory inside a table
void freeCells(cell *topLeft) {
    cell *row = topLeft;
    while (row) {
        cell *col = row;
        while (col) {
            cell *temp = col;
            col = col->right;
            
            free(temp->data);
            free(temp->colName);
            free(temp->dataType);
            free(temp);
        }
        cell *tempRow = row;
        row = row->down;
        free(tempRow);
    }
}