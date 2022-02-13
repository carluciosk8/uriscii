/***************************************************************************
                                 urisc_pipe.cpp
                             -------------------
    begin                : Tue Oct 03 2000
    copyright            : (C) 2000 by Carlucio Santos Cordeiro

    DCC - UFMG - Computer Organization & Design

 ***************************************************************************/

///   Header files   ////////////////////////////////////////
///                  ////////////////////////////////////////

#include "urisc_pipe.h"

#include <unistd.h>


urisc::urisc()
{
    word XXX = {X,X,X,X,X,X,X,X,X,X,X,X,X,X,X,X} ;

    int c ;

    EXMWB_NPC.EX (XXX , XXX , 1) ;      // EXM/WB.NPC
    EXMWB_DATA.EX (XXX , XXX , 1) ;     // EXM/WB.DATA
    EXMWB_EXT.EX (XXX , XXX , 1) ;      // EXM/WB.EXT
    for (c=0;c<3;c++) EXMWB_RC[c] = 0 ; // EXM/WB.RC
    for (c=0;c<4;c++) EXMWB_WB[c] = 0 ; // ID/EMX.WB


    IDEXM_NPC.EX (XXX , XXX , 1) ;    // ID/EMX.NPC
    IDEXM_A.EX (XXX , XXX , 1) ;            // ID/EMX.A
    IDEXM_B.EX (XXX , XXX , 1) ;               // ID/EMX.B
    IDEXM_EXT.EX (XXX , XXX , 1) ;        // ID/EMX.EXT
    for (c=0;c<4;c++) IDEXM_WB[c] = 0 ;           // ID/EMX.WB
    IDEXM_EXM[0]  = 0 ;
    IDEXM_EXM[1]  = 0 ;
    IDEXM_EXM[2]  = 0 ;
    IDEXM_EXM[3]  = 0 ;
    IDEXM_EXM[4]  = 0 ;
    IDEXM_EXM[5]  = 0 ;
    IDEXM_EXM[6]  = 0 ;
    IDEXM_EXM[7]  = 0 ;
    IDEXM_EXM[8]  = 0 ;
    IDEXM_EXM[9]  = 0 ;
    IDEXM_EXM[10] = 0 ;
    for (c=0;c<3;c++) IDEXM_RA[c] = 0 ;           // ID/EMX.RA
    for (c=0;c<3;c++) IDEXM_RB[c] = 0 ;           // ID/EMX.RB
    for (c=0;c<3;c++) IDEXM_RC[c] = 0 ;           // ID/EMX.RC

    IFID_NPC.EX (XXX , XXX , 1) ;      // IF/ID.NPC
    IFID_IR.EX (XXX , XXX , 1) ;        // IF/ID.IR

    HALT = 0 ;

    put_word_dec ( regop3 , 0 ) ;
    put_word_dec ( regop4 , 0 ) ;

    FLAGS[0] = 0 ;
    FLAGS[1] = 0 ;
    FLAGS[2] = 0 ;
    FLAGS[3] = 0 ;
    FLAGS[4] = 0 ;
    FLAGS[5] = 1 ;
}


urisc::~urisc()
{ }


///   FUNCTION    : urisc::HLT.
///   EXPLANATION : Detecta quando ocorre halt.
SIGNAL urisc::HLT ()
{
    return HALT ;
}


///   FUNCTION    : urisc::LOAD.
///   EXPLANATION : Carrega o programa para a memoria.
void urisc::load( char *FILE )
{
    MEM.LOAD ( FILE , PC ) ;
}


void urisc::DUMP ( int POS , int N , bool PAUSE )
{
    MEM.DUMP ( POS , N , PAUSE ) ;
}


