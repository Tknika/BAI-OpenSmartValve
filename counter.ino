unsigned long T0 = 0 ;  // Variable global para tiempo
void counter(){                  // etendurako pin-ak goranzko flag bat jasotzen duenean 
     
      if ( millis() > T0  + 250)
          {   count++ ;
              T0 = millis();
          }
    
    }
