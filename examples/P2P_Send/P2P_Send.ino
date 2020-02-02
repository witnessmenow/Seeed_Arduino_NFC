// Sends a NDEF Message to a Peer
// Requires SPI. Tested with Seeed Studio NFC Shield v2
#include <NfcAdapter.h>
#include <PN532/PN532/PN532.h>
#include "SPI.h"
#include "PN532/PN532_SPI/PN532_SPI.h"
#include "PN532/PN532/snep.h"
#include "NdefMessage.h"

PN532_SPI pn532spi(SPI, 10);
SNEP nfc(pn532spi);
uint8_t ndefBuf[128];

void setup() {
    SERIAL.begin(9600);
    SERIAL.println("NFC Peer to Peer Example - Send Message");
}

void loop() {
    SERIAL.println("Send a message to Peer");

    NdefMessage message = NdefMessage();
    message.addUriRecord("http://shop.oreilly.com/product/mobile/0636920021193.do");
    //message.addUriRecord("http://arduino.cc");
    //message.addUriRecord("https://github.com/don/NDEF");


    int messageSize = message.getEncodedSize();
    if (messageSize > sizeof(ndefBuf)) {
        SERIAL.println("ndefBuf is too small");
        while (1) {
        }
    }

    message.encode(ndefBuf);
    if (0 >= nfc.write(ndefBuf, messageSize)) {
        SERIAL.println("Failed");
    } else {
        SERIAL.println("Success");
    }

    delay(3000);
}
