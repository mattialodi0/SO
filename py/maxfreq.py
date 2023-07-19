import sys, os

# ritorna il file nel sottoalbero con la freq maggiore del caratter in input
def maxfreq():
    path = sys.argv[1]
    ichar = sys.argv[2]
    filestat = {}
    
    for (root, dirs, files) in os.walk(path):
        for file in files:
            ichars = totchars = 0
            with open(os.path.join(root, file), "r", encoding='utf-8') as f:
                while True:
                    char = f.read(1)
                    if not char:
                        break
                    totchars += 1
                    if char == ichar:
                        ichars += 1
            try:
                perc = ichars / totchars
            except ArithmeticError:
                perc = 0
            filestat[os.path.join(root, file)] = perc
    sortedfilestat = sorted(filestat.items(), key=lambda x:x[1])
    print(f'Il file con più {ichar} è: {sortedfilestat[-1][0]}, con {sortedfilestat[-1][1]}')
    #print(sortedfilestat)
    

if __name__ == "__main__":
    maxfreq()

# esame 14-6-17
