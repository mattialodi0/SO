#!/usr/bin/env python3

import os, sys, psutil

# stampa la tabella con l'occupazione e il nume di ogni programma di proprietà dell'utente
def table():
    dir_name = '/proc'
    pids = []
    name = ' '
    mem = 0

    for process in psutil.process_iter(['pid', 'name', 'username']):
        if process.info['username'] == psutil.Process().username():
            pids.append(str(process.info['pid']))
    print("Pids:")
    print(pids)

    print('name \t\t\t\t vmSize')
    files = os.listdir(dir_name)
    for filename in files:
        if filename in pids:
            path_name = os.path.join(dir_name,filename)
            if os.path.isdir(path_name) and filename not in ["net", "mounts", "self", "thread", "thread-self"]:
                with open(os.path.join(path_name,'status')) as f:
                    for line in f:
                        tokens = line.split()
                        if tokens[0] == 'Name:':
                            name = ' '.join(tokens[1:])
                        elif tokens[0] == 'VmSize:':
                            mem = ' '.join(tokens[1:])
                    print(f'{name:<20}\t\t{mem}')

if __name__ == "__main__":
    table()


# esame 22-06-8
"""proc = 
        if process is users:
            process = psutil.Process(os.getpid())
            memory  = float( process.memory_info()[0] ) / float(2 ** 20)
            print(filename + '\t\t' + memory)
        """     