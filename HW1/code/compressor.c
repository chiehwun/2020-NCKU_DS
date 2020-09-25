#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <ctype.h>
#include <string.h>
// getopt() global (cross-filed) variables
extern char *optarg;
extern int optind, opterr, optopt;
FILE *ifp, *ofp;

static const char base64_table[65] =
    "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
static const int eq_cnt[] = {0, 1, 2, 2, 3, 4, 4};
int getopt(int argc, char *const *argv, const char *optstring);
void getIO(int argc, char *const *argv, char *in, char *out);
int hex2int(char ch);
void convert_print(char ch, char *buffer);

int main(int argc, char *argv[])
{
    char infile_name[100] = "", outfile_name[100] = "";
    getIO(argc, argv, infile_name, outfile_name);
    ifp = fopen(infile_name, "r");
    ofp = fopen(outfile_name, "w");
    int cnt = 0;
    char ch = 0, buffer[7] = "######";
    while ((ch = getc(ifp)) != EOF)
    {
        if (isxdigit(ch))
        {
            buffer[cnt] = ch;
            if (cnt == 5) // last (6th) number
            {
                convert_print(ch, buffer);
                cnt = 0;
                continue;
            }
            ++cnt;
        }
        else
        {
            convert_print(ch, buffer);
            cnt = 0;
        }
    }
    convert_print(ch, buffer);
    return 0;
}

void convert_print(char ch, char *buffer)
{
    int base = 0, length = 0; // valid length(0~5, 6)
    // put 6 hex digits(24 bits) into int
    for (; length < 6 && isxdigit(buffer[length]); ++length)
        base |= hex2int(buffer[length]) << 4 * (5 - length);
    // print result
    for (int i = 0; i < eq_cnt[length]; ++i)
    {
        int b64 = (base >> 6 * (3 - i)) & 077;
        fprintf(ofp, "%c", base64_table[b64]);
    }
    if (length > 0)
        for (int i = 0; i < 4 - eq_cnt[length]; ++i)
            fprintf(ofp, "=");
    // occurs when ch == '\n', EOF should not print
    if (!isxdigit(ch) && ch != EOF)
        fprintf(ofp, "%c", ch);
    // reset buffer[7]
    strcpy(buffer, "######");
}

void getIO(int argc, char *const *argv, char *in, char *out)
{
    int cmd_opt = 0;
    while ((cmd_opt = getopt(argc, argv, "i:o:")) != -1)
    {
        // Lets parse
        switch (cmd_opt)
        {
        // No args

        // Single arg ":"
        case 'i':
            strcpy(in, optarg);
            break;
        case 'o':
            strcpy(out, optarg);
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
            exit(0);
            break;
        default:
            fprintf(stderr, "Not supported option\n");
            exit(0);
            break;
        }
    }
}

int hex2int(char ch)
{
    if (ch >= '0' && ch <= '9')
        return ch - '0';
    if (ch >= 'A' && ch <= 'F')
        return ch - 'A' + 10;
    if (ch >= 'a' && ch <= 'f')
        return ch - 'a' + 10;
    return -1;
}