/* 
 *  This code is for sunrom digital heart beat sensor model 1157
 *  For more details on this sensor visit
 *  http://www.sunrom.com/186
 *  For datasheet check resource for file "HeartBeat_1157.pdf"
 */
//Include DigiKeyboard to print on pc
#include <DigiKeyboard.h>
// digital pin 2 is connected to sunrom 1157 senson:
#define SENSOR 2

unsigned int beatms;
float bpm;
char buf[20];

// the setup routine runs once when you press reset:
void setup() {
  delay(1000);
  DigiKeyboard.println("\nDigital Heartbeat Sensor");
  // make the sensor's pin an input:
  pinMode(SENSOR, INPUT);
  beatms = 0; //will store duration between two pulses
}

// the loop routine runs over and over again forever:
void loop() {
  while(digitalRead(SENSOR) == 0)
      DigiKeyboard.println("Wait for High Pulse"); //wait for high pulse from sensor
  delay(1); //1 ms delay so that it does not listen any noise
  DigiKeyboard.println("High Recived");
  while(digitalRead(SENSOR) == 1) // wait until signal is high
  {
    delay(1); //wait 1ms
    beatms++; //keep incrementing count
      DigiKeyboard.println("Wait for Low Pulse"); //wait for high pulse from sensor
  }
  DigiKeyboard.println("Low Received");
  while(digitalRead(SENSOR) == 0) //keep looping till signal goes back high, wait for next
  {
    delay(1);
    beatms++;
      DigiKeyboard.println("Wait for High Pulse"); //wait for high pulse from sensor
  }
  DigiKeyboard.println("Low Received");
  //beatms variable will now have time in ms between two high edge pulse
  bpm = (float)60000/beatms; //see document for this calculation
  if(bpm > 200)
  {
    DigiKeyboard.println("Processing");
  }
  else
  {
    sprintf(buf, "%0.0f BPM", bpm);
    DigiKeyboard.println(buf);
  }
}



