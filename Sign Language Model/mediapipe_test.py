from Model import test_model
import mediapipe as mp
import numpy as np
import cvzone
import cv2

text_background = (198, 63, 88)  # PURPLE
corner_color = (53, 53, 249)  # RED
text_color = (239, 239, 239)  # WHITE
border_color = (61, 147, 8)  # GREEN

mp_drawing_styles = mp.solutions.drawing_styles  # type: ignore
mp_drawing = mp.solutions.drawing_utils  # type: ignore
mp_hands = mp.solutions.hands  # type: ignore
hands = mp_hands.Hands(max_num_hands=1)

list_message = []
text_message = ""

stream_url = "http://192.168.169.196:81/stream"
cap = cv2.VideoCapture(0)

counter = 0
while True:
    _, frame = cap.read()
    # frame = cv2.flip(frame, 1)
    frame_copy = np.copy(frame)

    frame_copy = cv2.cvtColor(frame_copy, cv2.COLOR_BGR2RGB)

    results = hands.process(frame_copy)
    hand_keypoints = np.zeros(21 * 2)
    if results.multi_hand_landmarks:
        for hand_landmarks in results.multi_hand_landmarks:
            mp_drawing.draw_landmarks(
                image=frame,
                landmark_list=hand_landmarks,
                connections=mp_hands.HAND_CONNECTIONS,
            )
        hand_keypoints = np.array(
            [
                [landmark.x, landmark.y]
                for landmark in results.multi_hand_landmarks[0].landmark
            ]
        ).flatten()

    if counter % 30 == 0:
        gesture = test_model.predict_hand_gesture(hand_keypoints)

    if gesture != "_BLANK" and gesture not in list_message:
        list_message.append(gesture)
    if len(list_message) % 4 == 0:
        list_message.append("\n")
    text_message = " ".join(list_message)

    if text_message.strip() != "":
        y0, dy = 50, 50
        for i, line in enumerate(text_message.split("\n")):
            y = y0 + i * dy
            cvzone.putTextRect(
                frame,
                f"{line}",
                pos=(30, y),
                scale=1,
                thickness=1,
                colorT=text_color,
                colorR=text_background,
                font=cv2.FONT_HERSHEY_COMPLEX_SMALL,
                offset=8,
                border=1,
                colorB=text_color,
            )

    cv2.imshow("Frame", frame)

    counter += 1
    key = cv2.waitKey(1) & 0xFF
    if key == ord("c"):
        list_message = []
        text_message = ""
    if key == ord("q"):
        break

cap.release()
cv2.destroyAllWindows()
