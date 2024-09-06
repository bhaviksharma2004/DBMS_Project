#!/bin/bash
gcc -c cell_menu/cell_functions.c -o cell_functions.o
gcc -c cell_menu/cell_menu.c -o cell_menu.o
gcc -c db_menu/db_functions.c -o db_functions.o
gcc -c table_menu/table_functions.c -o table_functions.o
gcc -c table_menu/table_menu.c -o table_menu.o
gcc -c utils/utils.c -o utils.o

gcc main.c cell_functions.o cell_menu.o db_functions.o table_functions.o table_menu.o utils.o -o myProgram

rm cell_functions.o cell_menu.o db_functions.o table_functions.o table_menu.o utils.o

./my_program