import os
import shutil


def move_txt_files(images_folder, labels_folder):
    if not os.path.exists(labels_folder):
        os.makedirs(labels_folder)

    for filename in os.listdir(images_folder):
        if filename.endswith(".txt"):
            shutil.move(
                os.path.join(images_folder, filename),
                os.path.join(labels_folder, filename),
            )


if __name__ == "__main__":
    data_folder = "Data 1"
    set_name = "test"
    data_path = f"C:\\Users\\Choaib ELMADI\\Downloads\\D.I.F.Y\\Electronics\\Robotics\\6- EchoLens\\Sign Language Model\\{ data_folder }\\{ set_name }\\"
    images_folder = data_path + "images"
    labels_folder = data_path + "labels"

    print("Started...")
    move_txt_files(images_folder, labels_folder)
    print("Done.")
