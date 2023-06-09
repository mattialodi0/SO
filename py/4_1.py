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
    
    for filename in os.listdir(dir):
        fullpath=os.path.join(dir,filename)
        if(not (os.path.isdir(fullpath))):
            filetype=magic.from_file(fullpath)
            if("ELF" in filetype):
                print(filename + "is ELF")


if __name__ == "__main__":
    exec()
