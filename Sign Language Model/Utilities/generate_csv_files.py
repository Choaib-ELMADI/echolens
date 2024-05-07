import pandas as pd
import numpy as np
import os

folder_path = "C:\\Users\\Choaib ELMADI\\Pictures\\Pictures\\TEST 2"

file_list = [f for f in os.listdir(folder_path) if f.endswith(".npy")]

arrays = []

for file_name in file_list:
    file_path = os.path.join(folder_path, file_name)
    array = np.load(file_path)
    filtered_array = np.delete(array, np.arange(2, len(array), 3))
    generated_array = np.insert(filtered_array, 0, 123)
    arrays.append(generated_array)

combined_array = np.vstack(arrays)

df = pd.DataFrame(combined_array)

output_csv_path = "C:\\Users\\Choaib ELMADI\\Pictures\\Pictures\\TEST 2\\output-3.csv"

df.to_csv(output_csv_path)

print("CSV file created successfully.")
