/*
    mux.h - Library for managing a multiplexer (MUX) with Arduino.
    This library allows you to select channels on a 4- or 8-pin multiplexer and read analog values from those channels.
    Created by Leonardo Aliperti - March 12, 2026
    Last edited by Leonardo Aliperti - March 17, 2026
*/

#include "Arduino.h"
#include "MuxControl.h"

Mux::Mux(uint32_t delayTime) {
  _delayTime = delayTime;
}

// --- FUNCTIONS FOR SINGLE MUX (4 PIN) ---

void Mux::setupMux(uint8_t s0, uint8_t s1, uint8_t s2, uint8_t s3, uint8_t sigPin) {
  _s0 = s0;
  _s1 = s1;
  _s2 = s2;
  _s3 = s3;
  _sigPin = sigPin;

  pinMode(_s0, OUTPUT);
  pinMode(_s1, OUTPUT);
  pinMode(_s2, OUTPUT);
  pinMode(_s3, OUTPUT);
  pinMode(_sigPin, INPUT);
} 

void Mux::muxSelectChannel(uint8_t channel) {
  digitalWrite(_s0, (channel >> 0) & 1); 
  digitalWrite(_s1, (channel >> 1) & 1);
  digitalWrite(_s2, (channel >> 2) & 1);
  digitalWrite(_s3, (channel >> 3) & 1);
}

uint16_t Mux::muxAnalogRead(uint8_t channel) {
  muxSelectChannel(channel);
  delayMicroseconds(_delayTime);
  analogRead(_sigPin); // Dummy read to allow the ADC's Sample & Hold capacitor to stabilize.
  return analogRead(_sigPin);
}

void Mux::fullMuxAnalogRead(uint8_t muxChannels, uint16_t muxValue[]) {
  for (uint8_t channel = 0; channel < muxChannels; channel++) {
    muxValue[channel] = muxAnalogRead(channel);
  }
}

// --- FUNCTIONS FOR MULTI-MUX (8 PIN) ---

void Mux::setupMultiMux(uint8_t s0, uint8_t s1, uint8_t s2, uint8_t s3, uint8_t s4, uint8_t s5, uint8_t s6, uint8_t s7, uint8_t sigPin) {
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
  pinMode(_sigPin, INPUT);
} 

void Mux::multiMuxSelectChannel(uint16_t channel) {
  digitalWrite(_s0, (channel >> 0) & 1); 
  digitalWrite(_s1, (channel >> 1) & 1);
  digitalWrite(_s2, (channel >> 2) & 1);
  digitalWrite(_s3, (channel >> 3) & 1);
  digitalWrite(_s4, (channel >> 4) & 1);
  digitalWrite(_s5, (channel >> 5) & 1);
  digitalWrite(_s6, (channel >> 6) & 1);
  digitalWrite(_s7, (channel >> 7) & 1);
}

uint16_t Mux::multiMuxAnalogRead(uint16_t channel) {
  multiMuxSelectChannel(channel); //Use the multiMuxSelectChannel function to set the channel on the 8-pin MUX.
  delayMicroseconds(_delayTime);
  analogRead(_sigPin); // Dummy read to allow the ADC's Sample & Hold capacitor to stabilize.
  return analogRead(_sigPin);
}

void Mux::fullMultiMuxAnalogRead(uint16_t muxChannels, uint16_t muxValue[]) {
  for (uint16_t channel = 0; channel < muxChannels; channel++) {
    muxValue[channel] = multiMuxAnalogRead(channel);
  }
}
