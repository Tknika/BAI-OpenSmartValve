#include "Functions.h"


 
void valveOpenClose (int a,int b){ // a=order eta b=balbularenLuzeraPultsotan

 count=0;
 int n = count ;
 unsigned long last_time=millis(); 
 
 if (a!=state){
  if (a==1){

   motorControl(0);             // EZKERRETARA BIRATU

    while (((millis()-last_time)<2000) && count<b){  // segundu bat pultsurik jaso gabe baldin badago irten (millis=now)
     if (n != count){              // pultso bat detektatzen duenean
            last_time=millis();       // segunduaren count berrabiarazi   
            n = count ;            // counter aktualizatu
           }
      }
      
    count=0;                       // counter reiniziatu
    n=count;
    
   motorControl(2);             // GELDITU
                         
    }                                 // if bukatu
    
  else {

   motorControl(1);             // ESKUBITARA BIRATU

    while (((millis()-last_time)<2000) && count<b){  // segundu bat pultsurik jaso gabe baldin badago irten (millis=now)
     if (n != count){              // pultso bat detektatzen duenean
            last_time=millis();       // segunduaren count reiniziatu   
            n = count ;            // counter aktualizatu
           }
      }
      
    count=0;                       // counterk reiniziatu
    n=count;
    
   motorControl(2);             // GELDITU    
    
    }                                 // else bukatu
    
  }                                   // if nagusia bukatu
  
 state=a;                            // balbularen azkeneko state (itxia edo irekia) gorde ondoren jakin dezan nola dagoen

}



