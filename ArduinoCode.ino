#define BLYNK_TEMPLATE_ID ""
#define BLYNK_TEMPLATE_NAME ""
#define BLYNK_AUTH_TOKEN ""

#define WIFI_SSID "" //wifi name
#define WIFI_PASS "" //wifi password

#include <WiFi.h>
#include <HTTPClient.h>
#include <BlynkSimpleEsp32.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Keypad.h>
#include <WidgetTerminal.h>

#define GAS_SENSOR 34
#define SWITCH_PIN 4
#define GREEN_LED 5
#define BLUE_LED 18
#define RED_LED 19

LiquidCrystal_I2C lcd(0x27, 16, 2);
WidgetTerminal terminal(V3); 

const byte ROWS = 4;
const byte COLS = 4;
char keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};
byte rowPins[ROWS] = {13, 12, 14, 27};
byte colPins[COLS] = {26, 25, 33, 32};
Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

String patientID = "";
bool idEntered = false;
bool systemBooted = false;
int entryNumber = 1; 

void setup() {
  Serial.begin(115200);

  pinMode(SWITCH_PIN, INPUT_PULLUP);
  pinMode(GREEN_LED, OUTPUT);
  pinMode(BLUE_LED, OUTPUT);
  pinMode(RED_LED, OUTPUT);

  digitalWrite(GREEN_LED, LOW);
  digitalWrite(BLUE_LED, LOW);
  digitalWrite(RED_LED, LOW);

  Wire.begin(21, 22);
  lcd.init();
  lcd.backlight();

  WiFi.begin(WIFI_SSID, WIFI_PASS);
  Blynk.begin(BLYNK_AUTH_TOKEN, WIFI_SSID, WIFI_PASS);
}

void loop() {
  Blynk.run();

  if (digitalRead(SWITCH_PIN) == HIGH) {
    if (systemBooted) {
      lcd.noBacklight();
      lcd.clear();
      systemBooted = false;
    }
    return;
  }

  if (!systemBooted) {
    lcd.backlight();
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("System Activated");
    delay(2000);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Enter Patient ID");
    lcd.setCursor(0, 1);
    lcd.print(" ");
    systemBooted = true;
  }

  if (!idEntered) {
    char key = keypad.getKey();
    if (key != NO_KEY) {
      delay(150);
      if (key >= '0' && key <= '9' && patientID.length() < 3) {
        patientID += key;
        lcd.setCursor(patientID.length() - 1, 1);
        lcd.print(key);
      } else if (key == '#') {
        patientID = "";
        lcd.setCursor(0, 1);
        lcd.print(" ");
      } else if (key == '*') {
        if (patientID.length() == 3) {
          idEntered = true;
          runBreathTest();
        } else {
          lcd.setCursor(0, 1);
          lcd.print("3 digits only!");
          delay(1000);
          lcd.setCursor(0, 1);
          lcd.print(" ");
        }
      }
    }
  }
}

void blinkLED(int pin) {
  for (int i = 0; i < 5; i++) {
    digitalWrite(pin, HIGH);
    delay(300);
    digitalWrite(pin, LOW);
    delay(300);
  }
}

void runBreathTest() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Blow in the tube!");
  delay(13000);

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Analyzing...");
  delay(1500);

  int gasVal = analogRead(GAS_SENSOR);
  float ppm = (gasVal / 4095.0) * 10.0;

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Acetone: ");
  lcd.print(ppm, 1);
  lcd.print(" ppm");

  String result = "";
  lcd.setCursor(0, 1);

  if (ppm <= 5.0) {
    lcd.print("Result: Normal");
    blinkLED(GREEN_LED);
    result = "Normal";
  } else if (ppm <= 7.0) {
    lcd.print("Result: Mild");
    blinkLED(BLUE_LED);
    result = "Mild";
  } else {
    lcd.print("Result: High");
    blinkLED(RED_LED);
    result = "High";
  }
  
  delay(2000);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Thank You!");
  delay(2000);

 
  Blynk.virtualWrite(V0, patientID);
  Blynk.virtualWrite(V1, ppm);
  Blynk.virtualWrite(V2, result);
  terminal.print(String(entryNumber) + ") ");
  terminal.println("ID: " + patientID + " | PPM: " + String(ppm, 1) + " | " + result);
  terminal.flush();
  entryNumber++;

  sendToGoogleSheets(patientID, ppm, result);

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Enter Patient ID");
  lcd.setCursor(0, 1);
  lcd.print(" ");
  patientID = "";
  idEntered = false;
}

void sendToGoogleSheets(String id, float ppmVal, String resultVal) {
  HTTPClient http;
  http.begin("https://script.google.com/macros/s/AKfycbzDs53BRDhdYGFydvhET9jQ-3vJh7ojuWCUCRZW8ekwsOpx4iW9D2D19uQiWqYvzb60Rw/exec");
  http.addHeader("Content-Type", "application/json");
  String postData = "{\"patientID\":\"" + id + "\",\"ppm\":" + String(ppmVal, 1) + ",\"result\":\"" + resultVal + "\"}";
  int httpCode = http.POST(postData);
  Serial.print("Sheets POST Response: ");
  Serial.println(httpCode);
  http.end();
}