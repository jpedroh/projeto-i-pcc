#include <getopt.h>
#include <iostream>

int num = -1;
bool is_beep = false;
float sigma = 2.034;
std::string write_file = "default_file.txt";

struct pmt_options
{
    int edit;
    std::string pattern_file;
    std::string algorithm_name;
    bool is_count;
    bool is_help;
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

pmt_options ProcessArgs(int argc, char **argv)
{
    const char *const short_opts = "e:p:a:c:h";
    const option long_opts[] = {
        {"edit", required_argument, nullptr, 'e'},
        {"pattern", required_argument, nullptr, 'p'},
        {"algorithm", required_argument, nullptr, 'a'},
        {"count", required_argument, nullptr, 'c'},
        {"help", no_argument, nullptr, 'h'}};
    struct pmt_options options;

    while (true)
    {
        const auto opt = getopt_long(argc, argv, short_opts, long_opts, nullptr);

        if (-1 == opt)
            break;

        switch (opt)
        {
        case 'e':
            options.edit = std::stoi(optarg);
            break;
        case 'p':
            options.pattern_file = optarg;
            break;
        case 'a':
            options.algorithm_name = optarg;
            break;
        case 'c':
            options.is_count = true;
            break;
        case 'h':
        case '?':
        default:
            options.is_help = true;
            break;
        }
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