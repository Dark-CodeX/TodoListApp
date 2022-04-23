#include "../../io/io.hh"
#include "../../date/date.hh"
#include "../../database/database.hh"
#include "../../help/help.hh"
#include <iostream>

int main(int argc, char const **argv)
{
    if (argc == 1)
    {
        std::cerr << "err: no argument, use `--help` flag to see help." << std::endl;
        return EXIT_FAILURE;
    }
    todo::io io;
    openutils::optional_t<openutils::sstring> data = io.open(io.get_home_dir() + "/todo_data.dat");

    if (data.is_null())
    {
        std::cerr << "err: bad data" << std::endl;
        return EXIT_FAILURE;
    }

    todo::database db;
    db.lexer(data.get());
    db.mark_active();

    if (openutils::sstring::to_sstring(argv[1]) == openutils::sstring::to_sstring("--help"))
        std::puts(help);
    else if (openutils::sstring::to_sstring(argv[1]) == openutils::sstring::to_sstring("--version"))
        std::cout << argv[0] << ": v1.0.0" << std::endl;
    else if (openutils::sstring::to_sstring(argv[1]) == openutils::sstring::to_sstring("--lib"))
        std::puts(lib_todo);
    else if (openutils::sstring::to_sstring(argv[1]) == openutils::sstring::to_sstring("--search"))
    {
        if (argc < 3)
        {
            std::cerr << "err: not enough arguments" << std::endl;
            return EXIT_FAILURE;
        }
        openutils::sstring key = argv[2];
        openutils::optional_t<openutils::vector_t<todo::heap_pair<todo::heap_pair<openutils::sstring, todo::task>, double>>> res = db.search(key);
        if (res)
        {
            openutils::vector_t<todo::heap_pair<todo::heap_pair<openutils::sstring, todo::task>, double>> temp = res.get();
            std::printf("%s\n", todo::center("Tasks", 144, '-').c_str());
            std::printf("| \u001b[34;1m%s\u001b[0m | \u001b[34;1m%s\u001b[0m | \u001b[34;1m%s\u001b[0m | \u001b[34;1m%s\u001b[0m | \u001b[34;1m%s\u001b[0m | \u001b[34;1m%s\u001b[0m |\n", todo::center("ID", 9).c_str(), todo::center("Description", 51).c_str(), todo::center("Valid Till", 21).c_str(), todo::center("Is Expired", 17).c_str(), todo::center("Is Completed", 17).c_str(), todo::center("% Matched", 10).c_str());
            std::printf("------------------------------------------------------------------------------------------------------------------------------------------------\n");
            for (openutils::vector_t<todo::heap_pair<todo::heap_pair<openutils::sstring, todo::task>, double>>::iter i = temp.iterator(); i.c_loop(); i.next())
            {
                if ((*i).first().second().is_completed() == false && (*i).first().second().is_expired() == true)
                    std::printf("| \u001b[31;1m%s\u001b[0m | \u001b[31;1m%s\u001b[0m | \u001b[31;1m%s\u001b[0m | \u001b[31;1m%s\u001b[0m | \u001b[31;1m%s\u001b[0m | \u001b[31;1m%s\u001b[0m |\n",
                                todo::center((*i).first().first(), 9).c_str(),
                                todo::center((*i).first().second().get_description(), 51).c_str(),
                                todo::center((*i).first().second().get_date().to_string() + " (" + openutils::sstring::to_sstring((*i).first().second().get_date().days_between(todo::date())) + " DAYS)", 21).c_str(),
                                todo::center(openutils::sstring::to_sstring((*i).first().second().is_expired()), 17).c_str(),
                                todo::center(openutils::sstring::to_sstring((*i).first().second().is_completed()), 17).c_str(),
                                todo::center(openutils::sstring::to_sstring((*i).second()), 10).c_str());
                else if ((*i).first().second().is_completed() == false && (*i).first().second().is_expired() == false)
                    std::printf("| \u001b[33;1m%s\u001b[0m | \u001b[33;1m%s\u001b[0m | \u001b[33;1m%s\u001b[0m | \u001b[33;1m%s\u001b[0m | \u001b[33;1m%s\u001b[0m | \u001b[33;1m%s\u001b[0m |\n",
                                todo::center((*i).first().first(), 9).c_str(),
                                todo::center((*i).first().second().get_description(), 51).c_str(),
                                todo::center((*i).first().second().get_date().to_string() + " (" + openutils::sstring::to_sstring((*i).first().second().get_date().days_between(todo::date())) + " DAYS)", 21).c_str(),
                                todo::center(openutils::sstring::to_sstring((*i).first().second().is_expired()), 17).c_str(),
                                todo::center(openutils::sstring::to_sstring((*i).first().second().is_completed()), 17).c_str(),
                                todo::center(openutils::sstring::to_sstring((*i).second()), 10).c_str());
                else if ((*i).first().second().is_completed() == true && (*i).first().second().is_expired() == false)
                    std::printf("| \u001b[32;1m%s\u001b[0m | \u001b[32;1m%s\u001b[0m | \u001b[32;1m%s\u001b[0m | \u001b[32;1m%s\u001b[0m | \u001b[32;1m%s\u001b[0m | \u001b[32;1m%s\u001b[0m |\n",
                                todo::center((*i).first().first(), 9).c_str(),
                                todo::center((*i).first().second().get_description(), 51).c_str(),
                                todo::center((*i).first().second().get_date().to_string() + " (" + openutils::sstring::to_sstring((*i).first().second().get_date().days_between(todo::date())) + " DAYS)", 21).c_str(),
                                todo::center(openutils::sstring::to_sstring((*i).first().second().is_expired()), 17).c_str(),
                                todo::center(openutils::sstring::to_sstring((*i).first().second().is_completed()), 17).c_str(),
                                todo::center(openutils::sstring::to_sstring((*i).second()), 10).c_str());
                else if ((*i).first().second().is_completed() == true && (*i).first().second().is_expired() == true)
                    std::printf("| %s | %s | %s | %s | %s | %s |\n", todo::center((*i).first().first(), 9).c_str(),
                                todo::center((*i).first().second().get_description(), 51).c_str(),
                                todo::center((*i).first().second().get_date().to_string() + " (" + openutils::sstring::to_sstring((*i).first().second().get_date().days_between(todo::date())) + " DAYS)", 21).c_str(),
                                todo::center(openutils::sstring::to_sstring((*i).first().second().is_expired()), 17).c_str(),
                                todo::center(openutils::sstring::to_sstring((*i).first().second().is_completed()), 17).c_str(),
                                todo::center(openutils::sstring::to_sstring((*i).second()), 10).c_str());
                std::printf("------------------------------------------------------------------------------------------------------------------------------------------------\n");
            }
        }
        else
        {
            std::cerr << "err: nothing found related to keyword `" << key << "`." << std::endl;
            return EXIT_FAILURE;
        }
    }
    else if (openutils::sstring::to_sstring(argv[1]) == openutils::sstring::to_sstring("--normalize"))
    {
        db.normalize();
        std::cout << "All tasks are now normalized." << std::endl;
        if (argc >= 3)
        {
            openutils::sstring command = argv[2];
            if (command == openutils::sstring::to_sstring("--log"))
                db.log();
            else
            {
                std::cerr << "err: unknown command `" << command << "`." << std::endl;
                return EXIT_FAILURE;
            }
        }
    }
    else if (openutils::sstring::to_sstring(argv[1]) == openutils::sstring::to_sstring("--import"))
    {
        if (argc < 3)
        {
            std::cerr << "err: not enough arguments" << std::endl;
            return EXIT_FAILURE;
        }
        std::FILE *f = std::fopen(argv[2], "rb");
        if (!f)
        {
            std::cerr << "err: could not open file `" << argv[2] << "`." << std::endl;
            return EXIT_FAILURE;
        }
        std::fclose(f);
        if (!io.import_file(io.get_home_dir() + "/todo_data.dat", argv[2]))
        {
            std::cerr << "err: could not read the contents of the file `" << argv[2] << "`." << std::endl;
            return EXIT_FAILURE;
        }
        std::cout << "All tasks are imported from `" << argv[2] << "`." << std::endl;
        return EXIT_SUCCESS;
    }
    else if (openutils::sstring::to_sstring(argv[1]) == openutils::sstring::to_sstring("--export"))
    {
        if (argc < 3)
        {
            std::cerr << "err: not enough arguments" << std::endl;
            return EXIT_FAILURE;
        }
        std::FILE *f = std::fopen(argv[2], "wb");
        if (!f)
        {
            std::cerr << "err: could not create file `" << argv[2] << "`." << std::endl;
            return EXIT_FAILURE;
        }
        std::fclose(f);
        if (!io.save(db.get(), argv[2]))
        {
            std::cerr << "err: could not write the contents to the file `" << argv[2] << "`." << std::endl;
            return EXIT_FAILURE;
        }
        std::cout << "All tasks are exported to `" << argv[2] << "`." << std::endl;
        return EXIT_SUCCESS;
    }
    else if (openutils::sstring::to_sstring(argv[1]) == openutils::sstring::to_sstring("--rm"))
    {
        if (argc < 3)
        {
            std::cerr << "err: not enough arguments" << std::endl;
            return EXIT_FAILURE;
        }
        openutils::sstring com = argv[2];
        if (com == "-all")
        {
            db.clear();
            std::cout << "Removed all the tasks." << std::endl;
            if (argc >= 4)
            {
                if (openutils::sstring::to_sstring(argv[3]) == openutils::sstring::to_sstring("--log"))
                    db.log();
                else
                {
                    std::cerr << "err: unknown command `" << argv[3] << "`." << std::endl;
                    return EXIT_FAILURE;
                }
            }
            if (db.is_changed())
                io.save(db.get(), io.get_home_dir() + "/todo_data.dat");
            return EXIT_SUCCESS;
        }
        if (!com.is_digit())
        {
            std::cerr << "err: " << com << " should be a number." << std::endl;
            return EXIT_FAILURE;
        }
        todo::task temp = db.get()[com];
        if (!db.remove(com))
        {
            std::cerr << "err: `" << com << "` is not available." << std::endl;
            return EXIT_FAILURE;
        }
        else
            std::cout << "Task [`" << temp.get_description() << "`, `" << temp.get_date().to_string() << "`] at index `" << com << "` is now removed." << std::endl;
        if (argc >= 4)
        {
            if (openutils::sstring::to_sstring(argv[3]) == openutils::sstring::to_sstring("--log"))
                db.log();
            else
            {
                std::cerr << "err: unknown command `" << argv[3] << "`." << std::endl;
                return EXIT_FAILURE;
            }
        }
    }
    else if (openutils::sstring::to_sstring(argv[1]) == openutils::sstring::to_sstring("--complete"))
    {
        if (argc < 3)
        {
            std::cerr << "err: not enough arguments" << std::endl;
            return EXIT_FAILURE;
        }
        openutils::sstring com = argv[2];
        if (!com.is_digit())
        {
            std::cerr << "err: `" << com << "` should be a number." << std::endl;
            return EXIT_FAILURE;
        }
        if (!db.completed(com))
        {
            std::cerr << "err: `" << com << "` is not available." << std::endl;
            return EXIT_FAILURE;
        }
        else
            std::cout << "Task [`" << db.get().get(com).get_description() << "`, `" << db.get().get(com).get_date().to_string() << "`] at index `" << com << "` is now completed." << std::endl;
        if (argc >= 4)
        {
            if (openutils::sstring::to_sstring(argv[3]) == openutils::sstring::to_sstring("--log"))
                db.log();
            else
            {
                std::cerr << "err: unknown command `" << argv[3] << "`." << std::endl;
                return EXIT_FAILURE;
            }
        }
    }
    else if (openutils::sstring::to_sstring(argv[1]) == openutils::sstring::to_sstring("--log"))
    {
        if (argc > 2)
        {
            openutils::sstring repeat = argv[2];
            if (!repeat.is_digit())
            {
                std::cerr << "err: `" << repeat << "` should be a number." << std::endl;
                return EXIT_FAILURE;
            }
            std::size_t n_rep = std::strtoul(argv[2], nullptr, 10);
            for (std::size_t i = 0; i < n_rep; i++)
                db.log();
        }
        else
            db.log();
    }
    else if (openutils::sstring::to_sstring(argv[1]) == openutils::sstring::to_sstring("--sort"))
    {
        if (argc < 4)
        {
            std::cerr << "err: not enough arguments" << std::endl;
            return EXIT_FAILURE;
        }
        openutils::sstring _order = argv[2];

        if (_order != openutils::sstring::to_sstring("-a") && _order != openutils::sstring::to_sstring("-d"))
        {
            std::cerr << "err: expected `-a` or `-d`, instead of `" << _order << "`." << std::endl;
            return EXIT_FAILURE;
        }

        openutils::sstring title = argv[3];

        if (!db.sort(title, _order))
        {
            std::cerr << "err: unknown column title `" << title << "`." << std::endl;
            return EXIT_FAILURE;
        }
        else
            std::cout << "Tasks are now sorted according to column `" << title << "` in " << ((_order == "-a") ? "ascending" : "descending") << " order." << std::endl;
        if (argc >= 5)
        {
            if (openutils::sstring::to_sstring(argv[4]) == openutils::sstring::to_sstring("--log"))
                db.log();
            else
            {
                std::cerr << "err: unknown command `" << argv[4] << "`." << std::endl;
                return EXIT_FAILURE;
            }
        }
    }
    else if (openutils::sstring::to_sstring(argv[1]) == openutils::sstring::to_sstring("--edit"))
    {
        if (argc < 7)
        {
            std::cerr << "err: not enough arguments" << std::endl;
            return EXIT_FAILURE;
        }
        openutils::sstring __date, __desc, __ind;
        bool first_date = false;
        __ind.set(argv[2]);
        if (!__ind.is_digit())
        {
            std::cerr << "err: `" << __ind << "` should be a number." << std::endl;
            return EXIT_FAILURE;
        }
        if (openutils::sstring::to_sstring(argv[3]) == openutils::sstring::to_sstring("-date"))
        {
            __date.set(argv[4]);
            first_date = true;
        }
        else if (openutils::sstring::to_sstring(argv[3]) == openutils::sstring::to_sstring("-desc"))
        {
            __desc.set(argv[4]);
            first_date = false;
        }
        else
        {
            std::cerr << "err: expected `-date` or `-desc`." << std::endl;
            return EXIT_FAILURE;
        }

        if (first_date)
        {
            if (openutils::sstring::to_sstring(argv[5]) == openutils::sstring::to_sstring("-desc"))
            {
                __desc.set(argv[6]);
            }
            else
            {
                std::cerr << "err: expected `-desc`." << std::endl;
                return EXIT_FAILURE;
            }
        }
        else
        {
            if (openutils::sstring::to_sstring(argv[5]) == openutils::sstring::to_sstring("-date"))
            {
                __date.set(argv[6]);
            }
            else
            {
                std::cerr << "err: expected `-date`." << std::endl;
                return EXIT_FAILURE;
            }
        }
        if (!db.edit(__ind, todo::task(__desc, todo::date(__date))))
        {
            std::cerr << "err: could not edit the task [`" << __desc << "`, `" << __date << "`] at index `" << __ind << "`." << std::endl;
            return EXIT_FAILURE;
        }
        else
        {
            std::cerr << "Task edited [`" << __desc << "`, `" << __date << "`] at index `" << __ind << "`." << std::endl;
            if (argc >= 8)
            {
                if (openutils::sstring::to_sstring(argv[7]) == openutils::sstring::to_sstring("--log"))
                    db.log();
                else
                {
                    std::cerr << "err: unknown command `" << argv[7] << "`." << std::endl;
                    return EXIT_FAILURE;
                }
            }
        }
    }
    else if (openutils::sstring::to_sstring(argv[1]) == openutils::sstring::to_sstring("--add"))
    {
        if (argc < 6)
        {
            std::cerr << "err: not enough arguments" << std::endl;
            return EXIT_FAILURE;
        }
        openutils::sstring __date, __desc;
        bool first_date = false;
        if (openutils::sstring::to_sstring(argv[2]) == openutils::sstring::to_sstring("-date"))
        {
            __date.set(argv[3]);
            first_date = true;
        }
        else if (openutils::sstring::to_sstring(argv[2]) == openutils::sstring::to_sstring("-desc"))
        {
            __desc.set(argv[3]);
            first_date = false;
        }
        else
        {
            std::cerr << "err: expected `-date` or `-desc`." << std::endl;
            return EXIT_FAILURE;
        }

        if (first_date)
        {
            if (openutils::sstring::to_sstring(argv[4]) == openutils::sstring::to_sstring("-desc"))
            {
                __desc.set(argv[5]);
            }
            else
            {
                std::cerr << "err: expected `-desc`." << std::endl;
                return EXIT_FAILURE;
            }
        }
        else
        {
            if (openutils::sstring::to_sstring(argv[4]) == openutils::sstring::to_sstring("-date"))
            {
                __date.set(argv[5]);
            }
            else
            {
                std::cerr << "err: expected `-date`." << std::endl;
                return EXIT_FAILURE;
            }
        }
        if (!db.add(todo::task(__desc, todo::date(__date))))
        {
            std::cerr << "err: could not add the task [`" << __desc << "`, `" << __date << "`] at index `" << db.get_last_index() + 1 << "`." << std::endl;
            return EXIT_FAILURE;
        }
        else
        {
            std::cerr << "Task added [`" << __desc << "`, `" << __date << "`] at index `" << db.get_last_index() + 1 << "`." << std::endl;
            if (argc >= 7)
            {
                if (openutils::sstring::to_sstring(argv[6]) == openutils::sstring::to_sstring("--log"))
                    db.log();
                else
                {
                    std::cerr << "err: unknown command `" << argv[6] << "`." << std::endl;
                    return EXIT_FAILURE;
                }
            }
        }
    }
    else
    {
        std::cerr << "err: unknown command `" << argv[1] << "`." << std::endl;
        return EXIT_FAILURE;
    }
    if (db.is_changed())
        io.save(db.get(), io.get_home_dir() + "/todo_data.dat");
    return EXIT_SUCCESS;
}
