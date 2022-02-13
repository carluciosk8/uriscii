/***************************************************************************
                                jumpctrl.h
                            -------------------
    begin                : Tue Oct 03 2000
    copyright            : (C) 2000 by Carlucio Santos Cordeiro

    DCC - UFMG - Computer Organization & Design

 ***************************************************************************/

#ifndef JUMPCTRL_H
#define JUMPCTRL_H

///   Header files   ////////////////////////////////////////
///                  ////////////////////////////////////////

#include "word.h"
#include "alu.h"

// FUNCTION    : jump_ctrl ( SIGNAL JUMPTYPE[2] , SIGNAL COND[3] , flag_t FLAGS , SIGNAL &PCSRC1 )
// DESCRIPTION :

void jump_ctrl ( SIGNAL JUMPTYPE[2] , SIGNAL COND[3] , flag_t FLAGS , SIGNAL& PCSRC1 ) ;

#endif
