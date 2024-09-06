@echo off

rem Compile the source files
gcc -c cell_menu/cell_functions.c -o cell_functions.o
gcc -c cell_menu/cell_menu.c -o cell_menu.o
gcc -c db_menu/db_functions.c -o db_functions.o
gcc -c table_menu/table_functions.c -o table_functions.o
gcc -c table_menu/table_menu.c -o table_menu.o
gcc -c utils/utils.c -o utils.o
gcc -c main.c -o main.o

rem Link the object files to create the executable
gcc main.o cell_functions.o cell_menu.o db_functions.o table_functions.o table_menu.o utils.o -o myProgram

rem Run the compiled program
myProgram

rem Remove the object files and the executable
del main.o cell_functions.o cell_menu.o db_functions.o table_functions.o table_menu.o utils.o myProgram.exe
rem Pause to see the output before the window closes
pause