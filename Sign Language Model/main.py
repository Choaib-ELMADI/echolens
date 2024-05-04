from ultralytics import YOLO
import cvzone
import os
import cv2
import math

weight_path = os.path.join("Train Results (1000epochs)", "weights", "best.pt")
model = YOLO(weight_path)
last_boxes = []

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

stream_url = 0  # "http://192.168.169.196:81/stream"  # 0
cap = cv2.VideoCapture(stream_url)

frame_counter = 0
while True:
    _, frame = cap.read()

    if frame_counter % 10 == 0:
        results = model(frame, stream=True, max_det=1)
        for r in results:
            for box in r.boxes:
                class_id = int(box.cls[0])
                conf = math.floor(box.conf[0] * 100)
                last_boxes = [
                    (
                        box,
                        conf,
                        class_id,
                    )
                ]

                if classNames[class_id] not in list_message:
                    list_message.append(classNames[class_id])

                if len(list_message) % 4 == 0:
                    list_message.append("\n")

    for box, conf, class_id in last_boxes:
        if len(list_message) > 0:
            text_message = " ".join(list_message)
            y0, dy = 50, 50
            for i, line in enumerate(text_message.split("\n")):
                y = y0 + i * dy
                cvzone.putTextRect(
                    frame,
                    f"{line}",
                    # pos=(max(8, x1 + 6), max(23, y1 - 12)),
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
