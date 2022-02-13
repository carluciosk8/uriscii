/***************************************************************************
                                 forward.cpp
                             -------------------
    begin                : Tue Oct 03 2000
    copyright            : (C) 2000 by Carlucio Santos Cordeiro

    DCC - UFMG - Computer Organization & Design

 ***************************************************************************/


///   Header files   ////////////////////////////////////////
///                  ////////////////////////////////////////

#include "forward.h"


// FUNCTION    : forward ( SIGNAL RA[3] , SIGNAL RB[3] , SIGNAL RC[3] , SIGNAL &FWA , SIGNAL &FWB )
// DESCRIPTION : Implements the forwarding unit.
void forward ( SIGNAL RA[3] , SIGNAL RB[3] , SIGNAL RC[3] , SIGNAL RW , SIGNAL& FWA , SIGNAL& FWB )
{
    SIGNAL t0 , t1 , t2 ;

    XOR2( t0 , RA[0] , RC[0] ) ;
    NOT( t0 , t0 ) ;
    XOR2( t1 , RA[1] , RC[1] ) ;
    NOT( t1 , t1 ) ;
    XOR2( t2 , RA[2] , RC[2] ) ;
    NOT( t2 , t2 ) ;
    AND4( FWA , t0 , t1 , t2 , RW ) ;

    XOR2( t0 , RB[0] , RC[0] ) ;
    NOT( t0 , t0 ) ;
    XOR2( t1 , RB[1] , RC[1] ) ;
    NOT( t1 , t1 ) ;
    XOR2( t2 , RB[2] , RC[2] ) ;
    NOT( t2 , t2 ) ;
    AND4( FWB , t0 , t1 , t2 , RW ) ;
}

void jmpfwd ( SIGNAL RB[3] , SIGNAL RC[3] , SIGNAL RW , SIGNAL& JMPFW )
{
    SIGNAL t0 , t1 , t2 ;

    XOR2( t0 , RB[0] , RC[0] ) ;
    NOT( t0 , t0 ) ;
    XOR2( t1 , RB[1] , RC[1] ) ;
    NOT( t1 , t1 ) ;
    XOR2( t2 , RB[2] , RC[2] ) ;
    NOT( t2 , t2 ) ;
    AND4( JMPFW , t0 , t1 , t2 , RW ) ;
}
