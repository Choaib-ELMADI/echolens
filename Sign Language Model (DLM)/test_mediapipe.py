import mediapipe as mp
import numpy as np
import cv2

mp_drawing_styles = mp.solutions.drawing_styles  # type: ignore
mp_drawing = mp.solutions.drawing_utils  # type: ignore
mp_hands = mp.solutions.hands  # type: ignore
hands = mp_hands.Hands(max_num_hands=1)

stream_url = "http://192.168.169.196:81/stream"
cap = cv2.VideoCapture(0)
frame_counter = 0

while True:
    _, frame = cap.read()
    frame = cv2.flip(frame, 1)
    frame_copy = np.copy(frame)

    frame_copy = cv2.cvtColor(frame_copy, cv2.COLOR_BGR2RGB)

    results = hands.process(frame_copy)
    hand_keypoints = np.zeros(21 * 3)
    if results.multi_hand_landmarks:
        for hand_landmarks in results.multi_hand_landmarks:
            mp_drawing.draw_landmarks(
                image=frame,
                landmark_list=hand_landmarks,
                connections=mp_hands.HAND_CONNECTIONS,
            )
        hand_keypoints = np.array(
            [
                [landmark.x, landmark.y, landmark.z]
                for landmark in results.multi_hand_landmarks[0].landmark
            ]
        ).flatten()

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
