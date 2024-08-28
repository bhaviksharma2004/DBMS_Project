#ifndef DATABASE_H
#define DATABASE_H

#include "../table_menu/table.h"

typedef struct database {
    char *name;
    table *table_head;
    table *table_tail;
    struct database *next;
} db;

// Function declarations related to the database structure
void createDatabase(db **db_head, db **db_tail);
void removeDatabase(db **db_head);
void selectDatabase(db **db_head);
void saveDatabase();

#endif