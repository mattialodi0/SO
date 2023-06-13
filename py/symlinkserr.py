import sys, os

#trova i symlinks che non puntano più da un file esistente
def finderrlinks():
    for root, dis, files in os.walk('.'):
        for file in files:
            path = os.path.join(root,file)
            if(os.path.islink(path)):    # se è un link simbolico
                if not os.path.exists(path):   # se il file a cui punta non esiste più
                    print(f"'{file}' is not working anymore because {os.readlink(path)} was deleted")

if __name__ == "__main__":
    finderrlinks()

# esame 18-9-18
