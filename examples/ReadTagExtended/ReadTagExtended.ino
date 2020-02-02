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
    SERIAL.println("NDEF Reader");
    nfc.begin();
}

void loop(void) {
    SERIAL.println("\nScan a NFC tag\n");

    if (nfc.tagPresent()) {
        NfcTag tag = nfc.read();
        SERIAL.println(tag.getTagType());
        SERIAL.print("UID: "); SERIAL.println(tag.getUidString());

        if (tag.hasNdefMessage()) { // every tag won't have a message

            NdefMessage message = tag.getNdefMessage();
            SERIAL.print("\nThis NFC Tag contains an NDEF Message with ");
            SERIAL.print(message.getRecordCount());
            SERIAL.print(" NDEF Record");
            if (message.getRecordCount() != 1) {
                SERIAL.print("s");
            }
            SERIAL.println(".");

            // cycle through the records, printing some info from each
            int recordCount = message.getRecordCount();
            for (int i = 0; i < recordCount; i++) {
                SERIAL.print("\nNDEF Record "); SERIAL.println(i + 1);
                NdefRecord record = message.getRecord(i);
                // NdefRecord record = message[i]; // alternate syntax

                SERIAL.print("  TNF: "); SERIAL.println(record.getTnf());
                SERIAL.print("  Type: "); SERIAL.println(record.getType()); // will be "" for TNF_EMPTY

                // The TNF and Type should be used to determine how your application processes the payload
                // There's no generic processing for the payload, it's returned as a byte[]
                int payloadLength = record.getPayloadLength();
                byte payload[payloadLength];
                record.getPayload(payload);

                // Print the Hex and Printable Characters
                SERIAL.print("  Payload (HEX): ");
                PrintHexChar(payload, payloadLength);

                // Force the data into a String (might work depending on the content)
                // Real code should use smarter processing
                String payloadAsString = "";
                for (int c = 0; c < payloadLength; c++) {
                    payloadAsString += (char)payload[c];
                }
                SERIAL.print("  Payload (as String): ");
                SERIAL.println(payloadAsString);

                // id is probably blank and will return ""
                String uid = record.getId();
                if (uid != "") {
                    SERIAL.print("  ID: "); SERIAL.println(uid);
                }
            }
        }
    }
    delay(3000);
}
