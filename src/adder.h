/***************************************************************************
                                  adder.h
                             -------------------
    begin                : Fri Jun 23 2000
    copyright            : (C) 2000 by Carlucio Santos Cordeiro

    DCC - UFMG - Computer Organization & Design

 ***************************************************************************/


#ifndef ADDER_H
#define ADDER_H

///   Header files   ////////////////////////////////////////
///                  ////////////////////////////////////////

#include "word.h"
#include "logic.h"


///   Class         /////////////////////////////////////////
///   Definitions   /////////////////////////////////////////

//  CLASS : adder_t
//  DESC  : Implementa um adder de 16 bits.

class Adder
{
public:

    void EX ( word &C , word A , word B ) ;
};


#endif
