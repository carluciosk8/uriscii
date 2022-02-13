/***************************************************************************
                          main.cpp  -  description
                             -------------------
    begin                : Wed May 10 2000
    copyright            : (C) 2000 by Carlucio Santos Cordeiro

    DCC - UFMG - Computer Organization & Design

 ***************************************************************************/

#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <iostream>

#include "urisc.h"


int main ( int ARGC , char **ARGV )
{
    int OPT ;
    char *ARQ_ENTRADA ;
    bool SCREEN , PAUSE , DUMP ;
    int POS_INICIAL , NUM_PALAVRAS ;

    urisc URISC ;   // Isso aqui que eh o processador.


    ///////////////////////////////////////////////////////////////////////////////////////////////////////////
    ////   Leitura dos argumentos da linha de comando /////////////////////////////////////////////////////////

    SCREEN = false ;
    PAUSE = false ;
    DUMP = false ;

    if ( ARGC < 2 || ARGC > 8 )
    {
        std::cout << "\nUso:  urisc -a <arq_entrada> [-d <pos_inicial> <num_palavras>] [-s] [-p]" ;
        std::cout << "\n\n    <arq_entrada> : Arquivo com o codigo a ser executado." ;
        std::cout << "\n\n  -d <pos_inicial> <num_palavras> : Dump de memoria a partir de <pos_inicial> e" ;
        std::cout << "\n                                   <num_palavras> o numero de palavras do dump." ;
        std::cout << "\n\n    -s : Mostra o status do processador." ;
        std::cout << "\n\n    -p : Pausa entre a execucao das instrucoes.\n\n" ;
        exit (0) ;
    }
    else
    {
        for ( OPT=1 ; OPT<ARGC ; OPT++ )
        {
            if ( !strcmp ( ARGV[OPT] , "-d" ) && OPT+2 < ARGC )
            {
                if ( ( ARGV[OPT+1][0] >= '0' && ARGV[OPT+1][0] <= '9' )
                  || ( ARGV[OPT+2][0] >= '0' && ARGV[OPT+2][0] <= '9' ) )
                {
                    POS_INICIAL = atoi (ARGV[OPT+1]) ;
                    NUM_PALAVRAS = atoi (ARGV[OPT+2]) ;
                    DUMP = true ;
                }
                else
                {
                    std::cout << "\nErro: Argumento invalido\n" ;
                    exit (0) ;
                }
            }
            if ( !strcmp ( ARGV[OPT] , "-s" ) ) SCREEN = true ;
            if ( !strcmp ( ARGV[OPT] , "-p" ) ) PAUSE = true ;
            if ( !strcmp ( ARGV[OPT] , "-a" ) ) ARQ_ENTRADA = ARGV[OPT+1] ;
        }
    }


    ///////////////////////////////////////////////////////////////////////////////////////////////////////////
    /////    Carrega o programa      //////////////////////////////////////////////////////////////////////////

    URISC.LOAD ( ARQ_ENTRADA ) ;


    ///////////////////////////////////////////////////////////////////////////////////////////////////////////
    /////    Executa os ciclos      ///////////////////////////////////////////////////////////////////////////

    do
    {
        URISC.IF() ;
        URISC.ID() ;
        URISC.EX() ;
        URISC.MEM() ;
        URISC.WB() ;

        if ( SCREEN ) URISC.STATUS ( PAUSE ) ;
    } while ( !URISC.HLT() ) ;

    if ( DUMP ) URISC.DUMP ( POS_INICIAL , NUM_PALAVRAS , PAUSE ) ;

    return 0 ;
}
