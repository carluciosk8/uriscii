/***************************************************************************
                                   alu.h
                             -------------------
    begin                : Fri Jun 23 2000
    copyright            : (C) 2000 by Carlucio Santos Cordeiro

    DCC - UFMG - Computer Organization & Design

 ***************************************************************************/


#ifndef ALU_H
#define ALU_H

///   Header files   ////////////////////////////////////////
///                  ////////////////////////////////////////

#include "logic.h"
#include "word.h"
#include "reg.h"



///   Definitions   /////////////////////////////////////////
///                 /////////////////////////////////////////

typedef SIGNAL flag_t[6] ;

const word ROM[32] = {
    //                       OP    ALU-SRC-A  ALU-SRC-B  CARRY_SRC  OVER_SRC  LS-AS  CIN    not used (don't care)
    /*  0 - zeros     */   {0,1,0,    0,1,      0,1,         0,0,      0,0,      X,   X,      X,X,X},
    /*  1 - ones      */   {1,1,0,    1,1,      0,1,         0,0,      0,0,      X,   X,      X,X,X},
    /*  2 - and       */   {0,1,0,    0,0,      0,0,         0,0,      0,0,      X,   X,      X,X,X},
    /*  3 - nand      */   {1,1,0,    1,0,      1,0,         0,0,      0,0,      X,   X,      X,X,X},
    /*  4 - or        */   {1,1,0,    0,0,      0,0,         0,0,      0,0,      X,   X,      X,X,X},
    /*  5 - nor       */   {0,1,0,    1,0,      1,0,         0,0,      0,0,      X,   X,      X,X,X},
    /*  6 - xor       */   {0,0,1,    0,0,      0,0,         0,0,      0,0,      X,   X,      X,X,X},
    /*  7 - xnor      */   {0,0,1,    1,0,      0,0,         0,0,      0,0,      X,   X,      X,X,X},
    /*  8 - passnota  */   {1,1,0,    1,0,      0,1,         0,0,      0,0,      X,   X,      X,X,X},
    /*  9 - passa     */   {1,1,0,    0,0,      0,1,         0,0,      0,0,      X,   X,      X,X,X},
    /* 10 - andnota   */   {0,1,0,    1,0,      0,0,         0,0,      0,0,      X,   X,      X,X,X},
    /* 11 - ornotb    */   {1,1,0,    0,0,      1,0,         0,0,      0,0,      X,   X,      X,X,X},
    /* 12 -           */   {X,X,X,    X,X,      X,X,         X,X,      X,X,      X,   X,      X,X,X},
    /* 13 -           */   {X,X,X,    X,X,      X,X,         X,X,      X,X,      X,   X,      X,X,X},
    /* 14 -           */   {X,X,X,    X,X,      X,X,         X,X,      X,X,      X,   X,      X,X,X},
    /* 15 -           */   {X,X,X,    X,X,      X,X,         X,X,      X,X,      X,   X,      X,X,X},
    /* 16 - lsl       */   {0,0,0,    0,0,      X,X,         0,1,      0,0,      0,   X,      X,X,X},
    /* 17 - asl       */   {0,0,0,    0,0,      X,X,         0,1,      0,1,      1,   X,      X,X,X},
    /* 18 - lsr       */   {1,0,1,    0,0,      X,X,         0,0,      0,0,      0,   X,      X,X,X},
    /* 19 - asr       */   {1,0,1,    0,0,      X,X,         0,0,      0,0,      1,   X,      X,X,X},
    /* 20 - load      */   {1,1,0,    0,0,      0,1,         X,X,      X,X,      X,   X,      X,X,X},
    /* 21 -           */   {X,X,X,    X,X,      X,X,         X,X,      X,X,      X,   X,      X,X,X},
    /* 22 - store     */   {1,1,0,    0,0,      0,1,         X,X,      X,X,      X,   X,      X,X,X},
    /* 23 -           */   {X,X,X,    X,X,      X,X,         X,X,      X,X,      X,   X,      X,X,X},
    /* 24 - add       */   {1,0,0,    0,0,      0,0,         1,0,      1,0,      X,   0,      X,X,X},
    /* 25 - sub       */   {1,0,0,    0,0,      1,0,         1,0,      1,0,      X,   1,      X,X,X},
    /* 26 - addinc    */   {1,0,0,    0,0,      0,0,         1,0,      1,0,      X,   1,      X,X,X},
    /* 27 - subdec    */   {1,0,0,    0,0,      1,0,         1,0,      1,0,      X,   0,      X,X,X},
    /* 28 - inca      */   {1,0,0,    0,0,      0,1,         1,0,      1,0,      X,   1,      X,X,X},
    /* 29 - deca      */   {1,0,0,    0,0,      1,1,         1,0,      1,0,      X,   0,      X,X,X},
    /* 30 -           */   {X,X,X,    X,X,      X,X,         X,X,      X,X,      X,   X,      X,X,X},
    /* 31 -           */   {X,X,X,    X,X,      X,X,         X,X,      X,X,      X,   X,      X,X,X},

};



///   Class         /////////////////////////////////////////
///   Definitions   /////////////////////////////////////////

// 1bit ALU object.
class bit_alu_t
{
private:
    SIGNAL MUX_IN[6] ;  // 0 = A[-1]
    // 1 = A + B
    // 2 = A & B
    // 3 = A | B
    // 4 = A ^ B
    // 5 = A[+1]


public:

    void EX ( SIGNAL &COUT , SIGNAL &C ,
              SIGNAL A , SIGNAL B , SIGNAL A_MINUS_1 , SIGNAL A_PLUS_1 ,
              SIGNAL CIN , SIGNAL OP[3] ) ;

};



// Flags register object.
class flag_reg_t
{
private:

    reg_t FLAG_REG[6] ;  // 0 - neg.
    // 1 - zero.
    // 2 - negzero.
    // 3 - carry.
    // 4 - overflow.
    // 5 - true.


public:

    void EX ( flag_t &O , flag_t I , SIGNAL RW ) ;

};



// ALU ROM object.
class alu_rom_t
{
private:

    word ROM_DATA[32] ;


public:

    alu_rom_t() ;

    void READ ( SIGNAL ADDRESS[5] , word &DATA ) ;

};



// 16 bit ALU object.
class alu_t
{
private:

    bit_alu_t  BIT_ALU[16] ;
    alu_rom_t  ALU_ROM ;
    flag_reg_t ALU_FLAGS ;


public:

    void EX ( word &ALUOUT , flag_t &FLAGS , word A , word B , SIGNAL ALUOP[5] , SIGNAL FLAGWRITE ) ;

};


#endif
