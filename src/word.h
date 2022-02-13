/***************************************************************************
                                 word.h
                             -------------------
    begin                : Wed May 10 2000
    copyright            : (C) 2000 by Carlucio Santos Cordeiro

    DCC - UFMG - Computer Organization & Design

 ***************************************************************************/

#ifndef WORD_H
#define WORD_H

///   Header files   ////////////////////////////////////////
///                  ////////////////////////////////////////

#include "logic.h"
#include <stdio.h>


///   Definitions   /////////////////////////////////////////
///                 /////////////////////////////////////////

#define WORDSIZE 16

typedef SIGNAL word[WORDSIZE] ;


///   Function     //////////////////////////////////////////
///   Prototypes   //////////////////////////////////////////

void WORD_NOT  ( word &O , word I ) ;
void WORD_AND2 ( word &O , word I0 , word I1 ) ;
void WORD_MUX2 ( word &O , word I0 ,
                            word I1 ,
                  SIGNAL C ) ;
void WORD_MUX4 ( word &O , word I0 ,
                            word I1 ,
                            word I2 ,
                            word I3 ,
                  SIGNAL C[2] ) ;
void WORD_MUX8 ( word &O , word I0 ,
                            word I1 ,
                            word I2 ,
                            word I3 ,
                            word I4 ,
                            word I5 ,
                            word I6 ,
                            word I7 ,
                  SIGNAL C[3] ) ;

void print_word_bin ( word W ) ;
void print_word_dec ( word W ) ;
void print_word_hex ( word W ) ;
void put_word_dec ( word &W , short D ) ;
void put_dec_word ( unsigned short &D , word W ) ;


#endif