void urisc::STATUS ( bool PAUSE )
{
    unsigned short PCV ,
            REGS[8] ;
    char IFOP[50] ,
            IDOP[50] ,
            EXMOP[50] ,
            WBOP[50] ,
            FORWARD[20] ,
            JMPFORWARD[20] ,
            BUBBLE[20] ;

    REGFILE.GET_REGS ( REGS ) ;

    put_dec_word ( PCV , ppcc ) ;

    INST_NAME ( IMOUT , IFOP ) ;
    INST_NAME ( op2 , IDOP ) ;
    INST_NAME ( op3 , EXMOP ) ;
    INST_NAME ( op4 , WBOP ) ;

    if ( FWA && !FWB ) strcpy ( FORWARD , "<< FORWARD ra    <<" ) ;
    else if ( !FWA && FWB ) strcpy ( FORWARD , "<< FORWARD rb    <<" ) ;
    else if ( FWA && FWB ) strcpy ( FORWARD , "<< FORWARD ra,rb <<" ) ;
    else strcpy ( FORWARD , "                   " ) ;

    if ( JFW ) strcpy ( JMPFORWARD , "<< JUMP FORWARD <<" ) ;
    else strcpy ( JMPFORWARD , "                  " ) ;

    if ( PCSRC1 ) strcpy ( BUBBLE , "CONTROL HAZARD" ) ;
    else strcpy ( BUBBLE , "              " ) ;

    system ( "tput cup 0,0" ) ;
    printf ( " _____________________________________________________________________________ \n" ) ;
    printf ( "|                  _                   _                   _                  |\n" ) ;
    printf ( "|       IF        | |       ID        | |      EXMEM      | |     WB          |\n" ) ;
    printf ( "|                 | |  _________      | |    ________     | |                 |\n" ) ;
    printf ( "|                 | | |         |     | |---| Memory |----| |                 |\n" ) ;
    printf ( "|                 | |-| Control |-----| |   |________|    | |                 |\n" ) ;
    printf ( "|    ________     | | |_________|     | |     ___         | |   ______        |\n" ) ;
    printf ( "|   | Memory |----| |                 | |____|   \\        | |--| Regs |       |\n" ) ;
    printf ( "|   |________|    | |   ______        | |    |  A \\       | |  |______|       |\n" ) ;
    printf ( "|                 | |--| Regs |-------| |     > L |-------| |                 |\n" ) ;
    printf ( "|                 | |  |______|       | |____|  U /       | |                 |\n" ) ;
    printf ( "|                 | |                 | |    |___/        | |                 |\n" ) ;
    printf ( "|%-17s| |%-17s| |%-17s| |%-17s|\n" , IFOP , IDOP , EXMOP , WBOP ) ;
    printf ( "|                 |_|                 |_|                 |_|                 |\n" ) ;
    printf ( "|   %s             %s  %s        |\n" , BUBBLE , JMPFORWARD , FORWARD ) ;
    printf ( "|________________________________                     ________________________|\n" ) ;
    printf ( "|              REGS              |    ___________    | FLAGS                  |\n" ) ;
    printf ( "|    r0 = %4X      r4 = %4X    |   |           |   |          neg : %1d       |\n", REGS[0]  , REGS[4] , FLAGS[0] ) ;
    printf ( "|    r1 = %4X      r5 = %4X    |   | PC = %4X |   |         zero : %1d       |\n", REGS[1]  , REGS[5] , PCV , FLAGS[1] ) ;
    printf ( "|    r2 = %4X      r6 = %4X    |   |___________|   |        carry : %1d       |\n", REGS[2]  , REGS[6] , FLAGS[3] ) ;
    printf ( "|    r3 = %4X      r7 = %4X    |                   |      negzero : %1d       |\n", REGS[3]  , REGS[7] , FLAGS[2] ) ;
    printf ( "|                                |                   |     overflow : %1d       |\n" , FLAGS[4] ) ;
    printf ( "|_____________________________________________________________________________|\n" ) ;

    if ( PAUSE ) getchar() ;
    //usleep (500000);
}


