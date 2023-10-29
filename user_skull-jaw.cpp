// enable for skull with jaw servo

#if 1  // change to 0 to disable this code

#include <ESP32Servo.h>
Servo servo;

#define SERVO_PIN 26

#define JAW_TIME_OPENING 500
#define JAW_REPEATS 2
#define JAW_TIME_TOTAL (JAW_TIME_OPENING * JAW_REPEATS)
#define JAW_COOLDOWN_BREAK 10000
#define JAW_CLOSED_ANGLE 20
#define JAW_OPEN_ANGLE 55

bool isAnimating = false;
unsigned long animationStartTime;
unsigned long cooldownTime;

void user_setup() {
  servo.attach(SERVO_PIN);
  servo.write(JAW_CLOSED_ANGLE);
  servo.detach();
}

void user_loop() {
  if (isAnimating) {
    unsigned long elapsed = millis() - animationStartTime;
    uint8_t servoAngle;

    if (!servo.attached()) {
      servo.attach(SERVO_PIN);
    }

    if (elapsed >= JAW_TIME_TOTAL) {
      isAnimating = false;
      servo.write(JAW_CLOSED_ANGLE);
      cooldownTime = millis();
    } else {
      elapsed %= JAW_TIME_OPENING;  // time within current bite cycle
      servoAngle = JAW_CLOSED_ANGLE + (elapsed * (JAW_OPEN_ANGLE - JAW_CLOSED_ANGLE) / JAW_TIME_OPENING);

      Serial.print("servo=");
      Serial.println(servoAngle);
      servo.write(servoAngle);
    }
  } else {
    unsigned long elapsed = millis() - cooldownTime;

    if (elapsed >= 250) {
      servo.detach();  // prevent vibration resulting from the jaw's pull
    }

    if (elapsed >= JAW_COOLDOWN_BREAK) {
      Serial.println("starting");
      animationStartTime = millis();
      isAnimating = true;
    }
  }
}

#endif