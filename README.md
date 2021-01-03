# RadCom_LoRa
These files contain code relating to a RadCom article on LoRa (RadCom is the journal of the Radio Society of Great Britain - RSGB)
The RSGB is the member-body of licensed radio amateurs in the UK.
The files are designed to be used in conjunction with that article and are modified versions of examples from the 
Sandeep Mistry LoRa library, encouraging licensed radio amateurs to experiment with LoRa technology using the Adafruit Lora Feather 32u4 RFM9x boards.

Please  note that the code for each module is designed to give you an indication of sucessful transmission and reception. There are two ways of providing this. The simplest is already set up for you. There is an on-board LED next to the USB port. The TX LED will flash on transmission, and the RX LED will flash on sucessful reception of a packet.

The other way is via the Serial.print commands. These commands, already in the code for you to see,  send text to the Serial output of the device. This allows the receiver to display the Received Signal Strength Indicator (RSSI) and Signal to Noise Ratio (SNR). To view this, connect the Feather via USB cable to a computer, open the Arduino IDE, choose the correct Adafruit board and correct COM port and select from the Menu Tools, Serial Monitor. You will now see the sequential number and text of the received packet and the RSSI / SNR displayed in the Serial Monitor.

Please feel free to use and modify as you wish without restriction.
Above all - enjoy!
