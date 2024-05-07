import mediapipe as mp
import numpy as np
import cv2

mp_holistic = mp.solutions.holistic  # type: ignore
mp_drawing = mp.solutions.drawing_utils  # type: ignore
mp_hands = mp.solutions.hands  # type: ignore


def mediapipe_detections(frame, model):
    frame = cv2.cvtColor(frame, cv2.COLOR_BGR2RGB)
    frame.flags.writeable = False
    results = model.process(frame)
    frame.flags.writeable = True
    frame = cv2.cvtColor(frame, cv2.COLOR_RGB2BGR)

    return frame, results


def draw_landmarks(frame, results, color):
    if results.multi_hand_landmarks:
        for hand_landmarks in results.multi_hand_landmarks:
            mp_drawing.draw_landmarks(frame, hand_landmarks, mp_hands.HAND_CONNECTIONS)


def extract_keypoints(results):
    right_hand = (
        np.array(
            [[r.x, r.y, r.z] for r in results.right_hand_landmarks.landmark]
        ).flatten()
        if results.right_hand_landmarks
        else np.zeros(63)
    )

    left_hand = (
        np.array(
            [[r.x, r.y, r.z] for r in results.left_hand_landmarks.landmark]
        ).flatten()
        if results.left_hand_landmarks
        else np.zeros(63)
    )

    return right_hand, left_hand
