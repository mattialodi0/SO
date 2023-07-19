import sys, os

# fa una statistica della lunghezza dei nomi dei file in una dir
def statlen():
    path = sys.argv[1]
    namelen = {}
    for file in os.listdir(path):
        flen = len(file)
        if flen in namelen:
            namelen[flen] += 1
        else:
            namelen[flen] = 1
    print(namelen)

if __name__ == "__main__":
    statlen()

# esame 14-5-29
