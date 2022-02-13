/***************************************************************************
                                   reg.h
                             -------------------
    begin                : Thu Jun 22 2000
    copyright            : (C) 2000 by Carlucio Santos Cordeiro

    DCC - UFMG - Computer Organization & Design

 ***************************************************************************/


#ifndef REG_H
#define REG_H

#include "word.h"
#include "sim_defines.h"

///   Class         /////////////////////////////////////////
///   Definitions   /////////////////////////////////////////


//  CLASS : reg_t
//  DESC  : This class implements a 1 bit register with a
//          regwirte control
class reg_t
{
private :
    SIGNAL DATA ;

public :
    reg_t() : DATA(1) {}
    void EX ( SIGNAL &O , SIGNAL I , SIGNAL RW ) ;
};


//  CLASS : word_reg_t
//  DESC  : This class implements a 16 bit word register with a
//          regwirte control
class word_reg_t
{
private :
    reg_t REG[16] ;

public :
    void EX ( word &O , word I , SIGNAL RW ) ;
};


#endif
