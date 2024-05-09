import pandas as pd
import numpy as np
import joblib  # type: ignore

labels_name = "data_label"
labels_path = f"C:\\Users\\Choaib ELMADI\\Downloads\\D.I.F.Y\\Electronics\\Robotics\\6- EchoLens\\Sign Language Model\\Model\\{ labels_name }.csv"
labels = pd.read_csv(labels_path, header=None)

model_name = "sign_language_model"
model_path = f"C:\\Users\\Choaib ELMADI\\Downloads\\D.I.F.Y\\Electronics\\Robotics\\6- EchoLens\\Sign Language Model\\Model\\{ model_name }.joblib"
model = joblib.load(model_path)


def predict_hand_gesture(hand):
    hand_reshaped = np.array(hand).reshape(1, -1)
    predictions = model.predict(hand_reshaped)
    class_id = int(predictions[0])
    return labels.iloc[class_id, 0]


if __name__ == "__main__":
    print(
        predict_hand_gesture(
            [
                1,
                0,
                0,
                0,
                0,
                0,
                0,
                0,
                0,
                0,
                0,
                0,
                0,
                0,
                0,
                0,
                0,
                0,
                0,
                1,
                0,
                0,
                0,
                0,
                0,
                0,
                0,
                0,
                0,
                0,
                0,
                0,
                0,
                0,
                0,
                0,
                0,
                0,
                0,
                0,
                0,
                0,
            ]
        )
    )
