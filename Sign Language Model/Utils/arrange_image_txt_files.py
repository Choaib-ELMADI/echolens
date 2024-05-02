import os
import shutil

image_folder = "C:\\Users\\Choaib ELMADI\\Downloads\\D.I.F.Y\\Electronics\\Robotics\\6- EchoLens\\Sign Language Model\\Data 1\\test\\images\\images"
output_folder = "C:\\Users\\Choaib ELMADI\\Downloads\\D.I.F.Y\\Electronics\\Robotics\\6- EchoLens\\Sign Language Model\\Data 1\\test\\images\\labels"
text_folder = "C:\\Users\\Choaib ELMADI\\Downloads\\D.I.F.Y\\Electronics\\Robotics\\6- EchoLens\\Sign Language Model\\Data 1\\test\\labels"

for image_file in os.listdir(image_folder):
    text_file = os.path.splitext(image_file)[0] + ".txt"

    if os.path.isfile(os.path.join(text_folder, text_file)):
        shutil.move(
            os.path.join(text_folder, text_file), os.path.join(output_folder, text_file)
        )