///   FUNCTION    : urisc::EX.
///   EXPLANATION : Executa um ciclo de clock no pipeline.
void urisc::EX ()
{
    word ONE = {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0} ;
    word NOP = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0} ;
    word XXX = {X,X,X,X,X,X,X,X,X,X,X,X,X,X,X,X} ;
    word FFOO = {0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1} ;
    word OOFF = {1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0} ;
    SIGNAL SEVEN[3] = {1,1,1} ;

    int c ;

    //
    // 1o. stage - Leitura dos latches PC, IFID, IDEXM e EXMWB.
    //
    PC.EX(PCOUT , XXX , 0) ;                   // PC

    IFID_NPC.EX (IFID_NPCOUT , XXX , 0) ;      // IF/ID.NPC
    IFID_IR.EX (IFID_IROUT , XXX , 0) ;        // IF/ID.IR

    IDEXM_NPC.EX (IDEXM_NPCOUT , XXX , 0) ;    // ID/EMX.NPC
    IDEXM_A.EX (IDEXM_AOUT , XXX , 0) ;        // ID/EMX.A
    IDEXM_B.EX (IDEXM_BOUT , XXX , 0) ;        // ID/EMX.B
    IDEXM_EXT.EX (IDEXM_EXTOUT , XXX , 0) ;    // ID/EMX.EXT
    for (c=0;c<4;c++) IDEXM_WBOUT[c] = IDEXM_WB[c] ;           // ID/EMX.WB
    for (c=0;c<3;c++) IDEXM_RAOUT[c] = IDEXM_RA[c] ;           // ID/EMX.RA
    for (c=0;c<3;c++) IDEXM_RBOUT[c] = IDEXM_RB[c] ;           // ID/EMX.RB
    for (c=0;c<3;c++) IDEXM_RCOUT[c] = IDEXM_RC[c] ;           // ID/EMX.RC
    MEMWRITE   = IDEXM_EXM[0] ;
    ALUSRCA[0] = IDEXM_EXM[1] ;
    ALUSRCA[1] = IDEXM_EXM[2] ;
    ALUSRCB    = IDEXM_EXM[3] ;
    ALUOP[0]   = IDEXM_EXM[4] ;
    ALUOP[1]   = IDEXM_EXM[5] ;
    ALUOP[2]   = IDEXM_EXM[6] ;
    ALUOP[3]   = IDEXM_EXM[7] ;
    ALUOP[4]   = IDEXM_EXM[8] ;
    FLAGWRITE  = IDEXM_EXM[9] ;
    LOAD       = IDEXM_EXM[10] ;

    EXMWB_NPC.EX (EXMWB_NPCOUT , XXX , 0) ;    // EXM/WB.NPC
    EXMWB_DATA.EX (EXMWB_DATAOUT , XXX , 0) ;  // EXM/WB.DATA
    EXMWB_EXT.EX (EXMWB_EXTOUT , XXX , 0) ;    // EXM/WB.EXT
    for (c=0;c<3;c++) EXMWB_RCOUT[c] = EXMWB_RC[c] ;           // EXM/WB.RC
    REGWRITE = EXMWB_WB[0] ;
    RCSRC    = EXMWB_WB[1] ;
    CSRC[0]  = EXMWB_WB[2] ;
    CSRC[1]  = EXMWB_WB[3] ;


    //
    // 2o. stage :  IF  - Leitura da memoria(instrucao), IF adder.
    //              ID  - Control set, extend system, jump forward system.
    //              EXM - Forward system.
    //              WB  - Escrita no register file.
    //

    // CONTROL SET
    CONTROL.EX (IFID_IROUT , CONTROL_LINE , HALT ) ;
    EXT[0]      = CONTROL_LINE[15] ;
    EXT[1]      = CONTROL_LINE[16] ;
    EXT[2]      = CONTROL_LINE[17] ;
    RASRC       = CONTROL_LINE[18] ;
    JUMPTYPE[0] = CONTROL_LINE[19] ;
    JUMPTYPE[1] = CONTROL_LINE[20] ;
    COND[0]     = CONTROL_LINE[21] ;
    COND[1]     = CONTROL_LINE[22] ;
    COND[2]     = CONTROL_LINE[23] ;
    PCSRC2      = CONTROL_LINE[24] ;

    // FORWARD
    RA1[0] = IFID_IROUT[3] ;
    RA1[1] = IFID_IROUT[4] ;
    RA1[2] = IFID_IROUT[5] ;
    RB[0] = IFID_IROUT[0] ;
    RB[1] = IFID_IROUT[1] ;
    RB[2] = IFID_IROUT[2] ;
    RC1[0] = IFID_IROUT[11] ;
    RC1[1] = IFID_IROUT[12] ;
    RC1[2] = IFID_IROUT[13] ;
    jmpfwd ( RB , IDEXM_RCOUT , IDEXM_WBOUT[0] , JFW ) ;
    forward ( IDEXM_RAOUT , IDEXM_RBOUT , EXMWB_RCOUT , REGWRITE , FWA , FWB ) ;

    // EXTEND
    EXTND[0] = IFID_IROUT[0] ;
    EXTND[1] = IFID_IROUT[1] ;
    EXTND[2] = IFID_IROUT[2] ;
    EXTND[3] = IFID_IROUT[3] ;
    EXTND[4] = IFID_IROUT[4] ;
    EXTND[5] = IFID_IROUT[5] ;
    EXTND[6] = IFID_IROUT[6] ;
    EXTND[7] = IFID_IROUT[7] ;
    EXTND[8] = IFID_IROUT[8] ;
    EXTND[9] = IFID_IROUT[9] ;
    EXTND[10] = IFID_IROUT[10] ;
    EXTND[11] = IFID_IROUT[11] ;
    EXTEND.EX (EXTND , EXT , EXTNDOUT) ;

    // MEMORIA (INSTRUCAO)
    MEM.EX (PCOUT , IMOUT , XXX , 1 , 0 ) ;

    // IF ADDER
    IFADDER.EX (IFADDEROUT , ONE , PCOUT) ;

    // ESCRITA NO REG. FILE
    MUX2 ( RC[0] , EXMWB_RCOUT[0] , SEVEN[0] , RCSRC ) ;
    MUX2 ( RC[1] , EXMWB_RCOUT[1] , SEVEN[1] , RCSRC ) ;
    MUX2 ( RC[2] , EXMWB_RCOUT[2] , SEVEN[2] , RCSRC ) ;
    WORD_MUX4 ( C , XXX , EXMWB_NPCOUT , EXMWB_DATAOUT , EXMWB_EXTOUT , CSRC) ;
    REGFILE.WRITE ( RC , C , REGWRITE ) ;

    //
    // 3o. stage :  IF  - Nada.
    //              ID  - Leitura no register file, ID adder.
    //              EXM - Memoria, alu.
    //              WB  - Nada.
    //
    WORD_MUX2 ( A , IDEXM_AOUT , C , FWA ) ;
    WORD_MUX2 ( B , IDEXM_BOUT , C , FWB ) ;

    // LEITURA NO REG. FILE
    MUX2 ( RA[0] , RA1[0] , RC1[0] , RASRC ) ;
    MUX2 ( RA[1] , RA1[1] , RC1[1] , RASRC ) ;
    MUX2 ( RA[2] , RA1[2] , RC1[2] , RASRC ) ;
    REGFILE.READ ( RA , RB , AOUT , BOUT ) ;

    // ID ADDER
    IDADDER.EX (IDADDEROUT , IFID_NPCOUT , EXTNDOUT) ;

    // ALU E MEMORIA
    WORD_AND2 ( IN2 , A , OOFF ) ;
    WORD_AND2 ( IN3 , A , FFOO ) ;
    WORD_MUX4 ( SRCA , A , XXX , IN2 , IN3 , ALUSRCA ) ;
    WORD_MUX2 ( SRCB , B , IDEXM_EXTOUT , ALUSRCB ) ;
    ALU.EX ( ALUOUT , FLAGS , SRCA , SRCB , ALUOP , FLAGWRITE ) ;
    MEM.EX (A , MEMOUT , B , 1 , MEMWRITE ) ;
    WORD_MUX2 ( DATA , ALUOUT , MEMOUT , LOAD ) ;

    //
    // 4o. stage :  IF  - Nada.
    //              ID  - Jump control.
    //              EXM - Nada.
    //              WB  - Nada.
    //
    jump_ctrl ( JUMPTYPE , COND , FLAGS , PCSRC1 ) ;

    WORD_MUX2 ( REGADDR , BOUT , DATA , JFW ) ;
    WORD_MUX2 ( JMPADDR , IDADDEROUT , REGADDR , PCSRC2 ) ;
    WORD_MUX2 ( PCIN , IFADDEROUT , JMPADDR , PCSRC1 ) ;

    WORD_MUX2 ( IRIN , IMOUT , NOP , PCSRC1 ) ;

    //
    // 5o. stage - Escrita nos latches PC, IFID, IDEXM e EXMWB.
    //
    for (c=0;c<WORDSIZE;c++) op2[c] = IFID_IROUT[c] ;
    for (c=0;c<WORDSIZE;c++) op3[c] = regop3[c] ;
    for (c=0;c<WORDSIZE;c++) op4[c] = regop4[c] ;

    for (c=0;c<WORDSIZE;c++) regop4[c] = regop3[c] ;
    for (c=0;c<WORDSIZE;c++) regop3[c] = op2[c] ;

    for (c=0;c<WORDSIZE;c++) ppcc[c] = PCOUT[c] ;
    PC.EX(PCOUT , PCIN , 1) ;                   // PC

    EXMWB_NPC.EX (EXMWB_NPCOUT , IDEXM_NPCOUT , 1) ;    // EXM/WB.NPC
    EXMWB_DATA.EX (EXMWB_DATAOUT , DATA , 1) ;  // EXM/WB.DATA
    EXMWB_EXT.EX (EXMWB_EXTOUT , IDEXM_EXTOUT , 1) ;    // EXM/WB.EXT
    for (c=0;c<3;c++) EXMWB_RC[c] = IDEXM_RCOUT[c] ;           // EXM/WB.RC
    for (c=0;c<4;c++) EXMWB_WB[c] = IDEXM_WBOUT[c] ;           // ID/EMX.WB

    IDEXM_NPC.EX (IDEXM_NPCOUT , IFID_NPCOUT , 1) ;    // ID/EMX.NPC
    IDEXM_A.EX (IDEXM_AOUT , AOUT , 1) ;        // ID/EMX.A
    IDEXM_B.EX (IDEXM_BOUT , BOUT , 1) ;        // ID/EMX.B
    IDEXM_EXT.EX (IDEXM_EXTOUT , EXTNDOUT , 1) ;    // ID/EMX.EXT
    for (c=0;c<4;c++) IDEXM_WB[c] = CONTROL_LINE[c] ;           // ID/EMX.WB
    IDEXM_EXM[0]  = CONTROL_LINE[4] ;
    IDEXM_EXM[1]  = CONTROL_LINE[5] ;
    IDEXM_EXM[2]  = CONTROL_LINE[6] ;
    IDEXM_EXM[3]  = CONTROL_LINE[7] ;
    IDEXM_EXM[4]  = CONTROL_LINE[8] ;
    IDEXM_EXM[5]  = CONTROL_LINE[9] ;
    IDEXM_EXM[6]  = CONTROL_LINE[10] ;
    IDEXM_EXM[7]  = CONTROL_LINE[11] ;
    IDEXM_EXM[8]  = CONTROL_LINE[12] ;
    IDEXM_EXM[9]  = CONTROL_LINE[13] ;
    IDEXM_EXM[10] = CONTROL_LINE[14] ;
    for (c=0;c<3;c++) IDEXM_RA[c] = RA[c] ;           // ID/EMX.RA
    for (c=0;c<3;c++) IDEXM_RB[c] = RB[c] ;           // ID/EMX.RB
    for (c=0;c<3;c++) IDEXM_RC[c] = RC1[c] ;           // ID/EMX.RC

    IFID_NPC.EX (IFID_NPCOUT , IFADDEROUT , 1) ;      // IF/ID.NPC
    IFID_IR.EX (IFID_IROUT , IRIN , 1) ;        // IF/ID.IR
}


