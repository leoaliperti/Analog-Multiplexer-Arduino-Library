/*
    mux.h - Library for managing a multiplexer (MUX) with Arduino.
    This library allows you to select channels on a 4- or 8-pin multiplexer and read analog values from those channels.
    Developed by Leonardo Aliperti - March 12, 2026
*/

#ifndef MUX_H
#define MUX_H

#include "Arduino.h"

class Mux {
  private:
    uint8_t _s0, _s1, _s2, _s3;
    uint8_t _s4, _s5, _s6, _s7;
    uint8_t _sigPin;
    uint32_t _delayTime;

  public:
    // --- SETUP ---
    Mux(uint32_t delayTime = 5);

    // --- FUNCTION FOR 4-PIN MUX ---
    void setupMux(uint8_t s0, uint8_t s1, uint8_t s2, uint8_t s3, uint8_t sigPin);
    void muxSelectChannel(uint8_t channel);
    uint16_t muxAnalogRead(uint8_t channel);
    void fullMuxAnalogRead(uint8_t muxChannels, uint16_t muxValue[]);

    // --- FUNCTIONS FOR MULTI-MUX (8 PIN) ---
    void setupMultiMux(uint8_t s0, uint8_t s1, uint8_t s2, uint8_t s3, uint8_t s4, uint8_t s5, uint8_t s6, uint8_t s7, uint8_t sigPin);
    void multiMuxSelectChannel(uint16_t channel);
    uint16_t multiMuxAnalogRead(uint16_t channel); 
    void fullMultiMuxAnalogRead(uint16_t muxChannels, uint16_t muxValue[]);
};

#endif
