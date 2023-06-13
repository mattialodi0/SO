#!/usr/bin/env python3

import os


#ritorna il numero di righe per tipo di file nella dir corrente
def clines():
    totc, toth, totm = 0, 0, 0

    files = os.listdir()

    for file in files:
        if file.endswith(".c"):
            with open(file) as f:
                n = len(f.readlines())
                totc += n
            print(file + '\t' + str(n))
    print('tot .c' + '\t' + str(totc) + '\n')
                    
    for file in files:
        if file.endswith(".h"):
            with open(file) as f:
                n = len(f.readlines())
                toth += n
            print(file + '\t' + str(n))
    print('tot .h' + '\t' + str(toth) + '\n')
            
    for file in files:
        if file == "makefile":
            with open(file) as f:
                n = len(f.readlines())
                totm += n
            print(file + '\t' + str(n))
    print('tot makefile' + '\t' + str(totm) + '\n')

    print('tot source\t' + str(totc+toth+totm))

if __name__ == "__main__":
    clines()
