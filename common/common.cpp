#include "common.h"

void errorCheck(const char* fmt)
{
    int error_no_save = errno;
    std::cout << fmt;

    if(error_no_save != 0)
    {
        fprintf(stdout, " (errno = %d) : %s\n", error_no_save, strerror(error_no_save));
        fprintf(stdout, "\n");
        fflush(stdout);
    }
    exit(1);
}