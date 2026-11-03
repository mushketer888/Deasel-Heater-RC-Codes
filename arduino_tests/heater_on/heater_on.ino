// 01_send.ino

// Simple example of sending codes with a Radio Frequencies device.
// Sends code 4 times every 5 seconds.


// Schematic:
//   RF433 TRANSMITTER data pin plugged on Arduino D4

#include "RF433send.h"

#define PIN_RFOUT  4

RfSend *tx_whatever;

void setup() {
    pinMode(PIN_RFOUT, OUTPUT);

    Serial.begin(115200);

        // rfsend_builder performs some asserts that, it failed, write details
        // to Serial and then block execution.
        // If construction is done before setup() execution (as is the case with
        // global variables), no output is done and we loose interesting debug
        // information.
        // Therefore I prefer this style over using a global radio object.

    tx_whatever = rfsend_builder(
        RfSendEncoding::TRIBIT,
        PIN_RFOUT,
        RFSEND_DEFAULT_CONVENTION,  // Do we want to invert 0 and 1 bits? No.
        4,       // Number of sendings
        nullptr, // No callback to keep/stop sending (if you want to send
                 // SO LONG AS a button is pressed, the function reading the
                 // button state is to be put here).
        7936,    // initseq
        0,       // lo_prefix
        0,       // hi_prefix
        0,       // first_lo_ign
        252,    // lo_short
        748,    // lo_long
        0,       // hi_short
        0,       // hi_long
        248,       // lo_last
        7936,    // sep
        32       // nb_bits
    );

}

byte data[] = { 0x89, 0x7e, 0x11, 0xb0 };
void loop() {
    static int count = 0;

    byte n = tx_whatever->send(sizeof(data), data);
    Serial.print("Send completed ");
    Serial.print(n);
    Serial.print(" times\n");

    delay(5000);
}
