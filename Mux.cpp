/*
    mux.h - Library for managing a multiplexer (MUX) with Arduino.
    This library allows you to select channels on a 4- or 8-pin multiplexer and read analog values from those channels.
    Developed by Leonardo Aliperti - March 12, 2026
*/

#include "Arduino.h"
#include "Mux.h"

Mux::Mux() {
}

// --- FUNCTIONS FOR SINGLE MUX (4 PIN) ---

void Mux::setupMux(int s0, int s1, int s2, int s3, int sigPin) {
  _s0 = s0;
  _s1 = s1;
  _s2 = s2;
  _s3 = s3;
  _sigPin = sigPin;

  pinMode(_s0, OUTPUT);
  pinMode(_s1, OUTPUT);
  pinMode(_s2, OUTPUT);
  pinMode(_s3, OUTPUT);
} 

void Mux::muxSelectChannel(int channel) {
  digitalWrite(_s0, bitRead(channel, 0));
  digitalWrite(_s1, bitRead(channel, 1));
  digitalWrite(_s2, bitRead(channel, 2));
  digitalWrite(_s3, bitRead(channel, 3));
}

int Mux::muxAnalogRead(int channel) {
  muxSelectChannel(channel);
  delayMicroseconds(5);
  return analogRead(_sigPin);
}

void Mux::fullMuxAnalogRead(int muxChannels, int muxValue[]) {
  for (int channel = 0; channel < muxChannels; channel++) {
    muxValue[channel] = muxAnalogRead(channel);
  }
}

// --- FUNCTIONS FOR MULTI-MUX (8 PIN) ---

void Mux::setupMultiMux(int s0, int s1, int s2, int s3, int s4, int s5, int s6, int s7, int sigPin) {
  _s0 = s0;
  _s1 = s1;
  _s2 = s2;
  _s3 = s3;
  _s4 = s4;
  _s5 = s5;
  _s6 = s6;
  _s7 = s7;
  _sigPin = sigPin;

  pinMode(_s0, OUTPUT);
  pinMode(_s1, OUTPUT);
  pinMode(_s2, OUTPUT);
  pinMode(_s3, OUTPUT);
  pinMode(_s4, OUTPUT);
  pinMode(_s5, OUTPUT);
  pinMode(_s6, OUTPUT);
  pinMode(_s7, OUTPUT);
} 

void Mux::multiMuxSelectChannel(int channel) {
  digitalWrite(_s0, bitRead(channel, 0));
  digitalWrite(_s1, bitRead(channel, 1));
  digitalWrite(_s2, bitRead(channel, 2));
  digitalWrite(_s3, bitRead(channel, 3));
  digitalWrite(_s4, bitRead(channel, 4));
  digitalWrite(_s5, bitRead(channel, 5));
  digitalWrite(_s6, bitRead(channel, 6));
  digitalWrite(_s7, bitRead(channel, 7));
}
