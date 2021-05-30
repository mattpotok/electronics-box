#include "FourDigitDisplay.h"

const ShiftRegister digit_register = { 6, 4, 3 };
const ShiftRegister segment_register = { 7, 5, 3 };

const FourDigitDisplay fdd(digit_register, segment_register);

void setup() {}

void loop() {
  uint8_t indices[4] = {1, 2, 3, 4};
  fdd.Display(indices);
}
