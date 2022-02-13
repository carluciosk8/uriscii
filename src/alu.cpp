/***************************************************************************
                                 alu.cpp
                             -------------------
    begin                : Fri Jun 23 2000
    copyright            : (C) 2000 by Carlucio Santos Cordeiro

    DCC - UFMG - Computer Organization & Design

 ***************************************************************************/

///   Header files   ////////////////////////////////////////
///                  ////////////////////////////////////////

#include "alu.h"

#include <cstring>


///   FUNCTION    : 1bit_alu_t::EX
///   EXPLANATION : Implementa uma ALU de 1 bit.

void bit_alu_t::EX ( SIGNAL &COUT , SIGNAL &C ,
                     SIGNAL A , SIGNAL B , SIGNAL A_MINUS_1 , SIGNAL A_PLUS_1 ,
                     SIGNAL CIN , SIGNAL OP[3] )
{
    MUX_IN[0] = A_MINUS_1 ;
    FULL_ADDER ( MUX_IN[1] , COUT , A , B , CIN ) ;
    AND2 ( MUX_IN[2] , A , B ) ;
    OR2  ( MUX_IN[3] , A , B ) ;
    XOR2 ( MUX_IN[4] , A , B ) ;
    MUX_IN[5] = A_PLUS_1 ;

    MUX8 ( C , MUX_IN[0] ,
            MUX_IN[1] ,
            MUX_IN[2] ,
            MUX_IN[3] ,
            MUX_IN[4] ,
            MUX_IN[5] ,
            X ,
            X ,
            OP ) ;
}



///   FUNCTION    : flag_reg_t::EX
///   EXPLANATION : Implementa o registrador de flags da ALU.

void flag_reg_t::EX ( flag_t &O , flag_t I , SIGNAL RW )
{
    FLAG_REG[0].EX ( O[0] , I[0] , RW ) ;
    FLAG_REG[1].EX ( O[1] , I[1] , RW ) ;
    FLAG_REG[2].EX ( O[2] , I[2] , RW ) ;
    FLAG_REG[3].EX ( O[3] , I[3] , RW ) ;
    FLAG_REG[4].EX ( O[4] , I[4] , RW ) ;
    FLAG_REG[5].EX ( O[5] , I[5] , RW ) ;
}



///   FUNCTION    : alu_rom_t::alu_rom_t
///   EXPLANATION : Construtora da classe alu_rom_t : Incicializa o conteudo da rom.

alu_rom_t::alu_rom_t()
{
    memcpy ( ROM_DATA , ROM , sizeof(word)*32 ) ;
}



///   FUNCTION    : flag_reg_t::EX
///   EXPLANATION : Implementa o registrador de flags da ALU.

void alu_rom_t::READ ( SIGNAL ADDRESS[5] , word &DATA )
{
    int ADDR , P2 ;

    P2 = 1 ;
    ADDR = 0 ;

    ADDR += P2 * ADDRESS[0]  ; P2 = P2 << 1 ;
    ADDR += P2 * ADDRESS[1]  ; P2 = P2 << 1 ;
    ADDR += P2 * ADDRESS[2]  ; P2 = P2 << 1 ;
    ADDR += P2 * ADDRESS[3]  ; P2 = P2 << 1 ;
    ADDR += P2 * ADDRESS[4]  ; P2 = P2 << 1 ;

    DATA[0]  = ROM_DATA[ADDR][0] ;
    DATA[1]  = ROM_DATA[ADDR][1] ;
    DATA[2]  = ROM_DATA[ADDR][2] ;
    DATA[3]  = ROM_DATA[ADDR][3] ;
    DATA[4]  = ROM_DATA[ADDR][4] ;
    DATA[5]  = ROM_DATA[ADDR][5] ;
    DATA[6]  = ROM_DATA[ADDR][6] ;
    DATA[7]  = ROM_DATA[ADDR][7] ;
    DATA[8]  = ROM_DATA[ADDR][8] ;
    DATA[9]  = ROM_DATA[ADDR][9] ;
    DATA[10] = ROM_DATA[ADDR][10] ;
    DATA[11] = ROM_DATA[ADDR][11] ;
    DATA[12] = ROM_DATA[ADDR][12] ;
    DATA[13] = ROM_DATA[ADDR][13] ;
    DATA[15] = ROM_DATA[ADDR][15] ;
    DATA[14] = ROM_DATA[ADDR][14] ;
}



