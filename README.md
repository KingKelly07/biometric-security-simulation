A basic Arduino High-Security Smart Lock Prototype

Project Overview
This is a hardware simulation of a 2-factor authentication smart lock system. It was built and tested using Autodesk Tinkercad. It uses C++ logic to manage input validation, actuator control (Servo), and audio-visual feedback.

  Features
* Secure Input: 4x4 Keypad requiring a 6-digit PIN.
* Actuator Control: Positional Micro Servo simulating a deadbolt.
* Feedback System:
    * RGB Logic (Red = Locked, Green = Open).
    * Piezo Buzzer (Beeps on keypress, Siren on intrusion attempt i.e wrong password).

Security Protocols:
    * Auto-lock timer (3 seconds).
    * System "Self-Check" on startup (Servo rotates 90° and back with green and red LEDs flashing).
    * Password masking in Serial Monitor.

  Hardware Components Simulated
* Arduino Uno R3 (Microcontroller)
* Micro Servo (Lock Mechanism)
* 4x4 Membrane Keypad
* Piezo Buzzer
* LEDs (Red/Green) + 220Ω Resistors

## How to Run
1.  Copy the code from `src/smart_lock.ino`.
2.  Paste into the Arduino IDE or Tinkercad Circuits.
3.  Wire components according to the `Pin Configuration` in the code.
