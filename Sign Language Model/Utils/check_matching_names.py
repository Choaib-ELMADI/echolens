import os
import time


def check_matching_names(images_folder, labels_folder):
    image_files = sorted([f[:-4] for f in os.listdir(images_folder)])
    txt_files = sorted([f[:-4] for f in os.listdir(labels_folder)])

    if not txt_files:
        print("No text files found in the labels folder.")
        return False

    for image_name, txt_name in zip(image_files, txt_files):
        print(image_name)
        print(txt_name)
        print("-----------------")
        # time.sleep(0.5)

        if image_name != txt_name:
            return False

    return True


if __name__ == "__main__":
    images_folder = "C:\\Users\\Choaib ELMADI\\Downloads\\D.I.F.Y\\Electronics\\Robotics\\6- EchoLens\\Sign Language Model\\Data 1\\READY TRAIN 2\\images"
    labels_folder = "C:\\Users\\Choaib ELMADI\\Downloads\\D.I.F.Y\\Electronics\\Robotics\\6- EchoLens\\Sign Language Model\\Data 1\\READY TRAIN 2\\labels"

    if check_matching_names(images_folder, labels_folder):
        print("All file names match.")
    else:
        print("File names do not match.")
