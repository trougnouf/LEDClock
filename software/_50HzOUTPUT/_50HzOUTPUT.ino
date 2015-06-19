#include <stdio.h>
#include <stdlib.h>

unsigned long time = 0;



void setup() {
  pinMode(13, OUTPUT);
  pinMode(12, OUTPUT);
  digitalWrite(12, HIGH);
  
}

void loop() {
  Serial.write("moo");
  printf("moo2");
  //digitalWrite(13, HIGH);
  time = millis();
  if(!(time % 16))
  {
    digitalWrite(13, HIGH);
  }
  else  digitalWrite(13,LOW);
}

//turned on @ full power, 1/16 at 2339
