#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <utime.h>
#include <fcntl.h>
#include <unistd.h>
#include "err_lib.h"
#include "cp_core.h"

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx


CpErrCodes my_cp (char* in_filename, char* out_filename, int h_flag, int i_flag, int f_flag, int v_flag, int p_flag) {
    ass (in_filename, "Null pointer passed", CpErrCodes::NULL_PTR_PASSED);
    ass (out_filename, "Null pointer passed", CpErrCodes::NULL_PTR_PASSED);

    ass (access (in_filename, F_OK) == 0, "Input file does not exist", CpErrCodes::CANT_OPEN_IN_FILE);

    if (h_flag) {
        print_help();
        return CpErrCodes::OK;
    }

    if (i_flag && access(out_filename, F_OK) == 0 && !ask_user())
            return CpErrCodes::OK;    

    if (f_flag && access(out_filename, W_OK) != 0)
        ass (remove(out_filename) == 0, "Can not delete out file", CpErrCodes::CANT_DELETE_OUT_FILE);

    CpErrCodes copy_ret_code = copy_file (in_filename, out_filename);
    ass (copy_ret_code == CpErrCodes::OK, "Error while copying file", copy_ret_code);
    
    if (p_flag) {
        CpErrCodes metainfo_copy_ret_code = copy_metainfo (in_filename, out_filename);
        ass (metainfo_copy_ret_code == CpErrCodes::OK, "Can not copy file mentainfo", metainfo_copy_ret_code);
    }

    if (v_flag)
        fprintf (stderr, "\"%s\" > \"%s\"", in_filename, out_filename);    

    return CpErrCodes::OK;
}

//flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

CpErrCodes copy_file (char* source, char* dest) {
    ass (source, "Null pointer passed", CpErrCodes::NULL_PTR_PASSED);
    ass (dest, "Null pointer passed", CpErrCodes::NULL_PTR_PASSED);

    int in_fd = -1, out_fd = -1;
    const int buf_size = 1024;
    char buffer[buf_size];
    int n_chars = 0;

    ass ((in_fd = open(source, O_RDONLY)) != -1, 
            "Can't open input file", CpErrCodes::CANT_OPEN_IN_FILE);

    ass ((out_fd = creat(dest, 0644)) != -1, 
            "Can't open output file", CpErrCodes::CANT_OPEN_OUT_FILE);

    while ((n_chars = read(in_fd, buffer, buf_size)) > 0) {
        ass (write (out_fd, buffer, n_chars) == n_chars, 
                "Write error", CpErrCodes::WRITE_ERROR);
    }

    ass ((close(in_fd)  != -1), 
            "Can't close input file",  CpErrCodes::CANT_CLOSE_IN_FILE);

    ass ((close(out_fd) != -1), 
            "Can't close output file", CpErrCodes::CANT_CLOSE_OUT_FILE);
    
    return CpErrCodes::OK;
}

void print_help() {
    char cmd_buf[] = "man cp";
    system(cmd_buf);
}

bool ask_user() {
    printf ("Out file already exists. Do you want to owerwrite it? [y/n]\n");
    char ans = 0;
    int c = 0;

    while (scanf("%c", &ans) != 1 && (ans == 'y' || ans == 'n')) {
        printf ("Incorrect input. Enter 'y' or 'n'\n");
        while ((c = getchar()) != '\n') {};
    }

    return ans == 'y';
}

CpErrCodes copy_metainfo (char* input_file, char* output_file) {
    ass (input_file, "Null pointer passed", CpErrCodes::NULL_PTR_PASSED);
    ass (output_file, "Null pointer passed", CpErrCodes::NULL_PTR_PASSED);

    struct stat stat_bufer;
    struct utimbuf new_times;
    
    int stat_result = stat (input_file, &stat_bufer);
    ass ((stat_result != -1), "Can't get input file stat", CpErrCodes::STAT_FUNC_FAILED);





    new_times.actime  = stat_bufer.st_atim.tv_sec;
    new_times.modtime  = stat_bufer.st_ctim.tv_sec; 

    ass(utime(output_file, &new_times) == 0, 
        "Can't set new file stat", CpErrCodes::UTIME_FUNC_FAILED);
    ass(chmod(output_file, stat_bufer.st_mode) == 0, 
        "Can't set new file mode", CpErrCodes::CHMOD_FUNC_FAILED);
    ass(chown(output_file, stat_bufer.st_uid, stat_bufer.st_gid) == 0, 
        "Can't set file owners", CpErrCodes::CHOWN_FUNC_FAILED);

    return CpErrCodes::OK;
}