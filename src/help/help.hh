/**
 * @file help.hh
 * @license This file is licensed under the GNU GENERAL PUBLIC LICENSE Version 3, 29 June 2007. You may obtain a copy of this license at https://www.gnu.org/licenses/gpl-3.0.en.html.
 * @author Tushar Chaurasia (Dark-CodeX)
 */

#ifndef TODO_HELP_H
#define TODO_HELP_H

#if defined _WIN32 || defined _WIN64 || defined __CYGWIN__
static const char *help = "USAGE: --OPTION -SUB-OPTIONS\r\n"
                          "    --log         print todo tasks, works with `--add`, `--rm`, `--edit`, `--complete`, `--sort` and `--normalize`\r\n"
                          "    --add         adds a task to the database [USE `-desc` and `-date` to enter your task respectively]\r\n"
                          "    --rm          removes a task at a given index, use `-all` to remove all tasks\r\n"
                          "    --edit        edit the date and description at a given index [USE `-desc` and `-date` to enter your task respectively]\r\n"
                          "    --complete    marks a task at a given index as completed\r\n"
                          "    --sort        sorts the column using given title name\r\n"
                          "    --help        print help\r\n"
                          "    --lib         print all the library used and their respective authors\r\n"
                          "    --search      search for a keyword in all columns\r\n"
                          "    --export      exports all the data to a file\r\n"
                          "    --import      imports a file\r\n"
                          "    --normalize   normalizes the `id` column like 1...n, where `n` is number of total tasks\r\n"
                          "    --init        opens a command prompt which executes commands\r\n"
                          "    --open        opens a file containing list of commands to be executed\r\n"
                          "    --version     print the current version of the application";

static const char *lib_todo = "Copyright 2022-2023 Tushar Chaurasia\r\n"
                              "    1. [sstring v" sstring_version "]      (https://github.com/Dark-CodeX/sstring.git)        Tushar Chaurasia\r\n"
                              "    2. [vector v" vector_t_version "]       (https://github.com/Dark-CodeX/vector.git)         Tushar Chaurasia\r\n"
                              "    3. [map v" map_t_version "]          (https://github.com/Dark-CodeX/map.git)            Tushar Chaurasia\r\n"
                              "    4. [optional v" optional_version "]      (https://github.com/Dark-CodeX/optional.git)        Tushar Chaurasia\r\n"
                              "    5. [date-time v" date_time_version "]    (https://github.com/Dark-CodeX/date-time.git)      Tushar Chaurasia\r\n"
                              "    6. [heap-pair v" heap_pair_version "]    (https://github.com/Dark-CodeX/heap-pair.git)      Tushar Chaurasia";
#else
static const char *help = "USAGE: --OPTION -SUB-OPTIONS\n"
                          "    --log         print todo tasks, works with `--add`, `--rm`, `--edit`, `--complete`, `--sort` and `--normalize`\n"
                          "    --add         adds a task to the database [USE `-desc` and `-date` to enter your task respectively]\n"
                          "    --rm          removes a task at a given index, use `-all` to remove all tasks\n"
                          "    --edit        edit the date and description at a given index [USE `-desc` and `-date` to enter your task respectively]\n"
                          "    --complete    marks a task at a given index as completed\n"
                          "    --sort        sorts the column using given title name\n"
                          "    --help        print help\n"
                          "    --libs        print all the library used and their respective authors\n"
                          "    --search      search for a keyword in all columns\n"
                          "    --export      exports all the data to a file\n"
                          "    --import      imports a file\n"
                          "    --normalize   normalizes the `id` column like 1...n, where `n` is number of total tasks\n"
                          "    --init        opens a command prompt which executes commands\n"
                          "    --open        opens a file containing list of commands to be executed\n"
                          "    --version     print the current version of the application";

static const char *libs_todo = "Copyright 2022-2023 Tushar Chaurasia\n"
                              "    1. [sstring v" OPENUTILS_sstring_version "]      (https://github.com/Dark-CodeX/openutils.git)      Tushar Chaurasia\n"
                              "    2. [vector v" OPENUTILS_vector_t_version "]       (https://github.com/Dark-CodeX/openutils.git)      Tushar Chaurasia\n"
                              "    3. [map v" map_t_version "]          (https://github.com/Dark-CodeX/openutils.git)      Tushar Chaurasia\n"
                              "    4. [optional v" OPENUTILS_optional_version "]     (https://github.com/Dark-CodeX/openutils.git)      Tushar Chaurasia\n"
                              "    5. [date-time v" OPENUTILS_date_time_version "]    (https://github.com/Dark-CodeX/openutils.git)      Tushar Chaurasia\n"
                              "    6. [heap-pair v" OPENUTILS_heap_pair_version "]    (https://github.com/Dark-CodeX/openutils.git)      Tushar Chaurasia";
#endif
#endif