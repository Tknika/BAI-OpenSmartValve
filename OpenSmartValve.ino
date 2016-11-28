#include "Functions.h"
#include "HardwareSerial.h"valveRegulation
#include "Wire.h"
#include "regtable.h"
#include "swap.h"
#ifdef PANSTAMP_NRG
#include "cc430aes.h"
#endif


volatile int count = 0; // Global variable for any kind of function
int state = 5; // It saves the first state of the valve, if the valve was closed it will maintain closed and if it was open mantining it open
int valveLengthPulses = 0; // This variable defines the quantity of pulses (it is declared as a global variable)

int order = 0; // 0 = valve closed = radiator OFF ; 1 = valve opened = radiator ON (it is declared as a global variable)
int sleepTime = 10; // Time that is going to be OFF the actuator

const int light = 12;
const int sensor = 14; // Ultrasound sensor pin definition (interrupt=1 --> digital pin=1 --> pin=21)
const int motorRedWire = 15;     // Motor pin declaration
const int motorBlackWire = 8;     // Motor pin declaration
int pulsesLight = 0;


void setup() {

    Serial.begin(9600);

    pinMode(light, OUTPUT);
    pinMode(sensor, INPUT);
    pinMode(motorRedWire, OUTPUT);
    pinMode(motorBlackWire, OUTPUT);

    digitalWrite(light, HIGH);    
	  attachInterrupt(sensor, counter, RISING); // Definition of an interruption that will be activated by 'sensor' pin, a 'RISING' flag executes motorService function

    valveLengthPulses = valveRegulation();
   
    // Init SWAP stack
    swap.init();
  
    // AES-128 encryption (for NRG only)
    //byte aesKey[] = {0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F};  
    //swap.setAesPassword(aesKey);
  
    // Smart Encryption (software encryption)
    //byte password[] = {1,2,3,4,5,6,7,8,9,10,11,12};
    //panstamp.setSmartPassword(password);

    // Transmit product code
    swap.getRegister(REGI_PRODUCTCODE)->getData();
    // Enter Rx ON state
    swap.enterSystemState(SYSTATE_RXON);
    // Transmit initial binary states
    swap.getRegister(REGI_OUTPUT)->getData();
    // Transmit initial PWM values
    swap.getRegister(REGI_TIME)->getData();
    // Transmit initial PWM values
    swap.getRegister(REGI_RECIVING)->getData();
    // Transmit initial PWM values
    swap.getRegister(REGI_LED)->getData();
    digitalWrite(light, LOW);
    while (pulsesLight<valveLengthPulses){
      
    digitalWrite(light, HIGH);
    delay(400);
    digitalWrite(light, LOW);
    delay(100);
    pulsesLight++;
    }

}


void loop() {
   
  //warning it is ready to receive
  sending=1;

  // "sending" value is sent and wait till receive the message
  swap.getRegister(REGI_RECIVING)->getData();
  
  delay(5000);
 
  //warning it is not ready to receive
  sending=0;
  
  //send the value "sending" 
  swap.getRegister(REGI_RECIVING)->getData();
  
  //open or close the valve
  valveCloseOpen (order,valveLengthPulses); 
  
  //go to sleep
  panstamp.sleepSec(sleepTime);

 }
