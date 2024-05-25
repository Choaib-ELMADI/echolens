import pandas as pd
import numpy as np
import joblib  # type: ignore

print("Loading...")

labels_name = "data_label"
labels_path = f"C:\\Users\\Choaib ELMADI\\Downloads\\D.I.F.Y\\Electronics\\Robotics\\6- EchoLens\\Sign Language Model\\Model\\{ labels_name }.csv"
labels = pd.read_csv(labels_path)

model_name = "sign_language_model"
model_path = f"C:\\Users\\Choaib ELMADI\\Downloads\\D.I.F.Y\\Electronics\\Robotics\\6- EchoLens\\Sign Language Model\\Model\\{ model_name }.joblib"
model = joblib.load(model_path)


def predict_hand_gesture(hand, lang):
    hand_reshaped = np.array(hand).reshape(1, -1)
    predictions = model.predict(hand_reshaped)
    class_id = int(predictions[0])
    return labels.iloc[class_id][lang]


if __name__ == "__main__":
    print("Loaded.")

    print(
        predict_hand_gesture(
            [
                0.9098092913627625,
                0.853937566280365,
                0.7992395758628845,
                0.8102204203605652,
                0.720649778842926,
                0.6693232655525208,
                0.6704489588737488,
                0.5307231545448303,
                0.6099956035614014,
                0.42946603894233704,
                0.7358801364898682,
                0.4741051197052002,
                0.6357476711273193,
                0.314233660697937,
                0.5781445503234863,
                0.2196536660194397,
                0.5352472066879272,
                0.14001449942588806,
                0.7619896531105042,
                0.4674549400806427,
                0.6666906476020813,
                0.31606975197792053,
                0.6016435027122498,
                0.22936466336250305,
                0.5551912188529968,
                0.15628385543823242,
                0.774957537651062,
                0.484797865152359,
                0.6890199184417725,
                0.3518107831478119,
                0.6281329989433289,
                0.27086132764816284,
                0.5847030878067017,
                0.19858065247535706,
                0.7760987281799316,
                0.5045469403266907,
                0.7081763744354248,
                0.3901268243789673,
                0.658607006072998,
                0.3274117708206177,
                0.6213232278823853,
                0.2722306549549103,
            ],
            "FR",
        )
    )
