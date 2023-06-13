import sys, os

# ritorna il percorso di ogni file
def rlsr():
    path = sys.argv[1]
    res = {}

    for (root, dirs, files) in os.walk(path):
        for file in files:
            res[file] = os.path.join(root)
    
    sortedres = {key: value for key, value in sorted(res.items())}
    for key, val in res.items():
        print(f'{key[:6]}:\t {val}')    # [:6] taglia la str per avere una formattazione migliore

if __name__ == "__main__":
    rlsr()
