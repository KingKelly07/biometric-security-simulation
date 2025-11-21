#include <Servo.h>
#include <Keypad.h>

// --- COMPONENTS SETUP ---
const int RED_LED = 12;
const int GREEN_LED = 11;
const int SERVO_PIN = 10;
const int BUZZER = 13; 

Servo myLock;
char masterPassword[] = "173804"; 
String inputPassword = "";

// --- KEYPAD CONFIGURATION ---
const byte ROWS = 4; 
const byte COLS = 4; 
char keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};
byte rowPins[ROWS] = {9, 8, 7, 6}; 
byte colPins[COLS] = {5, 4, 3, 2}; 

Keypad myKeypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

void setup() {
  Serial.begin(9600);
  
  // 1. Setup Pins
  myLock.attach(SERVO_PIN);
  pinMode(RED_LED, OUTPUT);
  pinMode(GREEN_LED, OUTPUT);
  pinMode(BUZZER, OUTPUT);

  // 2. --- THE SETUP WIGGLE (Self-Check) ---
  Serial.println("Performing Self-Check...");
  myLock.write(90);       // Swing OPEN
  digitalWrite(GREEN_LED, HIGH); // Green ON
  delay(500);             // Wait half a second
  
  myLock.write(0);        // Swing CLOSED
  digitalWrite(GREEN_LED, LOW);  // Green OFF
  digitalWrite(RED_LED, HIGH);   // Red ON
  delay(500);
  
  // 3. Startup Beep
  tone(BUZZER, 2000, 200); // High beep to say "Ready"
  delay(200);
  
  Serial.println("SYSTEM READY. Enter Password:");
}

void loop() {
  char key = myKeypad.getKey();
  
  if (key) {
    playBeep(); // Sound on every press
    
    if (key == '#') { // ENTER
      checkPassword();
    } 
    else if (key == '*') { // CLEAR
      inputPassword = "";
      tone(BUZZER, 500, 300); 
      Serial.println(" Cleared");
      blinkRed();
    } 
    else {
      inputPassword += key;
      Serial.print("*");
    }
  }
}

void checkPassword() {
  if (inputPassword == masterPassword) {
    Serial.println("\nACCESS GRANTED");
    playSuccessSound();
    
    digitalWrite(RED_LED, LOW);
    digitalWrite(GREEN_LED, HIGH); 
    myLock.write(90); // Unlock
    
    delay(3000); // Stay open for 3 seconds
    
    // Re-lock
    myLock.write(0);
    digitalWrite(GREEN_LED, LOW);
    digitalWrite(RED_LED, HIGH);
    Serial.println("LOCKED");
    
  } else {
    Serial.println("\nWRONG PASSWORD");
    playAlarm(); // SIREN!
    blinkRed();
  }
  inputPassword = "";
}

// --- SOUND & LIGHT EFFECTS ---

void playBeep() {
  tone(BUZZER, 1000, 100); 
}

void playSuccessSound() {
  // Happy "Da-Da-Daaa" sound
  tone(BUZZER, 1500, 100); delay(150);
  tone(BUZZER, 2000, 100); delay(150);
  tone(BUZZER, 2500, 200); delay(200);
}

void playAlarm() {
  // Siren sound
  for (int i = 0; i < 3; i++) {
    for (int hz = 500; hz < 2000; hz += 50) {
      tone(BUZZER, hz, 10); delay(5);
    }
    for (int hz = 2000; hz > 500; hz -= 50) {
      tone(BUZZER, hz, 10); delay(5);
    }
  }
}

void blinkRed() {
  digitalWrite(RED_LED, LOW); delay(100); digitalWrite(RED_LED, HIGH);
}
