/***************************************************************************
                                 control.cpp
                             -------------------
    begin                : Fri Jun 23 2000
    copyright            : (C) 2000 by Carlucio Santos Cordeiro

    DCC - UFMG - Computer Organization & Design

 ***************************************************************************/

///   Header files   ////////////////////////////////////////
///                  ////////////////////////////////////////

#include "control.h"



///   FUNCTION    : control_t::EX
///   EXPLANATION : Implementa o controle do processador.
void control_t::EX ( word IR , flag_t FLAGS , control_line_t &CONTROL_LINE , SIGNAL &HALT )
{
    //                      pc-source pc-write iord memread memwrite irwrite srcc jal lc regwrite extend alusrca alusrcb   aluop flagwrite

    control_line_t J_COND =   {1,0,      X,     X,     0,      0,       0,   X,X,  X,  X,    0,   0,1,0,   1,0,     1,   0,0,0,1,1,  0} ,
                   J_INCOND = {1,0,      1,     X,     0,      0,       0,   X,X,  X,  X,    0,   0,0,1,   1,0,     1,   0,0,0,1,1,  0} ,
                   JAL =      {0,1,      1,     X,     0,      0,       0,   1,0,  1,  X,    1,   X,X,X,   X,X,     X,   X,X,X,X,X,  0} ,
                   JR =       {0,1,      1,     X,     0,      0,       0,   X,X,  X,  X,    0,   X,X,X,   X,X,     X,   X,X,X,X,X,  0} ,
                   ALU =      {X,X,      0,     X,     0,      0,       0,   0,1,  0,  0,    1,   X,X,X,   0,0,     0,   X,X,X,X,X,  1} ,
                   LOAD =     {X,X,      0,     1,     1,      0,       0,   0,0,  0,  0,    1,   X,X,X,   0,0,     X,   0,0,1,0,1,  0} ,
                   STORE =    {X,X,      0,     1,     0,      1,       0,   X,X,  X,  0,    0,   X,X,X,   0,0,     X,   0,1,1,0,1,  0} ,
                   LOADLIT =  {X,X,      0,     X,     0,      0,       0,   1,1,  0,  X,    1,   1,1,0,   X,X,     X,   X,X,X,X,X,  0} ,
                   LCL =      {X,X,      0,     X,     0,      0,       0,   0,1,  0,  1,    1,   0,0,0,   1,1,     1,   0,0,1,0,0,  0} ,
                   LCH =      {X,X,      0,     X,     0,      0,       0,   0,1,  0,  1,    1,   1,0,0,   0,1,     1,   0,0,1,0,0,  0} ;

    SIGNAL         COND[3] , FLAG , TRUEORFALSE , ALUORMEM , LOADORSTORE , RJUMP , RCONST , OPJUMP[2] , OP[2] , TMP1 , TMP2 , TMP3 ;

    control_line_t JRJAL , LOADSTORE , JUMP , ALUMEM , CONST ;



    OP[0] = IR[14] ;
    OP[1] = IR[15] ;

    COND[0] = IR[8] ;
    COND[1] = IR[9] ;
    COND[2] = IR[10] ;

    OPJUMP[0] = IR[12] ;
    OPJUMP[1] = IR[13] ;

    RJUMP = IR[11] ;

    RCONST = IR[10] ;

    LOADORSTORE = IR[7] ;

    NOT (TMP1 , IR[6] ) ;
    NOT (TMP2 , IR[9] ) ;
    AND4 ( ALUORMEM , TMP1 , IR[8] , TMP2 , IR[10] ) ;


    ALU[18] = IR[6] ;
    ALU[19] = IR[7] ;
    ALU[20] = IR[8] ;
    ALU[21] = IR[9] ;
    ALU[22] = IR[10] ;


    MUX8 ( FLAG , FLAGS[5] , X , X , FLAGS[4] ,  FLAGS[0] , FLAGS[1] , FLAGS[3] , FLAGS[2] , COND ) ;
    NOT ( TRUEORFALSE , IR[12] ) ;
    XOR2 ( J_COND[2] , TRUEORFALSE , FLAG ) ;



    CONTROL_MUX2 ( JRJAL , JAL , JR , RJUMP ) ;

    CONTROL_MUX2 ( LOADSTORE , LOAD , STORE , LOADORSTORE ) ;

    CONTROL_MUX2 ( CONST , LCL , LCH , RCONST ) ;

    CONTROL_MUX2 ( ALUMEM , ALU , LOADSTORE , ALUORMEM ) ;

    CONTROL_MUX4 ( JUMP , J_COND , J_COND , J_INCOND , JRJAL , OPJUMP ) ;

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



///   FUNCTION    : control_t::FETCH
///   EXPLANATION : Prepara o controle para o ciclo fetch (busca da instrucao).
void control_t::FETCH ( control_line_t &CONTROL_LINE )
{
    //                      pc-source pc-write iord memread memwrite irwrite srcc jal lc regwrite extend alusrca alusrcb   aluop flagwrite
    control_line_t FETCH =    {0,0,      1,     0,     1,      0,       1,   X,X,  X,  X,    0,   X,X,X,   X,X,     X,   X,X,X,X,X,  0} ;

    for (int c = 0 ; c < 24 ; c++) CONTROL_LINE[c] = FETCH[c] ;
}



///   FUNCTION    : CONTROL_MUX2
///   EXPLANATION : Implementa um mux de 2 entradas para a linha de controle (24 bits).
void CONTROL_MUX2 ( control_line_t &O , control_line_t I0 , control_line_t I1 , SIGNAL C )
{
    //int CONT ;
    for ( int CONT = 0 ; CONT < 24 ; CONT++) MUX2 ( O[CONT] , I0[CONT] , I1[CONT] , C ) ;
}



///   FUNCTION    : CONTROL_MUX4
///   EXPLANATION : Implementa um mux de 4 entradas para a linha de controle (24 bits).
void CONTROL_MUX4 ( control_line_t &O , control_line_t I0 , control_line_t I1 , control_line_t I2 , control_line_t I3 , SIGNAL C[2] )
{
    for ( int CONT = 0 ; CONT < 24 ; CONT++) MUX4 ( O[CONT] , I0[CONT] , I1[CONT] , I2[CONT] , I3[CONT] , C ) ;
}
