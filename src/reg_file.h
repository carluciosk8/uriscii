/***************************************************************************
                                 reg_file.h
                             -------------------
    begin                : Fri Jun 23 2000
    copyright            : (C) 2000 by Carlucio Santos Cordeiro

    DCC - UFMG - Computer Organization & Design

 ***************************************************************************/


#ifndef REG_FILE_H
#define REG_FILE_H

///   Header files   ////////////////////////////////////////
///                  ////////////////////////////////////////

#include "reg.h"
#include "word.h"
#include "logic.h"


///   Class         /////////////////////////////////////////
///   Definitions   /////////////////////////////////////////

//  CLASS : reg_file_t
//  DESC  : Define o register-file (banco de registradores)
class reg_file_t
{
private:

    word REGS[8] ;


public:

    reg_file_t() ;

    void READ ( SIGNAL RA[3] , SIGNAL RB[3] , word &A , word &B ) ;
    void WRITE ( SIGNAL WC[3] , word C , SIGNAL REG_WRITE ) ;
    void GET_REGS ( unsigned short *REGSV ) ;
};


#endif
