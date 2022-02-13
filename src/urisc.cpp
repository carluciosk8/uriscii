/***************************************************************************
                                 urisc.cpp
                             -------------------
    begin                : Fri Jun 23 2000
    copyright            : (C) 2000 by Carlucio Santos Cordeiro

    DCC - UFMG - Computer Organization & Design

 ***************************************************************************/

///   Header files   ////////////////////////////////////////
///                  ////////////////////////////////////////

#include "urisc.h"


///   Definitions    ////////////////////////////////////////
///                  ////////////////////////////////////////

//    word ONE = {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0} ;
//    word XXX = {X,X,X,X,X,X,X,X,X,X,X,X,X,X,X,X} ;
//    word FFOO = {0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1} ;
//    word OOFF = {1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0} ;
//    SIGNAL SEVEN[3] = {1,1,1} ;



///   FUNCTION    : urisc::HLT.
///   EXPLANATION : Detecta quando ocorre halt.
SIGNAL urisc::HLT ()
{
    return HALT ;
}


///   FUNCTION    : urisc::LOAD.
///   EXPLANATION : Carrega o programa para a memoria.
void urisc::LOAD( char *FILE )
{
    MEMORY.LOAD ( FILE , PC ) ;
}


void urisc::STATUS ( bool PAUSE )
{
    unsigned short REGS[8] , IRV , ALUOUTV ;
    char NAME[50] , FL[10] ;

    REG_FILE.GET_REGS ( REGS ) ;
    put_dec_word ( IRV , IR_OUT ) ;
    put_dec_word ( ALUOUTV , ALUOUT_OUT ) ;

    INST_NAME ( IR_OUT , NAME , FL , EXT_OUT ) ;

    system ( "clear" ) ;
    printf ( "+===========================================================================+\n" ) ;
    printf ( "|                         Status do Processador                             |\n" ) ;
    printf ( "+---------------------------------------------------------------------------+\n" ) ;
    printf ( "|                                                                           |\n" ) ;
    printf ( "|        REGISTRADORES                 FLAGS                                |\n" ) ;
    printf ( "|        -------------                 -----                                |\n" ) ;
    printf ( "|                                                                           |\n" ) ;
    printf ( "|         R0 = %4X                      NEG : %1d                            |\n", REGS[0] , FLAGS[0] ) ;
    printf ( "|         R1 = %4X                     ZERO : %1d                            |\n", REGS[1] , FLAGS[1] ) ;
    printf ( "|         R2 = %4X                    CARRY : %1d                            |\n", REGS[2] , FLAGS[3] ) ;
    printf ( "|         R3 = %4X                  NEGZERO : %1d                            |\n", REGS[3] , FLAGS[2] ) ;
    printf ( "|         R4 = %4X                 OVERFLOW : %1d                            |\n", REGS[4] , FLAGS[4] ) ;
    printf ( "|         R5 = %4X                                                         |\n", REGS[5] ) ;
    printf ( "|         R6 = %4X                                                         |\n", REGS[6] ) ;
    printf ( "|         R7 = %4X                                                         |\n", REGS[7] ) ;
    printf ( "|                                                                           |\n" ) ;
    printf ( "|                                                                           |\n" ) ;
    printf ( "|         PC = %4X                                                         |\n", PC_ATUAL ) ;
    printf ( "|         IR = %4X     INSTRUCAO : %-30s          |\n", IRV , NAME ) ;
    printf ( "|     ALUOUT = %4X                                                         |\n", ALUOUTV ) ;
    printf ( "|                                                                           |\n" ) ;
    printf ( "|                                                                           |\n" ) ;
    printf ( "+===========================================================================+\n" ) ;

    if ( PAUSE ) getchar() ;
}


void urisc::DUMP ( int POS , int N , bool PAUSE )
{
    MEMORY.DUMP ( POS , N , PAUSE ) ;
}


