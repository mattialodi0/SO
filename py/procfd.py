import sys, os

# ritorna il numero di fd per ogni proc
def mostdes():
    path = '/proc'
    proc = {}

    for dir in os.listdir(path):
        try: 
            if os.path.isdir(os.path.join(path, dir)) and dir.isdigit():
                proc[dir] = 0
                for fd in os.listdir(os.path.join(path,dir,'fd')):
                    proc[dir] += 1
        except PermissionError:
            continue
    print(proc)



if __name__ == "__main__":
    mostdes()

# esame 18-2-18
