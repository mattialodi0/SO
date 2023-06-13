#!/usr/bin/env python3

import os
import sys
import magic

# esegue tutti gli script non ELF
def exec():
    if(len(sys.argv) == 1):
        dir = '.'
    else:
        if(len(sys.argv) == 2):
            dir = sys.argv[1]
        else:
            print("Erorr: too many arguments")
    
    files = os.listdir(dir)
    for f in files:
        fullpath=os.path.join(dir,f)
        if(not (os.path.isdir(fullpath))) and os.access(fullpath, os.X_OK):
            filetype=magic.from_file(fullpath)
            if(not "ELF" in filetype):
                os.system(os.path.join(dir,f))
                #print("1 found")



if __name__ == "__main__":
    exec()


# esame 22-09-07
