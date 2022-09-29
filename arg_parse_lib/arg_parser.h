
//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
namespace arg_parser {

enum ParserErrCodes {
    OK                      =  0,
    NULL_PTR_PASSED         = -1,
    GETOPT_ERROR            = -2,
};

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

int parse_args (int argc, char* argv[], 
                    std::map<char, std::pair<int*, int>> short_options, 
                    const struct option* options, int* fist_non_flag_idx);

}
//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
