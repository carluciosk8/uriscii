/***************************************************************************
                                   logic.h
                             -------------------
    begin                : Wed jun 21 2000
    copyright            : (C) 2000 by Carlucio Santos Cordeiro

    DCC - UFMG - Computer Organization & Design

 ***************************************************************************/

#ifndef LOGIC_H
#define LOGIC_H

///   Header files   ////////////////////////////////////////
///                  ////////////////////////////////////////

#include "sim_defines.h"


///   Definitions   /////////////////////////////////////////
///                 /////////////////////////////////////////

#define X 0        // Don't care.


///   Function     //////////////////////////////////////////
///   Prototypes   //////////////////////////////////////////

void AND4 ( SIGNAL &O , SIGNAL I0 ,
                        SIGNAL I1 ,
                        SIGNAL I2 ,
                        SIGNAL I3 ) ;

void OR4 ( SIGNAL &O , SIGNAL I0 ,
                        SIGNAL I1 ,
                        SIGNAL I2 ,
                        SIGNAL I3 ) ;

void AND16 ( SIGNAL &O , SIGNAL I0 ,
                          SIGNAL I1 ,
                          SIGNAL I2 ,
                          SIGNAL I3 ,
                          SIGNAL I4 ,
                          SIGNAL I5 ,
                          SIGNAL I6 ,
                          SIGNAL I7 ,
                          SIGNAL I8 ,
                          SIGNAL I9 ,
                          SIGNAL I10 ,
                          SIGNAL I11 ,
                          SIGNAL I12 ,
                          SIGNAL I13 ,
                          SIGNAL I14 ,
                          SIGNAL I15 ) ;

void NOR16 ( SIGNAL &O , SIGNAL I0 ,
                          SIGNAL I1 ,
                          SIGNAL I2 ,
                          SIGNAL I3 ,
                          SIGNAL I4 ,
                          SIGNAL I5 ,
                          SIGNAL I6 ,
                          SIGNAL I7 ,
                          SIGNAL I8 ,
                          SIGNAL I9 ,
                          SIGNAL I10 ,
                          SIGNAL I11 ,
                          SIGNAL I12 ,
                          SIGNAL I13 ,
                          SIGNAL I14 ,
                          SIGNAL I15 ) ;

void MUX4 ( SIGNAL &O , SIGNAL I0 ,
                        SIGNAL I1 ,
                        SIGNAL I2 ,
                        SIGNAL I3 ,
            SIGNAL C[2] ) ;

void MUX8 ( SIGNAL &O , SIGNAL I0 ,
                        SIGNAL I1 ,
                        SIGNAL I2 ,
                        SIGNAL I3 ,
                        SIGNAL I4 ,
                        SIGNAL I5 ,
                        SIGNAL I6 ,
                        SIGNAL I7 ,
            SIGNAL C[3] ) ;

void FULL_ADDER ( SIGNAL &C , SIGNAL &COUT , SIGNAL A , SIGNAL B , SIGNAL CIN ) ;


#endif
