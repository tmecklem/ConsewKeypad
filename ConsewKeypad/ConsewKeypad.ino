#include <Keypad.h>

const byte ROWS = 5;
const byte COLS = 8; 
const char keys[ROWS][COLS] = {
  {'7','5','3','1','6','4','2','0'},
  {'X','D','S','P','R','C','M','Y'},
  {' ',' ',' ',' ','<','v','>','^'},
  {'F','~','+','9','A','C','O','8'},
  {'E','{','?','*','H','}','!','I'}  
};
//const char * keys[ROWS][COLS] = {
//  {"7","5","3","1","6","4","2","0"},
//  {"Move X?","Disk","Select Needle?","Document","Rotate","Scissors","Move X,Y?","Move Y?"},
//  {"","","","","Left","Down","Right","Up"},
//  {"Fast Forward","Arch Arrow","+/-","9","Dash/10+","C","M Org","8"},
//  {"End","PD","?","Star Squares","Home","PU","Esc","Finger"}  
//};

// Leonardo pins
//byte rowPins[ROWS] = {4,5,6,11,12}; //connect to the row pinouts of the kpd
//byte colPins[COLS] = {A5,A4,2,3,7,8,9,10}; //connect to the column pinouts of the kpd

byte rowPins[ROWS] = {4,5,6,12,13}; //connect to the row pinouts of the kpd
byte colPins[COLS] = {0,1,2,3,8,9,10,11}; //connect to the column pinouts of the kpd

Keypad kpd = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

unsigned long loopCount;
unsigned long startTime;
String msg;


void setup() {
    Serial.begin(9600);
    loopCount = 0;
    startTime = millis();
    msg = "";
}


void loop() {
    loopCount++;
    if ( (millis()-startTime)>5000 ) {
        //Serial.print("Average loops per second = ");
        //Serial.println(loopCount/5);
        startTime = millis();
        loopCount = 0;
    }

    // Fills kpd.key[ ] array with up-to 10 active keys.
    // Returns true if there are ANY active keys.
    if (kpd.getKeys())
    {
        for (int i=0; i<LIST_MAX; i++)   // Scan the whole key list.
        {
            if ( kpd.key[i].stateChanged )   // Only find keys that have changed state.
            {
                switch (kpd.key[i].kstate) {  // Report active key state : IDLE, PRESSED, HOLD, or RELEASED
                    case PRESSED:
                    msg = " PRESSED.";
                break;
                    case HOLD:
                    msg = " HOLD.";
                break;
                    case RELEASED:
                    msg = " RELEASED.";
                break;
                    case IDLE:
                    msg = " IDLE.";
                }
                if(msg == " PRESSED.") {
                  Serial.print("Key ");
                  Serial.print(kpd.key[i].kchar);
                  Serial.println(msg);
                }
            }
        }
    }
}  // End loop
