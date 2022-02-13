/***************************************************************************
                              control_pipe.cpp
                             ------------------
    begin                : Fri Jun 23 2000
    copyright            : (C) 2000 by Carlucio Santos Cordeiro

    DCC - UFMG - Computer Organization & Design

 ***************************************************************************/

///   Header files   ////////////////////////////////////////
///                  ////////////////////////////////////////

#include "control_pipe.h"



///   FUNCTION    : control_t::EX
///   EXPLANATION : Implementa o controle do processador.

void control_t::EX ( word IR , control_line_t &CONTROL_LINE , SIGNAL &HALT )
{
    //                   REGWRITE RCSRC  CSRC  MEMWRITE ALUSRCA ALUSCRB   ALUOP     FLAGWRITE LOAD EXTEND RASRC JUMPTYPE COND  PCSRC2

    control_line_t JF =       {0,  X,    X,X,      0,     X,X,     X,   X,X,X,X,X,      0,     0,  0,1,0,   X,    0,1,   0,0,0,  0} ,
                   JT =       {0,  X,    X,X,      0,     X,X,     X,   X,X,X,X,X,      0,     0,  0,1,0,   X,    1,1,   0,0,0,  0} ,
                   J =        {0,  X,    X,X,      0,     X,X,     X,   X,X,X,X,X,      0,     0,  0,0,1,   X,    1,0,   X,X,X,  0} ,
                   JAL =      {1,  1,    1,0,      0,     X,X,     X,   X,X,X,X,X,      0,     0,  X,X,X,   X,    1,0,   X,X,X,  1} ,
                   JR =       {0,  X,    X,X,      0,     X,X,     X,   X,X,X,X,X,      0,     0,  X,X,X,   X,    1,0,   X,X,X,  1} ,
                   ALU =      {1,  0,    0,1,      0,     0,0,     0,   0,0,0,0,0,      1,     0,  X,X,X,   0,    0,0,   X,X,X,  X} ,
                   LOAD =     {1,  0,    0,1,      0,     X,X,     X,   X,X,X,X,X,      0,     1,  X,X,X,   0,    0,0,   X,X,X,  X} ,
                   STORE =    {0,  X,    X,X,      1,     X,X,     X,   X,X,X,X,X,      0,     0,  X,X,X,   0,    0,0,   X,X,X,  X} ,
                   LOADLIT =  {1,  0,    1,1,      0,     X,X,     X,   X,X,X,X,X,      0,     0,  1,1,0,   X,    0,0,   X,X,X,  X} ,
                   LCL =      {1,  0,    0,1,      0,     1,1,     1,   0,0,1,0,0,      0,     0,  0,0,0,   1,    0,0,   X,X,X,  X} ,
                   LCH =      {1,  0,    0,1,      0,     0,1,     1,   0,0,1,0,0,      0,     0,  1,0,0,   1,    0,0,   X,X,X,  X} ;

    SIGNAL         ALUORMEM , LOADORSTORE , RJUMP , RCONST , OPJUMP[2] , OP[2] , TMP1 , TMP2 , TMP3 ;

    control_line_t JRJAL , LOADSTORE , JUMP , ALUMEM , CONST ;



    OP[0] = IR[14] ;
    OP[1] = IR[15] ;

    OPJUMP[0] = IR[12] ;
    OPJUMP[1] = IR[13] ;

    RJUMP = IR[11] ;

    RCONST = IR[10] ;

    LOADORSTORE = IR[7] ;

    NOT (TMP1 , IR[6] ) ;
    NOT (TMP2 , IR[9] ) ;
    AND4 ( ALUORMEM , TMP1 , IR[8] , TMP2 , IR[10] ) ;

    ALU[8] = IR[6] ;
    ALU[9] = IR[7] ;
    ALU[10] = IR[8] ;
    ALU[11] = IR[9] ;
    ALU[12] = IR[10] ;

    JF[21] = IR[8] ;
    JF[22] = IR[9] ;
    JF[23] = IR[10] ;

    JT[21] = IR[8] ;
    JT[22] = IR[9] ;
    JT[23] = IR[10] ;



    CONTROL_MUX2 ( JRJAL , JAL , JR , RJUMP ) ;

    CONTROL_MUX2 ( LOADSTORE , LOAD , STORE , LOADORSTORE ) ;

    CONTROL_MUX2 ( CONST , LCL , LCH , RCONST ) ;

    CONTROL_MUX2 ( ALUMEM , ALU , LOADSTORE , ALUORMEM ) ;

    CONTROL_MUX4 ( JUMP , JF , JT , J , JRJAL , OPJUMP ) ;

    CONTROL_MUX4 ( CONTROL_LINE , JUMP , ALUMEM , LOADLIT , CONST , OP ) ;

    NOT ( TMP1 , IR[12] ) ;
    NOT ( TMP2 , IR[14] ) ;
    NOT ( TMP3 , IR[15] ) ;
    AND16 ( HALT , IR[0] ,
                   IR[1] ,
                   IR[2] ,
                   IR[3] ,
                   IR[4] ,
                   IR[5] ,
                   IR[6] ,
                   IR[7] ,
                   IR[8] ,
                   IR[9] ,
                   IR[10] ,
                   IR[11] ,
                   TMP1 ,
                   IR[13] ,
                   TMP2 ,
                   TMP3 ) ;
}



///   FUNCTION    : CONTROL_MUX2
///   EXPLANATION : Implementa um mux de 2 entradas para a linha de controle (24 bits).

void CONTROL_MUX2 ( control_line_t &O , control_line_t I0 , control_line_t I1 , SIGNAL C )
{
    int CONT ;

    for ( CONT = 0 ; CONT < 25 ; CONT++) MUX2 ( O[CONT] , I0[CONT] , I1[CONT] , C ) ;
}



///   FUNCTION    : CONTROL_MUX4
///   EXPLANATION : Implementa um mux de 4 entradas para a linha de controle (24 bits).

void CONTROL_MUX4 ( control_line_t &O , control_line_t I0 , control_line_t I1 , control_line_t I2 , control_line_t I3 , SIGNAL C[2] )
{
    int CONT ;

    for ( CONT = 0 ; CONT < 25 ; CONT++) MUX4 ( O[CONT] , I0[CONT] , I1[CONT] , I2[CONT] , I3[CONT] , C ) ;
}
