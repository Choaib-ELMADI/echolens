import cv2

url = "http://192.168.1.103"
stream = url + ":81/stream"
cap = cv2.VideoCapture(stream)
# cap.set(3, 640)  # set width
# cap.set(4, 480)  # set height

while True:
    _, frame = cap.read()
    cv2.imshow("Stream", frame)

    key = cv2.waitKey(1)
    if key & 0xFF == ord("s"):
        cv2.imwrite("uxga__img.jpg", frame)
        print("Save")

    if key & 0xFF == ord("q"):
        break

cap.release()
cv2.destroyAllWindows()
