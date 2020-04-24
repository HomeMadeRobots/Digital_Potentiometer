#ifndef E_TWO_PINS_ENCODER_STATE_H
#define E_TWO_PINS_ENCODER_STATE_H

/* Enumerated_Data_Type */
/* Allows to model a variable representing the (hardware) state that can have 
the two pins of an rotary encoder. */
typedef enum E_Two_Pins_Encoder_State {
    PIN_A_OFF_PIN_B_OFF = 0,
    PIN_A_OFF_PIN_B_ON = 1,
    PIN_A_ON_PIN_B_OFF = 2,
    PIN_A_ON_PIN_B_ON = 3
} E_Two_Pins_Encoder_State;

#endif