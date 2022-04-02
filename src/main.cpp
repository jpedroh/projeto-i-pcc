#include <getopt.h>
#include <iostream>
#include <vector>
#include <glob.h>
#include <fstream>
#include "sliding_window.h"
#include "sellers.h"
#include "shift_or.h"
#include "kmp.h"
#include "aho_corasick.h"
#include "wu_manber.h"
#include <iterator>
#include <memory>
#include <algorithm>

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
    std::cout << "-e,--edit:\tLocaliza todas as ocorrencias aproximadas do padrão a uma distância de edição máxima\n"
                 "-p, --pattern patternfile:\tRealiza a busca de todos os padroes contidos no arquivo pattern-file.\n"
                 "-a, --algorithm algorithm name:\tRealiza a busca de padroes usando o algoritmo.\n"
                 "-c, --count:\tImprime apenas a quantidade total de ocorrencias do(s) padrão(ões) contidas no(s) arquivo(s) de texto.\n"
                 "--help:\tShow help\n";
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

std::vector<std::string> get_patterns_from_options(pmt_options options)
{
    std::vector<std::string> patterns;
    if (options.pattern_file == "")
    {
        patterns.emplace_back(options.pattern);
    }
    else
    {
        std::ifstream file(options.pattern_file);
        std::string line;
        for (std::string line; std::getline(file, line);)
        {
            patterns.emplace_back(line);
        }
    }
    return patterns;
}

std::unique_ptr<Algorithm> get_search_algorithm_from_options(pmt_options options)
{
    if (options.algorithm_name == "sliding_window")
    {
        return std::make_unique<SlidingWindow>();
    }
    else if (options.algorithm_name == "sellers")
    {
        return std::make_unique<Sellers>();
    }
    else if (options.algorithm_name == "shift_or")
    {
        return std::make_unique<ShiftOr>();
    }
    else if (options.algorithm_name == "kmp")
    {
        return std::make_unique<KMP>();
    }
    else if (options.algorithm_name == "aho_corasick")
    {
        return std::make_unique<AhoCorasick>();
    }
    else if (options.algorithm_name == "wu_manber")
    {
        return std::make_unique<WuManber>();
    }

    return std::make_unique<SlidingWindow>();
}

int main(int argc, char **argv)
{
    if (argc < 3)
    {
        PrintHelp();
        return 1;
    }

    auto options = ProcessArgs(argc, argv);
    if (options.is_help)
    {
        PrintHelp();
        return 1;
    }

    auto patterns = get_patterns_from_options(options);
    auto algorithm = get_search_algorithm_from_options(options);

    // Faz a busca efetivamente
    std::vector<std::string> lines;
    int count = 0;
    algorithm->initialize(patterns, options.edit);
    for (auto file_name : options.files)
    {
        std::ifstream file(file_name);
        std::string line;
        while (getline(file, line))
        {
            auto line_occurrences = algorithm->search(patterns, line, options.edit);
            for (auto pattern_occurences : line_occurrences)
            {
                count += pattern_occurences.size();
                if (pattern_occurences.size() > 0)
                {
                    lines.push_back(line);
                }
            }
        }
    }

    if (options.is_count)
    {
        std::cout << count << std::endl;
        return 0;
    }

    for (auto line : lines)
    {
        std::cout << line << std::endl;
    }

    return 0;
}