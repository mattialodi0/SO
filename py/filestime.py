import sys, os
from datetime import datetime as dt


def modified():
    path = sys.argv[1]
    res = {} 

    for (root, dirs, files) in os.walk(path):
        for file in files:
            res[file] = os.path.getmtime(os.path.join(root,file))
    
    sortedres = {key: value for key, value in sorted(res.items(), key=lambda item: item[1])}
    print(f'First modified file: {list(sortedres.keys())[0]}, {dt.fromtimestamp(list(sortedres.values())[0])}')
    print(f'Last modified file: {list(sortedres.keys())[-1]}, {dt.fromtimestamp(list(sortedres.values())[-1])}')


if __name__ == "__main__":
    modified()
