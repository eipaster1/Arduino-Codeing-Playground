/* Importing Libraries required to use SD and Arduino Funcitons*/
#include <SD.h>
#include <SPI.h>
#include <Arduino.h>
#define SD_CHIP_SELECT_PIN 4

/*Introducing variables for analyzing the analog input*/

//OD Placehold for single analog read 
int V;
//Analog Tag for OD
int ReadV = A0;
//Amount of Readings before taking an average
int numReadings;
//Analog number recorded onto the SD
int VRecord;
//Readings Counter Goal
int numReadTar =5 ;
//Readings Counter
int numRead;
//File indentifier
File myfile;

//Now making a structure call writer

struct Datastore{
unsigned int AnalogV;
};

//Making a file name


const char filename = "System_State_Log.dat";




void setup(){
/*Setting pins*/

pinMode(A0,INPUT);

//Setting specific structure


//Starting serial terminal 

Serial.begin(9600);
SD.begin(SD_CHIP_SELECT_PIN);

//checking if the pin is actually being Read
if(!SD.begin(SD_CHIP_SELECT_PIN)){
Serial.println("initialization failed!");
        return;
}

//Now setting specific structure
const char datalen = 10;//Number of entries in structure
Datastore writer[datalen/* Arguement of how big structure is*/];








myfile = SD.open(filename,FILE_WRITE);

VRecord = 0;
numRead = 0;
V = 0;
}



void loop() {
//After Recording Value onto SD the num Reader goes back to zero


V = analogRead(ReadV);
VRecord += V;
numRead += 1;

//Now using if statement to determine if the number of readings were met


if(numRead == numReadTar){
  VRecord = VRecord/numRead;
  Serial.print("Analog Value: ");
  Serial.println(VRecord);
//Recording V Analog to Structure

writer.Voltage  = VRecord;
writer.time =  millis();

  
  myfile.write((const uint8_t *)writer, sizeof(writer));
  myfile.close();

//Resetting the Counters and the Recordering Variable

numRead = 0;
VRecord = 0;

}

delay(100);

}



