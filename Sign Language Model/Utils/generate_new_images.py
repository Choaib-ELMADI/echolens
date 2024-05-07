from image_color_shift import random_color_shift
import cv2
import os


input_folder = "C:\\Users\\Choaib ELMADI\\Downloads\\D.I.F.Y\\Electronics\\Robotics\\6- EchoLens\\Sign Language Model\\Data 1\\valid\\images"

for filename in os.listdir(input_folder):
    if filename.endswith(".jpg") or filename.endswith(".png"):
        image_path = os.path.join(input_folder, filename)

        modified_image = random_color_shift(image_path)
        new_filename = filename.split(".")[0] + "__r." + filename.split(".")[1]

        output_path = os.path.join(input_folder, new_filename)
        cv2.imwrite(output_path, modified_image)

        # print(f"Saved: {new_filename}")

print("Done.")
