#include <Arduino.h>
#include "FourDigitDisplay.h"

// TODO expand the segment map
static const uint8_t SEGMENT_MAP[] = {
  //   ABCDEFGH  | ASCII 10 / 16 | char
  0b11111100, // |    48 / 30    | '0'
  0b01100000, // |    49 / 31    | '1'
  0b11011010, // |    50 / 32    | '2'
  0b11110010, // |    51 / 33    | '3'
  0b01100110, // |    52 / 34    | '4'
  0b10110110, // |    53 / 35    | '5'
  0b10111110, // |    54 / 36    | '6'
  0b11100000, // |    55 / 37    | '7'
  0b11111110, // |    56 / 38    | '8'
  0b11110110, // |    57 / 39    | '9'
};

FourDigitDisplay::FourDigitDisplay(
  const ShiftRegister &digit_register,
  const ShiftRegister &segment_register
) {
  digit_register_ = digit_register;
  segment_register_ = segment_register;

  // Configure digit pins
  pinMode(digit_register_.data_pin, OUTPUT);
  pinMode(digit_register_.clk_pin, OUTPUT);
  pinMode(digit_register_.latch_pin, OUTPUT);

  // Configure segment pins
  pinMode(segment_register_.data_pin, OUTPUT);
  pinMode(segment_register_.clk_pin, OUTPUT);
  pinMode(segment_register_.latch_pin, OUTPUT);
}

void FourDigitDisplay::Display(uint8_t (&segment_indices)[MAX_NUM_DIGITS]) {
  for (uint8_t i = 0; i < MAX_NUM_DIGITS; i++) {
    DisplayDigit(i, segment_indices[i]);
    delay(2);
  }
}

void FourDigitDisplay::DisplayDigit(
  uint8_t digit_index,
  uint8_t segment_index
) {
  // Shift out values for digits
  uint8_t digit_value = 0b00001111 & ~(1 << (MAX_NUM_DIGITS - 1 - digit_index));
  shiftOut(digit_register_.data_pin, 
           digit_register_.clk_pin, 
           LSBFIRST,
           digit_value);

  // Shift out values for segments
  uint8_t segment_value = SEGMENT_MAP[segment_index];
  shiftOut(segment_register_.data_pin,
           segment_register_.clk_pin,
           LSBFIRST,
           segment_value);

  // Latch values
  Pulse(digit_register_.latch_pin);
  if (digit_register_.latch_pin != segment_register_.latch_pin) {
    Pulse(segment_register_.latch_pin);
  }
}

void FourDigitDisplay::Pulse(uint8_t pin) {
  digitalWrite(pin, HIGH);
  digitalWrite(pin, LOW);
}
