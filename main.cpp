#include <map>
#include <getopt.h>
#include <stdio.h>
#include "cp_core.h"
#include "arg_parser.h"
#include "err_lib.h"

int main (int argc, char* argv[]) {

    #ifdef _DEBUG
    printf ("Warning! Running in debug mode!\n");
    #endif

    int h_flag = 0;
    int i_flag = 0;
    int f_flag = 0;
    int v_flag = 0;
    int p_flag = 0;
    int arg_idx = 0;
    optind = 0;

    static const struct option long_options[] =
    {
        {"help",        no_argument, &h_flag, 1},
        {"interactive", no_argument, &i_flag, 1},
        {"force",       no_argument, &f_flag, 1},
        {"verbose",     no_argument, &v_flag, 1},
        {"preserve",    no_argument, &p_flag, 1},
    };

    using pair_t = std::pair<int*, int>;
    std::map<char, pair_t> short_options{
        {'h', {&h_flag, 1}},
        {'i', {&i_flag, 1}},
        {'f', {&f_flag, 1}},
        {'v', {&v_flag, 1}},
        {'p', {&p_flag, 1}}
    };

    arg_parser::parse_args (argc, argv, short_options, long_options, &arg_idx);

    #ifdef _DEBUG
    printf ("h[%d] i[%d] f[%d] v[%d] p[%d]\n", h_flag, i_flag, f_flag, v_flag, p_flag);
    printf ("last_flag_idx[%d], argc[%d]\n", optind, argc);
    printf ("in_file[%s]\nout_file[%s]\n", argv[optind], argv[optind + 1]);
    #endif

    if (optind != 0 && optind < argc) {

        my_cp(argv[optind], argv[optind + 1], h_flag, i_flag, f_flag, v_flag, p_flag);
        return 0;
    }
    
    print_help ();
    return 0;
}