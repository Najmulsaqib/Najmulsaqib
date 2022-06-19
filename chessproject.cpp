#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

#include "chess.h"
#include "uivga.h"

unsigned _stklen = 0x6000;

text_info StartupTextInfo;

void Advertise()
{
    printf ( "\n"
             "Chenard / MS-DOS VGA version (22 June 1997)\n"
             "A chess program by Don Cross <dcross@intersrv.com>\n"
             "http://www.intersrv.com/~dcross\n\n" );
}


void ExitCode()
{
    textmode ( StartupTextInfo.currmode );
    Advertise();
}


#pragma argsused
int main ( int argc, char *argv[] )
{
    gettextinfo ( &StartupTextInfo );
    atexit ( ExitCode );

    extern bool sound_flag;
    sound_flag = false;

    extern int Learn_Output;
    Learn_Output = 0;
    Advertise();

    ChessBoard       theBoard;
    ChessUI_dos_vga  theUserInterface;
    ChessGame theGame ( theBoard, theUserInterface );
    theGame.Play();

    Advertise();

    return 0;
}


void ChessFatal ( const char *message )
{
    fprintf ( stderr, "Chess fatal:\n%s\n", message );

    FILE *errorLog = fopen ( "doscga.err", "wt" );
    if ( errorLog )
    {
        fprintf ( errorLog, "Chess fatal:\n%s\n", message );
        fclose ( errorLog );
    }

    exit(1);
}