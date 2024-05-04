import mediapipe as mp
import numpy as np
import cv2

mp_drawing_styles = mp.solutions.drawing_styles  # type: ignore
mp_drawing = mp.solutions.drawing_utils  # type: ignore
mp_hands = mp.solutions.hands  # type: ignore
hands = mp_hands.Hands()

stream_url = 0  # "http://192.168.169.196:81/stream"
cap = cv2.VideoCapture(stream_url)

frame_counter = 0
while True:
    _, frame = cap.read()
    frame = cv2.flip(frame, 1)
    frame_copy = np.copy(frame)

    frame_copy = cv2.cvtColor(frame_copy, cv2.COLOR_BGR2RGB)

    results = hands.process(frame_copy)
    if results.multi_hand_landmarks:
        for hand_landmarks in results.multi_hand_landmarks:
            mp_drawing.draw_landmarks(frame, hand_landmarks, mp_hands.HAND_CONNECTIONS)

    cv2.imshow("Frame", frame)

    frame_counter += 1
    if frame_counter == cap.get(cv2.CAP_PROP_FRAME_COUNT):
        frame_counter = 0
        cap.set(cv2.CAP_PROP_POS_FRAMES, 0)

    key = cv2.waitKey(1) & 0xFF
    if key == ord("q"):
        break

cap.release()
cv2.destroyAllWindows()
