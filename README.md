# Menu-Driven Database Management System (DBMS)

## Overview

This project is a menu-driven DBMS implemented in C. It allows users to create and manage databases. Users interact with the system through a simple text-based interface, where they provide input to create databases, tables, and insert data. The DBMS can also save and load previous databases from a `.txt` file.

## Table of Contents

- [Features](#features)
- [File Format](#file-format)
- [Getting Started](#getting-started)
- [Usage](#usage)
- [Contributing](#contributing)
  
## Features

- **Create Databases:** Easily create or remove databases through user input.
- **Create Tables:** Define or remove tables within databases.
- **Insert Data:** Add and manipulate data to tables based on user input.
- **Save databases to File:** Save all databases meta-data to a `.txt` file.
- **Load databases from File:** Load previously saved databases from a `.txt` file.

## File Format

The saved `.txt` file will contain the metadata of the databases in the following format:
```
DATABASE:my_database
TABLE:my_table primary_key
column1 INTEGER  
column2 STRING  
column3 FLOAT  
column4 DATE
data_entry1  
data_entry2
END_TABLE
END_DATABASE
```


## Getting Started

1. Clone the repository to your local machine:
    ```bash
    git clone https://github.com/bhaviksharma2004/DBMS_Project.git
    ```
2. Navigate to the project directory:
    ```bash
    cd DBMS_Project
    ```
3. Compile and run the project:
   
     - For Windows:
     ```bash
     run_windows.bat
     ```
     - For Unix based systems:
     ```bash
     run_linux.sh
     ```
## Usage

1. Compile the source code using the provided shell scripts:
   - `run_project.sh` for Unix-like systems (bash shell).
   - `run_project.bat` for Windows Command Prompt.

2. Run the compiled executable

3. Saved databases get loaded automatically

4. Follow the on-screen menu to create databases, tables, and insert data.

5. Save databases.

## Contributing

If you would like to contribute to this project, please fork the repository and submit a pull request with your changes.
