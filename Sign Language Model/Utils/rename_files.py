import os

folder_path = "C:\\Users\\Choaib ELMADI\\Downloads\\D.I.F.Y\\Electronics\\Robotics\\6- EchoLens\\Sign Language Model\\Data 1\\READY TRAIN 2\\images"

files = os.listdir(folder_path)

for file in files:
    if "valid" in file:
        new_file_name = file.replace("valid", "train")

        old_file_path = os.path.join(folder_path, file)
        new_file_path = os.path.join(folder_path, new_file_name)

        os.rename(old_file_path, new_file_path)
