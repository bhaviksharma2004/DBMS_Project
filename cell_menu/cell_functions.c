#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cell.h"
#include "../utils/utils.h"

void showTable(cell *topLeft) {
    if (topLeft == NULL) {
        printf("The table is empty.\n");
        return;
    }
    printf("\n");
    cell *curr = topLeft;
    while(curr){
        printf("%-32s", curr->colName);
        curr = curr->right;
    }
    printf("\n\n");

    cell *row = topLeft;
    while (row) {
        cell *col = row;
        while (col) {            
            printCell(col);
            col = col->right;
        }
        printf("\n");
        row = row->down;
    }
    printf("_______________________\n\n");
}

void addRow(cell **bottomLeft, cell **topLeft, char **primaryKey) {
    // For the first row (header row)
    if (*bottomLeft == NULL) {
        printf("\nAdding the first row (header row).\n");

        int numCols;
        printf("Enter no. of columns to add: ");
        scanf("%d", &numCols);
        
        if (numCols < 1){
            printf("Invalid number of columns. Returning to menu.\n");
            cellMenu(*topLeft, *bottomLeft, *primaryKey);
            return;
        }
        createHeaderRow(numCols, bottomLeft, topLeft);
        assignPrimaryKey(topLeft, primaryKey);
        return;
    }
    processRowData(bottomLeft, topLeft, primaryKey);
}

void removeRow(cell **topLeft, cell **bottomLeft, char **primaryKey) {
    if (*bottomLeft == NULL) {
        printf("No rows to remove.\n");
        return;
    }

    if (*bottomLeft == *topLeft) { // Single row scenario
        freeCells(*topLeft);

        *topLeft = NULL;
        *bottomLeft = NULL;
        printf("Last row removed. The table is now empty.\n");
        return;
    }

    cell *prev = NULL;
    cell *row = *topLeft;

    while (row->down) {
        prev = row;
        row = row->down;
    }

    prev->down = NULL;
    freeCells(row);

    *bottomLeft = prev;
    printf("Row removed successfully.\n");
}

void removeRowByValue(cell **topLeft, cell **bottomLeft, char **primaryKey) {
    if (*topLeft == NULL) {
        printf("No Rows to delete\n");
        return;
    }

    char to_delete[33];
    printf("Enter value to delete (Value must be in primary key Column) : \n");
    scanf("%32s", to_delete);    
    while (getchar() != '\n');


    cell *searchCol = *topLeft;
    cell *rowStart = *topLeft;
    while(searchCol){
        if(strcmp(searchCol->colName, *primaryKey) == 0){
            while(searchCol){
                int isNumeric = isNum(to_delete);

                if(isNumeric && (*(int *)searchCol->data == atoi(to_delete)) || (!isNumeric && strcmp((char *)searchCol->data, to_delete) == 0)){
                    deleteRow(topLeft, bottomLeft, &rowStart);
                    return;
                }
                searchCol = searchCol->down;
                rowStart = rowStart->down;
            }
            printf("Value doesn't Exist");
            return;
        }
        searchCol = searchCol->right;
    }
    printf("Primary key column not found.\n");
}

void listColumns(cell *topLeft){
    cell *curr = topLeft;
    while(curr){
        printf("%-32s", curr->colName);
        curr = curr->right;
    }
    printf("\n");
}