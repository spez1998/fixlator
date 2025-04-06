#include <getopt.h>
#include <iostream>

#include <base/UserData.h>

constexpr const char *opts {"h012"};

Fixlator::UserData userdata;

static struct option long_options[] = {
    {"add",     required_argument, 0,  0 },
    {"append",  no_argument,       0,  0 },
    {"delete",  required_argument, 0,  0 },
    {"verbose", no_argument,       0,  0 },
    {"create",  required_argument, 0, 'c'},
    {"file",    required_argument, 0,  0 },
    {"help",    no_argument,       0, 'h'},
    {0,         0,                 0,  0 }
};

void print_help(char *proc_name)
{
    std::cout << "\nUsage:\n";
    std::cout << " " << proc_name << " [options]\n";
    std::cout << "Options:\n";
    std::cout << " -h, --help        displays this help text and exit\n";
    std::cout << "\nCalling " << proc_name << " without args will translate by default\n";
    std::cout << std::endl;
}

int translate_raw_fix()
{
    //for (std::string line; std::getline(std::cin, line);) {
    //    std::cout << line << std::endl;
    //}
    //
    
    userdata.SaveData(std::cin);
    std::cout << userdata.GetNumSavedMessages();

    return 0;
}

int main(int argc, char **argv)
{ 
    char *in_buf {};
    int c {-1};
    int digit_optind {0};

    while (1) {
        int this_option_optind {optind ? optind : 1};
        int option_index {0};

        c = getopt_long(argc, argv, opts, long_options, &option_index);
        if (c == -1) {
            std::cout << "\nNo argument provided" << std::endl;
            translate_raw_fix();
            break;
        }

        switch (c) {
        case 0:
            std::cout << "option " << long_options[option_index].name;
            if (optarg) {
                std::cout << " with arg " << optarg;
            }
            std::cout << std::endl;
            break;

        case '0':
        case '1':
        case '2':
            if (digit_optind != 0 && digit_optind != this_option_optind) {
                std::cout << "digits occur in two different argv-elements.\n";
            }
            digit_optind = this_option_optind;
            std::cout << "option " << (char)c << std::endl;
            break;

        case 'h':
            print_help(argv[0]);
            break;

        case '?':
            std::cout << "hello";
            break;

        default:
            std::cout << "?? getopt returned character code 0 " << (char)c << " ??" << std::endl;
        }
    }

    if (optind < argc) {
        std::cout << "non-option ARGV-elements: ";
        while (optind < argc) {
            std::cout << argv[optind++] << " ";
        }
        std::cout << std::endl;
    }

    return 0;
}
