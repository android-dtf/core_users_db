/*
 * Copyright (C) 2014 Jake Valletta (jakev)
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "sqlite3/sqlite3.h"

#include <stdio.h>
#include <stdlib.h>

#include <pwd.h>

#define MAX_PW_NAME_LEN 32
#define DEFAULT_MAX_UID 10499
#define USER_DB_FILE "users.db"

/* Drop the table */
int dropTables(sqlite3* pDb)
{
    int ret = 0;

    const char* drop_users_table = "DROP TABLE IF EXISTS users";

    if (0 != (ret = sqlite3_exec(pDb, drop_users_table, 0, 0, 0))) { goto bail; }

bail:
    return ret;
}

/* Create Table */
int createTables(sqlite3* pDb)
{
    int ret = 0;

    const char* create_users_table = "CREATE TABLE users(" \
                                 "id INTEGER PRIMARY KEY," \
                                 "name TEXT" \
                                 ");";

    if (0 != (ret = sqlite3_exec(pDb, create_users_table, 0, 0, 0))) { goto bail; }

bail:
    return ret;
}

int openDatabase(const char* fileName, sqlite3** pDb)
{
    return sqlite3_open(fileName, pDb);
}

int closeDatabase(sqlite3* pDb)
{
    return sqlite3_close(pDb);
}

/* Add user to the database */
int addUser(char *user_name, int id, sqlite3* pDb)
{
    char* buffer = NULL;

    int ret = 0;

    if ((ret = asprintf(&buffer, "INSERT INTO users VALUES(%d, '%s')", id, user_name)) < 0)
    {
        fprintf(stderr, "Error allocating memory for user, failing!\n");
        goto out;
    }

    ret = sqlite3_exec(pDb, buffer, 0, 0, 0);

cleanup_buffer:
    free(buffer);
out:
    return ret;
}

int process(sqlite3* pDb, int max_uid)
{
    int uid = 0;
    int i = 0;
    char user_name[MAX_PW_NAME_LEN] = {0};
    struct passwd *pw = 0;

    fprintf(stdout, "Generating User table...\n");



    for (i = 0; i < max_uid; i++)
    {
        pw = getpwuid(i);

        if(pw) {
            strcpy(user_name, pw->pw_name);
            addUser(user_name, i, pDb);
        }
    }
}

int makeDatabase(int max_uid)
{
    int ret = 0;
    sqlite3* pDb = NULL;

    printf("Creating user database...\n");

    // Initialize DB
    if (SQLITE_OK != (ret = sqlite3_initialize()))
    {
        printf("Failed to initialize library: %d\n", ret);
        goto out;
    }

    if (SQLITE_OK != (ret = openDatabase(USER_DB_FILE, &pDb)))
    {
        printf("Unable to open file: \"%s\" (%d)\n", USER_DB_FILE, ret);
        goto deinit;
    }

    printf("Dropping old data...\n");

    if (0 != (ret = dropTables(pDb)))
    {
        fprintf(stderr, "SQL error dropping old tables (%d), exiting!\n", ret);
        goto closedb;
    }

    if (0 != (ret = createTables(pDb)))
    {
        fprintf(stderr, "SQL error creating databases (%d), exiting!\n", ret);
        goto closedb;
    }

    // No error checking :(
    ret = process(pDb, max_uid);

closedb:
    if (SQLITE_OK != (ret = closeDatabase(pDb)))
    {
       printf("SQL error closing the database file: %d\n", ret);
       goto deinit;
    }
deinit:
   sqlite3_shutdown();
out:
   return ret;
}

int main(int argc, char **argv)
{
    int max_uid = 0;

    if (argc == 1)
        max_uid = DEFAULT_MAX_UID;
    else
        max_uid = atoi(argv[1]);

    return makeDatabase(max_uid);
}
