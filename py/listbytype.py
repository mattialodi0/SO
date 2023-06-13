#!/usr/bin/env python3

import os
import sys
import magic
import subprocess

# per ogni tipo di file ritorna i file di quel tipo
def listfile():
    if(len(sys.argv) == 1):
        dir = '.'
    else:
        if(len(sys.argv) == 2):
            dir = sys.argv[1]
        else:
            print("Erorr: too many arguments")

    # alternativa peggiore
    """for filename in os.listdir(dir):
        filepath = os.path.join(dir, filename)
        info = subprocess.run(['file', filepath], capture_output=True, text=True)
        print(f"{info.stdout.strip()}: {filename}")"""
    
    catalogue = {'dyrectory':[]}
    for filename in os.listdir(dir):
        fullpath=os.path.join(dir,filename)
        if os.path.isdir(fullpath):
            catalogue['dyrectory'].append(filename)
        else:
            m = magic.Magic(mime=True, uncompress=True)
            filetype = m.from_file(fullpath)
            if not filetype in catalogue:
                catalogue[filetype] = []
            catalogue[filetype].append(filename)
            
    #print(catalogue)
    for key in catalogue:
        names = str(catalogue[key])
        print(key + ': '+ names)


if __name__ == "__main__":
    listfile()


# esame 22-06-22
