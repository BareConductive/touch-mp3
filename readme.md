[![Bare Conductive](http://bareconductive.com/assets/images/LOGO_256x106.png)](http://www.bareconductive.com/)

# Bare Conductive Touch MP3 Demo Code

Simple touch-to-MP3 code for the [Bare Conductive Touch Board](http://www.bareconductive.com/shop/touch-board/).

You need twelve MP3 files named TRACK000.mp3 to TRACK011.mp3 in the root of the microSD card. 
 
When you touch electrode E0, TRACK000.mp3 will play. When you touch electrode E1, TRACK001.mp3 will play, and so on.

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

## Requirements
* You should make sure that you have followed our [Setting up Arduino with your Touch Board](http://www.bareconductive.com/make/setting-up-arduino-with-your-touch-board/) tutorial before using this (or any other) of our code examples


## Install

1. Close the Arduino IDE if you have it open.
1. Download the [.zip](https://github.com/BareConductive/touch-mp3/archive/public.zip) or clone the repository to your local machine - if downloading the .zip, extract the contents somewhere that suits you.
1. Take the **Touch_MP3** folder and move it to **Arduino Sketchbook Folder**. This will be different for each operating system: 

	**Windows**
	
	Libraries\\Documents\\Arduino
	
	or
	
	My Documents\\Arduino	
	
	**Mac**
	
	Documents/Arduino
	
	**Linux (Ubuntu)**
	
	Home/Arduino


	If this folder does not exist, create it first.
1. Reopen the Arduino IDE - you should now be able to open the sketch in the **File -> Sketchbook** menu.
