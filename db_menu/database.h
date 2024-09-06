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
void removeDatabase(db **db_head, db **db_tail);
void selectDatabase(db **db_head);
void saveDatabase(const char *filePath, db *db_head);
void listDatabases(db *db_head);

void loadDatabases(const char *filename, db **db_head, db **db_tail);
#endif