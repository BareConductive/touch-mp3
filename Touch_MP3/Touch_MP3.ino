
/*******************************************************************************

 Bare Conductive Touch MP3 player
 ------------------------------
 
 Touch_MP3.ino - touch triggered MP3 playback

 You need twelve MP3 files named TRACK000.mp3 to TRACK011.mp3 in the root of the 
 microSD card. 
 
 When you touch electrode E0, TRACK000.mp3 will play. When you touch electrode 
 E1, TRACK001.mp3 will play, and so on.

  SD card    
  │
    TRACK000.mp3  
    TRACK001.mp3  
    TRACK002.mp3  
    TRACK003.mp3  
    TRACK004.mp3  
    TRACK005.mp3  
    TRACK006.mp3  
    TRACK007.mp3  
    TRACK008.mp3  
    TRACK009.mp3  
    TRACK010.mp3  
    TRACK011.mp3  
 
 Based on code by Jim Lindblom and plenty of inspiration from the Freescale 
 Semiconductor datasheets and application notes.
 
 Bare Conductive code written by Stefan Dzisiewski-Smith and Peter Krige.
 
 This work is licensed under a MIT license https://opensource.org/licenses/MIT
 
 Copyright (c) 2016, Bare Conductive
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in all
 copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 SOFTWARE.

*******************************************************************************/

// compiler error handling
#include "Compiler_Errors.h"

// touch includes
#include <MPR121.h>
#include <Wire.h>
#define MPR121_ADDR 0x5C
#define MPR121_INT 4

// mp3 includes
#include <SPI.h>
#include <SdFat.h>
#include <FreeStack.h> 
#include <SFEMP3Shield.h>

// mp3 variables
SFEMP3Shield MP3player;
byte result;
int lastPlayed = 0;

// mp3 behaviour defines
#define REPLAY_MODE TRUE  // By default, touching an electrode repeatedly will 
                          // play the track again from the start each time.
                          //
                          // If you set this to FALSE, repeatedly touching an 
                          // electrode will stop the track if it is already 
                          // playing, or play it from the start if it is not.

// touch behaviour definitions
#define firstPin 0
#define lastPin 11

// sd card instantiation
SdFat sd;

void setup(){  
  Serial.begin(57600);
  
  pinMode(LED_BUILTIN, OUTPUT);
   
  //while (!Serial) ; {} //uncomment when using the serial monitor 
  Serial.println("Bare Conductive Touch MP3 player");

  if(!sd.begin(SD_SEL, SPI_HALF_SPEED)) sd.initErrorHalt();

  if(!MPR121.begin(MPR121_ADDR)) Serial.println("error setting up MPR121");
  MPR121.setInterruptPin(MPR121_INT);

  MPR121.setTouchThreshold(40);
  MPR121.setReleaseThreshold(20);

  result = MP3player.begin();
  MP3player.setVolume(10,10);
 
  if(result != 0) {
    Serial.print("Error code: ");
    Serial.print(result);
    Serial.println(" when trying to start MP3 player");
   }
   
}

void loop(){
  readTouchInputs();
}


void readTouchInputs(){
  if(MPR121.touchStatusChanged()){
    
    MPR121.updateTouchData();

    // only make an action if we have one or fewer pins touched
    // ignore multiple touches
    
    if(MPR121.getNumTouches()<=1){
      for (int i=0; i < 12; i++){  // Check which electrodes were pressed
        if(MPR121.isNewTouch(i)){
        
            //pin i was just touched
            Serial.print("pin ");
            Serial.print(i);
            Serial.println(" was just touched");
            digitalWrite(LED_BUILTIN, HIGH);
            
            if(i<=lastPin && i>=firstPin){
              if(MP3player.isPlaying()){
                if(lastPlayed==i && !REPLAY_MODE){
                  // if we're already playing the requested track, stop it
                  // (but only if we're not in REPLAY_MODE)
                  MP3player.stopTrack();
                  Serial.print("stopping track ");
                  Serial.println(i-firstPin);
                } else {
                  // if we're already playing a different track (or we're in
                  // REPLAY_MODE), stop and play the newly requested one
                  MP3player.stopTrack();
                  MP3player.playTrack(i-firstPin);
                  Serial.print("playing track ");
                  Serial.println(i-firstPin);
                  
                  // don't forget to update lastPlayed - without it we don't
                  // have a history
                  lastPlayed = i;
                }
              } else {
                // if we're playing nothing, play the requested track 
                // and update lastplayed
                MP3player.playTrack(i-firstPin);
                Serial.print("playing track ");
                Serial.println(i-firstPin);
                lastPlayed = i;
              }
            }     
        }else{
          if(MPR121.isNewRelease(i)){
            Serial.print("pin ");
            Serial.print(i);
            Serial.println(" is no longer being touched");
            digitalWrite(LED_BUILTIN, LOW);
         } 
        }
      }
    }
  }
}
