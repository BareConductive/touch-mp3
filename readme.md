<a href="http://www.bareconductive.com/"><img src="https://www.dropbox.com/s/5c4yatkrnqqbgrm/BareConductive.LOGO_553x221.jpg?dl=1" width="200px" alt="Bare Conductive" /></a>

# Bare Conductive Touch MP3 Demo Code

Simple touch-to-MP3 code for the [Bare Conductive Touch Board](http://www.bareconductive.com/shop/touch-board/). Touch electrode 0, **TRACK000.MP3** plays from the micro SD card. Touch electrode 1, **TRACK001.MP3** plays from the micro SD card, and so on. This is the code that ships with the [Touch Board](http://www.bareconductive.com/shop/touch-board/).

## Requirements
* [Arduino](http://arduino.cc/en/Main/Software) 1.0.5 or 1.5.6+ (1.5.6+ is strongly preferred).

* Arduino's instructions for installing libraries are available [here](http://arduino.cc/en/Guide/Libraries)

* [SFEMP3shield library](https://github.com/madsci1016/Sparkfun-MP3-Player-Shield-Arduino-Library) (zip file download [here](https://github.com/madsci1016/Sparkfun-MP3-Player-Shield-Arduino-Library/archive/master.zip)) - if you are using Arduino 1.0.5 you will need to edit the line containing

	

	```
	#define BARETOUCH 0

	```
	
	in SFEMP3ShieldConfig.h to read
	
	```
	#define BARETOUCH 1

	```
	If you are using Arduino 1.5.6 or later you will not need to do this.
	
* [Bare Conductive MPR121 library](https://github.com/bareconductive/mpr121) (zip file download [here](https://github.com/bareconductive/mpr121/archive/public.zip))

* [Bare Conductive Arduino Hardware Plugins](https://github.com/bareconductive/bare-conductive-arduino) (zip file download [here](https://github.com/bareconductive/bare-conductive-arduino/archive/public.zip)) - instructions on installing this hardware plugin folder are available [here](https://github.com/bareconductive/bare-conductive-arduino).


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