import requests
import urllib.parse
import time

text_data = "Hello, ESP32-CAM!"
url = "http://192.168.169.196/GET_TEXT_SIGN"

while True:
    encoded_text_data = urllib.parse.quote(text_data)
    full_url = f"{url}?signs={encoded_text_data}"
    response = requests.post(full_url)

    if response.status_code == 200:
        print("Text data sent successfully to ESP32-CAM!")
    else:
        print("Failed to send text data to ESP32-CAM.")

    time.sleep(1)
