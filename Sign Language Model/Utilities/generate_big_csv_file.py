import pandas as pd
import numpy as np
import os

main_folder_path = "C:\\Users\\Choaib ELMADI\\Downloads\\D.I.F.Y\\Electronics\\Robotics\\6- EchoLens\\Sign Language Model (DLM)\\Data"
output_csv_path = "C:\\Users\\Choaib ELMADI\\Downloads\\D.I.F.Y\\Electronics\\Robotics\\6- EchoLens\\Sign Language Model (DLM)\\Data\\data.csv"
folders_collection = {
    "_BLANK": 0,
    "Bye": 1,
    "Good": 2,
    "Hello": 3,
    "HowAreYou": 4,
    "IHear": 5,
    "Nothing": 6,
    "Point": 7,
    "Question": 8,
    "SameAsYou": 9,
    "TakeCare": 10,
    "ThankYou": 11,
    "ToMeet": 12,
    "TryBeing": 13,
    "WhatAreYouDoing": 14,
    "Yes": 15,
}

arrays = []
for folder_name in os.listdir(main_folder_path):
    folder_path = os.path.join(main_folder_path, folder_name)
    if os.path.isdir(folder_path):
        folder_number = folders_collection.get(folder_name, -1)
        for subfolder_name in os.listdir(folder_path):
            subfolder_path = os.path.join(folder_path, subfolder_name)
            if os.path.isdir(subfolder_path):
                for file_name in os.listdir(subfolder_path):
                    if file_name.endswith(".npy"):
                        file_path = os.path.join(subfolder_path, file_name)
                        array = np.load(file_path)
                        filtered_array = np.delete(array, np.arange(2, len(array), 3))
                        generated_array = np.insert(filtered_array, 0, folder_number)
                        arrays.append(generated_array)

combined_array = np.vstack(arrays)
df = pd.DataFrame(combined_array)
df.to_csv(output_csv_path)

print("CSV file created successfully.")
