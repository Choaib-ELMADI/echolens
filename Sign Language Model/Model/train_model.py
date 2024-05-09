from sklearn.tree import DecisionTreeClassifier
import pandas as pd
import joblib
import warnings

warnings.filterwarnings("ignore", category=UserWarning, module="sklearn")


def train_new_model(data_path, model_output):
    df = pd.read_csv(data_path, header=None)
    df = df.iloc[:, 1:]

    X = df.iloc[:, 1:]
    y = df.iloc[:, 0]

    model = DecisionTreeClassifier()
    model.fit(X, y)
    joblib.dump(model, model_output)

    print(f"Model Trained: '{model_output}")


data_name = "dead_data"
data_path = f"C:\\Users\\Choaib ELMADI\\Downloads\\D.I.F.Y\\Electronics\\Robotics\\6- EchoLens\\Sign Language Model\\Model\\{ data_name }.csv"

model_name = "dead_model"
model_output = f"C:\\Users\\Choaib ELMADI\\Downloads\\D.I.F.Y\\Electronics\\Robotics\\6- EchoLens\\Sign Language Model\\Model\\{ model_name }.joblib"


train_new_model(data_path, model_output)
