#ifndef ENCODER_ROTATED_H
#define ENCODER_ROTATED_H

#include "E_Encoder_Rotation_Direction.h"

/* Event_Interface */
/* Sent when the encoder is rotated. */
typedef void (*Encoder_Rotated) (
    E_Encoder_Rotation_Direction Rotation_Direction );

#endif