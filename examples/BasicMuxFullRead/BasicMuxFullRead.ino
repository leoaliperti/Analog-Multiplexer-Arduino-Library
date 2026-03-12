#include <MuxControl.h>

// 1. Create the Mux object
Mux myMux; 

// 2. Prepare an array for 16 channels
int myReadings[16]; 

void setup() {
  Serial.begin(9600);
  
  // 3. Configure pins (S0=2, S1=3, S2=4, S3=5, Signal=A0)
  myMux.setupMux(2, 3, 4, 5, A0);
}

void loop() {
  // Read all 16 channels automatically into the array
  myMux.fullMuxAnalogRead(16, myReadings);
  
  // Print the results
  for(int i = 0; i < 16; i++) {
    Serial.print("Ch ");
    Serial.print(i);
    Serial.print(": ");
    Serial.println(myReadings[i]);
  }
  
  Serial.println("---");
  delay(1000);
}
