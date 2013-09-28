/***********************************************************************

Welcome to the Tweak Zone - this is where we will make modifications to 
the threshold levels

TouchThr MUST be greater than ReleaseThr - see the MPR121 datasheet

Guidelines:

// for reasonable sized pads connected to a mains power supply or
// laptop USB

#define TouchThr 40 // 
#define ReleaseThr 20 // MUST be LESS than TouchThr

// for battery powere applications

#define TouchThr 5
#define ReleaseThr 3 // MUST be LESS than TouchThr



***********************************************************************/


// touch behaviour definitions
#define TouchThr 40 
#define ReleaseThr 20 


/***********************************************************************

End of the Tweak Zone - good bye!

***********************************************************************/


#define MPR121_ADDR 0x5A // address set on touch shield

#include <Wire.h>
#include "mpr121_defs.h"

void set_register(int address, unsigned char r, unsigned char v){
    Wire.beginTransmission(address);
    Wire.write(r);
    Wire.write(v);
    Wire.endTransmission();
}

void mpr121_setup(void){
  
// this code is all taken directly from the MPR121 Touch Sensing Design Guidelines document

set_register(MPR121_ADDR, SRST, 0x63); // soft reset if MPR121 not reset properly

set_register(MPR121_ADDR, CTL0, 0xFF); // optional LED config section
set_register(MPR121_ADDR, CTL1, 0xFF);
set_register(MPR121_ADDR, DIR, 0xFF);
set_register(MPR121_ADDR, EN, 0xFF);
set_register(MPR121_ADDR, DAT, 0xFF);

//touch pad baseline filter 
//rising: baseline quick rising 
set_register(MPR121_ADDR, MHDR, 0x3F);        // max half delta rising      0..3F
set_register(MPR121_ADDR, NHDR, 0x3F);        // noise half delta rising    0..3F
set_register(MPR121_ADDR, NCLR, 0x05);        // noise count limit rising   0..FF
set_register(MPR121_ADDR, FDLR, 0x00);        // delay limit rising         0..FF

//falling: baseline slow falling 
set_register(MPR121_ADDR, MHDF, 0x00);        // max half delta falling
set_register(MPR121_ADDR, NHDF, 0x3F);        // noise half delta falling
set_register(MPR121_ADDR, NCLF, 0x10);        // noise count limit falling
set_register(MPR121_ADDR, FDLF, 0x03);        // delay limit falling

//touched: baseline keep 
set_register(MPR121_ADDR, NHDT, 0x00);        // noise half delta touched  
set_register(MPR121_ADDR, NCLT, 0x00);        // noise count touched
set_register(MPR121_ADDR, FDLT, 0xFF);        // delay limit touched

// this looks like what we're looking for

//Proximity baseline filter
//rising: very quick rising 
set_register(MPR121_ADDR, MHDPROXR, 0x0F); 
set_register(MPR121_ADDR, NHDPROXR, 0x0F); 
set_register(MPR121_ADDR, NCLPROXR, 0x00); 
set_register(MPR121_ADDR, FDLPROXR, 0x00);

//falling: very slow rising 
set_register(MPR121_ADDR, 0x3A,0x01); 
set_register(MPR121_ADDR, 0x3B,0x01); 
set_register(MPR121_ADDR, 0x3C,0xFF); 
set_register(MPR121_ADDR, 0x3D,0xFF);

//touched 
set_register(MPR121_ADDR, NHDPROXT, 0x00); 
set_register(MPR121_ADDR, NCLPROXT, 0x00); 
set_register(MPR121_ADDR, FDLPROXT, 0x00);

//Touch pad threshold 
set_register(MPR121_ADDR, E0TTH, TouchThr); 
set_register(MPR121_ADDR, E0RTH, ReleaseThr); 
set_register(MPR121_ADDR, E1TTH, TouchThr); 
set_register(MPR121_ADDR, E1RTH, ReleaseThr); 
set_register(MPR121_ADDR, E2TTH, TouchThr); 
set_register(MPR121_ADDR, E2RTH, ReleaseThr); 
set_register(MPR121_ADDR, E3TTH, TouchThr); 
set_register(MPR121_ADDR, E3RTH, ReleaseThr); 
set_register(MPR121_ADDR, E4TTH, TouchThr); 
set_register(MPR121_ADDR, E4RTH, ReleaseThr); 
set_register(MPR121_ADDR, E5TTH, TouchThr); 
set_register(MPR121_ADDR, E5RTH, ReleaseThr); 
set_register(MPR121_ADDR, E6TTH, TouchThr); 
set_register(MPR121_ADDR, E6RTH, ReleaseThr); 
set_register(MPR121_ADDR, E7TTH, TouchThr); 
set_register(MPR121_ADDR, E7RTH, ReleaseThr); 
set_register(MPR121_ADDR, E8TTH, TouchThr); 
set_register(MPR121_ADDR, E8RTH, ReleaseThr); 
set_register(MPR121_ADDR, E9TTH, TouchThr); 
set_register(MPR121_ADDR, E9RTH, ReleaseThr); 
set_register(MPR121_ADDR, E10TTH, TouchThr); 
set_register(MPR121_ADDR, E10RTH, ReleaseThr); 
set_register(MPR121_ADDR, E11TTH, TouchThr); 
set_register(MPR121_ADDR, E11RTH, ReleaseThr);

//Proximity threshold
set_register(MPR121_ADDR, E12TTH, TouchThr); 
set_register(MPR121_ADDR, E12RTH, ReleaseThr);

//touch and release interrupt debounce
  set_register(MPR121_ADDR, DTR, 0x11);

//AFE and filter configuration 
set_register(MPR121_ADDR, AFE1, 0xFF);  
//set_register(MPR121_ADDR, AFE2, 0x24);
set_register(MPR121_ADDR, AFE2, 0x38);
//set_register(MPR121_ADDR, ECR, 0x80);
set_register(MPR121_ADDR, ECR, 0x0C);

//Auto Configuration 
set_register(MPR121_ADDR, ACCR0, 0x0B);
//set_register(MPR121_ADDR, ACCR1, 0x80);

set_register(MPR121_ADDR, USL, 0xC8); 
set_register(MPR121_ADDR, LSL, 0x82); 
set_register(MPR121_ADDR, TL, 0xB4); 
set_register(MPR121_ADDR, ECR, 0xBC);
  
}
