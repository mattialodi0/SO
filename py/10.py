import sys, os


def indent():
    path = sys.argv[1]

    for (root, dirs, files) in os.walk(path):
        for file in files:
            tokens = file.split('.')
            if tokens[-1] == 'c' or tokens[-1] == 'h':
                filepath = os.path.join(root, file)
                print(f"indented: {filepath}")
                os.system(f"ex -n '+norm!gg=G' +wq {filepath}")


if __name__ == "__main__":
    indent()