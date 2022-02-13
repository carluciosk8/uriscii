/***************************************************************************
                                 word.cpp
                             -------------------
    begin                : Wed Jun 21 2000
    copyright            : (C) 2000 by Carlucio Santos Cordeiro

    DCC - UFMG - Computer Organization & Design

 ***************************************************************************/

///   Header files   ////////////////////////////////////////
///                  ////////////////////////////////////////

#include "word.h"


///   FUNCTION    : WORD_NOT.
///   EXPLANATION : 16 bit word inversor.
void WORD_NOT ( word &O , word I )
{
    int CONT ;

    for ( CONT = 0 ; CONT < WORDSIZE ; CONT++) NOT ( O[CONT] , I[CONT] ) ;
}


///   FUNCTION    : WORD_AND2.
///   EXPLANATION : 2 16 bit words and gate.
void WORD_AND2 ( word &O , word I0 , word I1 )
{
    int CONT ;

    for ( CONT = 0 ; CONT < WORDSIZE ; CONT++) AND2 ( O[CONT] , I0[CONT] , I1[CONT] ) ;
}


///   FUNCTION    : WORD_MUX2.
///   EXPLANATION : Implements a 2:1 mux on a 16 bit word.
void WORD_MUX2 ( word &O , word I0 , word I1 , SIGNAL C )
{
    int CONT ;

    for ( CONT = 0 ; CONT < WORDSIZE ; CONT++) MUX2 ( O[CONT] , I0[CONT] , I1[CONT] , C ) ;
}


///   FUNCTION    : WORD_MUX4.
///   EXPLANATION : Implements a 4:1 mux on a 16 bit word.
void WORD_MUX4 ( word &O , word I0 ,
                            word I1 ,
                            word I2 ,
                            word I3 ,
                  SIGNAL C[2] )
{
    int CONT ;

    for ( CONT = 0 ; CONT < WORDSIZE ; CONT++) MUX4 ( O[CONT] , I0[CONT] , I1[CONT] , I2[CONT] , I3[CONT] , C ) ;
}


///   FUNCTION    : WORD_MUX8.
///   EXPLANATION : Implements a 8:1 mux on a 16 bit word.
void WORD_MUX8 ( word &O , word I0 ,
                            word I1 ,
                            word I2 ,
                            word I3 ,
                            word I4 ,
                            word I5 ,
                            word I6 ,
                            word I7 ,
                  SIGNAL C[3] )
{
    int CONT ;

    for ( CONT = 0 ; CONT < WORDSIZE ; CONT++) MUX8 ( O[CONT] , I0[CONT] , I1[CONT] , I2[CONT] , I3[CONT] , I4[CONT] , I5[CONT] , I6[CONT] , I7[CONT] , C ) ;
}


///   FUNCTION    : print_word_bin .
///   INPUTS      : word W .
///   OUTPUTS     : none .
///   EXPLANATION : Prints the word in binary representation
void print_word_bin ( word W )
{
    int CONT ;

    for ( CONT=WORDSIZE-1 ; CONT >= 0 ; CONT-- ) printf ( "%d" , W[CONT] ) ;
}


///   FUNCTION    : print_word_dec .
///   INPUTS      : word W .
///   OUTPUTS     : none .
///   EXPLANATION : Prints the word in decimal representation
void print_word_dec ( word W )
{
    short VAL ;
    int CONT , P2 ;

    P2 = 1 ;
    VAL = 0 ;
    for ( CONT = 0 ; CONT < WORDSIZE ; CONT++)
    {
        VAL = VAL + P2*W[CONT] ;
        P2 = P2 << 1 ;
    }
    printf ( "%d" , VAL ) ;
}


///   FUNCTION    : print_word_hex .
///   INPUTS      : word W .
///   OUTPUTS     : none .
///   EXPLANATION : Prints the word in hexadecimal representation
void print_word_hex ( word W )
{
    unsigned short VAL ;
    int CONT , P2 ;

    P2 = 1 ;
    VAL = 0 ;
    for ( CONT = 0 ; CONT < WORDSIZE ; CONT++)
    {
        VAL = VAL + P2*W[CONT] ;
        P2 = P2 << 1 ;
    }
    printf ( "%4X" , VAL ) ;
}


///   FUNCTION    : put_word_dec .
///   INPUTS      : int D .
///   OUTPUTS     : word W .
///   EXPLANATION : Converts the decimal representation to 16 bit word representation.
void put_word_dec ( word &W , short D )
{
    int CONT , P2 ;

    P2 = 1 ;
    for ( CONT = 0 ; CONT < WORDSIZE ; CONT++)
    {
        if ( P2 & D ) W[CONT] = 1 ;
        else W[CONT] = 0 ;
        P2 = P2 << 1 ;
    }
}


///   FUNCTION    : put_dec_word .
///   EXPLANATION : Converts the 16 bit word representation decimal to representation.
void put_dec_word ( unsigned short &D , word W )
{
    short VAL ;
    int CONT , P2 ;

    P2 = 1 ;
    VAL = 0 ;
    for ( CONT = 0 ; CONT < WORDSIZE ; CONT++)
    {
        VAL = VAL + P2*W[CONT] ;
        P2 = P2 << 1 ;
    }
    D = (unsigned short) VAL ;
}
