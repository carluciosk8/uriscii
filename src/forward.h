/***************************************************************************
                                  forward.h
                             -------------------
    begin                : Tue Oct 03 2000
    copyright            : (C) 2000 by Carlucio Santos Cordeiro

    DCC - UFMG - Computer Organization & Design

 ***************************************************************************/


#ifndef FORWARD_H
#define FORWARD_H


///   Header files   ////////////////////////////////////////
///                  ////////////////////////////////////////

#include "logic.h"


/// FUNCTION PROTOTYPES  ////////////////////////////////////
///                      ////////////////////////////////////
void forward ( SIGNAL RA[3] , SIGNAL RB[3] , SIGNAL RC[3] , SIGNAL RW , SIGNAL& FWA , SIGNAL& FWB ) ;
void jmpfwd ( SIGNAL RB[3] , SIGNAL RC[3] , SIGNAL RW , SIGNAL& JMPFW ) ;


#endif
