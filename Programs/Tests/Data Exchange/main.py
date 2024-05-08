import requests
import time

text_data = "Hello, ESP32-CAM!"
url = f"http://192.168.169.196/SIGN_TEXT_DATA?data={ text_data }"

while True:
    response = requests.post(url)

    if response.status_code == 200:
        print("Text data sent successfully to ESP32-CAM!")
    else:
        print("Failed to send text data to ESP32-CAM.")

    time.sleep(1)
