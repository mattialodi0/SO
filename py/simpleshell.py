import sys, os, subprocess


def shell():
    while True:
        try:
            inn = input()
            cmd = inn.split(' ')

            if 'logout' in cmd:
                break

            res = subprocess.run(cmd, shell=False) #, capture_output=True, text=True
            """if res.stdout != "":
                print(res.stdout)
            if res.stderr != "":
                print(res.stderr)"""
        except KeyboardInterrupt:
            print(' error')
            continue
        except EOFError:
            print(' error')
        

if __name__ == "__main__":
    shell()

# esame 18-7-18
