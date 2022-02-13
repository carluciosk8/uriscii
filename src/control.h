/***************************************************************************
                                 control.h
                             -------------------
    begin                : Fri Jun 23 2000
    copyright            : (C) 2000 by Carlucio Santos Cordeiro

    DCC - UFMG - Computer Organization & Design

 ***************************************************************************/


#ifndef CONTROL_H
#define CONTROL_H

///   Header files   ////////////////////////////////////////
///                  ////////////////////////////////////////

#include "logic.h"
#include "alu.h"
#include "word.h"
#include "reg.h"


///   Definitions   /////////////////////////////////////////
///                 /////////////////////////////////////////

typedef SIGNAL control_line_t[24] ;


///   Class         /////////////////////////////////////////
///   Definitions   /////////////////////////////////////////


//  CLASS : control_t
//  DESC  : Define o controle do processador.
class control_t
{
public:
    void EX ( word IR , flag_t FLAGS , control_line_t &CONTROL_LINE , SIGNAL &HALT ) ;
    void FETCH ( control_line_t &CONTROL_LINE ) ;
};


///   Function     //////////////////////////////////////////
///   Prototypes   //////////////////////////////////////////

void CONTROL_MUX2 ( control_line_t &O , control_line_t I0 , control_line_t I1 , SIGNAL C ) ;
void CONTROL_MUX4 ( control_line_t &O , control_line_t I0 , control_line_t I1 , control_line_t I2 , control_line_t I3 , SIGNAL C[2] ) ;


#endif
