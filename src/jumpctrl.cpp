/***************************************************************************
                                jumpctrl.cpp
                            -------------------
    begin                : Tue Oct 03 2000
    copyright            : (C) 2000 by Carlucio Santos Cordeiro

    DCC - UFMG - Computer Organization & Design

 ***************************************************************************/

///   Header files   ////////////////////////////////////////
///                  ////////////////////////////////////////

#include "jumpctrl.h"


// FUNCTION    : jump_ctrl ( SIGNAL JUMPTYPE[2] , SIGNAL COND[3] , flag_t FLAGS , SIGNAL &PCSRC1 )
// DESCRIPTION :
void jump_ctrl ( SIGNAL JUMPTYPE[2] , SIGNAL COND[3] , flag_t FLAGS , SIGNAL& PCSRC1 )
{
    SIGNAL FLAG ;

    MUX8 ( FLAG , FLAGS[5] , X , X , FLAGS[4] ,  FLAGS[0] , FLAGS[1] , FLAGS[3] , FLAGS[2] , COND ) ;
    MUX4 ( PCSRC1 , 0 , 1 , !FLAG , FLAG , JUMPTYPE ) ;
}
