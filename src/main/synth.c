#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <sys/time.h>
#include <pthread.h>
#include <signal.h>
#include <alsa/asoundlib.h>

#include "alsa_functions.h"
#include "nonblocking.h"
#include "X11_helpers.h"
#include "synth.h"


void sig_handler(int signo){
  if (signo == SIGINT){
    system("xset r rate 300 23");
    nonblock(0);
    exit(0);
  }
}

void run_synth(ALSA_params *P){

  nonblock(1);
  int S = 0;
  char c = '\0';
  float key = 1.0; 

  while(1){
    usleep(1);
    if ( kbhit() ){
      c=fgetc(stdin);

      // Major CHORDS
      if( c == 'q'){break;}
      while( c == 'a'){c = fgetc(stdin); genChord(P, key*F*RATIO_MA[0], MAJOR, A_MAJOR, PHASE,VOL);}
      while( c == 's'){c = fgetc(stdin); genChord(P, key*F*RATIO_MA[1], MINOR, A_MINOR, PHASE,VOL);}
      while( c == 'd'){c = fgetc(stdin); genChord(P, key*F*RATIO_MA[2], MINOR, A_MINOR, PHASE,VOL);}
      while( c == 'f'){c = fgetc(stdin); genChord(P, key*F*RATIO_MA[3], MAJOR, A_MAJOR, PHASE,VOL);}
      while( c == 'g'){c = fgetc(stdin); genChord(P, key*F*RATIO_MA[4], MAJOR, A_MAJOR, PHASE,VOL);}
      while( c == 'h'){c = fgetc(stdin); genChord(P, key*F*RATIO_MA[5], MINOR, A_MINOR, PHASE,VOL);}
      while( c == 'j'){c = fgetc(stdin); genChord(P, key*F*RATIO_MA[6], MINOR, A_MAJOR, PHASE,VOL);}
      while( c == 'k'){c = fgetc(stdin); genChord(P, key*F*RATIO_MA[7], MAJOR, A_MAJOR, PHASE,VOL);}
      while( c == 'l'){c = fgetc(stdin); genChord(P, key*F*RATIO_MA[8], NINTH, A_NINTH, PHASE,VOL);}
      // 7th chords
      while( c == 'w'){c = fgetc(stdin); S=1;genChord(P, key*F*RATIO_MA[0], MAJ_7, A_MAJ_7, PHASE,VOL);}
      while( c == 'e'){c = fgetc(stdin); S=1;genChord(P, key*F*RATIO_MA[1], MIN_7, A_MIN_7, PHASE,VOL);}
      while( c == 'r'){c = fgetc(stdin); S=1;genChord(P, key*F*RATIO_MA[2], MIN_7, A_MIN_7, PHASE,VOL);}
      while( c == 't'){c = fgetc(stdin); S=1;genChord(P, key*F*RATIO_MA[3], MAJ_7, A_MAJ_7, PHASE,VOL);}
      while( c == 'y'){c = fgetc(stdin); S=1;genChord(P, key*F*RATIO_MA[4], MAJ_7, A_MAJ_7, PHASE,VOL);}
      while( c == 'u'){c = fgetc(stdin); S=1;genChord(P, key*F*RATIO_MA[5], MIN_7, A_MIN_7, PHASE,VOL);}
      while( c == 'i'){c = fgetc(stdin); S=1;genChord(P, key*F*RATIO_MA[6], MIN_7, A_MIN_7, PHASE,VOL);}
      while( c == 'o'){c = fgetc(stdin); S=1;genChord(P, key*F*RATIO_MA[7], MAJ_7, A_MAJ_7, PHASE,VOL);}
      // Minor CHORDS
      while( c == 'z'){c = fgetc(stdin); S=1;genChord(P, 0.8437*key*F*RATIO_MI[0], MIN_M, A_MIN_M, PHASE,VOL);}
      while( c == 'x'){c = fgetc(stdin); S=1;genChord(P, 0.8437*key*F*RATIO_MI[1], MN7b5, A_MN7b5, PHASE,VOL);}
      while( c == 'c'){c = fgetc(stdin); S=1;genChord(P, 0.8437*key*F*RATIO_MI[2], MAJ_M, A_MAJ_M, PHASE,VOL);}
      while( c == 'v'){c = fgetc(stdin); S=1;genChord(P, 0.8437*key*F*RATIO_MI[3], MIN_M, A_MIN_M, PHASE,VOL);}
      while( c == 'b'){c = fgetc(stdin); S=1;genChord(P, 0.8437*key*F*RATIO_MI[4], MIN_M, A_MIN_M, PHASE,VOL);}
      while( c == 'n'){c = fgetc(stdin); S=1;genChord(P, 0.8437*key*F*RATIO_MI[5], MAJ_M, A_MAJ_M, PHASE,VOL);}
      while( c == 'm'){c = fgetc(stdin); S=1;genChord(P, 0.8437*key*F*RATIO_MI[6], MAJ_M, A_MAJ_M, PHASE,VOL);}
      while( c == ','){c = fgetc(stdin); S=1;genChord(P, 0.8437*key*F*RATIO_MI[7], MIN_M, A_MIN_M, PHASE,VOL);}
      while( c == '.'){c = fgetc(stdin); S=1;genChord(P, 0.8437*key*F*RATIO_MI[8], MN7b5, A_MN7b5, PHASE,VOL);}
    }
  }
  nonblock(0);
}
          
int main(void){
  signal(SIGINT, sig_handler) == SIG_ERR;

  // Take care of keyboard rate issues
  Display *dpy = XOpenDisplay(":0.0");
  kbrate* kb_bak = xkbset_repeatrate(dpy, 22.5, 1000/22.5);

  printf("---------------------------------------\n");
  printf("   ______    _____             __  __  \n");
  printf("  / ____/   / ___/__  ______  / /_/ /_ \n");
  printf(" / /  ______\\__ \\/ / / / __ \\/ __/ __ \\ \n");
  printf("/ /__/_____/__/ / /_/ / / / / /_/ / / / \n");
  printf("\\____/    /____/\\__, /_/ /_/\\__/_/ /_/ \n");
  printf("               /____/                  \n");
  printf("---------------------------------------\n");
  printf("Major Key 7th Chords: (first row of keyboard) \n");
  printf("Major Key Chords: (second row of keyboard) \n");
  printf("Minor Key Chords: (third row of keyboard) \n");
  printf("---------------------------------------\n");
  printf("Exit: q \n");


  ALSA_params* P = initALSA();

  run_synth(P);
  xkbset_repeatrate(dpy, kb_bak->delay,kb_bak->interval);

  snd_pcm_drain(P->pcm_handle);
  snd_pcm_close(P->pcm_handle);
  return 0;
}


