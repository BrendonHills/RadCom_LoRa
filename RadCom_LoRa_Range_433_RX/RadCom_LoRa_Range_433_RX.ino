
// RadCom LoRa Range Tester
// Feather9x_RX 433 Mhz
// Daimon Tilley, G4USI. Sept. 2020


// this section includes the required libraries

#include <SPI.h>
#include <LoRa.h>

//this section defines the pins used for the SemTech radio module and the led

#define RFM95_CS 8
#define RFM95_RST 4
#define RFM95_INT 7
#define LED 13 

void setup() {
  pinMode (LED, OUTPUT);//tells the Feather this pin is for output rather than input
  LoRa.setPins(RFM95_CS, RFM95_RST, RFM95_INT);//sets the pins for the radio module
  Serial.begin(9600);//initialise serial output
  Serial.println("LoRa Sender");
  //initialise radio to 433.3 mhz you can change this as long as you stay in the license free ISM band or the band you are licensed for
  if (!LoRa.begin(433.3E6)) {
    Serial.println("Starting LoRa failed!");
    while (1);
  }
  //the values in the following section MUST MATCH EXACTLY those set in the Transmitter code or nothing will be understood!
  //if you make a change in one you must make the exact change in the other! See transmitter code for explanation.
  
  LoRa.setTxPower(10); 
  LoRa.enableCrc(); 
  LoRa.setSpreadingFactor(7); 
  LoRa.setCodingRate4(4); 
  LoRa.setSignalBandwidth(125E3); 
}
void loop() {
  // try to parse packet
    int packetSize = LoRa.parsePacket();
  if (packetSize) {
    // successfully received a packet
    Serial.print("Received packet  ");

    // read packet
    while (LoRa.available()) {
      Serial.print((char)LoRa.read());//output contents of packet tothe serial monitor
    }
    //flash led to show packet received
    digitalWrite (LED, HIGH);
    delay (250);
    digitalWrite (LED, LOW);

    // print RSSI and SNR of packet
    Serial.print(" with RSSI ");
    Serial.print(LoRa.packetRssi());
    Serial.print("  with SNR ");
    Serial.println(LoRa.packetSnr());
    
  }
}
