// Receive a NDEF message from a Peer
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
    SERIAL.println("NFC Peer to Peer Example - Receive Message");
}

void loop() {
    SERIAL.println("Waiting for message from Peer");
    int msgSize = nfc.read(ndefBuf, sizeof(ndefBuf));
    if (msgSize > 0) {
        NdefMessage msg  = NdefMessage(ndefBuf, msgSize);
        msg.print();
        SERIAL.println("\nSuccess");
    } else {
        SERIAL.println("Failed");
    }
    delay(3000);
}

