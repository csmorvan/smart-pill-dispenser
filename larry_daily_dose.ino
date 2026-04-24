#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Servo.h>
#include <SoftwareSerial.h>
#include <DFRobotDFPlayerMini.h>

#define BUTTON_PIN 9
#define LED_PIN 8
#define SERVO_PIN 6

LiquidCrystal_I2C lcd(0x27, 16, 2);
Servo servo;
SoftwareSerial mySerial(2, 3);
DFRobotDFPlayerMini df;

// ===== TIMING =====
#define TRACK1_TIME      12000
#define MESSAGE1_TIME     2200
#define MESSAGE2_TIME     1500
#define RESPONSE_TIME     5000
#define BLINK_DELAY        300

bool waiting = false;
bool escalated = false;
unsigned long startWait = 0;
unsigned long lastBlink = 0;
bool ledState = false;

void setup() {
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);

  Serial.begin(115200);
  mySerial.begin(9600);
  delay(1000);

  lcd.init();
  lcd.backlight();
  lcd.clear();
  lcd.print("Starting...");

  servo.attach(SERVO_PIN);
  servo.write(0);
  delay(1000);

  if (!df.begin(mySerial)) {
    lcd.clear();
    lcd.print("DFPlayer error");
    Serial.println("DFPlayer error");
    while (1);
  }

  df.volume(30);
  delay(1500);

  runSequence();
}

void runSequence() {
  // 1) 0001
  lcd.clear();
  lcd.print("Reminder soon");
  Serial.println("Playing 0001");
  df.play(1);
  delay(TRACK1_TIME);

  // 2) Message
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Larry, this is");
  lcd.setCursor(0, 1);
  lcd.print("your daily dose");
  delay(MESSAGE1_TIME);

  lcd.clear();
  lcd.print("of meds");
  delay(MESSAGE2_TIME);

  // 3) Servo
  moveServo();

  // 4) 0002 + LED blink/wait
  lcd.clear();
  lcd.print("Take your meds!");
  Serial.println("Playing 0002");
  df.play(2);

  waiting = true;
  escalated = false;
  startWait = millis();
  lastBlink = millis();
}

void loop() {
  if (!waiting) return;

  // LED keeps blinking while waiting
  if (millis() - lastBlink >= BLINK_DELAY) {
    ledState = !ledState;
    digitalWrite(LED_PIN, ledState);
    lastBlink = millis();
  }

  // Button press stops everything
  if (digitalRead(BUTTON_PIN) == LOW) {
    delay(30);
    if (digitalRead(BUTTON_PIN) == LOW) {
      Serial.println("Button pressed");

      waiting = false;
      digitalWrite(LED_PIN, LOW);
      df.stop();

      lcd.clear();
      lcd.print("Acknowledged");
      delay(1500);

      while (digitalRead(BUTTON_PIN) == LOW) {}
      return;
    }
  }

  // If no button press after 5 seconds, play 0003 once
  // BUT keep LED blinking until button is pressed
  if (!escalated && millis() - startWait >= RESPONSE_TIME) {
    Serial.println("Playing 0003");

    df.stop();
    delay(300);
    df.play(3);

    lcd.clear();
    lcd.print("No response");
    lcd.setCursor(0, 1);
    lcd.print("Press button");

    escalated = true;
  }
}

void moveServo() {
  lcd.clear();
  lcd.print("Dispensing...");

  for (int pos = 0; pos <= 90; pos++) {
    servo.write(pos);
    delay(15);
  }

  delay(800);

  for (int pos = 90; pos >= 0; pos--) {
    servo.write(pos);
    delay(15);
  }

  lcd.clear();
  lcd.print("Dispensed");
  delay(1000);
}