#!/usr/bin/env python3

import os
import sys

# ritorna la somma della dim dei file ELF
def elfsize():
    dim = 0
    dirs = []
    # riempe la lista delle dir da visitare
    if(len(sys.argv) == 1):
        dirs = ['.']
    else:    
        for i in range(1,len(sys.argv)):
            dirs.append(sys.argv[i])
    # visita le dir richieste ricorsivamente
    for dir in dirs:
        for root, directories, files in os.walk(dir):
            for f in files:
                if(os.path.isfile(os.path.abspath(f)) and os.access(os.path.abspath(f), os.X_OK)):
                    dim +=os.path.getsize(os.path.abspath(f))

    print(dim)

if __name__ == "__main__":
    elfsize()


# esame 22-07-22
