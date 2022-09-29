#ifndef CP_CORE
#define CP_CORE


enum CpErrCodes {
    OK                      =  0,
    CANT_OPEN_IN_FILE       = -1,
    CANT_CLOSE_IN_FILE      = -2,
    CANT_OPEN_OUT_FILE      = -3,
    CANT_CLOSE_OUT_FILE     = -4,
    CANT_DELETE_OUT_FILE    = -5,
    WRITE_ERROR             = -6,
    STAT_FUNC_FAILED        = -7,
    NULL_PTR_PASSED         = -8,
    UTIME_FUNC_FAILED       = -9,
};

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

CpErrCodes my_cp (char* in_filename, char* out_filename, 
                  int h_flag, int i_flag, int f_flag, int v_flag, int p_flag);


CpErrCodes copy_file (char* source, char* dest);
void print_help();
bool ask_user();
CpErrCodes recreate_file (char* filename);
CpErrCodes copy_metainfo (char* input_file, char* output_file);

#endif