///   FUNCTION    : alu_t::EX
///   EXPLANATION : Implementa uma ALU de 16 bits.

void alu_t::EX ( word &ALUOUT , flag_t &FLAGS , word A , word B , SIGNAL ALUOP[5] , SIGNAL FLAGWRITE )
{
    word SRC_A , SRC_B ,
            NEG_A , NEG_B ,
            ZERO = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0} ,
            ONE  = {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0} ,
            MINUS_ONE  = {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1} ,
            ALU_CONTROL ;

    SIGNAL OP[3] ,
            ALU_SRC_A[2] ,
            ALU_SRC_B[2] ,
            OVER_SRC[2] ,
            CARRY_SRC[2] ,
            LS_AS ,
            CIN ;

    SIGNAL CO , CI ,
            A16 , SUM_OV , SH_OV ;

    flag_t FL ;

    int CONT ;



    ALU_ROM.READ ( ALUOP , ALU_CONTROL ) ;
    OP[0]        = ALU_CONTROL[0] ;
    OP[1]        = ALU_CONTROL[1] ;
    OP[2]        = ALU_CONTROL[2] ;
    ALU_SRC_A[0] = ALU_CONTROL[3] ;
    ALU_SRC_A[1] = ALU_CONTROL[4] ;
    ALU_SRC_B[0] = ALU_CONTROL[5] ;
    ALU_SRC_B[1] = ALU_CONTROL[6] ;
    CARRY_SRC[0] = ALU_CONTROL[7] ;
    CARRY_SRC[1] = ALU_CONTROL[8] ;
    OVER_SRC[0]  = ALU_CONTROL[9] ;
    OVER_SRC[1]  = ALU_CONTROL[10] ;
    LS_AS        = ALU_CONTROL[11] ;
    CIN          = ALU_CONTROL[12] ;

    WORD_NOT ( NEG_A , A ) ;
    WORD_NOT ( NEG_B , B ) ;

    WORD_MUX4 ( SRC_A , A , NEG_A , ZERO , ONE , ALU_SRC_A ) ;
    WORD_MUX4 ( SRC_B , B , NEG_B , ZERO , MINUS_ONE , ALU_SRC_B ) ;

    BIT_ALU[0].EX ( CO , ALUOUT[0] , SRC_A[0] , SRC_B[0] , 0 , SRC_A[1] , CIN , OP ) ;
    for ( CONT = 1 ; CONT < WORDSIZE-1 ; CONT++)
    {
        CI = CO ;
        BIT_ALU[CONT].EX ( CO , ALUOUT[CONT] ,
                           SRC_A[CONT] , SRC_B[CONT] , SRC_A[CONT-1] , SRC_A[CONT+1] ,
                CI , OP ) ;
    }
    MUX2 ( A16 , 0 , SRC_A[15] , LS_AS ) ;
    CI = CO ;
    BIT_ALU[15].EX ( CO , ALUOUT[15] , SRC_A[15] , SRC_B[15] , SRC_A[14] , A16 , CI , OP ) ;

    NOR16 ( FL[1] , ALUOUT[0] ,
            ALUOUT[1] ,
            ALUOUT[2] ,
            ALUOUT[3] ,
            ALUOUT[4] ,
            ALUOUT[5] ,
            ALUOUT[6] ,
            ALUOUT[7] ,
            ALUOUT[8] ,
            ALUOUT[9] ,
            ALUOUT[10] ,
            ALUOUT[11] ,
            ALUOUT[12] ,
            ALUOUT[13] ,
            ALUOUT[14] ,
            ALUOUT[15] ) ;

    FL[0] = ALUOUT[15] ;

    OR2 ( FL[2] , FL[0] , FL[1] ) ;

    MUX4 ( FL[3] , 0 , CO , SRC_A[15] , 0 , CARRY_SRC ) ;

    XOR2 ( SUM_OV , CI , CO ) ;
    XOR2 ( SH_OV , SRC_A[15] , SRC_A[14] ) ;
    MUX4 ( FL[4] , 0 , SUM_OV , SH_OV , 0 , OVER_SRC ) ;

    FL[5] = 1 ;

    ALU_FLAGS.EX ( FLAGS , FL , FLAGWRITE ) ;

}
