import numpy as np
import os

data_folder = "C:\\Users\\Choaib ELMADI\\Downloads\\D.I.F.Y\\Electronics\\Robotics\\6- EchoLens\\Sign Language Model (DLM)\\Data"


def all_zero(array):
    return np.all(array == 0)


counter = 0
for root, dirs, files in os.walk(data_folder):
    for file in files:
        if file.endswith(".npy"):
            file_path = os.path.join(root, file)
            data = np.load(file_path)
            if all_zero(data):
                # print(f"File {file_path} contains all zero values.")
                counter += 1
                print(counter)

print("Done.")
