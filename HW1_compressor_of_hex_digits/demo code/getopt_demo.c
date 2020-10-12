// http://wen00072.github.io/blog/2013/12/29/using-getopt-parse-command-line-parameter/#%E5%8F%83%E8%80%83%E8%B3%87%E6%96%99
// .\getopt_demo -a -emy_args -c dddd  123 456 7890 -b -f -d
// abc:d:e:: >> -a, -b, -c<carg> or -c <carg>, -d<darg> or -d <darg>, -e<earg> or -e
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <ctype.h>
// getopt() global (cross-filed) variables
extern char *optarg;
extern int optind, opterr, optopt;
int getopt(int argc, char *const *argv, const char *optstring);

int main(int argc, char *argv[])
{
    int cmd_opt = 0;

    fprintf(stderr, "argc:%d\n", argc);
    while ((cmd_opt = getopt(argc, argv, "abc:d:e::")) != -1)
    {

        // // End condition always first
        // if (cmd_opt == -1)
        // {
        //     break;
        // }

        // Print option when it is valid
        if (cmd_opt != '?')
            fprintf(stderr, "option:-%c\n", cmd_opt);

        // Lets parse
        switch (cmd_opt)
        {
        // No args
        case 'a':
        case 'b':
            break;

        // Single arg ":"
        case 'c':
        case 'd':
            fprintf(stderr, "option arg:%s\n", optarg);
            break;

        // Optional args "::"
        case 'e':
            if (optarg)
            {
                fprintf(stderr, "option arg:%s\n", optarg);
            }
            break;

        // Error handle: Mainly missing arg (Single arg ":") or illegal option
        case '?':
            fprintf(stderr, "Illegal option:-%c\n", isprint(optopt) ? optopt : '#');
            break;
        default:
            fprintf(stderr, "Not supported option\n");
            break;
        }
        fprintf(stderr, "process index:%d\n", optind); // next pointer
    }

    // Do we have args?
    if (argc > optind)
        for (int i = optind; i < argc; ++i)
            fprintf(stderr, "argv[%d] = %s\n", i, argv[i]);
}