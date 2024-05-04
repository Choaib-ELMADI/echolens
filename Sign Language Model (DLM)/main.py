from matplotlib import pyplot as plt
import mediapipe as mp
import numpy as np
import cv2
import os

from sklearn.model_selection import train_test_split  # type: ignore
from tensorflow.keras.utils import to_categorical  # type: ignore
from tensorflow.keras.models import Sequential  # type: ignore
from tensorflow.keras.layers import LSTM, Dense  # type: ignore
from tensorflow.keras.callbacks import TensorBoard  # type: ignore

from utils import *

DATA_PATH = os.path.join("Data")
actions = np.array(["Hello", "ThankYou", "Bye", "Nothing"])
no_sequences = 30
sequence_length = 30

text_background = (198, 63, 88)  # PURPLE
corner_color = (53, 53, 249)  # RED
text_color = (239, 239, 239)  # WHITE
border_color = (61, 147, 8)  # GREEN

mp_holistic = mp.solutions.holistic  # type: ignore
model = mp_holistic.Holistic(min_detection_confidence=0.5, min_tracking_confidence=0.5)

cap = cv2.VideoCapture(0)

while True:
    _, frame = cap.read()
    frame = cv2.flip(frame, 1)

    frame, results = mediapipe_detections(frame, model)
    draw_landmarks(frame, results, corner_color)
    cv2.imshow("Frame", frame)

    right_hand, left_hand = extract_keypoints(results)
    print("Right: ", right_hand)
    print("Left: ", left_hand)

    key = cv2.waitKey(1) & 0xFF
    if key == ord("q"):
        break

cap.release()
cv2.destroyAllWindows()