///   FUNCTION    : urisc::IF.
///   EXPLANATION : Executa o ciclo FETCH ( busca da instrucao ).
void urisc::IF ()
{
    word ONE = {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0} ;
    word XXX = {X,X,X,X,X,X,X,X,X,X,X,X,X,X,X,X} ;

    word ADR ;

    CONTROL.FETCH ( CTRL_LINE ) ;

    IorD = CTRL_LINE[3] ;
    WORD_MUX2 ( ADR , PC_OUT , ALUOUT_OUT , IorD ) ;
    put_dec_word ( PC_ATUAL , ADR ) ;

    MEM_READ = CTRL_LINE[4] ;
    MEM_WRITE = CTRL_LINE[5] ;
    MEMORY.EX ( ADR , DATA_OUT , B_OUT , MEM_READ , MEM_WRITE ) ;

    IR_WRITE = CTRL_LINE[6] ;
    IR.EX ( IR_OUT , DATA_OUT , IR_WRITE ) ;
    MDR.EX ( MDR_OUT , DATA_OUT , 1 ) ;

    ADDER.EX ( ADDER_OUT , ONE , PC_OUT ) ;
    PC_SOURCE[0] = CTRL_LINE[0] ;
    PC_SOURCE[1] = CTRL_LINE[1] ;
    PC_WRITE = CTRL_LINE[2] ;

    WORD_MUX4 ( PC_IN , ADDER_OUT , ALUOUT_OUT , B_OUT , XXX , PC_SOURCE ) ;
    PC.EX ( PC_OUT , PC_IN , PC_WRITE ) ;
    PCR.EX ( PCR_OUT , PC_OUT , 1 ) ;
}


///   FUNCTION    : urisc::ID.
///   EXPLANATION : Executa o ciclo DECODE ( decodificacao da instrucao ).
void urisc::ID ()
{
    SIGNAL RA[3] , RB[3] ,
            TMP1[3] , TMP2[3] ;
    offset_t OFFSET ;

    IR.EX ( IR_OUT , DATA_OUT , 0 ) ;

    CONTROL.EX ( IR_OUT , FLAGS , CTRL_LINE , HALT ) ;

    PC_SOURCE[0] = CTRL_LINE[0] ;
    PC_SOURCE[1] = CTRL_LINE[1] ;
    PC_WRITE     = CTRL_LINE[2] ;
    IorD         = CTRL_LINE[3] ;
    MEM_READ     = CTRL_LINE[4] ;
    MEM_WRITE    = CTRL_LINE[5] ;
    IR_WRITE     = CTRL_LINE[6] ;
    SRC_C[0]     = CTRL_LINE[7] ;
    SRC_C[1]     = CTRL_LINE[8] ;
    JAL          = CTRL_LINE[9] ;
    LC           = CTRL_LINE[10] ;
    REG_WRITE    = CTRL_LINE[11] ;
    EXTEND[0]    = CTRL_LINE[12] ;
    EXTEND[1]    = CTRL_LINE[13] ;
    EXTEND[2]    = CTRL_LINE[14] ;
    ALU_SRC_A[0] = CTRL_LINE[15] ;
    ALU_SRC_A[1] = CTRL_LINE[16] ;
    ALU_SRC_B    = CTRL_LINE[17] ;
    ALUOP[0]     = CTRL_LINE[18] ;
    ALUOP[1]     = CTRL_LINE[19] ;
    ALUOP[2]     = CTRL_LINE[20] ;
    ALUOP[3]     = CTRL_LINE[21] ;
    ALUOP[4]     = CTRL_LINE[22] ;
    FLAG_WRITE   = CTRL_LINE[23] ;

    TMP1[0] = IR_OUT[3] ;
    TMP1[1] = IR_OUT[4] ;
    TMP1[2] = IR_OUT[5] ;
    RB[0] = IR_OUT[0] ;
    RB[1] = IR_OUT[1] ;
    RB[2] = IR_OUT[2] ;
    TMP2[0] = IR_OUT[11] ;
    TMP2[1] = IR_OUT[12] ;
    TMP2[2] = IR_OUT[13] ;
    MUX2 ( RA[0] , TMP1[0] , TMP2[0] , LC ) ;
    MUX2 ( RA[1] , TMP1[1] , TMP2[1] , LC ) ;
    MUX2 ( RA[2] , TMP1[2] , TMP2[2] , LC ) ;

    REG_FILE.READ ( RA , RB , A_IN , B_IN ) ;
    A.EX ( A_OUT , A_IN , 1 ) ;
    B.EX ( B_OUT , B_IN , 1 ) ;

    OFFSET[0] = IR_OUT[0] ;
    OFFSET[1] = IR_OUT[1] ;
    OFFSET[2] = IR_OUT[2] ;
    OFFSET[3] = IR_OUT[3] ;
    OFFSET[4] = IR_OUT[4] ;
    OFFSET[5] = IR_OUT[5] ;
    OFFSET[6] = IR_OUT[6] ;
    OFFSET[7] = IR_OUT[7] ;
    OFFSET[8] = IR_OUT[8] ;
    OFFSET[9] = IR_OUT[9] ;
    OFFSET[10] = IR_OUT[10] ;
    OFFSET[11] = IR_OUT[11] ;

    EXT.EX ( OFFSET , EXTEND , EXT_OUT ) ;
}


