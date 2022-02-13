/***************************************************************************
                                  memory.h
                             -------------------
    begin                : Fri Jun 23 2000
    copyright            : (C) 2000 by Carlucio Santos Cordeiro

    DCC - UFMG - Computer Organization & Design

 ***************************************************************************/


#ifndef MEMORY_H
#define MEMORY_H

///   Header files   ////////////////////////////////////////
///                  ////////////////////////////////////////

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "word.h"
#include "logic.h"
#include "reg.h"


#define MAX_MEM 65536

///   Class         /////////////////////////////////////////
///   Definitions   /////////////////////////////////////////

//  CLASS : memory_t
//  DESC  : Define a memoria do processador.

class memory_t
{
private:
    word MEM[MAX_MEM] ;

public:
    memory_t() ;

    void EX ( word ADDRESS , word &DATA_OUT , word DATA_IN , SIGNAL MEM_READ , SIGNAL MEM_WRITE ) ;
    void LOAD ( char *ARQ_ENTRADA , word_reg_t &PC ) ;
    void DUMP ( int START , int LENGHT , bool PAUSE ) ;
};


#endif
