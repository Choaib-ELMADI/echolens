from ultralytics import YOLO
import cvzone
import os
import cv2
import math

weight_path = os.path.join("Train Results", "weights", "best.pt")
model = YOLO(weight_path)

classNames = [
    "You",
    "Yes",
    "WhatAreYouDoing",
    "TryBeing",
    "ToMeet",
    "ThankYou",
    "TakeCare",
    "SameAsYou",
    "Question",
    "Point",
    "Nothing",
    "IHear",
]
text_background = (198, 63, 88)
corner_color = (53, 53, 249)
text_color = (239, 239, 239)
border_color = (61, 147, 8)
text_message = ""
list_message = []

stream_url = "http://192.168.169.196:81/stream"  # 0
cap = cv2.VideoCapture(stream_url)

frame_counter = 0
while True:
    _, frame = cap.read()
    results = model(frame, stream=True, max_det=1)

    for r in results:
        for box in r.boxes:
            x1, y1, x2, y2 = box.xyxy[0]
            x1, y1, w, h = int(x1), int(y1), int(x2 - x1), int(y2 - y1)
            conf = math.floor(box.conf[0] * 100) / 100
            class_id = int(box.cls[0])
            cvzone.cornerRect(
                frame,
                (x1, y1, w, h),
                10,
                2,
                1,
                colorR=text_background,
                colorC=text_color,
            )
            cvzone.putTextRect(
                frame,
                classNames[class_id],
                (x1, y1 - 5),
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

    frame_counter += 1
    if frame_counter == cap.get(cv2.CAP_PROP_FRAME_COUNT):
        frame_counter = 0
        cap.set(cv2.CAP_PROP_POS_FRAMES, 0)

    key = cv2.waitKey(1)
    if key & 0xFF == ord("q"):
        break

cap.release()
cv2.destroyAllWindows()
