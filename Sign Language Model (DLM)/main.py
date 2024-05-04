# 0. Installation
# 1. Import Libraries
# 2. Read the Camera Feed
# 3. Keypoints with MP Holistic

from matplotlib import pyplot as plt
import mediapipe as mp
import numpy as np
import time
import cv2
import os

text_background = (198, 63, 88)  # PURPLE
corner_color = (53, 53, 249)  # RED
text_color = (239, 239, 239)  # WHITE
border_color = (61, 147, 8)  # GREEN

mp_holistic = mp.solutions.holistic  # type: ignore
mp_drawing = mp.solutions.drawing_utils  # type: ignore


def mediapipe_detections(frame, model):
    frame = cv2.cvtColor(frame, cv2.COLOR_BGR2RGB)
    frame.flags.writeable = False
    results = model.process(frame)
    frame.flags.writeable = True
    frame = cv2.cvtColor(frame, cv2.COLOR_RGB2BGR)

    return frame, results


def draw_landmarks(frame, results):
    mp_drawing.draw_landmarks(
        frame,
        results.left_hand_landmarks,
        mp_holistic.HAND_CONNECTIONS,
        mp_drawing.DrawingSpec(color=corner_color, thickness=2, circle_radius=2),
    )
    mp_drawing.draw_landmarks(
        frame,
        results.right_hand_landmarks,
        mp_holistic.HAND_CONNECTIONS,
        mp_drawing.DrawingSpec(color=corner_color, thickness=2, circle_radius=2),
    )


model = mp_holistic.Holistic(min_detection_confidence=0.5, min_tracking_confidence=0.5)

cap = cv2.VideoCapture(0)
# frame_counter = 0
# frame_counter += 1
# if frame_counter == cap.get(cv2.CAP_PROP_FRAME_COUNT):
#     frame_counter = 0
#     cap.set(cv2.CAP_PROP_POS_FRAMES, 0)

while True:
    _, frame = cap.read()
    frame = cv2.flip(frame, 1)

    frame, results = mediapipe_detections(frame, model)
    draw_landmarks(frame, results)

    cv2.imshow("Frame", frame)

    key = cv2.waitKey(1) & 0xFF
    if key == ord("q"):
        break

cap.release()
cv2.destroyAllWindows()
