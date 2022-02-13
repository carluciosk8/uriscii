/***************************************************************************
                                reg_file.cpp
                             -------------------
    begin                : Fri Jun 23 2000
    copyright            : (C) 2000 by Carlucio Santos Cordeiro

    DCC - UFMG - Computer Organization & Design

 ***************************************************************************/

///   Header files   ////////////////////////////////////////
///                  ////////////////////////////////////////

#include "reg_file.h"


///   FUNCTION    : reg_file_t::reg_file_t
///   EXPLANATION : Construtora: Zera o banco de registradores.
reg_file_t::reg_file_t()
{
    int CONT , C ;

    for ( CONT=0 ; CONT<8 ; CONT++ )
        for ( C=0 ; C<WORDSIZE ; C++ )
            REGS[CONT][C] = 0 ;
}


///   FUNCTION    : reg_file_t::READ
///   EXPLANATION : Le do banco de registradores.
void reg_file_t::READ ( SIGNAL RA[3] , SIGNAL RB[3] , word &A , word &B )
{
    int  AA , BB ,
         CONT , P2 ;

    P2 = 1 ;
    AA = 0 ;
    for ( CONT = 0 ; CONT < 3 ; CONT++)
    {
        AA = AA + P2*RA[CONT] ;
        P2 = P2 << 1 ;
    }

    P2 = 1 ;
    BB = 0 ;
    for ( CONT = 0 ; CONT < 3 ; CONT++)
    {
        BB = BB + P2*RB[CONT] ;
        P2 = P2 << 1 ;
    }

    for ( CONT = 0 ; CONT < WORDSIZE ; CONT++) A[CONT] = REGS[AA][CONT] ;
    for ( CONT = 0 ; CONT < WORDSIZE ; CONT++) B[CONT] = REGS[BB][CONT] ;
}


///   FUNCTION    : reg_file_t::WRITE
///   EXPLANATION : Escreve no banco de registradores.
void reg_file_t::WRITE ( SIGNAL WC[3] , word C , SIGNAL REG_WRITE )
{
    int  CC ,
         CONT , P2 ;

    P2 = 1 ;
    CC = 0 ;
    for ( CONT = 0 ; CONT < 3 ; CONT++)
    {
        CC = CC + P2*WC[CONT] ;
        P2 = P2 << 1 ;
    }

    for ( CONT = 0 ; CONT < WORDSIZE ; CONT++) MUX2 ( REGS[CC][CONT] , REGS[CC][CONT] , C[CONT] , REG_WRITE ) ;
}


///   FUNCTION    : reg_file_t::GET_REGS
///   EXPLANATION : Le os valores dos registradores.
void reg_file_t::GET_REGS ( unsigned short *REGSV )
{
    int CONT ;

    for ( CONT = 0 ; CONT < 8 ; CONT++) put_dec_word ( REGSV[CONT] , REGS[CONT] ) ;
}
