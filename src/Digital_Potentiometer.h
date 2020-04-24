#ifndef DIGITAL_POTENTIOMETER_H
#define DIGITAL_POTENTIOMETER_H


/*============================================================================*/
/* Inclusions */
/*============================================================================*/
/* Attributes */
#include <stdint.h>


/* Realized interfaces */
#include "Rotary_Encoder.h"


/* Required interfaces */
#include "Discrete_Input.h"


/* Received events */
#include "Hardware_Interruption_Arised.h"


/* Sent events */
#include "Encoder_Rotated.h"
#include "Button_Pressed.h"
#include "Button_Released.h"


/*============================================================================*/
/* Component_Type */
/*============================================================================*/
typedef struct {
    uint16_t Absolute_Angular_Position;
    uint8_t Last_Code;
} Digital_Potentiometer_Var;


typedef struct {
    
    /* Variable attributes */
    Digital_Potentiometer_Var* Var_Attr;
    
    /* Required interfaces */
    const Discrete_Input* Pin_A_Level;
    const Discrete_Input* Pin_B_Level;
    
    /* Sent events */
    Encoder_Rotated Shaft_Rotated;
    Button_Pressed Button_Pressed;
    Button_Released Button_Released;

    /* Configuration_Parameters */
    const uint16_t Number_Of_Increments;
    
} Digital_Potentiometer;


/*============================================================================*/
/* Realized interfaces */
/*============================================================================*/
void DigitPot__Shaft_Position__Get_Shaft_Absolute_Angular_Position( 
    const Digital_Potentiometer* Me,
    uint16_t* shaft_pos );
void DigitPot__Shaft_Position__Reset_Shaft_Absolute_Angular_Position( 
    const Digital_Potentiometer* Me );


/*============================================================================*/
/* Received events */
/*============================================================================*/
void DigitPot__Hw_Interrupt_On_A_Pin( 
    const Digital_Potentiometer* Me,
    E_IO_Level Pin_Level );
void DigitPot__Hw_Interrupt_On_B_Pin(
    const Digital_Potentiometer* Me,
    E_IO_Level Pin_Level );
void DigitPot__Hw_Interrupt_On_Push_Button_Pin(
    const Digital_Potentiometer* Me, 
    E_IO_Level Pin_Level );

#endif