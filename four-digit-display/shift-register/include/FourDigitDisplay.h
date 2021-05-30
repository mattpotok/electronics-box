#ifndef SHIFT_FOUR_DIGIT_DISPLAY_H_
#define SHIFT_FOUR_DIGIT_DISPLAY_H_

#include <stdint.h>

const uint8_t MAX_NUM_DIGITS = 4;

struct ShiftRegister {
  uint8_t data_pin;
  uint8_t clk_pin;
  uint8_t latch_pin;
};

class FourDigitDisplay {
  public:
    FourDigitDisplay(
        const ShiftRegister &digit_register,
        const ShiftRegister &segment_register
    );

    void Display(uint8_t (&segment_indices)[MAX_NUM_DIGITS]);
    void DisplayDigit(uint8_t digit_index, uint8_t segment_index);
    
  private:
    const ShiftRegister digit_register_;
    const ShiftRegister segment_register_;

    void Pulse(uint8_t pin);
};

#endif  // SHIFT_FOUR_DIGIT_DISPLAY_H_
