// RadCom LoRa Range Tester
// Feather9x_TX 433 Mhz
// Daimon Tilley, G4USI Sept. 2020

// this section includes the required libraries

#include <SPI.h>
#include <LoRa.h>

//this section defines the pins used for the SemTech radio module and the led/piezo

#define RFM95_CS 8
#define RFM95_RST 4
#define RFM95_INT 7
#define LED A0

int counter = 0;//creates a variable to count the number of packets sent

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
  //This section sets the modulation parameters described in the first article and are for experimentation
  LoRa.setTxPower(10); //this is the licence-free max erp. The board can go as high as 20dbm (100mw) just replace the number 10 with a number of your choice up to 20
  LoRa.enableCrc(); //prevent bad packets - do not change. Can be removed but must also be removed in the RX code too!
  LoRa.setSpreadingFactor(12); //Set Spreading Factor 7 to 12. 7 is the fastest transmission time. 12 the slowest, working further below the noise floor
  LoRa.setCodingRate4(8); //Set coding rate for best signal immunity - range 4(5) - 4(8) - default 5 -  8 doubles TX time but more robust
  LoRa.setSignalBandwidth(125E3); //Supported values are 7.8E3, 10.4E3, 15.6E3, 20.8E3, 31.25E3, 41.7E3, 62.5E3, 125E3, and 250E3. 125E3 recommended for normal use.
  // frequency instability can be an issue below 62.5E3 leading to bad packets, unless using a TCXO. 
}

void loop() {
  //this section runs repeatedly, sending a packet which is identified by the number contained in the variable 'counter'
  //flashing the led each time. incrementing the counter, witing for two seconds and then sending the next packet ad infinitum
  
  Serial.print("Sending packet: ");
  Serial.println(counter);

  // send packet
  LoRa.beginPacket();
  LoRa.print("RadCom Range Test my_callsign");//change this text to whatever you wish. If using more than 10dbm power, ensure you send your callsign too!
  LoRa.print(counter);
  LoRa.endPacket();

  //flash led to show packet sent
  digitalWrite (LED, HIGH);
  delay (250);
  digitalWrite (LED, LOW);

  counter++; //increment the counter by 1

  delay(2000);//wait 2 seconds and repeat
}
