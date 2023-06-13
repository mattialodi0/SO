import sys, os


def users():
    users = {}
    path = '/proc'
    for file in os.listdir(path):
        if os.path.isdir(os.path.join(path,file)):
            try:
                with open(os.path.join(path,file,'status')) as f:
                    c = f.read().split("\n")

                    for e in c:
                        if e.startswith('Uid'):
                            l = e.split('\t')
                            for i in [1,2,3,4]:
                                if l[i] not in users:
                                    users[l[i]] = [0,0,0,0]
                                    users[l[i]][i-1] += 1
                                else:
                                    users[l[i]][i-1] += 1    
            except FileNotFoundError:
                continue
    print(users)

if __name__ == "__main__":
    users()

# esame 18-5-29


# Versione di ChatGPT:
"""
import os

# Dizionario per mantenere il conteggio dei processi per ogni utente con un ruolo
process_count = {}

# Scansiona la directory /proc/*/status per ottenere l'UID di ciascun processo
for status_file in os.listdir('/proc'):
    if status_file.isdigit():
        uid = None
        with open(f'/proc/{status_file}/status') as f:
            for line in f:
                if line.startswith('Uid:'):
                    uid = int(line.split()[1])
                    break

        if uid is not None:
            username = None
            with open('/etc/passwd') as passwd_file:
                for passwd_line in passwd_file:
                    if int(passwd_line.split(':')[2]) == uid:
                        username = passwd_line.split(':')[0]
                        break

            if username is not None:
                if username not in process_count:
                    process_count[username] = 0
                process_count[username] += 1

# Stampa il conteggio dei processi per ogni utente con un ruolo
for username, count in process_count.items():
    print(f"Utente: {username}, Processi attivi: {count}")
"""