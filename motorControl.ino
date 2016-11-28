#include "Functions.h"

void motorControl(int orderM ){   // order irakurri
   
    if(orderM==0){
      digitalWrite(motorRedWire, LOW);
      digitalWrite(motorBlackWire, HIGH); 
    }
    if (orderM==1){
      digitalWrite(motorRedWire, HIGH);
      digitalWrite(motorBlackWire, LOW); 
      }
    if (orderM==2){
      digitalWrite(motorRedWire, LOW);
      digitalWrite(motorBlackWire, LOW); 
      }

   } 
