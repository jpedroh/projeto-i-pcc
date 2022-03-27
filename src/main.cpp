#include <getopt.h>
#include <iostream>
#include <vector>
#include <glob.h>

struct pmt_options
{
    int edit;
    std::string pattern_file;
    std::string algorithm_name;
    bool is_count;
    bool is_help;
    std::string pattern;
    std::vector<std::string> files;
};

void PrintHelp()
{
    std::cout << "-e,--edit: Localiza todas as ocorrencias aproximadas do padrão a uma distância de edição máxima\n"
                 "--beep:              Beep the user\n"
                 "--sigma <val>:       Set sigma of program\n"
                 "--writeFile <fname>: File to write to\n"
                 "--help:              Show help\n";
    exit(1);
}

std::vector<std::string> parse_files_from_glob(std::string pattern)
{
    glob_t globbuf;
    int err = glob(pattern.c_str(), 0, NULL, &globbuf);
    std::vector<std::string> files;
    if (err == 0)
    {
        for (size_t i = 0; i < globbuf.gl_pathc; i++)
        {
            files.emplace_back(globbuf.gl_pathv[i]);
        }

        globfree(&globbuf);
    }

    return files;
}

pmt_options ProcessArgs(int argc, char **argv)
{
    const char *const short_opts = "e:p:a:c:h";
    const option long_opts[] = {
        {"edit", required_argument, nullptr, 'e'},
        {"pattern", required_argument, nullptr, 'p'},
        {"algorithm", required_argument, nullptr, 'a'},
        {"count", required_argument, nullptr, 'c'},
        {"help", no_argument, nullptr, 'h'}};
    struct pmt_options options = {0, "", "", false, false, ""};

    int args = 1;

    while (true)
    {
        const auto opt = getopt_long(argc, argv, short_opts, long_opts, nullptr);
        if (-1 == opt)
        {
            break;
        }

        switch (opt)
        {
        case 'e':
            args += 2;
            options.edit = std::stoi(optarg);
            break;
        case 'p':
            args += 2;
            options.pattern_file = optarg;
            break;
        case 'a':
            args += 2;
            options.algorithm_name = optarg;
            break;
        case 'c':
            args += 1;
            options.is_count = true;
            break;
        case 'h':
        case '?':
        default:
            options.is_help = true;
            break;
        }
    }

    if (options.pattern_file == "")
    {
        options.pattern = argv[args];
        args++;
    }

    for (int i = args; i < argc; i++)
    {
        auto files = parse_files_from_glob(argv[i]);
        options.files.insert(options.files.end(), files.begin(), files.end());
    }

    return options;
}

int main(int argc, char **argv)
{
    auto args = ProcessArgs(argc, argv);

    if (args.is_help)
    {
        PrintHelp();
        return 1;
    }

    return 0;
}