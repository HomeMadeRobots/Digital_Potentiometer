#include "Digital_Potentiometer.h"


/*============================================================================*/
/* Attributes access */
/*============================================================================*/
#define My_Absolute_Angular_Position (Me->Var_Attr->Absolute_Angular_Position)
#define My_Last_Code (Me->Var_Attr->Last_Code)


/*============================================================================*/
/* Required interfaces access */
/*============================================================================*/
#define Pin_A_Level__Get_Level( level ) \
        Me->Pin_A_Level->Get_Level( level )

#define Pin_B_Level__Get_Level( level ) \
        Me->Pin_B_Level->Get_Level( level )
        

/*============================================================================*/
/* Private methods declaration */
/*============================================================================*/
static void Treat_Code( 
    const Digital_Potentiometer* Me, 
    uint8_t pin_A_level, 
    uint8_t pin_B_level );


/*============================================================================*/
/* Realized interfaces */
/*============================================================================*/
void DigitPot__Shaft_Position__Get_Shaft_Absolute_Angular_Position( 
    const Digital_Potentiometer* Me,
    uint16_t* shaft_pos )
{
    *shaft_pos = My_Absolute_Angular_Position;
}
/*----------------------------------------------------------------------------*/
void DigitPot__Shaft_Position__Reset_Shaft_Absolute_Angular_Position( 
    const Digital_Potentiometer* Me )
{
    My_Absolute_Angular_Position = 0;
}


/*============================================================================*/
/* Received events */
/*============================================================================*/
void DigitPot__Hw_Interrupt_On_A_Pin( 
    const Digital_Potentiometer* Me,
    E_IO_Level Pin_Level,
    uint32_t Interruption_Timestamp )
{
    /* Get level of Pin B */
    E_IO_Level pin_B_level = IO_LEVEL_LOW;
    Pin_B_Level__Get_Level( &pin_B_level );

    /* Compute sensor motion */
    Treat_Code( Me, Pin_Level, pin_B_level );
}
/*----------------------------------------------------------------------------*/    
void DigitPot__Hw_Interrupt_On_B_Pin(
    const Digital_Potentiometer* Me,
    E_IO_Level Pin_Level,
    uint32_t Interruption_Timestamp )
{
    /* Get level of Pin A */
    E_IO_Level pin_A_level = IO_LEVEL_LOW;
    Pin_A_Level__Get_Level( &pin_A_level );

    /* Compute sensor motion */
    Treat_Code( Me, pin_A_level, Pin_Level );
}    
/*----------------------------------------------------------------------------*/
void DigitPot__Hw_Interrupt_On_Push_Button_Pin(
    const Digital_Potentiometer* Me, 
    E_IO_Level Pin_Level,
    uint32_t Interruption_Timestamp )
{
    /* Test level of switch pin */
    if( IO_LEVEL_LOW==Pin_Level )
    { /* Pin is low */
        (Me->Button_Pressed)();
    }
    else
    { /* Pin is high */
        (Me->Button_Released)();
    }
}


/*============================================================================*/
/* Private methods definition */
/*============================================================================*/
static void Treat_Code( 
    const Digital_Potentiometer* Me, 
    uint8_t pin_A_level,
    uint8_t pin_B_level )
{
    uint8_t current_code; /* 2 bits carrier for pins current status, 
                             bit 0 for B, bit 1 for A */
    uint8_t state; /* 4 bits carrier */
    /*
    state = bit3|bit2|bit1|bit0
              |    |    |    |
              |    |    |    ----> current status of pin B    
              |    |    ---------> current status of pin A
              |    --------------> previous status of pin B
              -------------------> previous status of pin A

    Following states are invalid : 0b0011, 0b1100, 0b1001, 0b0110.
    Both pins cannot change state at mean time.

    Following states mean the encoder has not moved (idle) : 
    0b0000, 0b0101, 0b1010, 0b1111.
    */

    current_code = ( (pin_A_level==IO_LEVEL_HIGH) << 1)
                    | (pin_B_level==IO_LEVEL_HIGH);
    state = (My_Last_Code << 2) | current_code;

    if( 0b1101==state || 0b0100==state || 0b0010==state || 0b1011==state )
    { /* Encoder has moved clockwise */
        /* Update Absolute_Angular_Position */
        if( My_Absolute_Angular_Position == (Me->Number_Of_Increments - 1) )
        { /* Full turn */
            My_Absolute_Angular_Position = 0;
        }
        else
        {
            My_Absolute_Angular_Position++;
        }

        /* Send Shaft_Rotated event */
        (Me->Shaft_Rotated)(CLOCKWISE);
    }
    if( 0b1110==state || 0b0111==state || 0b0001==state || 0b1000==state )
    { /* Encoder has moved counterclockwise */
        /* Update Absolute_Angular_Position */
        if( My_Absolute_Angular_Position == 0 )
        { /* Full turn */
            My_Absolute_Angular_Position = (Me->Number_Of_Increments - 1);
        }
        else
        {
            My_Absolute_Angular_Position--;
        }

        /* Send Shaft_Rotated event */
        (Me->Shaft_Rotated)(COUNTERCLOCKWISE);
    }

    /* Save current code */
    My_Last_Code = current_code;  
}