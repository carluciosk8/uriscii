/***************************************************************************
                                 memory.cpp
                             -------------------
    begin                : Fri Jun 23 2000
    copyright            : (C) 2000 by Carlucio Santos Cordeiro

    DCC - UFMG - Computer Organization & Design

 ***************************************************************************/

///   Header files   ////////////////////////////////////////
///                  ////////////////////////////////////////

#include "memory.h"


///   FUNCTION    : memory_t::memory_t
///   EXPLANATION : Construtora da classe (inicializa a memoria com 0s.
memory_t::memory_t()
{
    word ZERO = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0} ;
    int CONT ;

    for ( CONT=0 ; CONT<MAX_MEM ; CONT++ )
    {
        for ( int J=0 ; J<WORDSIZE ; J++ )
        {
            MEM[CONT][J] = ZERO[J] ;
        }
    }
}


///   FUNCTION    : memory_t::EX
///   EXPLANATION : Implementa a memoria do processador.
void memory_t::EX ( word ADDRESS , word &DATA_OUT , word DATA_IN , SIGNAL MEM_READ , SIGNAL MEM_WRITE )
{
    int VAL ;
    int CONT , P2 ;

    P2 = 1 ;
    VAL = 0 ;
    for ( CONT = 0 ; CONT < WORDSIZE ; CONT++)
    {
        VAL = VAL + P2*ADDRESS[CONT] ;
        P2 = P2 << 1 ;
    }

    for ( CONT = 0 ; CONT < WORDSIZE ; CONT++) DATA_OUT[CONT] = MEM[VAL][CONT] ;
    for ( CONT = 0 ; CONT < WORDSIZE ; CONT++) MUX2 ( MEM[VAL][CONT] , MEM[VAL][CONT] , DATA_IN[CONT] , MEM_WRITE ) ;
}


///   FUNCTION    : memory_t::LOAD
///   EXPLANATION : Carrega o codigo de maquina do arquivo para
///                 a memoria e faz PC apontar para o inicio do prog.
void memory_t::LOAD ( char *ARQ_ENTRADA , word_reg_t &PC )
{
    word  ADR , DAT , TRASH , ZERO = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0} ;
    char  WORD[7] , W[6] ;
    short DATA ;
    int   ADDRESS=0 ;
    FILE *ARQ ;

    if ( ( ARQ = fopen ( ARQ_ENTRADA , "rt" ) ) == NULL  )
    {
        fprintf(stderr,"\nNao foi possivel abrir o arquivo %15s .\n" , ARQ_ENTRADA ) ;
        exit(0);
    }

    fscanf ( ARQ , "%s" , WORD ) ;
    if ( (strcmp( WORD , "address" ) == 0) || (strcmp( WORD , "ADDRESS" ) == 0) )
    {
        fscanf ( ARQ , "%x" , &ADDRESS ) ;
        put_word_dec ( ADR , ADDRESS ) ;
        PC.EX ( TRASH , ADR , 1 ) ;
    }
    else PC.EX ( TRASH , ZERO , 1 ) ;

    while ( !feof ( ARQ ) )
    {
        fscanf ( ARQ , "%s" , WORD ) ;
        if ( (strcmp( WORD , "address" ) == 0) || (strcmp( WORD , "ADDRESS" ) == 0) )
        {
            fscanf ( ARQ , "%x" , (int*) &ADDRESS ) ;
        }
        else
        {
            strcpy ( W , "0x" );
            strcat ( W , WORD );
            DATA = strtol ( W , NULL , 16 );
            put_word_dec ( DAT , DATA );
            for ( int CONT=0 ; CONT<WORDSIZE ; CONT++ ) MEM[ADDRESS][CONT] = DAT[CONT];
            ADDRESS++ ;
        }
    }
    fclose ( ARQ ) ;
}


void memory_t::DUMP ( int START , int LENGHT , bool PAUSE )
{
    int CONT ;
    word DAT , ADR ;

    for ( CONT=START ; CONT<START+LENGHT ; CONT++ )
    {
        if ( PAUSE && ((CONT-START)%18==0) )
        {
            printf ( "Mais." ) ;
            getchar() ;
            system ( "clear" ) ;
            printf ( "\nADDRESS - DATA\n" ) ;
        }
        for ( int C=0 ; C<WORDSIZE ; C++ ) DAT[C] = MEM[CONT][C] ;
        put_word_dec ( ADR , CONT ) ;
        print_word_hex ( ADR ) ;
        printf ( "    - " ) ;
        print_word_hex ( DAT ) ;
        printf ( "\n" ) ;
    }
}