///   FUNCTION    : urisc::EX.
///   EXPLANATION : Executa o ciclo EXECUTE ( execucao da instrucao ).
void urisc::EX ()
{
    word FFOO = {0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1} ;
    word OOFF = {1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0} ;

    word IN2 , IN3 , SRCA , SRCB , OUT ;

    WORD_AND2 ( IN2 , A_OUT , OOFF ) ;
    WORD_AND2 ( IN3 , A_OUT , FFOO ) ;

    WORD_MUX4 ( SRCA , A_OUT , PC_OUT , IN2 , IN3 , ALU_SRC_A ) ;
    WORD_MUX2 ( SRCB , B_OUT , EXT_OUT , ALU_SRC_B ) ;

    ALU.EX ( OUT , FLAGS , SRCA , SRCB , ALUOP , FLAG_WRITE ) ;
    ALUOUT.EX ( ALUOUT_OUT , OUT , 1 ) ;
}


///   FUNCTION    : urisc::MEM.
///   EXPLANATION : Executa o ciclo MEMORY ( se instrucao de memoria ).
void urisc::MEM()
{
    word XXX = {X,X,X,X,X,X,X,X,X,X,X,X,X,X,X,X} ;

    word ADR ;

    ALUOUT.EX ( ALUOUT_OUT , XXX , 0 ) ;
    WORD_MUX2 ( ADR , PC_OUT , ALUOUT_OUT , IorD ) ;
    B.EX ( B_OUT , B_IN , 0 ) ;
    MEMORY.EX ( ADR , DATA_OUT , B_OUT , MEM_READ , MEM_WRITE ) ;

    IR.EX ( IR_OUT , DATA_OUT , IR_WRITE ) ;
    MDR.EX ( MDR_OUT , DATA_OUT , 1 ) ;
}


///   FUNCTION    : urisc::WB.
///   EXPLANATION : Executa o ciclo WRITE_BACK ( escreve o resultado ).
void urisc::WB()
{
    word XXX = {X,X,X,X,X,X,X,X,X,X,X,X,X,X,X,X} ;

    word C ;
    SIGNAL WC[3] ;

    PCR.EX ( PCR_OUT , PC_OUT , 0 ) ;
    WORD_MUX4 ( C , MDR_OUT , PCR_OUT , ALUOUT_OUT , EXT_OUT , SRC_C ) ;
    MUX2 ( WC[0] , IR_OUT[11] , 1 , JAL ) ;
    MUX2 ( WC[1] , IR_OUT[12] , 1 , JAL ) ;
    MUX2 ( WC[2] , IR_OUT[13] , 1 , JAL ) ;

    REG_FILE.WRITE ( WC , C , REG_WRITE ) ;

    WORD_MUX4 ( PC_IN , ADDER_OUT , ALUOUT_OUT , B_OUT , XXX , PC_SOURCE ) ;
    PC.EX ( PC_OUT , PC_IN , PC_WRITE ) ;
}



///   FUNCTION    : INST_NAME.
///   EXPLANATION : Identifica o mnemonico da instrucao.

