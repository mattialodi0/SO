#!/usr/bin/env python3

import os, sys, threading


#esegue contemporaneamente i comandi in input
def para():
    if(len(sys.argv) < 2):
        print("Too few arguments")
        return
    
    #lista dei comandi da eseguire
    cmds = ' '.join(sys.argv[1:])
    cmds = list(cmds.split('//'))
    cmds = [c.strip() for c in cmds]
    print("commands to run: ",cmds)

    threads = []
    for cmd in cmds:
        threads.append(threading.Thread(target=run, args=(cmd,)))

    i = 0
    for thread in threads:
        print(f"starting thread {i}, {cmds[i]}")
        thread.start()
        i += 1

    for thread in threads:
        thread.join()

    print("All commands are terminated")

#lancia il comando in input
def run(cmd):
    os.system(cmd)

if __name__ == "__main__":
    para()
