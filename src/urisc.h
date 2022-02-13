/***************************************************************************
                                  urisc.h
                             -------------------
    begin                : Fri Jun 30 2000
    copyright            : (C) 2000 by Carlucio Santos Cordeiro

    DCC - UFMG - Computer Organization & Design

 ***************************************************************************/


#ifndef URISC_H
#define URISC_H

///   Header files   ////////////////////////////////////////
///                  ////////////////////////////////////////

#include "adder.h"
#include "alu.h"
#include "control.h"
#include "extend.h"
#include "logic.h"
#include "memory.h"
#include "reg.h"
#include "reg_file.h"
#include "word.h"



///   Class         /////////////////////////////////////////
///   Definitions   /////////////////////////////////////////

//  CLASS : urisc
//  DESC  : define o processador.

class urisc
{
private:

    word_reg_t PC ,
                IR ,
                MDR ,
                PCR ,
                ALUOUT ,
                A ,
                B ;

    word       PC_IN ,
                PC_OUT ,
                ADDER_OUT ,
                DATA_OUT ,
                IR_OUT ,
                MDR_OUT ,
                PCR_OUT ,
                EXT_OUT ,
                ALUOUT_OUT ,
                A_IN ,
                A_OUT ,
                B_IN ,
                B_OUT ;

    flag_t     FLAGS ;

    reg_file_t REG_FILE ;
    extend_t EXT ;
    Adder ADDER ;
    alu_t ALU ;
    memory_t MEMORY ;
    control_t CONTROL ;
    control_line_t CTRL_LINE ;

    SIGNAL PC_SOURCE[2] ,  //
            PC_WRITE ,      //
            IorD ,          //
            MEM_READ ,      //
            MEM_WRITE ,     //
            IR_WRITE ,      //
            SRC_C[2] ,      //
            JAL ,           //
            LC ,            //
            REG_WRITE ,     //
            EXTEND[3] ,     //
            ALU_SRC_A[2] ,  //
            ALU_SRC_B ,     //
            ALUOP[5] ,      //
            FLAG_WRITE ,    //

            HALT ;          //

    unsigned short PC_ATUAL ;


public:

    void LOAD( char *FILE ) ;
    SIGNAL HLT () ;
    void STATUS ( bool PAUSE ) ;
    void DUMP ( int POS , int N , bool PAUSE ) ;

    void IF() ;
    void ID() ;
    void EX() ;
    void MEM() ;
    void WB() ;
};

///   Function     //////////////////////////////////////////
///   Prototypes   //////////////////////////////////////////

void INST_NAME ( word BITS , char OPNAME[50] , char FLAGNAME[10] , word EXT_OUT ) ;


#endif
