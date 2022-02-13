/***************************************************************************
                                  extend.h
                             -------------------
    begin                : Mon Jun 26 2000
    copyright            : (C) 2000 by Carlucio Santos Cordeiro

    DCC - UFMG - Computer Organization & Design

 ***************************************************************************/


#ifndef EXTEND_H
#define EXTEND_H

///   Header files   ////////////////////////////////////////
///                  ////////////////////////////////////////

#include "word.h"
#include "logic.h"


///   Definitions   /////////////////////////////////////////
///                 /////////////////////////////////////////

typedef SIGNAL offset_t[12] ;


///   Class         /////////////////////////////////////////
///   Definitions   /////////////////////////////////////////

//  CLASS : extend_t
//  DESC  : Define o subsistema extensor de bits
class extend_t
{
public:
    void EX ( offset_t OFFSET , SIGNAL EXT_CTRL[3] , word &OUT ) ;
};


#endif
