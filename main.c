#include <stdio.h>
#include "db_menu/database.h"

int main(){
    db *db_head = NULL;
    db *db_tail = NULL;

    // Define the metadata file path before the switch statement
    const char *filePath = "databases_metadata.txt";

    // Optionally load databases at the start
    loadDatabases(&db_head, &db_tail);


    while(1){
        printf("Menu:\n");
        printf(" 1. Create Database\n");
        printf(" 2. Remove Database\n");
        printf(" 3. Select Database\n");
        printf(" 4. Save Database\n");
        printf(" 5. List all Databases\n");
        printf(" 0. Exit\n");

        char choice[2];
        scanf("%1s", choice);
        while (getchar() != '\n');

        switch(choice[0]){
            case '1':
                createDatabase(&db_head, &db_tail);
                break;
            case '2' :
                removeDatabase(&db_head, &db_tail);
                break;
            case '3' :
                selectDatabase(&db_head);
                break;
            case '4' :
                saveDatabase(filePath, db_head);
                break;
            case '5' :
                listDatabases(db_head);
                break;
            case '0' :
                printf("Do you want to exit without saving? (y/n): ");
                char flag;
                scanf(" %c", &flag);  // ' ' before %c to skip any '\n' in buffer bcoz of 'int choice'
                if(flag == 'y') {
                    printf("Exiting without saving.\n\n");
                    return 0;
                }
                else if(flag == 'n'){
                    printf("Saving database.\n\n");
                    saveDatabase(filePath, db_head);
                }
                break;
            default:
                printf("Invalid choice! Please try again.\n\n");
        }
    }
}