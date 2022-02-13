/***************************************************************************
                                  urisc.h
                             -------------------
    begin                : Tue Oct 03 2000
    copyright            : (C) 2000 by Carlucio Santos Cordeiro

    DCC - UFMG - Computer Organization & Design

 ***************************************************************************/


#ifndef URISC_H
#define URISC_H

///   Header files   ////////////////////////////////////////
///                  ////////////////////////////////////////

#include "adder.h"
#include "alu.h"
#include "control_pipe.h"
#include "extend.h"
#include "logic.h"
#include "memory.h"
#include "reg.h"
#include "reg_file.h"
#include "word.h"
#include "jumpctrl.h"
#include "forward.h"


///   Class         /////////////////////////////////////////
///   Definitions   /////////////////////////////////////////

//  CLASS : urisc
//  DESC  : define o processador.
class urisc
{
private:

    /////
    ///// COMPONENTES
    /////
    memory_t   MEM ;      // UNID. DE MEMORIA
    control_t  CONTROL ;  // UNID. DE CONTROLE
    reg_file_t REGFILE ;  // BANCO DE REGS.
    extend_t   EXTEND ;   // EXTEND SYSTEM
    alu_t      ALU ;      // uRISC ALU
    Adder    IFADDER ,  // 16 BIT ADDER
                IDADDER ;


    /////
    ///// PIPELINE INTERMEDIATE LATCHES.
    /////
    word_reg_t  PC ,                //  PC

                IFID_NPC ,          //  IF/ID
                IFID_IR ,           //

                IDEXM_NPC ,         //  ID/EXM
                IDEXM_A ,           //
                IDEXM_B ,           //
                IDEXM_EXT ;         //
    SIGNAL      IDEXM_WB[4] ,       //
                IDEXM_EXM[11] ,     //
                IDEXM_RA[3] ,       //
                IDEXM_RB[3] ,       //
                IDEXM_RC[3] ;       //

    word_reg_t  EXMWB_NPC ,         //  EXM/WB
                EXMWB_DATA ,        //
                EXMWB_EXT ;         //
    SIGNAL      EXMWB_WB[4] ,       //
                EXMWB_RC[3] ;       //

    //
    // Auxiliares
    //
    SIGNAL     HALT ;
    word   op2 ,
            op3 ,
            op4 ,
            regop3 ,
            regop4 ,
            ppcc ;


    //
    // Valores intermediarios (ligacoes)
    //

    // IF  ////////////////////
    word        PCOUT ;      //
    word        PCIN ;       //
    word        IFADDEROUT ; //
    word        IMOUT ;      //
    word        IRIN ;       //

    // ID  //////////////////////
    word        IFID_NPCOUT ,  //
                IFID_IROUT ;   //
    SIGNAL      RA1[3] ,       //
                RA[3] ,        //
                RB[3] ,        //
                RC1[3] ;       //
    offset_t    EXTND ;        //
    word        EXTNDOUT ,     //
                AOUT ,         //
                BOUT ,         //
                REGADDR ,      //
                IDADDEROUT ,   //
                JMPADDR ;      //

    // EXM  ////////////////////////
    word        IDEXM_NPCOUT ,    //
                IDEXM_AOUT ,      //
                IDEXM_BOUT ,      //
                IDEXM_EXTOUT ;    //
    SIGNAL      IDEXM_WBOUT[4] ,  //
                IDEXM_RAOUT[3] ,  //
                IDEXM_RBOUT[3] ,  //
                IDEXM_RCOUT[3] ;  //
    word        A ,               //
                B ,               //
                SRCA ,            //
                SRCB ,            //
                IN2 ,             //
                IN3 ,             //
                ALUOUT ,          //
                MEMOUT ,          //
                DATA ;            //
    flag_t      FLAGS ;           //

    //WB  /////////////////////////////
    word        EXMWB_NPCOUT ,       //
                EXMWB_DATAOUT ,      //
                EXMWB_EXTOUT ,       //
                C ;                  //
    SIGNAL      EXMWB_RCOUT[3] ,     //
                RC[3] ;              //

    //
    // Linha de controle (25 bits)
    //
    control_line_t CONTROL_LINE ;

    //
    // Sinais de controle
    //
    SIGNAL    REGWRITE ,
              RCSRC ,
              CSRC[2] ,
              MEMWRITE ,
              ALUSRCA[2] ,
              ALUSRCB ,
              ALUOP[5] ,
              FLAGWRITE ,
              LOAD ,
              EXT[3] ,
              RASRC ,
              JUMPTYPE[2] ,
              COND[3] ,
              PCSRC2 ,

              JFW ,
              FWA ,
              FWB ,
              PCSRC1 ;


public:
    urisc() ;
    ~urisc() ;
    void load( char *FILE ) ;
    SIGNAL HLT () ;
    void STATUS ( bool PAUSE ) ;
    void DUMP ( int POS , int N , bool PAUSE ) ;

    void EX () ;
};

///   Function     //////////////////////////////////////////
///   Prototypes   //////////////////////////////////////////

void INST_NAME ( word BITS , char OPNAME[50] ) ;



#endif
