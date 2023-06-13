#!/usr/bin/env python3

import os
import sys
import shutil

# funzione ricorsiva per fare il merge di 2 dir
def merge(path1, path2, path3):
    # copia path1 in path3
    shutil.copytree(path1, path3)

    # copia path2 in path3
    for root, directories, files in os.walk(path2):
        relative_path = os.path.relpath(root, path2)
        destination_dir = os.path.join(path3, relative_path)

        # Crea la directory nella destinazione se non esiste già
        if not os.path.exists(destination_dir):
            os.makedirs(destination_dir)

        # Copia i file mancanti
        for file in files:
            source_file_path = os.path.join(root, file)
            destination_file_path = os.path.join(destination_dir, file)

            # Se il file esiste già nella destinazione, concatena i contenuti
            if os.path.exists(destination_file_path):
                with open(destination_file_path, 'a') as dest_file, open(source_file_path, 'r') as source_file:
                    dest_file.write(source_file.read())
            else:
                shutil.copy2(source_file_path, destination_file_path)




if __name__ == "__main__":
    merge(sys.argv[1], sys.argv[2], sys.argv[3])


# esame 23-01-19
