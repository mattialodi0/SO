import sys, os


def search():
    path = sys.argv[1]

    fdict = {}

    for (root, dirs, files) in os.walk(path):
        for file in files:
            with open(os.path.join(root,file), "r") as f:
                line = f.readline()
                line = line.strip()
                if line.startswith('#!'):
                    if line in fdict:
                        fdict[line].append(os.path.join(root,file))
                    else:
                        fdict[line] = [os.path.join(root,file)]

    for key in fdict:
        print(f'{key}: {fdict[key]}')
        

if __name__ == "__main__":
    search()

# esame 18-9-21