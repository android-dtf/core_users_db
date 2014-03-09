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

#include <stdio.h>
#include <stdlib.h>

#include <pwd.h>

#define MAX_PW_NAME_LEN 32

int main(int argc, char **argv) {

    int uid = 0;
    char user_name[MAX_PW_NAME_LEN] = {0};
    struct passwd *pw = 0;

    if (argc < 2) {
        fprintf(stdout, "Usage: %s [uid]\n", argv[0]);
        fprintf(stdout, "\n");
        exit(-2);
    }

    uid = atoi(argv[1]);
    pw = getpwuid(uid);

    if(pw) {
        strcpy(user_name, pw->pw_name);
    } else {
        fprintf(stderr, "User ID %d does not resolve!\n", uid);
        return -1;
    }

    fprintf(stdout, "Username: %s\n", user_name);

    return 0;
}
