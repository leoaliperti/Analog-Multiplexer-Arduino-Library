# MuxControl Library for Arduino

A comprehensive, Object-Oriented Arduino library designed to easily control and read analog multiplexers (such as the popular CD74HC4067) and custom multi-multiplexer arrays.

## 🧠 How It Works: The Logic

An analog multiplexer acts like a digital switchboard. It allows you to connect multiple input channels to a single analog pin on your Arduino. 

To tell the multiplexer *which* channel to connect, we must send it a binary address using the selection pins (S0, S1, S2, etc.). For example, to read channel 5 (which is `0101` in binary), the library automatically pulls S0 High, S1 Low, S2 High, and S3 Low. 



This library abstracts all this binary math away. It takes a simple decimal number (like `5`), extracts the individual bits using fast bitwise operations (right shift `>>` and bitwise AND `&`), and drives the corresponding selection pins. It also includes a crucial, customizable stabilization delay (defaulting to 5 microseconds) before reading the analog value, ensuring clean and accurate data without cross-talk between channels. You can easily adjust this delay when instantiating the Mux object to suit your specific hardware needs.

---

## 🚀 Features

* **Object-Oriented Design:** Instantiate multiple `Mux` objects to control entirely independent multiplexer circuits within the same sketch.
* **Standard 4-Pin Mode:** Seamlessly control standard 16-channel multiplexers using 4 selection pins (tested with CD74HC4067).
* **Custom 8-Pin Multi-Mux Mode:** Control advanced, cascaded, or dual multiplexer setups requiring up to 8 selection pins.
* **Automatic Array Population:** Read all channels sequentially and store them directly into an array with a single line of code.
* **Hardware-Safe Initialization:** Uses a standard `setup()` methodology rather than doing hardware configurations inside the constructor, preventing early-boot crashes on AVR chips.

---

## 🛠️ API Reference & Function Breakdown

### 1. Initialization
The library uses a standard constructor and separate setup functions to safely initialize the pins.

* **`Mux()`**
  The constructor. It creates the Mux object in your code's memory but does not configure the hardware yet. 
  *Usage:* `Mux myMux;`

* **`void setupMux(uint8_t s0, uint8_t s1, uint8_t s2, uint8_t s3, uint8_t sigPin)`**
  Initializes a standard 4-pin multiplexer.
  * `s0`, `s1`, `s2`, `s3`: The Arduino digital pins connected to the multiplexer's selection pins.
  * `sigPin`: The Arduino analog pin connected to the multiplexer's common signal output.
  * *Logic:* Saves the pin numbers internally and sets S0-S3 as `OUTPUT`.

* **`void setupMultiMux(uint8_t s0, uint8_t s1, uint8_t s2, uint8_t s3, uint8_t s4, uint8_t s5, uint8_t s6, uint8_t s7, uint8_t sigPin)`**
  Initializes a custom 8-pin multi-multiplexer array.
  * `s0` to `s7`: The digital pins for the selection logic (e.g., S0-S3 for the back mux, S4-S7 for the front mux).
  * `sigPin`: The analog pin reading the final routed signal.
  * *Logic:* Sets all 8 pins as `OUTPUT`.

### 2. Standard 4-Pin Functions (Up to 16 Channels)

* **`void muxSelectChannel(int channel)`**
  Changes the physical state of the S0-S3 pins to route the requested channel to the signal pin.
  * `channel`: The decimal number of the channel to select (0-15).
  * *Logic:* Uses `bitRead()` to extract the first 4 bits of the decimal number and writes them to the output pins.

* **`uint16_t muxAnalogRead(uint8_t channel)`**
  The primary function for reading a specific channel.
  * `channel`: The decimal number of the channel to read.
  * *Returns:* An integer representing the analog value (0-1023 on standard 10-bit ADCs).
  * *Logic:* Calls `muxSelectChannel()`, halts execution for 5 microseconds to let the ADC capacitor charge and the signal stabilize, then triggers an `analogRead()`.

* **`void fullMuxAnalogRead(uint8_t muxChannels, uint8_t muxValue[])`**
  A batch-processing function that reads multiple channels and stores them in a provided array.
  * `muxChannels`: The total number of channels to iterate through.
  * `muxValue[]`: An array passed by reference where the readings will be stored.
  * *Logic:* Runs a standard `for` loop from 0 to `muxChannels - 1`, calling `muxAnalogRead()` for each step and populating the array.

### 3. Advanced 8-Pin Multi-Mux Functions

* **`void multiMuxSelectChannel(uint8_t channel)`**
  Similar to the standard selection function, but handles 8 distinct bits for complex routing setups.
  * `channel`: The decimal representation of the routing path (up to 255).
  * *Logic:* Uses `bitRead()` to extract the first 8 bits of the integer and drives S0 through S7 accordingly. *(Note: To read analog values from an 8-pin setup, you will manually call this function followed by an `analogRead()` of your signal pin).*

---

## 💻 Quick Start Example
You can find the file to download in the examples folder.

```cpp
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
