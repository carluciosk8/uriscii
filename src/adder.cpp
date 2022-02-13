/***************************************************************************
                                  adder.cpp
                             -------------------
    begin                : Fri Jun 23 2000
    copyright            : (C) 2000 by Carlucio Santos Cordeiro

    DCC - UFMG - Computer Organization & Design

 ***************************************************************************/

///   Header files   ////////////////////////////////////////
///                  ////////////////////////////////////////

#include "adder.h"


///   FUNCTION    : adder_t::EX
///   EXPLANATION : Executa a operacao com o 16 bit adder.

void Adder::EX ( word &C , word A , word B )
{
    SIGNAL CIN;
    SIGNAL COUT;

    COUT = 0 ;
    CIN = COUT ; FULL_ADDER ( C[0]  , COUT , A[0]  , B[0]  , CIN ) ;
    CIN = COUT ; FULL_ADDER ( C[1]  , COUT , A[1]  , B[1]  , CIN ) ;
    CIN = COUT ; FULL_ADDER ( C[2]  , COUT , A[2]  , B[2]  , CIN ) ;
    CIN = COUT ; FULL_ADDER ( C[3]  , COUT , A[3]  , B[3]  , CIN ) ;
    CIN = COUT ; FULL_ADDER ( C[4]  , COUT , A[4]  , B[4]  , CIN ) ;
    CIN = COUT ; FULL_ADDER ( C[5]  , COUT , A[5]  , B[5]  , CIN ) ;
    CIN = COUT ; FULL_ADDER ( C[6]  , COUT , A[6]  , B[6]  , CIN ) ;
    CIN = COUT ; FULL_ADDER ( C[7]  , COUT , A[7]  , B[7]  , CIN ) ;
    CIN = COUT ; FULL_ADDER ( C[8]  , COUT , A[8]  , B[8]  , CIN ) ;
    CIN = COUT ; FULL_ADDER ( C[9]  , COUT , A[9]  , B[9]  , CIN ) ;
    CIN = COUT ; FULL_ADDER ( C[10] , COUT , A[10] , B[10] , CIN ) ;
    CIN = COUT ; FULL_ADDER ( C[11] , COUT , A[11] , B[11] , CIN ) ;
    CIN = COUT ; FULL_ADDER ( C[12] , COUT , A[12] , B[12] , CIN ) ;
    CIN = COUT ; FULL_ADDER ( C[13] , COUT , A[13] , B[13] , CIN ) ;
    CIN = COUT ; FULL_ADDER ( C[14] , COUT , A[14] , B[14] , CIN ) ;
    CIN = COUT ; FULL_ADDER ( C[15] , COUT , A[15] , B[15] , CIN ) ;
}
