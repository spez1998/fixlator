#include <getopt.h>
#include <stdio.h>     /* for printf */
#include <stdlib.h>    /* for exit */

#include <iostream>

constexpr const char *opts {"abc:d:h012"};

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
    std::cout << "\nCalling " << proc_name << " without args will run CLI translation by default\n";
    std::cout << std::endl;
}

int main(int argc, char **argv)
{
   int c {};
   int digit_optind {0};

   while (1) {
       int this_option_optind {optind ? optind : 1};
       int option_index {0};

       c = getopt_long(argc, argv, opts, long_options, &option_index);
       if (c == -1)
           break;

       switch (c) {
       case 0:
           printf("option %s", long_options[option_index].name);
           if (optarg)
               printf(" with arg %s", optarg);
           printf("\n");
           break;

       case '0':
       case '1':
       case '2':
           if (digit_optind != 0 && digit_optind != this_option_optind)
             printf("digits occur in two different argv-elements.\n");
           digit_optind = this_option_optind;
           printf("option %c\n", c);
           break;

       case 'a':
           printf("option a\n");
           break;

       case 'b':
           printf("option b\n");
           break;

       case 'c':
           printf("option c with value '%s'\n", optarg);
           break;

       case 'd':
           printf("option d with value '%s'\n", optarg);
           break;

       case 'h':
           print_help(argv[0]);
           break;

       case '?':
           break;

       default:
           printf("?? getopt returned character code 0%o ??\n", c);
       }
   }

   if (optind < argc) {
       printf("non-option ARGV-elements: ");
       while (optind < argc)
           printf("%s ", argv[optind++]);
       printf("\n");
   }

   exit(EXIT_SUCCESS);
}
