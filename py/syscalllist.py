#!/usr/bin/env python3

import os


#ritorna la lista delle syscalls
def listsyscalls():
    inputfile = "/usr/include/x86_64-linux-gnu/asm/unistd_64.h"
    syscallslist = []

    with open(inputfile, "r") as f:
        for line in f:
            if line.startswith("#define __NR_"):
                line = line.split()
                syscallslist.append('"'+line[1][5:] + '",\n')

    #print(syscallslist)
    syscallstr = ' '.join(syscallslist)

    with open("out.c", "w") as o:
        o.write("char *syscall_name[] = {\n")
        o.write(syscallstr)
        o.write("\n}")

if __name__ == "__main__":
    listsyscalls()
