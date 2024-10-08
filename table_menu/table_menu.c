#include <stdio.h>
#include "table.h"

void tableMenu(table **table_head, table **table_tail) {
    while (1) {
        printf("Table Menu:\n");
        printf(" 1. Create Table\n");
        printf(" 2. Remove Table\n");
        printf(" 3. Select Table\n");
        printf(" 4. List all tables\n");
        printf(" 0. Go to databases\n");

        char choice[2];
        scanf("%1s", choice);
        while (getchar() != '\n');

        switch(choice[0]){
            case '1':
                createTable(table_head, table_tail);
                break;
            case '2':
                removeTable(table_head);
                break;
            case '3':
                selectTable(table_head);
                break;
            case '4':
                listTables(*table_head);
                break;
            case '0':
                return;
            default:
                printf("\nInvalid choice. Please try again.\n");
        }
    }
}