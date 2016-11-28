#include "Functions.h"

//volatile int counter = 0;            // Somos de lo mas obedientes

int valveRegulation(){ 
    
    count=0;
    int travel=0;
    int n = count ;
    unsigned long last_time=millis();

   motorControl(0);             // EZKERRETARA BIRATU
    
    while (millis()-last_time<2000){  // segundu bat pultsurik jaso gabe baldin badago irten (millis=now)
     if (n != count){              // pultso bat detektatzen duenean
            last_time=millis();       // segunduaren count reiniziatu   
            n = count ;            // counter aktualizatu
           }
    }
    
   motorControl(1);             // ESKUBITARA BIRATU (pistoia atera=balbula itxi)
    
    last_time=millis();
    count=0;
    n=count;
    
    while (millis()-last_time<2000){
     if (n != count)
           {last_time=millis();   
            n = count ;
           }
    }
    
    travel=count;                  // balbularen travel pultsotan gorde
    count=0;
    n=count;
    
   motorControl(2);
    
    return (travel);                   // travel pultsotan itzuli
  }
  

