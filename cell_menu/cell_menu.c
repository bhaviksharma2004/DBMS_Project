#include <stdio.h>
#include "cell.h"


void cellMenu(cell *topLeft, cell *bottomLeft, char *primaryKey) {
    while (1) {
        printf("Menu:\n");
        printf(" 1. Show table\n");
        printf(" 2. Add row\n");
        printf(" 3. Remove last row\n");
        printf(" 4. Remove row by value\n");
        printf(" 0. Go back to tables\n");

        char choice[2];
        scanf("%1s", choice);
        while (getchar() != '\n');

        switch (choice[0]) {
            case '1':
                printf("Printing Table\n\n");
                showTable(topLeft);
                break;
            case '2':
                printf("Selected Add row\n");
                addRow(&bottomLeft, &topLeft, &primaryKey);
                break;
            case '3':
                printf("Selected remove last row\n");
                removeRow(&bottomLeft, &primaryKey);
                break;
            case '4':
                printf("Selected remove row by value\n");
                removeRowByValue(&topLeft, &primaryKey);
                break;
            case '0':
                return;
            default:
                printf("\nInvalid choice. Please try again.\n\n");
        }
    }
}
