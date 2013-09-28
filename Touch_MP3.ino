/**********************************************************
       SINGLE VERSION - ORANGE STICKERS 
 **********************************************************

  Bare Conductive Touch MP3 player for Universal
  
  Uses SparkFun Touch Shield and MP3 shield
  
  Touch shield is modified to bring the interrupt out
  to Arduino digital pin 4, not 2-f
  
  MP3 shield is unmodified
  
 **********************************************************  
  
  Code is by Stefan Dzisiewski-Smith, building on example
  code from Sparkfun Website and Jim Lindblom
  
*Slighty modified by Peter Krige to work with ATMega 32U4* (for internal use only)
I have signed the additions for now as I am not properly connected to GitHub.
  

void setup() {
  
  if(MP3player.begin() != 0) {Serial.print(F("ERROR"));
***********************************************************/

// touch shield includes
#include "mpr121_setup.h"
#include <Wire.h>
#define MPR121 0x5A // address set on touch shield

// mp3 shield includes

#include <SPI.h>
#include <SdFat.h>
#include <SdFatUtil.h> 
#include <SFEMP3Shield.h>


// Below is not needed if interrupt driven. Safe to remove if not using.
//#if defined(USE_MP3_REFILL_MEANS) && USE_MP3_REFILL_MEANS == USE_MP3_Timer1
//  #include <TimerOne.h>
//#elif defined(USE_MP3_REFILL_MEANS) && USE_MP3_REFILL_MEANS == USE_MP3_SimpleTimer
//  #include <SimpleTimer.h>
//#endif

// touch shield variables
int irqpin = 4;
boolean touchStates[12]; //to keep track of the previous touch states

// mp3 shield variables
SFEMP3Shield MP3player;
byte temp;
byte result;
int lastPlayed = 0;

// touch behaviour definitions
#define TouchThr 5
#define ReleaseThr 3 
#define firstPin 0
#define lastPin 11

SdFat sd; // newly required in Arduino 1.01.00 and higher - This provides more immediate access to the SdCard's files by the main sketch. (Peter Krige)
void setup(){


  
  pinMode(irqpin, INPUT);
  digitalWrite(irqpin, HIGH); //enable pullup resistor
  
  pinMode(1, INPUT);
  pinMode(13, OUTPUT);
  digitalWrite(13, LOW);
  delay(1000);
  
  
  Serial.begin(115200);
   
  //while (!Serial) ; {} //use for debugging with the serail monitor - this is needed with all ATMega 32U4s. Uncomment when using the serial monitor (Peter Krige) 
 
  Serial.println("Bare Conductive Touch Sensitive Album Art Demo");
  Serial.println("SINGLE VERSION");  
  Wire.begin();

  mpr121_setup();
  
  sd.begin(); //open up communication with the SD card (Peter Krige)
  if(!sd.begin(SD_SEL, SPI_HALF_SPEED)) sd.initErrorHalt(); //newly required in 1.01.00 and higher (Peter Krige)
  
  //boot up the MP3 Player Shield
  result = MP3player.begin();
  //check result, see readme for error codes.
  MP3player.SetVolume(0,0);
 
  if(result != 0) {
    Serial.print("Error code: ");
    Serial.print(result);
    Serial.println(" when trying to start MP3 player");
   }
}

void loop(){
  
//  // Below is only needed if not interrupt driven. Safe to remove if not using.
//#if defined(USE_MP3_REFILL_MEANS) \
//    && ( (USE_MP3_REFILL_MEANS == USE_MP3_SimpleTimer) \
//    ||   (USE_MP3_REFILL_MEANS == USE_MP3_Polled)      )
//
//  MP3player.available();
//#endif

  digitalWrite(13, digitalRead(1)); 

  readTouchInputs();
}


void readTouchInputs(){
  if(!checkInterrupt()){
    
    //read the touch state from the MPR121
    Wire.requestFrom(MPR121,2); 
    
    byte LSB = Wire.read();
    byte MSB = Wire.read();
    
    uint16_t touched = ((MSB << 8) | LSB); //16bits that make up the touch states
    
    int touchedCount = 0;
    
    // count number of touched inputs
    for (int i=0; i<12; i++){
      if(touched & (1<<i)){
        touchedCount++;  
      }  
    }

    // only make an action if we have one or fewer pins touched
    // ignore multiple touches
    if(touchedCount<=1){
      for (int i=0; i < 12; i++){  // Check which electrodes were pressed
        if(touched & (1<<i)){
        
          if(touchStates[i] == 0){
            //pin i was just touched
            Serial.print("pin ");
            Serial.print(i);
            Serial.println(" was just touched");\
            
            // 9..11 are the pins broken out on the side header
            // we map these to files 1..3 on the MP3 shield
            if(i<=lastPin && i>=firstPin){
              if(MP3player.isPlaying()){
                if(lastPlayed==i){
                  // if we're already playing the requested track, stop it
                  MP3player.stopTrack();
                  Serial.print("stopping track ");
                  Serial.println(i-firstPin+1);
                } else {
                  // if we're already playing a different track, stop that 
                  // one and play the newly requested one
                  MP3player.stopTrack();
                  MP3player.playTrack(i-firstPin+1); // add one as the first track is Track1.mp3, not Track0.mp3
                  Serial.print("playing track ");
                  Serial.println(i-firstPin+1);
                  
                  // don't forget to update lastPlayed - without it we don't
                  // have a history
                  lastPlayed = i;
                }
              } else {
                // if we're playing nothing, play the requested track 
                // and update lastplayed
                MP3player.playTrack(i-firstPin+1);
                Serial.print("playing track ");
                Serial.println(i-firstPin+1);
                lastPlayed = i;
              }
            }
          
          }else if(touchStates[i] == 1){
            //pin i is still being touched
          }  
        
          touchStates[i] = 1;      
        }else{
          if(touchStates[i] == 1){
            Serial.print("pin ");
            Serial.print(i);
            Serial.println(" is no longer being touched");
            
            //pin i is no longer being touched
         }
          
          touchStates[i] = 0;
        }
      
      }
    }
  }
}

boolean checkInterrupt(void){
  return digitalRead(irqpin);
}

