from ultralytics import YOLO
import cv2

image = "1.png"
image_path = f"C:\\Users\\Choaib ELMADI\\Downloads\\D.I.F.Y\\Electronics\\Robotics\\6- EchoLens\\Sign Language Model\\Tests\\Images\\{ image }"

weight = "yolo_v8_n.pt"
weight_path = f"C:\\Users\\Choaib ELMADI\\Downloads\\D.I.F.Y\\Electronics\\Robotics\\6- EchoLens\\Sign Language Model\\Tests\\Weights\\{ weight }"
model = YOLO(weight_path)

results = model(image_path, show=True)
cv2.waitKey(0)