///////////////////////////////////////////////////////////////////////////////////////
///   FUNCTION    : INST_NAME.
///   EXPLANATION : Identifica o mnemonico da instrucao.
///                 Esta funcao nao influencia na solucao logica, ela so eh
///                 usada para gerar uma string com o mnemonico da instrucao no IR.
void INST_NAME ( word BITS , char OPNAME[50] )
{
    unsigned short OFFSET ,
            TYPE ,
            WC , RA ,RB , RJUMP , RCONST , OPJUMP ;


    char FLAGNAME[10] ;
    word EXT_OUT ;

    EXT_OUT[0] = BITS[0] ;
    EXT_OUT[1] = BITS[1] ;
    EXT_OUT[2] = BITS[2] ;
    EXT_OUT[3] = BITS[3] ;
    EXT_OUT[4] = BITS[4] ;
    EXT_OUT[5] = BITS[5] ;
    EXT_OUT[6] = BITS[6] ;
    EXT_OUT[7] = BITS[7] ;
    EXT_OUT[8] = BITS[8] ;
    EXT_OUT[9] = BITS[9] ;
    EXT_OUT[10] = BITS[10] ;
    EXT_OUT[11] = BITS[11] ;
    EXT_OUT[12] = 0 ;
    EXT_OUT[13] = 0 ;
    EXT_OUT[14] = 0 ;
    EXT_OUT[15] = 0 ;


    put_dec_word ( OFFSET , EXT_OUT ) ;

    // Determina o tipo da instrucao.
    if ( !BITS[15] && !BITS[14] ) TYPE = 0 ;                  // A instrucao e de transferencia de controle.
    if ( !BITS[15] && BITS[14] )  TYPE = 1 ;                  // A instrucao e de ALU ou memoria.
    if ( BITS[15] && !BITS[14] )  TYPE = 2 ;                  // A instrucao e de constante de 11 bits.
    if ( BITS[15] && BITS[14] )   TYPE = 3 ;                  // A instrucao e de carga de byte.

    // Determina o registrador WC
    if ( !BITS[13] && !BITS[12] && !BITS[11] ) WC = 0 ;
    if ( !BITS[13] && !BITS[12] && BITS[11] )  WC = 1 ;
    if ( !BITS[13] && BITS[12] && !BITS[11] )  WC = 2 ;
    if ( !BITS[13] && BITS[12] && BITS[11] )   WC = 3 ;
    if ( BITS[13] && !BITS[12] && !BITS[11] )  WC = 4 ;
    if ( BITS[13] && !BITS[12] && BITS[11] )   WC = 5 ;
    if ( BITS[13] && BITS[12] && !BITS[11] )   WC = 6 ;
    if ( BITS[13] && BITS[12] && BITS[11] )    WC = 7 ;

    // Determina o registrador RA
    if ( !BITS[5] && !BITS[4] && !BITS[3] ) RA = 0 ;
    if ( !BITS[5] && !BITS[4] &&  BITS[3] ) RA = 1 ;
    if ( !BITS[5] &&  BITS[4] && !BITS[3] ) RA = 2 ;
    if ( !BITS[5] &&  BITS[4] &&  BITS[3] ) RA = 3 ;
    if (  BITS[5] && !BITS[4] && !BITS[3] ) RA = 4 ;
    if (  BITS[5] && !BITS[4] &&  BITS[3] ) RA = 5 ;
    if (  BITS[5] &&  BITS[4] && !BITS[3] ) RA = 6 ;
    if (  BITS[5] &&  BITS[4] &&  BITS[3] ) RA = 7 ;

    // Determina o registrador RB
    if ( !BITS[2] && !BITS[1] && !BITS[0] ) RB = 0 ;
    if ( !BITS[2] && !BITS[1] && BITS[0] ) RB = 1 ;
    if ( !BITS[2] && BITS[1] && !BITS[0] ) RB = 2 ;
    if ( !BITS[2] && BITS[1] && BITS[0] ) RB = 3 ;
    if ( BITS[2] && !BITS[1] && !BITS[0] ) RB = 4 ;
    if ( BITS[2] && !BITS[1] && BITS[0] ) RB = 5 ;
    if ( BITS[2] && BITS[1] && !BITS[0] ) RB = 6 ;
    if ( BITS[2] && BITS[1] && BITS[0] ) RB = 7 ;

    // Determina RCONST
    if ( BITS[10] ) RCONST = 1 ;   // lch.
    else            RCONST = 0 ;   // lcl.

    // Determina OPJUMP
    if ( !BITS[13] && !BITS[12] )  // jump false.
        OPJUMP = 0 ;
    if ( !BITS[13] && BITS[12] )   // jump true.
        OPJUMP = 1 ;
    if ( BITS[13] && !BITS[12] )   // jump incondicional.
        OPJUMP = 2 ;
    if ( BITS[13] && BITS[12] )    // jump and link ou jump register.
        OPJUMP = 3 ;

    // Determina RJUMP
    if ( BITS[11] ) RJUMP = 1 ;    // jump register.
    else            RJUMP = 0 ;    // jump and link.

    // Determina COND :
    if (!BITS[11] && !BITS[10] && !BITS[9] && !BITS[8] )
    {
        strcpy ( FLAGNAME , "true " ) ;
    }

    if (!BITS[11] && !BITS[10] && BITS[9] && BITS[8] )
    {
        strcpy ( FLAGNAME , "overflow " ) ;
    }

    if (!BITS[11] && BITS[10] && !BITS[9] && !BITS[8] )
    {
        strcpy ( FLAGNAME , "neg " ) ;
    }

    if (!BITS[11] && BITS[10] && !BITS[9] && BITS[8] )
    {
        strcpy ( FLAGNAME , "zero " ) ;
    }

    if (!BITS[11] && BITS[10] && BITS[9] && !BITS[8] )
    {
        strcpy ( FLAGNAME , "carry " ) ;
    }

    if (!BITS[11] && BITS[10] && BITS[9] && BITS[8] )
    {
        strcpy ( FLAGNAME , "negzero " ) ;
    }


    switch ( TYPE )
    {
    case 0 :   // A instrucao e de transferencia de controle.
        switch ( OPJUMP )
        {
        case 0:   // JUMP FALSE:

            if ( !BITS[11] && !BITS[10] && !BITS[9] && !BITS[8] )
                strcpy ( OPNAME , "nop" ) ;
            else
            {
                strcpy ( OPNAME , "jf." ) ;
                strcat ( OPNAME , FLAGNAME ) ;
                sprintf ( FLAGNAME , "%4X" , OFFSET ) ;
                strcat ( OPNAME , FLAGNAME ) ;
            }

            break ; // case 0

        case 1: // JUMP TRUE

            strcpy ( OPNAME , "jt." ) ;
            strcat ( OPNAME , FLAGNAME ) ;
            sprintf ( FLAGNAME , "%4X" , OFFSET ) ;
            strcat ( OPNAME , FLAGNAME ) ;

            break ; // case 1

        case 2:   //Jump incondicional

            strcpy ( OPNAME , "j " ) ;
            sprintf ( FLAGNAME , "%4X" , OFFSET ) ;
            strcat ( OPNAME , FLAGNAME ) ;

            break; // case 2

        case 3:

            if( !RJUMP )      // jump and link
            {
                strcpy ( OPNAME , "jal r" ) ;
                sprintf ( FLAGNAME , "%d" , RB ) ;
                strcat ( OPNAME , FLAGNAME ) ;
            }
            else      // jump register
            {
                strcpy ( OPNAME , "jr r" ) ;
                sprintf ( FLAGNAME , "%d" , RB ) ;
                strcat ( OPNAME , FLAGNAME ) ;
            }
            break ; // break case 3.
        } // end switch (OPJUMP).

        break ; // break case 0.

    case 1 :   // A instrucao e de instrucao e de ALU ou memoria.

        // Operacao 0 : zeros C :
        if ( !BITS[10] && !BITS[9] && !BITS[8] && !BITS[7] && !BITS[6] )
        {
            strcpy ( OPNAME , "zeros r" ) ;
            sprintf ( FLAGNAME , "%u" , WC ) ;
            strcat ( OPNAME , FLAGNAME ) ;
        }

        // Operacao 1 : ones c :
        if ( !BITS[10] && !BITS[9] && !BITS[8] && !BITS[7] && BITS[6] )
        {
            strcpy ( OPNAME , "ones r" ) ;
            sprintf ( FLAGNAME , "%u" , WC ) ;
            strcat ( OPNAME , FLAGNAME ) ;

        }

        // Operacao 2 : and C = A & B :
        if ( !BITS[10] && !BITS[9] && !BITS[8] && BITS[7] && !BITS[6] )
        {
            strcpy ( OPNAME , "and r" ) ;
            sprintf ( FLAGNAME , "%u" , WC ) ;
            strcat ( OPNAME , FLAGNAME ) ;
            strcat ( OPNAME , ",r" ) ;
            sprintf ( FLAGNAME , "%u" , RA ) ;
            strcat ( OPNAME , FLAGNAME ) ;
            strcat ( OPNAME , ",r" ) ;
            sprintf ( FLAGNAME , "%u" , RB ) ;
            strcat ( OPNAME , FLAGNAME ) ;

        }

        // Operacao 3 : nand C = !A | !B :
        if ( !BITS[10] && !BITS[9] && !BITS[8] && BITS[7] && BITS[6] )
        {
            strcpy ( OPNAME , "nand r" ) ;
            sprintf ( FLAGNAME , "%u" , WC ) ;
            strcat ( OPNAME , FLAGNAME ) ;
            strcat ( OPNAME , ",r" ) ;
            sprintf ( FLAGNAME , "%u" , RA ) ;
            strcat ( OPNAME , FLAGNAME ) ;
            strcat ( OPNAME , ",r" ) ;
            sprintf ( FLAGNAME , "%u" , RB ) ;
            strcat ( OPNAME , FLAGNAME ) ;

        }

        // Operacao 4 : or C = A | B :
        if ( !BITS[10] && !BITS[9] && BITS[8] && !BITS[7] && !BITS[6] )
        {
            strcpy ( OPNAME , "or r" ) ;
            sprintf ( FLAGNAME , "%u" , WC ) ;
            strcat ( OPNAME , FLAGNAME ) ;
            strcat ( OPNAME , ",r" ) ;
            sprintf ( FLAGNAME , "%u" , RA ) ;
            strcat ( OPNAME , FLAGNAME ) ;
            strcat ( OPNAME , ",r" ) ;
            sprintf ( FLAGNAME , "%u" , RB ) ;
            strcat ( OPNAME , FLAGNAME ) ;

        }

        // Operacao 5 : nor C = !A & !B :
        if ( !BITS[10] && !BITS[9] && BITS[8] && !BITS[7] && BITS[6] )
        {
            strcpy ( OPNAME , "nor r" ) ;
            sprintf ( FLAGNAME , "%u" , WC ) ;
            strcat ( OPNAME , FLAGNAME ) ;
            strcat ( OPNAME , ",r" ) ;
            sprintf ( FLAGNAME , "%u" , RA ) ;
            strcat ( OPNAME , FLAGNAME ) ;
            strcat ( OPNAME , ",r" ) ;
            sprintf ( FLAGNAME , "%u" , RB ) ;
            strcat ( OPNAME , FLAGNAME ) ;

        }

        // Operacao 6 : xor C = A ^ B :
        if ( !BITS[10] && !BITS[9] && BITS[8] && BITS[7] && !BITS[6] )
        {
            strcpy ( OPNAME , "xor r" ) ;
            sprintf ( FLAGNAME , "%u" , WC ) ;
            strcat ( OPNAME , FLAGNAME ) ;
            strcat ( OPNAME , ",r" ) ;
            sprintf ( FLAGNAME , "%u" , RA ) ;
            strcat ( OPNAME , FLAGNAME ) ;
            strcat ( OPNAME , ",r" ) ;
            sprintf ( FLAGNAME , "%u" , RB ) ;
            strcat ( OPNAME , FLAGNAME ) ;

        }

        // Operacao 7 : xnor C = !A ^ B :
        if ( !BITS[10] && !BITS[9] && BITS[8] && BITS[7] && BITS[6] )
        {
            strcpy ( OPNAME , "xnor r" ) ;
            sprintf ( FLAGNAME , "%u" , WC ) ;
            strcat ( OPNAME , FLAGNAME ) ;
            strcat ( OPNAME , ",r" ) ;
            sprintf ( FLAGNAME , "%u" , RA ) ;
            strcat ( OPNAME , FLAGNAME ) ;
            strcat ( OPNAME , ",r" ) ;
            sprintf ( FLAGNAME , "%u" , RB ) ;
            strcat ( OPNAME , FLAGNAME ) ;

        }

        // Operacao 8 : passnota C = !A :
        if ( !BITS[10] && BITS[9] && !BITS[8] && !BITS[7] && !BITS[6] )
        {
            strcpy ( OPNAME , "passnota r" ) ;
            sprintf ( FLAGNAME , "%u" , WC ) ;
            strcat ( OPNAME , FLAGNAME ) ;
            strcat ( OPNAME , ",r" ) ;
            sprintf ( FLAGNAME , "%u" , RA ) ;
            strcat ( OPNAME , FLAGNAME ) ;

        }

        // Operacao 9 : passa C = A :
        if ( !BITS[10] && BITS[9] && !BITS[8] && !BITS[7] && BITS[6] )
        {
            strcpy ( OPNAME , "passa r" ) ;
            sprintf ( FLAGNAME , "%u" , WC ) ;
            strcat ( OPNAME , FLAGNAME ) ;
            strcat ( OPNAME , ",r" ) ;
            sprintf ( FLAGNAME , "%u" , RA ) ;
            strcat ( OPNAME , FLAGNAME ) ;

        }

        // Operacao 10 : andnota C = !A & B :
        if ( !BITS[10] && BITS[9] && !BITS[8] && BITS[7] && !BITS[6] )
        {
            strcpy ( OPNAME , "andnota r" ) ;
            sprintf ( FLAGNAME , "%u" , WC ) ;
            strcat ( OPNAME , FLAGNAME ) ;
            strcat ( OPNAME , ",r" ) ;
            sprintf ( FLAGNAME , "%u" , RA ) ;
            strcat ( OPNAME , FLAGNAME ) ;
            strcat ( OPNAME , ",r" ) ;
            sprintf ( FLAGNAME , "%u" , RB ) ;
            strcat ( OPNAME , FLAGNAME ) ;

        }

        // Operacao 11 : ornotb C = A | !B :
        if ( !BITS[10] && BITS[9] && !BITS[8] && BITS[7] && BITS[6] )
        {
            strcpy ( OPNAME , "ornotb r" ) ;
            sprintf ( FLAGNAME , "%u" , WC ) ;
            strcat ( OPNAME , FLAGNAME ) ;
            strcat ( OPNAME , ",r" ) ;
            sprintf ( FLAGNAME , "%u" , RA ) ;
            strcat ( OPNAME , FLAGNAME ) ;
            strcat ( OPNAME , ",r" ) ;
            sprintf ( FLAGNAME , "%u" , RB ) ;
            strcat ( OPNAME , FLAGNAME ) ;

        }

        // Operacao 16 :  lsl c a :
        if ( BITS[10] && !BITS[9] && !BITS[8] && !BITS[7] && !BITS[6] )
        {
            strcpy ( OPNAME , "lsl r" ) ;
            sprintf ( FLAGNAME , "%u" , WC ) ;
            strcat ( OPNAME , FLAGNAME ) ;
            strcat ( OPNAME , ",r" ) ;
            sprintf ( FLAGNAME , "%u" , RA ) ;
            strcat ( OPNAME , FLAGNAME ) ;

        }

        // Operacao 17 : asl c a :
        if ( BITS[10] && !BITS[9] && !BITS[8] && !BITS[7] && BITS[6] )
        {
            strcpy ( OPNAME , "asl r" ) ;
            sprintf ( FLAGNAME , "%u" , WC ) ;
            strcat ( OPNAME , FLAGNAME ) ;
            strcat ( OPNAME , ",r" ) ;
            sprintf ( FLAGNAME , "%u" , RA ) ;
            strcat ( OPNAME , FLAGNAME ) ;

        }

        // Operacao 18 : lsr c a :
        if ( BITS[10] && !BITS[9] && !BITS[8] && BITS[7] && !BITS[6] )
        {
            strcpy ( OPNAME , "lsr r" ) ;
            sprintf ( FLAGNAME , "%u" , WC ) ;
            strcat ( OPNAME , FLAGNAME ) ;
            strcat ( OPNAME , ",r" ) ;
            sprintf ( FLAGNAME , "%u" , RA ) ;
            strcat ( OPNAME , FLAGNAME ) ;

        }

        // Operacao 19 : asr c a :
        if ( BITS[10] && !BITS[9] && !BITS[8] && BITS[7] && BITS[6] )
        {
            strcpy ( OPNAME , "asr r" ) ;
            sprintf ( FLAGNAME , "%u" , WC ) ;
            strcat ( OPNAME , FLAGNAME ) ;
            strcat ( OPNAME , ",r" ) ;
            sprintf ( FLAGNAME , "%u" , RA ) ;
            strcat ( OPNAME , FLAGNAME ) ;

        }

        // Operacao 20 : load c a WC = MEM[RA] :
        if ( BITS[10] && !BITS[9] && BITS[8] && !BITS[7] && !BITS[6] )
        {
            strcpy ( OPNAME , "load r" ) ;
            sprintf ( FLAGNAME , "%u" , WC ) ;
            strcat ( OPNAME , FLAGNAME ) ;
            strcat ( OPNAME , ",r" ) ;
            sprintf ( FLAGNAME , "%u" , RA ) ;
            strcat ( OPNAME , FLAGNAME ) ;

        }

        // Operacao 22 : store a b  MEM[RA] = B :
        if ( BITS[10] && !BITS[9] && BITS[8] && BITS[7] && !BITS[6] )
        {
            strcpy ( OPNAME , "store r" ) ;
            sprintf ( FLAGNAME , "%u" , RA ) ;
            strcat ( OPNAME , FLAGNAME ) ;
            strcat ( OPNAME , ",r" ) ;
            sprintf ( FLAGNAME , "%u" , RB ) ;
            strcat ( OPNAME , FLAGNAME ) ;

        }

        // Operacao 24 : add c a b   C = A + B :
        if ( BITS[10] && BITS[9] && !BITS[8] && !BITS[7] && !BITS[6] )
        {
            strcpy ( OPNAME , "add r" ) ;
            sprintf ( FLAGNAME , "%u" , WC ) ;
            strcat ( OPNAME , FLAGNAME ) ;
            strcat ( OPNAME , ",r" ) ;
            sprintf ( FLAGNAME , "%u" , RA ) ;
            strcat ( OPNAME , FLAGNAME ) ;
            strcat ( OPNAME , ",r" ) ;
            sprintf ( FLAGNAME , "%u" , RB ) ;
            strcat ( OPNAME , FLAGNAME ) ;

        }

        // Operacao 25 : sub c a b   C = A - B :
        if ( BITS[10] && BITS[9] && !BITS[8] && !BITS[7] && BITS[6] )
        {
            strcpy ( OPNAME , "sub r" ) ;
            sprintf ( FLAGNAME , "%u" , WC ) ;
            strcat ( OPNAME , FLAGNAME ) ;
            strcat ( OPNAME , ",r" ) ;
            sprintf ( FLAGNAME , "%u" , RA ) ;
            strcat ( OPNAME , FLAGNAME ) ;
            strcat ( OPNAME , ",r" ) ;
            sprintf ( FLAGNAME , "%u" , RB ) ;
            strcat ( OPNAME , FLAGNAME ) ;

        }

        // Operacao 26 : addinca c a b   C = A + B + 1 :
        if ( BITS[10] && BITS[9] && !BITS[8] && BITS[7] && !BITS[6] )
        {
            strcpy ( OPNAME , "addinc r" ) ;
            sprintf ( FLAGNAME , "%u" , WC ) ;
            strcat ( OPNAME , FLAGNAME ) ;
            strcat ( OPNAME , ",r" ) ;
            sprintf ( FLAGNAME , "%u" , RA ) ;
            strcat ( OPNAME , FLAGNAME ) ;
            strcat ( OPNAME , ",r" ) ;
            sprintf ( FLAGNAME , "%u" , RB ) ;
            strcat ( OPNAME , FLAGNAME ) ;

        }

        // Operacao 27 : subdec c a b   C = A - B - 1 :
        if ( BITS[10] && BITS[9] && !BITS[8] && BITS[7] && BITS[6] )
        {
            strcpy ( OPNAME , "subdec r" ) ;
            sprintf ( FLAGNAME , "%u" , WC ) ;
            strcat ( OPNAME , FLAGNAME ) ;
            strcat ( OPNAME , ",r" ) ;
            sprintf ( FLAGNAME , "%u" , RA ) ;
            strcat ( OPNAME , FLAGNAME ) ;
            strcat ( OPNAME , ",r" ) ;
            sprintf ( FLAGNAME , "%u" , RB ) ;
            strcat ( OPNAME , FLAGNAME ) ;

        }

        // Operacao 28 : inca c a  C = A + 1 :
        if ( BITS[10] && BITS[9] && BITS[8] && !BITS[7] && !BITS[6] )
        {
            strcpy ( OPNAME , "inca r" ) ;
            sprintf ( FLAGNAME , "%u" , WC ) ;
            strcat ( OPNAME , FLAGNAME ) ;
            strcat ( OPNAME , ",r" ) ;
            sprintf ( FLAGNAME , "%u" , RA ) ;
            strcat ( OPNAME , FLAGNAME ) ;

        }

        // Operacao 29 : dec c a    C = A - 1 :
        if ( BITS[10] && BITS[9] && BITS[8] && !BITS[7] && BITS[6] )
        {
            strcpy ( OPNAME , "deca r" ) ;
            sprintf ( FLAGNAME , "%u" , WC ) ;
            strcat ( OPNAME , FLAGNAME ) ;
            strcat ( OPNAME , ",r" ) ;
            sprintf ( FLAGNAME , "%u" , RA ) ;
            strcat ( OPNAME , FLAGNAME ) ;

        }

        break ; // end case 1

    case 2 :   // A instrucao e de constante de 11 bits.

        strcpy ( OPNAME , "loadlit r" ) ;
        sprintf ( FLAGNAME , "%u" , WC ) ;
        strcat ( OPNAME , FLAGNAME ) ;
        strcat ( OPNAME , "," ) ;
        sprintf ( FLAGNAME , "%4X" , OFFSET ) ;
        strcat ( OPNAME , FLAGNAME ) ;

        break ; // end case 2

    case 3 :   // A instrucao e de carga de byte.

        if( RCONST )  		//lch rc, const 8
        {
            OFFSET = OFFSET>>8 ;
            strcpy ( OPNAME , "lch r" ) ;
            sprintf ( FLAGNAME , "%u" , WC ) ;
            strcat ( OPNAME , FLAGNAME ) ;
            strcat ( OPNAME , "," ) ;
            sprintf ( FLAGNAME , "%4X" , OFFSET ) ;
            strcat ( OPNAME , FLAGNAME ) ;
        }
        else
        {
            strcpy ( OPNAME , "lcl r" ) ;
            sprintf ( FLAGNAME , "%u" , WC ) ;
            strcat ( OPNAME , FLAGNAME ) ;
            strcat ( OPNAME , "," ) ;
            sprintf ( FLAGNAME , "%4X" , OFFSET ) ;
            strcat ( OPNAME , FLAGNAME ) ;
        }

        break ; // end case 3

    } // end switch (TYPE) ;

} // end inst_name(~) ;
