#include "pitches.h" // include pitches


// music
int songState = 0;

int melody[] = {
 NOTE_F4, NOTE_E4, NOTE_D4, NOTE_CS4,
 NOTE_C4, NOTE_B3, NOTE_AS3, NOTE_A3,
 NOTE_G3, NOTE_A3, NOTE_AS3, NOTE_A3, 
 NOTE_G3, NOTE_C4, 0, 
 
 NOTE_C4, NOTE_A3, NOTE_A3, NOTE_A3,
 NOTE_GS3, NOTE_A3, NOTE_F4, NOTE_C4, 
 NOTE_C4, NOTE_A3, NOTE_AS3, NOTE_AS3, 
 NOTE_AS3, NOTE_C4, NOTE_D4, 0, 
 
 NOTE_AS3, NOTE_G3, NOTE_G3, NOTE_G3,
 NOTE_FS3, NOTE_G3, NOTE_E4, NOTE_D4, 
 NOTE_D4, NOTE_AS3, NOTE_A3, NOTE_A3, 
 NOTE_A3, NOTE_AS3, NOTE_C4, 0,
 
 NOTE_C4, NOTE_A3, NOTE_A3, NOTE_A3,
 NOTE_GS3, NOTE_A3, NOTE_A4, NOTE_F4, 
 NOTE_F4, NOTE_C4, NOTE_B3, NOTE_G4, 
 NOTE_G4, NOTE_G4, NOTE_G4, 0,
 
 NOTE_G4, NOTE_E4, NOTE_G4, NOTE_G4,
 NOTE_FS4, NOTE_G4, NOTE_D4, NOTE_G4, 
 NOTE_G4, NOTE_FS4, NOTE_G4, NOTE_C4, 
 NOTE_B3, NOTE_C4, NOTE_B3, NOTE_C4, 0
};

int tempo[] = {
 8, 16, 8, 16,
 8, 16, 8, 16,
 16, 16, 16, 8,
 16, 8, 3,
 
 12, 16, 16, 16,
 8, 16, 8, 16,
 8, 16, 8, 16,
 8, 16, 4, 12,
 
 12, 16, 16, 16,
 8, 16, 8, 16,
 8, 16, 8, 16,
 8, 16, 4, 12,
 
 12, 16, 16, 16,
 8, 16, 8, 16,
 8, 16, 8, 16,
 8, 16, 4, 16,
 
 12, 17, 17, 17,
 8, 12, 17, 17, 
 17, 8, 16, 8,
 16, 8, 16, 8, 1 
};
//pins used
const int buzzer = 11;
const int startPin = 7;
const int endPin = 8;
const int touchPin = 5;
const int touchLed = 4;
// music
unsigned long previousMillis = 0; // time last changed
const long interval2 = 100; // interval between notes

//game states
int startGame = 0;
int endGame = 0;
int touchingNo = 0;
long timeTaken = 0;
int playing = 0;


void setup() { 
 // put your setup code here, to run once:
 Serial.begin(9600);
 pinMode(touchPin, INPUT); // setup circuit
 pinMode(buzzer, OUTPUT); // setup buzzer 2
 pinMode(touchLed, OUTPUT);
 pinMode(startPin, INPUT); // setup button
 pinMode(endPin, INPUT); // setup button
digitalWrite(touchLed,LOW);

}

void loop() {

startGame = digitalRead(startPin);

endGame = digitalRead(endPin);
 // Serial.println(endGame);

if (startGame) {
  playing = 1;
  touchingNo = 0;
  timeTaken = millis();
    buzz(0, 1000/3);
    delay(75);

//  Serial.println("Started the game");
  //display start game
} else if (endGame) {
  playing = 0;
  buzz(0, 1000/3);
  //display score
   Serial.println(touchingNo);

}else if (playing){ //playing state
  //start sing
   if(digitalRead(touchPin) == HIGH) {
   delay(25);
   if(digitalRead(touchPin) == HIGH) {
     while(digitalRead(touchPin) == HIGH) {
     buzz(NOTE_B0, 1000/24);
     digitalWrite(touchLed,HIGH);
     touchingNo++;
             Serial.println(touchingNo);

     delay(25);
     }
   }
  } else if (playing) {
    digitalWrite(touchLed,LOW);
    sing();
  }
 //check 
//   Serial.println("Playing");

  
}
}

void buzz(long frequency, long length) {

 long delayValue = 1000000/frequency/2; // calculate the delay value between transitions
 //// 1 second's worth of microseconds, divided by the frequency, then split in half since
 //// there are two phases to each cycle
 long numCycles = frequency * length/ 1000; // calculate the number of cycles for proper timing
 //// multiply frequency, which is really cycles per second, by the number of seconds to
 //// get the total number of cycles to produce
 for (long i=0; i < numCycles; i++){ // for the calculated length of time...
   digitalWrite(buzzer,HIGH); // write the buzzer pin high to push out the diaphragm
   delayMicroseconds(delayValue); // wait for the calculated delay value
   digitalWrite(buzzer,LOW); // write the buzzer pin low to pull back the diaphragm
   delayMicroseconds(delayValue); // wait again for the calculated delay value
 }
}

void sing() {
 // play the song in a non blocking way
 unsigned long currentMillis = millis();

 if (currentMillis - previousMillis >= interval2) {
   previousMillis = currentMillis;
   int noteDuration = 1000 / tempo[songState];
   buzz(melody[songState], noteDuration);
   int pauseBetweenNotes = noteDuration;
   delay(pauseBetweenNotes);
  
   // stop the tone playing:
   buzz(0, noteDuration);
   
   ++songState;
   // start song again if finished
   if(songState > 79) {
   songState = 14; // skip intro 
   } 
 }
}
