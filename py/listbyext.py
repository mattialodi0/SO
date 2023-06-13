import sys, os


def listsuff():
    files = {}

    for file in os.listdir('.'):
        name, ext = os.path.splitext(file)
        if ext in files:
            files[ext].append(name)
        else:
            files[ext] = [name]
    
    files = dict(sorted(files.items(), reverse=True))
    
    for ext in files:
        if ext == '':
            print(files[ext])
        else:
            print(f'{ext}: {files[ext]}')

if __name__ == "__main__":
    listsuff()

# esame 17-2-17
