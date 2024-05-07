import os

actions = [
    "Yes",
    "WhatAreYouDoing",
    "TryBeing",
    "ToMeet",
    "ThankYou",
    "TakeCare",
    "SameAsYou",
    "Question",
    "Point",
    "Nothing",
    "IHear",
    "HowAreYou",
    "Hello",
    "Bye",
    "Good",
]

for action in actions:
    folder_path = f"C:\\Users\\Choaib ELMADI\\Downloads\\D.I.F.Y\\Electronics\\Robotics\\6- EchoLens\\Sign Language Model (DLM)\\Data\\{ action }"

    for i in range(20):
        old_folder_name = os.path.join(folder_path, f"{i} - Copy")
        new_folder_name = os.path.join(folder_path, f"{i + 20}")
        os.rename(old_folder_name, new_folder_name)

    print(f"Done for { action }")

print("Done.")
