/***************************************************************************
                                 logic.cpp
                             -------------------
    begin                : Wed Jun 21 2000
    copyright            : (C) 2000 by Carlucio Santos Cordeiro

    DCC - UFMG - Computer Organization & Design

 ***************************************************************************/

///   Header files   ////////////////////////////////////////
///                  ////////////////////////////////////////

#include "logic.h"


///   FUNCTION    : AND4 .
///   EXPLANATION : Implements a 4 inputs and gate.
void AND4 ( SIGNAL &O , SIGNAL I0 ,
                        SIGNAL I1 ,
                        SIGNAL I2 ,
                        SIGNAL I3 )
{
    SIGNAL O1 , O2 ;

    AND2 ( O1 , I0 , I1 ) ;
    AND2 ( O2 , I2 , I3 ) ;
    AND2 ( O , O1 , O2 ) ;
}


///   FUNCTION    : OR4 .
///   EXPLANATION : Implements a 4 inputs or gate.
void OR4 ( SIGNAL &O , SIGNAL I0 ,
                        SIGNAL I1 ,
                        SIGNAL I2 ,
                        SIGNAL I3 )
{
    SIGNAL O1 , O2 ;

    OR2 ( O1 , I0 , I1 ) ;
    OR2 ( O2 , I2 , I3 ) ;
    OR2 ( O , O1 , O2 ) ;
}


///   FUNCTION    : AND16 .
///   EXPLANATION : Implements a 16 inputs and gate.
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
                          SIGNAL I15 )
{
    SIGNAL O1 , O2 , O3 , O4 ;

    AND4 ( O1 , I0 , I1 , I2 , I3 ) ;
    AND4 ( O2 , I4 , I5 , I6 , I7 ) ;
    AND4 ( O3 , I8 , I9 , I10 , I11 ) ;
    AND4 ( O4 , I12 , I13 , I14 , I15 ) ;
    AND4 ( O , O1 , O2 , O3 , O4 ) ;
}


///   FUNCTION    : NOR16 .
///   EXPLANATION : Implements a 16 inputs nor gate.
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
                          SIGNAL I15 )
{
    SIGNAL O1 , O2 , O3 , O4 ,O0 ;

    OR4 ( O1 , I0 , I1 , I2 , I3 ) ;
    OR4 ( O2 , I4 , I5 , I6 , I7 ) ;
    OR4 ( O3 , I8 , I9 , I10 , I11 ) ;
    OR4 ( O4 , I12 , I13 , I14 , I15 ) ;
    OR4 ( O0 , O1 , O2 , O3 , O4 ) ;
    NOT ( O , O0 ) ;
}


///   FUNCTION    : MUX4 .
///   EXPLANATION : Implements a 4:1 mux .
void MUX4 ( SIGNAL &O , SIGNAL I0 ,
                        SIGNAL I1 ,
                        SIGNAL I2 ,
                        SIGNAL I3 ,
            SIGNAL C[2] )
{
    SIGNAL AUX0 , AUX1 ;

    MUX2 ( AUX0 , I0 , I1 , C[0] ) ;
    MUX2 ( AUX1 , I2 , I3 , C[0] ) ;

    MUX2 ( O , AUX0 , AUX1 , C[1] ) ;
}


///   FUNCTION    : MUX8 .
///   EXPLANATION : Implements a 8:1 mux .
void MUX8 ( SIGNAL &O , SIGNAL I0 ,
                        SIGNAL I1 ,
                        SIGNAL I2 ,
                        SIGNAL I3 ,
                        SIGNAL I4 ,
                        SIGNAL I5 ,
                        SIGNAL I6 ,
                        SIGNAL I7 ,
            SIGNAL C[3] )
{
    SIGNAL AUX0 , AUX1 ;

    MUX4 ( AUX0 , I0 , I1 , I2 , I3 , &C[0] ) ;
    MUX4 ( AUX1 , I4 , I5 , I6 , I7 , &C[0] ) ;

    MUX2 ( O , AUX0 , AUX1 , C[2] ) ;
}


///   FUNCTION    : FULL_ADDER .
///   EXPLANATION : Implements a full adder ( 1 bit ) .
void FULL_ADDER ( SIGNAL &C , SIGNAL &COUT , SIGNAL A , SIGNAL B , SIGNAL CIN )
{
    SIGNAL A1 , A2 , A3 ;

    XOR3 ( C , A , B , CIN ) ;

    AND2 ( A1 , B , CIN ) ;
    AND2 ( A2 , A , CIN ) ;
    AND2 ( A3 , A , B ) ;
    OR3 ( COUT , A1 , A2 , A3 ) ;
}
