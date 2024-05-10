#include "camera_index.h"
#include "camera_pins.h"
#include "esp_camera.h"
#include <WebServer.h>
#include <WiFi.h>

bool DEBUGGING = true;

const char *ssid = "Choaibs-Phone";
const char *password = "devchoaib";

bool isListening = false;
bool isTalking = false;
String signTextData = "_EMPTY_";
String selectedLang = "EN";
unsigned long lastDataMillis = 0;
const uint8_t delayTime = 250;

const uint8_t listeningLED = 14;
const uint8_t talkingLED = 2;
const long listeningLEDInterval = 250;
const long talkingLEDInterval = 250;
unsigned long previousMillisArray[2] = {0, 0};
bool ledStateArray[2] = {LOW, LOW};

WebServer server(80);

void setupCamera();
camera_config_t setupConfiguration();
void connectToWiFi();
void startCameraServer();

/**********************************/
/*             MAIN               */
/**********************************/
void setup() {
    Serial.begin(115200);

    setupCamera();
    Serial.println("Done setup camera.");

    connectToWiFi();
    Serial.println("Done connect WiFi.");

    pinMode(listeningLED, OUTPUT);
    pinMode(talkingLED, OUTPUT);

    server.on("/", sendMainPage);
    server.on("/GET_TEXT_SIGN", getTextSign);        // Get text from Py
    server.on("/SEND_TEXT_SIGN", sendTextSign);      // Send text to JS
    server.on("/TOGGLE_LISTENING", toggleListening); // Toggle listening
    server.on("/TOGGLE_TALKING", toggleTalking);     // Toggle talking
    server.on("/IS_TALKING", sendTalkingState);      // Send talking state to Py
    server.on("/GET_SELECTED_LANG", getSelectedLang);   // Get lang from JS
    server.on("/SEND_SELECTED_LANG", sendSelectedLang); // Send lang to Py

    server.begin();
}
void loop() {
    if (millis() - lastDataMillis >= delayTime) {
        lastDataMillis = millis();

        if (isListening) {
            blinkLED(listeningLED, listeningLEDInterval, 0);
            digitalWrite(talkingLED, LOW);
        }

        if (isTalking) {
            blinkLED(talkingLED, talkingLEDInterval, 1);
            digitalWrite(listeningLED, LOW);
        }

        if (DEBUGGING) {
            printData();
        }
    }

    server.handleClient();
}

/**********************************/
/*         WIFI & CAMERA          */
/**********************************/
void setupCamera() {
    camera_config_t config = setupConfiguration();

    esp_err_t err = esp_camera_init(&config);
    if (err != ESP_OK) {
        Serial.printf("Camera init failed with error 0x%x", err);
        return;
    }

    sensor_t *s = esp_camera_sensor_get();
    s->set_framesize(s, FRAMESIZE_VGA);
}
camera_config_t setupConfiguration() {
    camera_config_t config;

    config.ledc_channel = LEDC_CHANNEL_0;
    config.ledc_timer = LEDC_TIMER_0;
    config.pin_d0 = Y2_GPIO_NUM;
    config.pin_d1 = Y3_GPIO_NUM;
    config.pin_d2 = Y4_GPIO_NUM;
    config.pin_d3 = Y5_GPIO_NUM;
    config.pin_d4 = Y6_GPIO_NUM;
    config.pin_d5 = Y7_GPIO_NUM;
    config.pin_d6 = Y8_GPIO_NUM;
    config.pin_d7 = Y9_GPIO_NUM;
    config.pin_xclk = XCLK_GPIO_NUM;
    config.pin_pclk = PCLK_GPIO_NUM;
    config.pin_vsync = VSYNC_GPIO_NUM;
    config.pin_href = HREF_GPIO_NUM;
    config.pin_sccb_sda = SIOD_GPIO_NUM;
    config.pin_sccb_scl = SIOC_GPIO_NUM;
    config.pin_pwdn = PWDN_GPIO_NUM;
    config.pin_reset = RESET_GPIO_NUM;
    config.xclk_freq_hz = 10000000;
    config.frame_size = FRAMESIZE_VGA;
    config.pixel_format = PIXFORMAT_JPEG;
    config.grab_mode = CAMERA_GRAB_WHEN_EMPTY;
    config.fb_location = CAMERA_FB_IN_PSRAM;
    config.jpeg_quality = 16;
    config.fb_count = 1;

    return config;
}
void connectToWiFi() {
    WiFi.begin(ssid, password);
    WiFi.setSleep(false);

    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    Serial.println("");
    Serial.println("WiFi connected");

    startCameraServer();

    Serial.print("Camera Ready! Use 'http://");
    Serial.print(WiFi.localIP());
    Serial.println("' to connect");
}

/**********************************/
/*          DEBUGINNING           */
/**********************************/
void printData() {
    Serial.print("Listening: ");
    Serial.print(isListening);

    Serial.print(", Talking: ");
    Serial.print(isTalking);

    Serial.print(", data: ");
    Serial.print(signTextData);

    Serial.print(", lang: ");
    Serial.println(selectedLang);
}

/**********************************/
/*        RENDER WEBPAGE          */
/**********************************/
void sendMainPage() { server.send(200, "text/html", htmlWebPage); }

/**********************************/
/*      COMMUNICATION HERE        */
/**********************************/
void toggleListening() {
    String listeningState = server.arg("state");
    isListening = listeningState.toInt();
    server.send(200, "text/plain", "");
}
void toggleTalking() {
    String talkingState = server.arg("state");
    isTalking = talkingState.toInt();
    server.send(200, "text/plain", "");
}
void getTextSign() {
    signTextData = server.arg("signs");
    server.send(200, "text/plain", "");
}
void sendTextSign() { server.send(200, "text/plain", signTextData); }
void sendTalkingState() { server.send(200, "text/plain", String(isTalking)); }
void getSelectedLang() {
    selectedLang = server.arg("lang");
    server.send(200, "text/plain", "");
}
void sendSelectedLang() { server.send(200, "text/plain", selectedLang); }

/**********************************/
/*         FUNCTIONS HERE         */
/**********************************/
void blinkLED(uint8_t ledPin, long interval, uint8_t ledIndex) {
    if (millis() - previousMillisArray[ledIndex] >= interval) {
        previousMillisArray[ledIndex] = millis();

        if (ledStateArray[ledIndex] == LOW)
            ledStateArray[ledIndex] = HIGH;
        else
            ledStateArray[ledIndex] = LOW;

        digitalWrite(ledPin, ledStateArray[ledIndex]);
    }
}
