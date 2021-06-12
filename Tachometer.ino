#include <LiquidCrystal.h>
//define LCD Pins
int rs = 11;
int e = 12;
int d4 = 4;
int d5 = 5;
int d6 = 6;
int d7 = 7;
int contrastPin = 3; //This allows you you to use the LCD screen without a potentiometer
int contrast = 10; //Change LCD contrast using this
LiquidCrystal lcd(rs, e, d4, d5, d6, d7);
#define ClockPin 2 //defines Hall Sensor Pin
int pulsesPerRev = 3; //If you are using one magnet this is 1, if you are using 2 change it 2, etc.                                   
int revolutions = 0;
int RPM = 0;
unsigned long startTime = 0;
unsigned long elapsedTime;


int minTrip = 1;


void setup() {
  // put your setup code here, to run once:
pinMode(ClockPin,INPUT);
analogWrite(contrastPin,contrast);
lcd.begin(16,2);
}

void loop() { 
  // put your main code here, to run repeatedly:
revolutions = 0;
RPM = 0;
startTime = millis(); //how much time passed since last time
attachInterrupt(digitalPinToInterrupt(2),isr,RISING); //attach interrupt to begin counting number of revolutions
delay(1000); //During this delay, the number of rotations is counted by the interrupt
detachInterrupt(ClockPin); //detach interrupt to stop counting revolutions and process the data to be displayed

elapsedTime = millis()-startTime;

//The interrupt is detached so that the RPM data can be processed and displayed

if(revolutions>0){
  RPM = max(minTrip,revolutions)*60000/pulsesPerRev/elapsedTime;
}
lcd.clear();
lcd.setCursor(0,0);
lcd.print("RPM:");
lcd.setCursor(10,0);
lcd.print(RPM);
}

void isr(){
  revolutions++;
}

//IF USING OLD ARDUINO NANO USE MEGA328P (OLD BOOTLOADER), this is what worked for me
