import sys, os

# ritorna i file che contengono il testo in input
def matchpath():
    path = sys.argv[1]
    matchedfiles = {}

    for (root, dirs, files) in os.walk('.'):
        for filename in files:
            with open(os.path.join(root,filename)) as f:
                s = f.read()
                if path in s:
                    matchedfiles[filename] = os.path.getmtime(os.path.join(root,filename))
    sort = sorted(matchedfiles.items(), reverse=True, key=lambda item: item[1])
    keys = dict(sort)
    print(list(keys))

if __name__ == "__main__":
    matchpath()
