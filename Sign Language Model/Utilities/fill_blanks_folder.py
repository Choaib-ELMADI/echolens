import numpy as np
import os

blank_folder_path = "C:\\Users\\Choaib ELMADI\\Downloads\\D.I.F.Y\\Electronics\\Robotics\\6- EchoLens\\Sign Language Model (DLM)\\Data\\_BLANK"

for folder in range(20):
    subfolder_path = os.path.join(blank_folder_path, str(folder))
    os.makedirs(subfolder_path)

    for file in range(30):
        file_path = os.path.join(blank_folder_path, str(folder), f"{file}.npy")
        data = np.zeros(63)
        np.save(file_path, data)

print("Done.")
