// Dial-A-Servo
// Loi Cheng
// See Credits at End of File

/* Servo */
#include <Servo.h> 
#define ard_log Serial.printf
Servo myservo;

/* ReceiveVoiceCall */
#include <LGSM.h>  
#define PINNUMBER ""
char numtel[20];

void setup() {
  
  /* LED Setup */
  pinMode(13, OUTPUT);      // initialize digital pin 13 as an output.
  
  /* Servo Setup */
  Serial.begin(115200);
  myservo.attach(9);       // attach servo to pin
  myservo.write(90);        // set servo rotation
  
  /* LVoiceCallStatus */
  // initialize serial communications
  Serial1.begin(115200);
  Serial1.println("Receive Voice Call");

  // connection state
  boolean notConnected = true;

  // This makes sure the modem notifies correctly incoming events
  LVoiceCall.hangCall();

  Serial1.println("Waiting Call");
}

void loop() {
    
  // blink LED
  digitalWrite(13, HIGH);    // turn the LED on (HIGH is the voltage level) 
  digitalWrite(13, LOW);    // turn the LED off by making the voltage LOW
    
  // Check the status of the voice call
  switch (LVoiceCall.getVoiceCallStatus()) 
  {
    case IDLE_CALL: // Nothing is happening

      break;

    case CALLING: // This should never happen, as we are not placing a call

      Serial1.println("CALLING");
      break;

    case RECEIVINGCALL: // Yes! Someone is calling us
    
      /* ---Run Servo ---*/
      myservo.write(120);       // set servo rotation
      delay(1000);              // wait for some millseconds
      myservo.write(90);        // set servo rotation
      /* ---Run Servo ---*/

      Serial1.println("RECEIVING CALL");

      // Retrieve the calling number
      LVoiceCall.retrieveCallingNumber(numtel, 20);

      // Print the calling number
      Serial1.print("Number:");
      Serial1.println(numtel);

      // Answer the call, establish the call
      // LVoiceCall.answerCall();         
      break;

    case TALKING:  // In this case the call would be established

      Serial1.println("TALKING. Enter line to interrupt.");
      while(Serial1.read()!='\n')
        delay(100);
      LVoiceCall.hangCall();
      Serial1.println("HANG. Waiting Call.");      
      break;
  }
  delay(1000);
}

/* Credits */

/*
  Copyright (c) 2014 MediaTek Inc.  All right reserved.

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License..

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. 
   See the GNU Lesser General Public License for more details.
*/

/*
  Blink
  Turns on an LED on for one second, then off for one second, repeatedly.

  Most Arduinos have an on-board LED you can control. On the Uno and
  Leonardo, it is attached to digital pin 13. If you're unsure what
  pin the on-board LED is connected to on your Arduino model, check
  the documentation at http://arduino.cc

  This example code is in the public domain.

  modified 8 May 2014
  by Scott Fitzgerald
 */
