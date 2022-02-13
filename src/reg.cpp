/***************************************************************************
                                 reg.cpp
                             -------------------
    begin                : Wed Jun 21 2000
    copyright            : (C) 2000 by Carlucio Santos Cordeiro

    DCC - UFMG - Computer Organization & Design

 ***************************************************************************/

///   Header files   ////////////////////////////////////////
///                  ////////////////////////////////////////

#include "reg.h"


///   FUNCTION    : reg_t::EX
///   EXPLANATION : Executa a operacao com o registrador de 1 bit.
void reg_t::EX ( SIGNAL &O , SIGNAL I , SIGNAL RW )
{
    MUX2 ( DATA , DATA , I , RW ) ;
    O = DATA ;
}



///   FUNCTION    : word_reg_t::EX
///   EXPLANATION : Executa a operacao com o registrador de 16 bits.
void word_reg_t::EX ( word &O , word I , SIGNAL RW )
{
    int CONT ;
    for ( CONT = 0 ; CONT < WORDSIZE ; CONT++) REG[CONT].EX ( O[CONT] , I[CONT] , RW ) ;
}
