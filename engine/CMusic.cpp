/*===============================================================================================
 SIMPLEST.EXE
 Copyright (c), Firelight Technologies Pty, Ltd, 1999,2000.

 This is the simplest way to play a song through FMOD.  It is basically Init, Load, Play!
===============================================================================================*/

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>

#include <fmod.h>

FMUSIC_MODULE *mod = NULL;

void playmusic()
{
    FSOUND_Init(32000, 64, 0);
    mod = FMUSIC_LoadSong("EHA-P4CE.XM");
    FMUSIC_PlaySong(mod);   
}

void stopmusic()
{
	    FMUSIC_FreeSong(mod);
    FSOUND_Close();
}