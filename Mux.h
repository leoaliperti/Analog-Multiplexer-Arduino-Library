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
    int _s0, _s1, _s2, _s3;
    int _s4, _s5, _s6, _s7;
    int _sigPin;

  public:
    Mux();

    // --- FUNCTION FOR 4-PIN MUX ---
    void setupMux(int s0, int s1, int s2, int s3, int sigPin);
    void muxSelectChannel(int channel);
    int muxAnalogRead(int channel);
    void fullMuxAnalogRead(int muxChannels, int muxValue[]);

    // --- FUNCTIONS FOR MULTI-MUX (8 PIN) ---
    void setupMultiMux(int s0, int s1, int s2, int s3, int s4, int s5, int s6, int s7, int sigPin);
    void multiMuxSelectChannel(int channel);
};

#endif