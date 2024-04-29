#include "camera_index.h"
#include "camera_pins.h"
#include "esp_camera.h"
#include <WebServer.h>
#include <WiFi.h>

// const char *ssid = "TL-MR110  5G";
const char *ssid = "Choaibs-Phone";
// const char *password = "UMRA2024";
const char *password = "devchoaib";

char XML[1024];
char buffer[32];

bool isShowingStream = false;
bool isListening = false;
bool isTalking = false;
int ledIntensity = 125;
char generatedText[30] = "empty";
uint32_t lastDataMillis = 0;

const uint8_t greenLED = 2;
const uint8_t yellowLED = 14;
const long greenLEDInterval = 1000;
const long yellowLEDInterval = 500;
unsigned long previousMillisArray[2] = {0, 0};
bool ledStateArray[2] = {LOW, LOW};

WebServer server(80);

void setupCamera();
camera_config_t setupConfiguration();
void connectToWiFi();
void startCameraServer();

void setup() {
    Serial.begin(115200);

    setupCamera();
    Serial.println("Done setup camera.");

    connectToWiFi();
    Serial.println("Done connect WiFi.");

    pinMode(greenLED, OUTPUT);
    pinMode(yellowLED, OUTPUT);

    server.on("/", sendMainPage);
    server.on("/xml", sendXmlData);
    server.on("/UPDATE_INTENSITY", sliderIntensityUpdate);
    server.on("/TOGGLE_VIEW_STREAM", toggleViewStream);
    server.on("/TOGGLE_LISTENING", toggleListening);
    server.on("/TOGGLE_TALKING", toggleTalking);

    server.begin();
}

void loop() {
    blinkLED(greenLED, greenLEDInterval, 0);
    blinkLED(yellowLED, yellowLEDInterval, 1);

    server.handleClient();
}

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

void printData() {
    Serial.print("Showing stream: ");
    Serial.print(isShowingStream);

    Serial.print(", Listening: ");
    Serial.print(isListening);

    Serial.print(", Talking: ");
    Serial.print(isTalking);

    Serial.print(", Intensity: ");
    Serial.print(ledIntensity);

    Serial.print(", Text: ");
    Serial.println(generatedText);
}

void sendMainPage() { server.send(200, "text/html", htmlWebPage); }
void sendXmlData() {
    // sprintf(buffer, "<V0>%d.%d</V0>\n", (int)(voltsA0),
    // abs((int)(voltsA0 * 10) - ((int)(voltsA0)*10)));
    // strcat(XML, buffer);

    strcpy(XML, "<?xml version = '1.0'?>\n<Data>\n");

    if (isShowingStream) {
        strcat(XML, "<StreamState>1</StreamState>\n");
    } else {
        strcat(XML, "<StreamState>0</StreamState>\n");
    }

    if (isListening) {
        strcat(XML, "<ListeningState>1</ListeningState>\n");
    } else {
        strcat(XML, "<ListeningState>0</ListeningState>\n");
    }

    if (isTalking) {
        strcat(XML, "<TalkingState>1</TalkingState>\n");
    } else {
        strcat(XML, "<TalkingState>0</TalkingState>\n");
    }

    strcat(XML, "</Data>\n");

    server.send(200, "text/xml", XML);
}

void toggleViewStream() {
    isShowingStream = !isShowingStream;
    isListening = false;
    isTalking = false;

    server.send(200, "text/plain", "");
}
void toggleListening() {
    isListening = !isListening;
    isShowingStream = false;
    isTalking = false;

    server.send(200, "text/plain", "");
}
void toggleTalking() {
    isTalking = !isTalking;
    isShowingStream = false;
    isListening = false;

    server.send(200, "text/plain", "");
}
void sliderIntensityUpdate() {
    String intensityString = server.arg("intensity");
    ledIntensity = intensityString.toInt();

    server.send(200, "text/plain", "");
}

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
