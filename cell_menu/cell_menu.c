#include <stdio.h>
#include "cell.h"


void cellMenu(cell *topLeft, cell *bottomLeft, char *primaryKey) {
    while (1) {
        printf("Menu:\n");
        printf(" 1. Show table\n");
        printf(" 2. Add row\n");
        printf(" 3. Remove last row\n");
        printf(" 4. Remove row by value\n");
        printf(" 5. List all columns\n");
        printf(" 0. Go back to tables\n");

        char choice[2];
        scanf("%1s", choice);
        while (getchar() != '\n');

        switch (choice[0]) {
            case '1' :
                showTable(topLeft);
                break;
            case '2' :
                addRow(&bottomLeft, &topLeft, &primaryKey);
                break;
            case '3' :
                removeRow(&topLeft, &bottomLeft, &primaryKey);
                break;
            case '4' :
                removeRowByValue(&topLeft, &bottomLeft, &primaryKey);
                break;
            case '5' :
                listColumns(topLeft);
                break;
            case '0' :
                return;
            default:
                printf("\nInvalid choice. Please try again.\n\n");
        }
    }
}
