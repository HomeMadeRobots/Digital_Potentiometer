#ifndef ROTARY_ENCODER_H
#define ROTARY_ENCODER_H

#include "stdint.h"

/* Client_Server_Interface */
/* Gathers operations allowing to manage a rotary encoder. */
typedef struct {
    void (*Get_Shaft_Absolute_Angular_Position)( uint16_t* shaft_pos );
    void (*Reset_Shaft_Absolute_Angular_Position)( void );
} Rotary_Encoder;

#endif