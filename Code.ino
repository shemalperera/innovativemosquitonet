#include <IRremote.h>

#define IR_RECEIVE_PIN 8

#define IR_BUTTON_1 69  //remote button 1  for the light
#define IR_BUTTON_2 70  // remote button 2  for the fan
#define IR_BUTTON_3 71  // remote button 3  far the casing and unfolding the net
#define IR_BUTTON_4 68  // remote button 4  for folding the net

// stepper 1 for folding and unfolding the net
#define stepPin_1 1
#define dirPin_1 0

// stepper 2 for lifting the casing
#define stepPin_2 2
#define dirPin_2 3

int in1 = 7;  // relay 1 light
int in2 = 6;  // relay 2 fan


void setup() {
  Serial.begin(9600);
  IrReceiver.begin(IR_RECEIVE_PIN);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  // Sets the two pins as Outputs
  pinMode(stepPin_1, OUTPUT);
  pinMode(dirPin_1, OUTPUT);
  pinMode(stepPin_2, OUTPUT);
  pinMode(dirPin_2, OUTPUT);

}

void loop() {
  if (IrReceiver.decode()) {
    IrReceiver.resume();
    int command = IrReceiver.decodedIRData.command;
    switch (command) {


      case IR_BUTTON_1:  // relay operation of the LIGHT
        {
          if (digitalRead(in1) == HIGH) {
            digitalWrite(in1, LOW);
          } else if (digitalRead(in1) == LOW) {
            digitalWrite(in1, HIGH);
          }
          break;
        }
      case IR_BUTTON_2:  // relay 2 operation of the fan
        {
          if (digitalRead(in2) == HIGH) {
            digitalWrite(in2, LOW);
          } else if (digitalRead(in2) == LOW) {
            digitalWrite(in2, HIGH);
          }
          break;
        }
      case IR_BUTTON_3:  // lifting the outer casing and unfolding the net
        {
          digitalWrite(dirPin_2, HIGH);  //cup up
          // Makes 200 pulses for making one full cycle rotation
          for (int x = 0; x < 1600; x++) {
            digitalWrite(stepPin_2, HIGH);
            delayMicroseconds(1000);  // can used to change the rotating speed
            digitalWrite(stepPin_2, LOW);
            delayMicroseconds(1000);
          }
          digitalWrite(dirPin_1, HIGH);  // Enables the motor to move in a particular direction
          // Makes 200 pulses for making one full cycle rotation
          for (int x = 0; x < 1600; x++) {
            digitalWrite(stepPin_1, HIGH);
            delayMicroseconds(1000);
            digitalWrite(stepPin_1, LOW);
            delayMicroseconds(1000);  // by changing this time delay between the steps we can change the rotation speed
          }
          digitalWrite(dirPin_2, LOW);  //cup down
          // Makes 200 pulses for making one full cycle rotation
          for (int x = 0; x < 1600; x++) {
            digitalWrite(stepPin_2, HIGH);
            delayMicroseconds(1000);  // can used to change the rotating speed
            digitalWrite(stepPin_2, LOW);
            delayMicroseconds(1000);
          }

          break;
        }
      case IR_BUTTON_4:  // folding the net
        {
         
          digitalWrite(dirPin_1, LOW);  // Enables the motor to move in a particular direction
          // Makes 200 pulses for making one full cycle rotation
          for (int x = 0; x < 1600; x++) {
            digitalWrite(stepPin_1, HIGH);
            delayMicroseconds(1000);
            digitalWrite(stepPin_1, LOW);
            delayMicroseconds(1000);  // by changing this time delay between the steps we can change the rotation speed
            Serial.println(IrReceiver.decodedIRData.command);
          }
          break;
        }
    }
  }
}
