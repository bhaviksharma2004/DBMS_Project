#ifndef TABLE_H
#define TABLE_H

#include "../cell_menu/cell.h"

// Definition of the table structure
typedef struct table {
    char *name;
    char *primaryKey;
    cell *topLeft;
    cell *bottomLeft;
    struct table *next;
} table;

// Function declarations related to the table structure
void tableMenu(table **table_head, table **table_tail);
void createTable(table **table_head, table **table_tail);
void removeTable(table **table_head);
void selectTable(table **table_head);
void listTables(table *table_head);

#endif