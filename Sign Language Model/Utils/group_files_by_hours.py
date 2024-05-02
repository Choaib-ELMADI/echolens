import os
import time
import shutil

folder_path = "C:\\Users\\Choaib ELMADI\\Downloads\\D.I.F.Y\\Electronics\\Robotics\\6- EchoLens\\Sign Language Model\\Data 1\\test\\images"

images_by_hour = {hour: [] for hour in range(11, 20)}

for filename in os.listdir(folder_path):
    filepath = os.path.join(folder_path, filename)

    if os.path.isfile(filepath):
        modification_time = os.path.getmtime(filepath)
        modification_hour = time.localtime(modification_time).tm_hour

        if modification_hour in range(11, 20):
            images_by_hour[modification_hour].append(filename)

for hour, images in images_by_hour.items():
    hour_folder_path = os.path.join(folder_path, str(hour))
    os.makedirs(hour_folder_path, exist_ok=True)

    for image in images:
        src_path = os.path.join(folder_path, image)
        dst_path = os.path.join(hour_folder_path, image)
        shutil.copy2(src_path, dst_path)
