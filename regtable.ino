/**
 * regtable
 *
 * Copyright (c) 2014 panStamp <contact@panstamp.com>
 * 
 * This file is part of the panStamp project.
 * 
 * panStamp  is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * any later version.
 * 
 * panStamp is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with panStamp; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301 
 * USA
 * 
 * Author: Daniel Berenguer
 * Creation date: 01/26/2012
 */

#include "product.h"
#include "regtable.h"




/**
 * Definition of common registers
 */
DEFINE_COMMON_REGISTERS()

const void setOutput(byte rId, byte *state);
const void setTime(byte rId, byte *value);
const void setReciving(byte rId);
const void setLED(byte rId, byte *light);




/*
 * Definition of custom registers
 * REGISTER(uint8_t *value, const uint8_t length, const void (*updater)(uint8_t rId), const void (*setter)(uint8_t rId, uint8_t *v), const SWDTYPE typ=SWDTYPE_OTHER, const int eepromAddr=-1, const uint16_t bank=DEFAULT_NVOLAT_SECTION)
 */
// Binary output register
byte dtOutput[1];       // 8 Binary output state (7 bits over) --> we only use 1 output
REGISTER regOutput(dtOutput, sizeof(dtOutput), NULL, &setOutput);
// Sleep time register
byte dtTime[1];    // 1 Time value
REGISTER regTime(dtTime, sizeof(dtTime), NULL, &setTime);
// Binary output register
byte dtReciving[1];       // 1 Binary output state 
REGISTER regReciving(dtReciving, sizeof(dtReciving), &setReciving, NULL);
// Binary output register LED
byte dtLED[1];       // 8 Binary output state (7 bits over) --> we only use 1 output
REGISTER regLED(dtLED, sizeof(dtLED), NULL, &setLED);





/**
 * Initialize table of registers
 */
DECLARE_REGISTERS_START()
  &regOutput,  // Register ID = 11 (0x0B)
  &regTime,     // Register ID = 12 (0x0C)
  &regReciving,  // Register ID = 13 (0x0B)
  &regLED  // Register ID = 14 (0x0E)
DECLARE_REGISTERS_END()






/**
 * Definition of common getter/setter callback functions
 */
DEFINE_COMMON_CALLBACKS()

/**
 * Definition of custom getter/setter callback functions
 */

/**
 * setBinOutputs
 *
 * Set binary outputs
 *
 * 'rId'     Register ID
 * 'states'  New output levels
 */
const void setOutput(byte rId, byte *state)
{
  // Update register
  memcpy(dtOutput, state, sizeof(dtOutput));

  order=dtOutput[0];

}

/**
 * setPwmOutputs
 *
 * Set PWM levels
 *
 * 'rId'     Register ID
 * 'levels'  New PWM levels
 */
const void setTime(byte rId, byte *value)
{
  byte i;
  
  // Update register
  memcpy(dtTime, value, sizeof(dtTime));

  // SleepTime from binary to decimal
  sleepTime=0;                                
  for(i=0 ; i<sizeof(dtTime) ; i++){
  sleepTime=dtTime[i]*pow(10,i)+sleepTime;
  }
  
}

const void setReciving(byte rId)
{ 
    dtReciving[0]=sending;
 
}

const void setLED(byte rId, byte *light)
{
  byte x;
  // Update register
  memcpy(dtLED, light, sizeof(dtLED));

  if(dtLED[0]==1){
  for(x=0 ; x<6 ; x++){
    digitalWrite(light, HIGH);
    delay(400);
    digitalWrite(light, LOW);
    delay(100);
    }
  }
    
}


