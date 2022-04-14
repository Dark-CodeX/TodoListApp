#pragma once

static const char *help = "USAGE: --OPTION -SUB-OPTIONS\n"
                          "    --log         print todo tasks, works with `--add`, `--rm`, `--edit` and `--complete`\n"
                          "    --add         adds a task to the database [USE `-desc` and `-date` to enter your task respectively]\n"
                          "    --rm          removes a task at a given index, use `-all` to remove all tasks\n"
                          "    --edit        edit the date and description at a given index [USE `-desc` and `-date` to enter your task respectively]\n"
                          "    --complete    marks a task at a given index as completed\n"
                          "    --sort        sorts the column using given title name\n"
                          "    --help        print help\n"
                          "    --lib         print all the library used and their respective authors\n"
                          "    --search      search for a keyword in all columns"
                          "    --version     print the current version of the application";

static const char *lib_todo = "Copyright 2022-2023 Tushar Chaurasia\n"
                              "    1. [sstring](https://github.com/Dark-CodeX/sstring.git):    Tushar Chaurasia\n"
                              "    2. [vector](https://github.com/Dark-CodeX/vector.git):      Tushar Chaurasia\n"
                              "    3. [map](https://github.com/Dark-CodeX/map.git):            Tushar Chaurasia\n"
                              "    4. [returns](https://github.com/Dark-CodeX/returns.git):    Tushar Chaurasia";