void INST_NAME ( word BITS , char OPNAME[50] , char FLAGNAME[10] , word EXT_OUT )
{
    unsigned short OFFSET ,
            TYPE ,
            WC , RA ,RB , RJUMP , RCONST , OPJUMP ;


    put_dec_word ( OFFSET , EXT_OUT ) ;

    // Determina o tipo da instrucao.
    if ( !BITS[15] && !BITS[14] )
        TYPE = 0 ;                  // A instrucao e de transferencia de controle.
    if ( !BITS[15] && BITS[14] )
        TYPE = 1 ;                  // A instrucao e de ALU ou memoria.
    if ( BITS[15] && !BITS[14] )
        TYPE = 2 ;                  // A instrucao e de constante de 11 bits.
    if ( BITS[15] && BITS[14] )
        TYPE = 3 ;                  // A instrucao e de carga de byte.


    // Determina o registrador WC
    if ( !BITS[13] && !BITS[12] && !BITS[11] )
        WC = 0 ;
    if ( !BITS[13] && !BITS[12] && BITS[11] )
        WC = 1 ;
    if ( !BITS[13] && BITS[12] && !BITS[11] )
        WC = 2 ;
    if ( !BITS[13] && BITS[12] && BITS[11] )
        WC = 3 ;
    if ( BITS[13] && !BITS[12] && !BITS[11] )
        WC = 4 ;
    if ( BITS[13] && !BITS[12] && BITS[11] )
        WC = 5 ;
    if ( BITS[13] && BITS[12] && !BITS[11] )
        WC = 6 ;
    if ( BITS[13] && BITS[12] && BITS[11] )
        WC = 7 ;


    // Determina o registrador RA
    if ( !BITS[5] && !BITS[4] && !BITS[3] )
        RA = 0 ;
    if ( !BITS[5] && !BITS[4] && BITS[3] )
        RA = 1 ;
    if ( !BITS[5] && BITS[4] && !BITS[3] )
        RA = 2 ;
    if ( !BITS[5] && BITS[4] && BITS[3] )
        RA = 3 ;
    if ( BITS[5] && !BITS[4] && !BITS[3] )
        RA = 4 ;
    if ( BITS[5] && !BITS[4] && BITS[3] )
        RA = 5 ;
    if ( BITS[5] && BITS[4] && !BITS[3] )
        RA = 6 ;
    if ( BITS[5] && BITS[4] && BITS[3] )
        RA = 7 ;


    // Determina o registrador RB
    if ( !BITS[2] && !BITS[1] && !BITS[0] )
        RB = 0 ;
    if ( !BITS[2] && !BITS[1] && BITS[0] )
        RB = 1 ;
    if ( !BITS[2] && BITS[1] && !BITS[0] )
        RB = 2 ;
    if ( !BITS[2] && BITS[1] && BITS[0] )
        RB = 3 ;
    if ( BITS[2] && !BITS[1] && !BITS[0] )
        RB = 4 ;
    if ( BITS[2] && !BITS[1] && BITS[0] )
        RB = 5 ;
    if ( BITS[2] && BITS[1] && !BITS[0] )
        RB = 6 ;
    if ( BITS[2] && BITS[1] && BITS[0] )
        RB = 7 ;


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


    // Aqui eh que a instrucao eh docodificada.

    switch ( TYPE )
    {
    case 0 :   // A instrucao e de transferencia de controle.
        switch ( OPJUMP )
        {
        case 0:   // JUMP FALSE:

            strcpy ( OPNAME , "jf." ) ;
            strcat ( OPNAME , FLAGNAME ) ;
            sprintf ( FLAGNAME , "%4X" , OFFSET ) ;
            strcat ( OPNAME , FLAGNAME ) ;

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
            strcat ( OPNAME , " , r" ) ;
            sprintf ( FLAGNAME , "%u" , RA ) ;
            strcat ( OPNAME , FLAGNAME ) ;
            strcat ( OPNAME , " , r" ) ;
            sprintf ( FLAGNAME , "%u" , RB ) ;
            strcat ( OPNAME , FLAGNAME ) ;

        }

        // Operacao 3 : nand C = !A | !B :
        if ( !BITS[10] && !BITS[9] && !BITS[8] && BITS[7] && BITS[6] )
        {
            strcpy ( OPNAME , "nand r" ) ;
            sprintf ( FLAGNAME , "%u" , WC ) ;
            strcat ( OPNAME , FLAGNAME ) ;
            strcat ( OPNAME , " , r" ) ;
            sprintf ( FLAGNAME , "%u" , RA ) ;
            strcat ( OPNAME , FLAGNAME ) ;
            strcat ( OPNAME , " , r" ) ;
            sprintf ( FLAGNAME , "%u" , RB ) ;
            strcat ( OPNAME , FLAGNAME ) ;

        }

        // Operacao 4 : or C = A | B :
        if ( !BITS[10] && !BITS[9] && BITS[8] && !BITS[7] && !BITS[6] )
        {
            strcpy ( OPNAME , "or r" ) ;
            sprintf ( FLAGNAME , "%u" , WC ) ;
            strcat ( OPNAME , FLAGNAME ) ;
            strcat ( OPNAME , " , r" ) ;
            sprintf ( FLAGNAME , "%u" , RA ) ;
            strcat ( OPNAME , FLAGNAME ) ;
            strcat ( OPNAME , " , r" ) ;
            sprintf ( FLAGNAME , "%u" , RB ) ;
            strcat ( OPNAME , FLAGNAME ) ;

        }

        // Operacao 5 : nor C = !A & !B :
        if ( !BITS[10] && !BITS[9] && BITS[8] && !BITS[7] && BITS[6] )
        {
            strcpy ( OPNAME , "nor r" ) ;
            sprintf ( FLAGNAME , "%u" , WC ) ;
            strcat ( OPNAME , FLAGNAME ) ;
            strcat ( OPNAME , " , r" ) ;
            sprintf ( FLAGNAME , "%u" , RA ) ;
            strcat ( OPNAME , FLAGNAME ) ;
            strcat ( OPNAME , " , r" ) ;
            sprintf ( FLAGNAME , "%u" , RB ) ;
            strcat ( OPNAME , FLAGNAME ) ;

        }

        // Operacao 6 : xor C = A ^ B :
        if ( !BITS[10] && !BITS[9] && BITS[8] && BITS[7] && !BITS[6] )
        {
            strcpy ( OPNAME , "xor r" ) ;
            sprintf ( FLAGNAME , "%u" , WC ) ;
            strcat ( OPNAME , FLAGNAME ) ;
            strcat ( OPNAME , " , r" ) ;
            sprintf ( FLAGNAME , "%u" , RA ) ;
            strcat ( OPNAME , FLAGNAME ) ;
            strcat ( OPNAME , " , r" ) ;
            sprintf ( FLAGNAME , "%u" , RB ) ;
            strcat ( OPNAME , FLAGNAME ) ;

        }

        // Operacao 7 : xnor C = !A ^ B :
        if ( !BITS[10] && !BITS[9] && BITS[8] && BITS[7] && BITS[6] )
        {
            strcpy ( OPNAME , "xnor r" ) ;
            sprintf ( FLAGNAME , "%u" , WC ) ;
            strcat ( OPNAME , FLAGNAME ) ;
            strcat ( OPNAME , " , r" ) ;
            sprintf ( FLAGNAME , "%u" , RA ) ;
            strcat ( OPNAME , FLAGNAME ) ;
            strcat ( OPNAME , " , r" ) ;
            sprintf ( FLAGNAME , "%u" , RB ) ;
            strcat ( OPNAME , FLAGNAME ) ;

        }

        // Operacao 8 : passnota C = !A :
        if ( !BITS[10] && BITS[9] && !BITS[8] && !BITS[7] && !BITS[6] )
        {
            strcpy ( OPNAME , "passnota r" ) ;
            sprintf ( FLAGNAME , "%u" , WC ) ;
            strcat ( OPNAME , FLAGNAME ) ;
            strcat ( OPNAME , " , r" ) ;
            sprintf ( FLAGNAME , "%u" , RA ) ;
            strcat ( OPNAME , FLAGNAME ) ;

        }

        // Operacao 9 : passa C = A :
        if ( !BITS[10] && BITS[9] && !BITS[8] && !BITS[7] && BITS[6] )
        {
            strcpy ( OPNAME , "passa r" ) ;
            sprintf ( FLAGNAME , "%u" , WC ) ;
            strcat ( OPNAME , FLAGNAME ) ;
            strcat ( OPNAME , " , r" ) ;
            sprintf ( FLAGNAME , "%u" , RA ) ;
            strcat ( OPNAME , FLAGNAME ) ;

        }

        // Operacao 10 : andnota C = !A & B :
        if ( !BITS[10] && BITS[9] && !BITS[8] && BITS[7] && !BITS[6] )
        {
            strcpy ( OPNAME , "andnota r" ) ;
            sprintf ( FLAGNAME , "%u" , WC ) ;
            strcat ( OPNAME , FLAGNAME ) ;
            strcat ( OPNAME , " , r" ) ;
            sprintf ( FLAGNAME , "%u" , RA ) ;
            strcat ( OPNAME , FLAGNAME ) ;
            strcat ( OPNAME , " , r" ) ;
            sprintf ( FLAGNAME , "%u" , RB ) ;
            strcat ( OPNAME , FLAGNAME ) ;

        }

        // Operacao 11 : ornotb C = A | !B :
        if ( !BITS[10] && BITS[9] && !BITS[8] && BITS[7] && BITS[6] )
        {
            strcpy ( OPNAME , "ornotb r" ) ;
            sprintf ( FLAGNAME , "%u" , WC ) ;
            strcat ( OPNAME , FLAGNAME ) ;
            strcat ( OPNAME , " , r" ) ;
            sprintf ( FLAGNAME , "%u" , RA ) ;
            strcat ( OPNAME , FLAGNAME ) ;
            strcat ( OPNAME , " , r" ) ;
            sprintf ( FLAGNAME , "%u" , RB ) ;
            strcat ( OPNAME , FLAGNAME ) ;

        }

        // Operacao 16 :  lsl c a :
        if ( BITS[10] && !BITS[9] && !BITS[8] && !BITS[7] && !BITS[6] )
        {
            strcpy ( OPNAME , "lsl r" ) ;
            sprintf ( FLAGNAME , "%u" , WC ) ;
            strcat ( OPNAME , FLAGNAME ) ;
            strcat ( OPNAME , " , r" ) ;
            sprintf ( FLAGNAME , "%u" , RA ) ;
            strcat ( OPNAME , FLAGNAME ) ;

        }

        // Operacao 17 : asl c a :
        if ( BITS[10] && !BITS[9] && !BITS[8] && !BITS[7] && BITS[6] )
        {
            strcpy ( OPNAME , "asl r" ) ;
            sprintf ( FLAGNAME , "%u" , WC ) ;
            strcat ( OPNAME , FLAGNAME ) ;
            strcat ( OPNAME , " , r" ) ;
            sprintf ( FLAGNAME , "%u" , RA ) ;
            strcat ( OPNAME , FLAGNAME ) ;

        }

        // Operacao 18 : lsr c a :
        if ( BITS[10] && !BITS[9] && !BITS[8] && BITS[7] && !BITS[6] )
        {
            strcpy ( OPNAME , "lsr r" ) ;
            sprintf ( FLAGNAME , "%u" , WC ) ;
            strcat ( OPNAME , FLAGNAME ) ;
            strcat ( OPNAME , " , r" ) ;
            sprintf ( FLAGNAME , "%u" , RA ) ;
            strcat ( OPNAME , FLAGNAME ) ;

        }

        // Operacao 19 : asr c a :
        if ( BITS[10] && !BITS[9] && !BITS[8] && BITS[7] && BITS[6] )
        {
            strcpy ( OPNAME , "asr r" ) ;
            sprintf ( FLAGNAME , "%u" , WC ) ;
            strcat ( OPNAME , FLAGNAME ) ;
            strcat ( OPNAME , " , r" ) ;
            sprintf ( FLAGNAME , "%u" , RA ) ;
            strcat ( OPNAME , FLAGNAME ) ;

        }

        // Operacao 20 : load c a WC = MEM[RA] :
        if ( BITS[10] && !BITS[9] && BITS[8] && !BITS[7] && !BITS[6] )
        {
            strcpy ( OPNAME , "load r" ) ;
            sprintf ( FLAGNAME , "%u" , WC ) ;
            strcat ( OPNAME , FLAGNAME ) ;
            strcat ( OPNAME , " , r" ) ;
            sprintf ( FLAGNAME , "%u" , RA ) ;
            strcat ( OPNAME , FLAGNAME ) ;

        }

        // Operacao 22 : store a b  MEM[RA] = B :
        if ( BITS[10] && !BITS[9] && BITS[8] && BITS[7] && !BITS[6] )
        {
            strcpy ( OPNAME , "store r" ) ;
            sprintf ( FLAGNAME , "%u" , RA ) ;
            strcat ( OPNAME , FLAGNAME ) ;
            strcat ( OPNAME , " , r" ) ;
            sprintf ( FLAGNAME , "%u" , RB ) ;
            strcat ( OPNAME , FLAGNAME ) ;

        }

        // Operacao 24 : add c a b   C = A + B :
        if ( BITS[10] && BITS[9] && !BITS[8] && !BITS[7] && !BITS[6] )
        {
            strcpy ( OPNAME , "add r" ) ;
            sprintf ( FLAGNAME , "%u" , WC ) ;
            strcat ( OPNAME , FLAGNAME ) ;
            strcat ( OPNAME , " , r" ) ;
            sprintf ( FLAGNAME , "%u" , RA ) ;
            strcat ( OPNAME , FLAGNAME ) ;
            strcat ( OPNAME , " , r" ) ;
            sprintf ( FLAGNAME , "%u" , RB ) ;
            strcat ( OPNAME , FLAGNAME ) ;

        }

        // Operacao 25 : sub c a b   C = A - B :
        if ( BITS[10] && BITS[9] && !BITS[8] && !BITS[7] && BITS[6] )
        {
            strcpy ( OPNAME , "sub r" ) ;
            sprintf ( FLAGNAME , "%u" , WC ) ;
            strcat ( OPNAME , FLAGNAME ) ;
            strcat ( OPNAME , " , r" ) ;
            sprintf ( FLAGNAME , "%u" , RA ) ;
            strcat ( OPNAME , FLAGNAME ) ;
            strcat ( OPNAME , " , r" ) ;
            sprintf ( FLAGNAME , "%u" , RB ) ;
            strcat ( OPNAME , FLAGNAME ) ;

        }

        // Operacao 26 : addinca c a b   C = A + B + 1 :
        if ( BITS[10] && BITS[9] && !BITS[8] && BITS[7] && !BITS[6] )
        {
            strcpy ( OPNAME , "addinc r" ) ;
            sprintf ( FLAGNAME , "%u" , WC ) ;
            strcat ( OPNAME , FLAGNAME ) ;
            strcat ( OPNAME , " , r" ) ;
            sprintf ( FLAGNAME , "%u" , RA ) ;
            strcat ( OPNAME , FLAGNAME ) ;
            strcat ( OPNAME , " , r" ) ;
            sprintf ( FLAGNAME , "%u" , RB ) ;
            strcat ( OPNAME , FLAGNAME ) ;

        }

        // Operacao 27 : subdec c a b   C = A - B - 1 :
        if ( BITS[10] && BITS[9] && !BITS[8] && BITS[7] && BITS[6] )
        {
            strcpy ( OPNAME , "subdec r" ) ;
            sprintf ( FLAGNAME , "%u" , WC ) ;
            strcat ( OPNAME , FLAGNAME ) ;
            strcat ( OPNAME , " , r" ) ;
            sprintf ( FLAGNAME , "%u" , RA ) ;
            strcat ( OPNAME , FLAGNAME ) ;
            strcat ( OPNAME , " , r" ) ;
            sprintf ( FLAGNAME , "%u" , RB ) ;
            strcat ( OPNAME , FLAGNAME ) ;

        }

        // Operacao 28 : inca c a  C = A + 1 :
        if ( BITS[10] && BITS[9] && BITS[8] && !BITS[7] && !BITS[6] )
        {
            strcpy ( OPNAME , "inca r" ) ;
            sprintf ( FLAGNAME , "%u" , WC ) ;
            strcat ( OPNAME , FLAGNAME ) ;
            strcat ( OPNAME , " , r" ) ;
            sprintf ( FLAGNAME , "%u" , RA ) ;
            strcat ( OPNAME , FLAGNAME ) ;

        }

        // Operacao 29 : dec c a    C = A - 1 :
        if ( BITS[10] && BITS[9] && BITS[8] && !BITS[7] && BITS[6] )
        {
            strcpy ( OPNAME , "deca r" ) ;
            sprintf ( FLAGNAME , "%u" , WC ) ;
            strcat ( OPNAME , FLAGNAME ) ;
            strcat ( OPNAME , " , r" ) ;
            sprintf ( FLAGNAME , "%u" , RA ) ;
            strcat ( OPNAME , FLAGNAME ) ;

        }

        break ; // end case 1

    case 2 :   // A instrucao e de constante de 11 bits.

        strcpy ( OPNAME , "loadlit r" ) ;
        sprintf ( FLAGNAME , "%u" , WC ) ;
        strcat ( OPNAME , FLAGNAME ) ;
        strcat ( OPNAME , " , " ) ;
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
            strcat ( OPNAME , " , " ) ;
            sprintf ( FLAGNAME , "%4X" , OFFSET ) ;
            strcat ( OPNAME , FLAGNAME ) ;
        }
        else
        {
            strcpy ( OPNAME , "lcl r" ) ;
            sprintf ( FLAGNAME , "%u" , WC ) ;
            strcat ( OPNAME , FLAGNAME ) ;
            strcat ( OPNAME , " , " ) ;
            sprintf ( FLAGNAME , "%4X" , OFFSET ) ;
            strcat ( OPNAME , FLAGNAME ) ;
        }

        break ; // end case 3

    } // end switch (TYPE) ;

} // end controle_set(~) ;
