// Erases a NFC tag by writing an empty NDEF message
#include <NfcAdapter.h>
#include <PN532/PN532/PN532.h>
#if 0
    #include <SPI.h>
    #include <PN532/PN532_SPI/PN532_SPI.h>


    PN532_SPI pn532spi(SPI, 10);
    NfcAdapter nfc = NfcAdapter(pn532spi);
#else

    #include <Wire.h>
    #include <PN532/PN532_I2C/PN532_I2C.h>


    PN532_I2C pn532_i2c(Wire);
    NfcAdapter nfc = NfcAdapter(pn532_i2c);
#endif

void setup(void) {
    SERIAL.begin(9600);
    SERIAL.println("NFC Tag Eraser");
    nfc.begin();
}

void loop(void) {
    SERIAL.println("\nPlace a tag on the NFC reader to erase.");

    if (nfc.tagPresent()) {

        bool success = nfc.erase();
        if (success) {
            SERIAL.println("\nSuccess, tag contains an empty record.");
        } else {
            SERIAL.println("\nUnable to erase tag.");
        }

    }
    delay(5000);
}
