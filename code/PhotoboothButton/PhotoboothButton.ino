#define MODE_WAITING 0
#define MODE_PRESSED 1
#define MODE_LOCKOUT 2

#define INTERVAL 10
#define INTERVAL_2 2
#define INTERVAL_LOCKOUT 5000
#define NUM_BLINKS 5

#define LEDOUT 1
#define BUTTON 4

void setup() {
  // put your setup code here, to run once:
  pinMode(LEDOUT, OUTPUT);
  pinMode(BUTTON, INPUT);
  Keyboard.begin();
}

void loop() {
  static long lastMillis = 0;
  static int fadeBrightness = 0;
  static int fadeDirection = 1;
  static int mode = MODE_WAITING;
  static int blinkCount = 0;
  
  long currentMillis = millis();
  
  if(mode == MODE_WAITING) {
    if(currentMillis - lastMillis >= INTERVAL) {
      lastMillis = currentMillis;
      if(fadeDirection == 1) {
        fadeBrightness += 1;
        if(fadeBrightness > 255) {
          fadeBrightness = 255;
          fadeDirection = -1;
        }
      } else if(fadeDirection == -1) {
        fadeBrightness -= 1;
        if(fadeBrightness == 0) {
          fadeBrightness = 0;
          fadeDirection = 1;
        }
      }
      analogWrite(LEDOUT, fadeBrightness);
    }
    if(digitalRead(BUTTON) == LOW) {
      mode = MODE_PRESSED;
      Keyboard.print(' ');
      blinkCount = 0;
    }
  } else if(mode == MODE_PRESSED) {
    if(currentMillis - lastMillis >= INTERVAL_2) {
      lastMillis = currentMillis;
      if(fadeDirection == 1) {
        fadeBrightness += 1;
        if(fadeBrightness > 255) {
          fadeBrightness = 255;
          fadeDirection = -1;
        }
      } else if(fadeDirection == -1) {
        fadeBrightness -= 1;
        if(fadeBrightness == 0) {
          fadeBrightness = 0;
          fadeDirection = 1;
          blinkCount++;
        }
      }
      analogWrite(LEDOUT, fadeBrightness);
      if(blinkCount >= NUM_BLINKS) {
        mode = MODE_LOCKOUT;
      }
    }
  } else if(mode == MODE_LOCKOUT) {
    analogWrite(LEDOUT, 0);
    if(currentMillis - lastMillis >= INTERVAL_LOCKOUT) {
      mode = MODE_WAITING;
    }
  } else {
    mode = MODE_WAITING;
  }
}
