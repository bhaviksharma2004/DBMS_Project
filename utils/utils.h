#include <stdio.h>

#ifndef UTILS_H
#define UTILS_H

#include "../db_menu/database.h"
#include "../table_menu/table.h"
#include "../cell_menu/cell.h"

int dbExist(char *name, db *db_head);
int tableExist(char *name, table *table_head);
int ifValueExist(cell **topLeft, char *data, char *primaryKey);

void printCell(cell *cell);
cell *createCell(char *type);

int checkInputRange(int a, int b);

void deleteRow(cell **topLeft, cell **bottomLeft, cell **head);

void processRowData(cell **bottomLeft, cell **topLeft, char **primaryKey);
void createHeaderRow(int numCols, cell **bottomLeft, cell **topLeft);
void assignPrimaryKey(cell **topLeft, char **primaryKey);

int isNum(char *to_delete);

void freeCells(cell *topLeft);

#endif