#!/usr/bin/env python3

import os
import sys

def difdir(dir1, dir2, dir3, dir4):
    #prende i file dalle dir
    filedir1 = []
    filedir2 = []
    for file in os.listdir(dir1):
        if(os.path.isfile(os.path.join(dir1,file))):
            filedir1.append(file)
    for file in os.listdir(dir2):
        if(os.path.isfile(os.path.join(dir2,file))):
            filedir2.append(file)
 
    #prende i file di dir1 in dir2
    files1 = []
    for f in filedir1:
        if f in filedir2:
            files1.append(f)

    #prende i file di dir2 in dir1
    files2 = []
    for f in filedir2:
        if f in filedir1:
            files2.append(f)

    #crea la dir3
    os.mkdir(dir3)
    for f in files1:
        with open(os.path.join(dir1,f), 'r') as oldfile:
            with open(os.path.join(dir3,os.path.basename(f)), 'w') as newfile:
                newfile.write(oldfile.read())

    #crea la dir4
    os.mkdir(dir4)
    for f in files2:
        with open(os.path.join(dir2,f), 'r') as oldfile:
            with open(os.path.join(dir4,os.path.basename(f)), 'w') as newfile:
                newfile.write(oldfile.read())

if __name__ == "__main__":
    difdir(sys.argv[1], sys.argv[2], sys.argv[3], sys.argv[4])


# esame 23-01-23
