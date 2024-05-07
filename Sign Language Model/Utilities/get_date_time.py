import os
import time

folder_path = "C:\\Users\\Choaib ELMADI\\Downloads\\D.I.F.Y\\Electronics\\Robotics\\6- EchoLens\\Sign Language Model\\Data 1\\test\\images"

for filename in os.listdir(folder_path):
    filepath = os.path.join(folder_path, filename)

    if os.path.isfile(filepath):
        modification_time = os.path.getmtime(filepath)
        formatted_time = time.strftime(
            "%Y-%m-%d %H:%M:%S", time.localtime(modification_time)
        )
        print(f"File: {filename}, Modification Time: {formatted_time}")
