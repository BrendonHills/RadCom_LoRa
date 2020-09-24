
// RadCom LoRa Range Tester
// Feather9x_RX 433 Mhz
// Daimon Tilley, G4USI. Sept. 2020


#include <SPI.h>
#include <LoRa.h>

#define RFM95_CS 8
#define RFM95_RST 4
#define RFM95_INT 7
#define LED A0

int counter = 0;

void setup() {
  pinMode (LED, OUTPUT);
  LoRa.setPins(RFM95_CS, RFM95_RST, RFM95_INT);
  Serial.begin(9600);
  
  Serial.println("LoRa Receiver 433.3 Mhz");

  if (!LoRa.begin(433.3E6)) {
    Serial.println("Starting LoRa failed!");
    while (1);
  }
  //the values in the follwong section MUST MATCH EXACTLY those set in the Transmitter code or nothing will be understood!
  //if you make a change in one you must make the exact change in the other!
  
  LoRa.setTxPower(10); 
  LoRa.enableCrc(); 
  LoRa.setSpreadingFactor(12); 
  LoRa.setCodingRate4(8); 
  LoRa.setSignalBandwidth(125E3); 
}
void loop() {
  // try to parse packet
    int packetSize = LoRa.parsePacket();
  if (packetSize) {
    // successfully received a packet
    Serial.print("Received packet '");

    // read packet
    while (LoRa.available()) {
      Serial.print((char)LoRa.read());
    }
    //flash led and sound piezo to show packet received
    digitalWrite (LED, HIGH);
    delay (250);
    digitalWrite (LED, LOW);

    // print RSSI and SNR of packet
    Serial.print("' with RSSI ");
    Serial.print(LoRa.packetRssi());
    Serial.print("' with SNR ");
    Serial.println(LoRa.packetSnr());
    
  }
}
