from ultralytics import YOLO
from sort import *
import numpy as np
import cvzone
import math
import cv2

weight = "yolo_v8_n.pt"
weight_path = f"C:\\Users\\Choaib ELMADI\\Downloads\\D.I.F.Y\\Electronics\\Robotics\\6- EchoLens\\Sign Language Model\\Tests\\Weights\\{ weight }"
model = YOLO(weight_path)

classNames = [
    "person",
    "bicycle",
    "car",
    "motorbike",
    "aeroplane",
    "bus",
    "train",
    "truck",
    "boat",
    "traffic light",
    "fire hydrant",
    "stop sign",
    "parking meter",
    "bench",
    "bird",
    "cat",
    "dog",
    "horse",
    "sheep",
    "cow",
    "elephant",
    "bear",
    "zebra",
    "giraffe",
    "backpack",
    "umbrella",
    "handbag",
    "tie",
    "suitcase",
    "frisbee",
    "skis",
    "snowboard",
    "sports ball",
    "kite",
    "baseball bat",
    "baseball glove",
    "skateboard",
    "surfboard",
    "tennis racket",
    "bottle",
    "wine glass",
    "cup",
    "fork",
    "knife",
    "spoon",
    "bowl",
    "banana",
    "apple",
    "sandwich",
    "orange",
    "broccoli",
    "carrot",
    "hot dog",
    "pizza",
    "donut",
    "cake",
    "chair",
    "sofa",
    "pottedplant",
    "bed",
    "diningtable",
    "toilet",
    "tvmonitor",
    "laptop",
    "mouse",
    "remote",
    "keyboard",
    "cell phone",
    "microwave",
    "oven",
    "toaster",
    "sink",
    "refrigerator",
    "book",
    "clock",
    "vase",
    "scissors",
    "teddy bear",
    "hair drier",
    "toothbrush",
]

cap = cv2.VideoCapture(0)
WIDTH = 640
HEIGHT = 480

text_background = (198, 63, 88)
corner_color = (53, 53, 249)
text_color = (239, 239, 239)
border_color = (61, 147, 8)

tracker = Sort(max_age=20)

while True:
    _, frame = cap.read()
    frame = cv2.resize(frame, (WIDTH, HEIGHT))

    results = model(frame, stream=True)
    detections = np.empty([0, 5])
    object_class = ""

    for result in results:
        boxes = result.boxes

        for box in boxes:
            conf = math.floor((box.conf[0] * 100))
            class_id = int(box.cls[0])
            object_class = classNames[class_id].capitalize()

            if conf > 50:
                x1, y1, x2, y2 = box.xyxy[0]
                x1, y1, w, h = int(x1), int(y1), int(x2 - x1), int(y2 - y1)
                current = np.array([x1, y1, x2, y2, conf])
                detections = np.vstack((detections, current))

    tracker_results = tracker.update(detections)
    for x1, y1, x2, y2, ID in tracker_results:
        x1, y1, w, h = int(x1), int(y1), int(x2 - x1), int(y2 - y1)
        cvzone.cornerRect(
            frame,
            [x1, y1, w, h],
            t=3,
            rt=2,
            colorR=border_color,
            colorC=corner_color,
        )
        cvzone.putTextRect(
            frame,
            f"{ object_class }: { int(ID) }",
            pos=(max(8, x1 + 6), max(23, y1 - 12)),
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
    if cv2.waitKey(1) & 0xFF == ord("q"):
        break

cap.release()
cv2.destroyAllWindows()
