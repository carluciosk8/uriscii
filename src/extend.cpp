/***************************************************************************
                                 extend.cpp
                             -------------------
    begin                : Fri Jun 23 2000
    copyright            : (C) 2000 by Carlucio Santos Cordeiro

    DCC - UFMG - Computer Organization & Design

 ***************************************************************************/

///   Header files   ////////////////////////////////////////
///                  ////////////////////////////////////////

#include "extend.h"



///   FUNCTION    : extend_t::EX
///   EXPLANATION : Implementa o extensor de sinais.
void extend_t::EX ( offset_t OFFSET , SIGNAL EXT_CTRL[3] , word &OUT )
{
    word OITO ,        // Oito bits sem sinal
         OITO_SL8 ,    // Oito bits << 8
         OITO_SINAL ,  // Oito bits com sinal
         ONZE_SINAL ,  // Onze  '    '    '
         DOZE_SINAL ,  // Doze  '    '    '
         XX={X,X,X,X,X,X,X,X,X,X,X,X,X,X,X,X} ; // Don't care


    OITO[0] = OFFSET[0] ;
    OITO[1] = OFFSET[1] ;
    OITO[2] = OFFSET[2] ;
    OITO[3] = OFFSET[3] ;
    OITO[4] = OFFSET[4] ;
    OITO[5] = OFFSET[5] ;
    OITO[6] = OFFSET[6] ;
    OITO[7] = OFFSET[7] ;
    OITO[8] = 0 ;
    OITO[9] = 0 ;
    OITO[10] = 0 ;
    OITO[11] = 0 ;
    OITO[12] = 0 ;
    OITO[13] = 0 ;
    OITO[14] = 0 ;
    OITO[15] = 0 ;

    OITO_SL8[0] = 0 ;
    OITO_SL8[1] = 0 ;
    OITO_SL8[2] = 0 ;
    OITO_SL8[3] = 0 ;
    OITO_SL8[4] = 0 ;
    OITO_SL8[5] = 0 ;
    OITO_SL8[6] = 0 ;
    OITO_SL8[7] = 0 ;
    OITO_SL8[8] =  OFFSET[0] ;
    OITO_SL8[9] =  OFFSET[1] ;
    OITO_SL8[10] = OFFSET[2] ;
    OITO_SL8[11] = OFFSET[3] ;
    OITO_SL8[12] = OFFSET[4] ;
    OITO_SL8[13] = OFFSET[5] ;
    OITO_SL8[14] = OFFSET[6] ;
    OITO_SL8[15] = OFFSET[7] ;

    OITO_SINAL[0] = OFFSET[0] ;
    OITO_SINAL[1] = OFFSET[1] ;
    OITO_SINAL[2] = OFFSET[2] ;
    OITO_SINAL[3] = OFFSET[3] ;
    OITO_SINAL[4] = OFFSET[4] ;
    OITO_SINAL[5] = OFFSET[5] ;
    OITO_SINAL[6] = OFFSET[6] ;
    OITO_SINAL[7] = OFFSET[7] ;
    OITO_SINAL[8] = OFFSET[7] ;
    OITO_SINAL[9] = OFFSET[7] ;
    OITO_SINAL[10] = OFFSET[7] ;
    OITO_SINAL[11] = OFFSET[7] ;
    OITO_SINAL[12] = OFFSET[7] ;
    OITO_SINAL[13] = OFFSET[7] ;
    OITO_SINAL[14] = OFFSET[7] ;
    OITO_SINAL[15] = OFFSET[7] ;

    ONZE_SINAL[0] = OFFSET[0] ;
    ONZE_SINAL[1] = OFFSET[1] ;
    ONZE_SINAL[2] = OFFSET[2] ;
    ONZE_SINAL[3] = OFFSET[3] ;
    ONZE_SINAL[4] = OFFSET[4] ;
    ONZE_SINAL[5] = OFFSET[5] ;
    ONZE_SINAL[6] = OFFSET[6] ;
    ONZE_SINAL[7] = OFFSET[7] ;
    ONZE_SINAL[8] = OFFSET[8] ;
    ONZE_SINAL[9] = OFFSET[9] ;
    ONZE_SINAL[10] = OFFSET[10] ;
    ONZE_SINAL[11] = OFFSET[10] ;
    ONZE_SINAL[12] = OFFSET[10] ;
    ONZE_SINAL[13] = OFFSET[10] ;
    ONZE_SINAL[14] = OFFSET[10] ;
    ONZE_SINAL[15] = OFFSET[10] ;

    DOZE_SINAL[0] = OFFSET[0] ;
    DOZE_SINAL[1] = OFFSET[1] ;
    DOZE_SINAL[2] = OFFSET[2] ;
    DOZE_SINAL[3] = OFFSET[3] ;
    DOZE_SINAL[4] = OFFSET[4] ;
    DOZE_SINAL[5] = OFFSET[5] ;
    DOZE_SINAL[6] = OFFSET[6] ;
    DOZE_SINAL[7] = OFFSET[7] ;
    DOZE_SINAL[8] = OFFSET[8] ;
    DOZE_SINAL[9] = OFFSET[9] ;
    DOZE_SINAL[10] = OFFSET[10] ;
    DOZE_SINAL[11] = OFFSET[11] ;
    DOZE_SINAL[12] = OFFSET[11] ;
    DOZE_SINAL[13] = OFFSET[11] ;
    DOZE_SINAL[14] = OFFSET[11] ;
    DOZE_SINAL[15] = OFFSET[11] ;


    WORD_MUX8 ( OUT , OITO , OITO_SL8 , OITO_SINAL , ONZE_SINAL , DOZE_SINAL , XX , XX , XX , EXT_CTRL ) ;
}
