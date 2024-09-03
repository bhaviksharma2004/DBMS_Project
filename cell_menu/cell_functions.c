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
    printf("_______________________");
    printf("\n\n");
}

void addRow(cell **bottomLeft, cell **topLeft, char **primaryKey) {
    // For the first row (header row)
    if (*bottomLeft == NULL) {
        printf("\nAdding the first row (header row).\n");

        int numCols;
        printf("Enter the number of columns to add: ");
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
    deleteRow(topLeft, bottomLeft);
}

void removeRowByValue(cell **topLeft, char **primaryKey) {
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
                    deleteRow(topLeft, &rowStart);
                    return;
                }
                searchCol = searchCol->down;
                rowStart = rowStart->down;
            }
            printf("Value doesn't Exist");
            break;
        }
        searchCol = searchCol->right;
    }
}