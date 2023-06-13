#!/usr/bin/env python3

import os, sys


#ritorna la lista ordinata al contrario dei file nella dir in input
def listsuff():
    if(len(sys.argv) != 2):
        print("Wrong num of arguments")
        return
    
    files = os.listdir(sys.argv[1])

    sortedfiles = sorted(files, reverse=False, key=f)

    print(files)
    print(sortedfiles)

#inverte i nomi dei file
def f(item):
    return item[::-1]

if __name__ == "__main__":
    listsuff()
