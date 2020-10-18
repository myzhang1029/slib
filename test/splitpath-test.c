#include <string.h>
#include <slib/fileopt.h>
#include "tests.h"

int splitpath_main(void)
{
    const char *path1 = "/usr/local/bin/gcc";
    const char *path2 = "C:/Program Files/test/test.exe";
    char drive[3];
    char dirname[21];
    char basename[5];
    char ext[5];
    splitpathS(path1, drive, dirname, basename, ext);
    asrt_str_equ(drive, "", "splitpath-drive1");
    asrt_str_equ(dirname, "/usr/local/bin/", "splitpath-dirname1");
    asrt_str_equ(basename, "gcc", "splitpath-basename1");
    asrt_str_equ(ext, "", "splitpath-ext1");
    splitpathS(path2, drive, dirname, basename, ext);
    asrt_str_equ(drive, "C:", "splitpath-drive2");
    asrt_str_equ(dirname, "/Program Files/test/", "splitpath-dirname2");
    asrt_str_equ(basename, "test", "splitpath-basename2");
    asrt_str_equ(ext, ".exe", "splitpath-ext2");
    return 0;
}
