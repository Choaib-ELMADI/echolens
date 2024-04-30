from ultralytics import YOLO
import numpy as np
import cvzone
import os
import cv2
import math

weight_path = os.path.join("Weights", "best__200epochs.pt")
model = YOLO(weight_path)

classNames = ["thumsup", "thumsdown", "thankyou", "livelong"]
text_background = (198, 63, 88)
corner_color = (53, 53, 249)
text_color = (239, 239, 239)
border_color = (61, 147, 8)
text_message = ""
list_message = []

stream_url = 0  # "http://192.168.169.196:81/stream"
cap = cv2.VideoCapture(stream_url)

frame_counter = 0
while True:
    _, frame = cap.read()
    frame = cv2.resize(frame, (640, 640))
    frame = cv2.flip(frame, 1)
    frame_copy = np.copy(frame)

    if frame_counter % 10 == 0:
        results = model(frame_copy, stream=True, max_det=1)

        for r in results:
            boxes = r.boxes
            for box in boxes:
                conf = math.floor((box.conf[0] * 100))
                class_id = int(box.cls[0])
                object_class = classNames[class_id].capitalize()

                if object_class not in list_message:
                    list_message.append(object_class)

                text_message = " ".join(list_message)

                x1, y1, x2, y2 = box.xyxy[0]
                x1, y1, w, h = int(x1), int(y1), int(x2 - x1), int(y2 - y1)
                # cvzone.cornerRect(
                #     frame_copy,
                #     [x1, y1, w, h],
                #     t=3,
                #     rt=2,
                #     colorR=border_color,
                #     colorC=corner_color,
                # )
                cvzone.putTextRect(
                    frame_copy,
                    f"{text_message}",
                    # pos=(max(8, x1 + 6), max(23, y1 - 12)),
                    pos=(30, 30),
                    scale=1,
                    thickness=1,
                    colorT=text_color,
                    colorR=text_background,
                    font=cv2.FONT_HERSHEY_COMPLEX_SMALL,
                    offset=8,
                    border=1,
                    colorB=text_color,
                )

                cv2.imshow("Processed Frame", frame_copy)

    cv2.imshow("Frame", frame)

    frame_counter += 1
    if frame_counter == cap.get(cv2.CAP_PROP_FRAME_COUNT):
        frame_counter = 0
        cap.set(cv2.CAP_PROP_POS_FRAMES, 0)

    key = cv2.waitKey(1)
    if key & 0xFF == ord("c"):
        list_message = []
        text_message = ""
    if key & 0xFF == ord("q"):
        break

cap.release()
cv2.destroyAllWindows()
