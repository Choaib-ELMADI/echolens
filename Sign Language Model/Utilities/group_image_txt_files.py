import os
import shutil

images_path = "C:\\Users\\Choaib ELMADI\\Downloads\\D.I.F.Y\\Electronics\\Robotics\\6- EchoLens\\Sign Language Model\\Data 1\\READY TRAIN 2\\images"
labels_path_src = "C:\\Users\\Choaib ELMADI\\Downloads\\D.I.F.Y\\Electronics\\Robotics\\6- EchoLens\\Sign Language Model\\Data 1\\valid\\labels"
labels_path_dst = "C:\\Users\\Choaib ELMADI\\Downloads\\D.I.F.Y\\Electronics\\Robotics\\6- EchoLens\\Sign Language Model\\Data 1\\READY TRAIN 2\\labels"

files = os.listdir(images_path)

for file in files:
    if file.endswith(".jpg"):
        txt_file = os.path.splitext(file)[0] + ".txt"
        txt_file_path = os.path.join(labels_path_src, txt_file)

        if os.path.exists(txt_file_path):
            shutil.move(txt_file_path, os.path.join(labels_path_dst, txt_file))
            print(f"Moved {txt_file} next to {file}")
        else:
            print(f"Warning: No matching txt file found for {file}")
