#!/usr/bin/env python3

import os, sys


#ritorna il numero data la syscall o viceversa
def getsyscalls():
    if(len(sys.argv) != 2):
        print("Wrong num of arguments")
        return
    
    inputfile = "out.c"


    with open(inputfile, "r") as f:
        if sys.argv[1].isnumeric():
            num = int(sys.argv[1])+2
            i = 0
            for line in f:
                i += 1
                if num == i: 
                    print(line)
                    break
        else:
            i = 0
            for line in f:
                i += 1
                if sys.argv[1] in line: 
                    print(i-2)
                    break


if __name__ == "__main__":
    getsyscalls()
