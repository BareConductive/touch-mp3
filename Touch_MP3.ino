/**********************************************************

  Bare Conductive Touch MP3 player
  
 **********************************************************  
  
  Code is by Stefan Dzisiewski-Smith, building on example
  code from Sparkfun Website and Jim Lindblom

  Extra modifications by Peter Krige (PK2_modified)

***********************************************************/

// touch includes
#include <MPR121.h>
#include <Wire.h>
#define MPR121_ADDR 0x5A
#define MPR121_INT 4

// touch variables
int touchStates[13];

// mp3 includes
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


// mp3 variables
SFEMP3Shield MP3player;
byte temp;
byte result;
int lastPlayed = 0;
SdFat sd; 

// touch behaviour definitions
#define firstPin 0
#define lastPin 11


void setup(){  
  Serial.begin(57600);
   
  while (!Serial) ; {} //uncomment when not using the serial monitor
 
  Serial.println("Bare Conductive Touch MP3 player");

  if(!MPR121.begin(MPR121_ADDR)) Serial.println("error setting up MPR121");
  
  sd.begin(); //open up communication with the SD card 
  if(!sd.begin(SD_SEL, SPI_HALF_SPEED)) sd.initErrorHalt();
  
  result = MP3player.begin();
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

  readTouchInputs();
}


void readTouchInputs(){
  if(!checkInterrupt()){
    
    //read the touch state from the MPR121
    Wire.requestFrom(MPR121_ADDR,2); 
    
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
  //return digitalRead(irqpin);
  return MPR121.touchStatusChanged();
}

