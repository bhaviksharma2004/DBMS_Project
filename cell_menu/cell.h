#ifndef CELL_H
#define CELL_H

typedef struct cell {
    char *dataType;
    char *colName;
    void *data;
    struct cell *right;
    struct cell *down;
    struct cell *top;
} cell;

void cellMenu(cell *topLeft, cell *bottomLeft, char *primaryKey);
void showTable(cell *topLeft);
void addRow(cell **bottomLeft, cell **topLeft, char **primaryKey);
void removeRow(cell **topLeft, cell **bottomLeft, char **primaryKey);
void removeRowByValue(cell **topLeft, char **primaryKey);

#endif