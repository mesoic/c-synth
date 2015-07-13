#include <alsa/asoundlib.h>
#include <unistd.h>
#include <math.h>
#include "alsa_functions.h"

#define PERIOD_SIZE 1024
#define BUFFER_LEN 2048
#define RATE 44100
////////////////////////////////////
//        Initialize ALSA         //
////////////////////////////////////
ALSA_params* initALSA(void){

  ALSA_params* P = malloc(sizeof(ALSA_params));
  P->rate = RATE;
  P->stream = SND_PCM_STREAM_PLAYBACK;
  P->pcm_name = strdup("plughw:0,0");
  P->periodsize = PERIOD_SIZE;
  P->periods = 2;
  P->frames = (P->periodsize) >> 1; 
  P->buffer = (float*)malloc(BUFFER_LEN*sizeof(float));

  snd_pcm_hw_params_t *hwparams;
  // Try to initialize soundcard
  snd_pcm_hw_params_alloca(&hwparams);
  if (snd_pcm_open(&P->pcm_handle, P->pcm_name, P->stream, 0) < 0) {
    fprintf(stderr, "Error opening PCM device %s\n", P->pcm_name);
  }

  int exact_rate = P->rate;
  // All of the following functions "fill up" hwparams
  snd_pcm_hw_params_any(P->pcm_handle, hwparams);
  snd_pcm_hw_params_set_access(P->pcm_handle, hwparams, SND_PCM_ACCESS_RW_INTERLEAVED) ;
  snd_pcm_hw_params_set_format(P->pcm_handle, hwparams, SND_PCM_FORMAT_FLOAT);
  snd_pcm_hw_params_set_rate_near(P->pcm_handle, hwparams, &exact_rate, 0);
  snd_pcm_hw_params_set_channels(P->pcm_handle, hwparams, 1);
  snd_pcm_hw_params_set_periods(P->pcm_handle, hwparams, P->periods, 0);
  snd_pcm_hw_params_set_buffer_size(P->pcm_handle, hwparams, BUFFER_LEN); 
  
  // Finally send the final hwparams to the sound card
  snd_pcm_hw_params(P->pcm_handle, hwparams);
  return P;
}

void genChord(ALSA_params* P, float FREQ, float* TYPE, float* AMPL, float* PHASE, float VOL){
  int i,j;
  snd_pcm_prepare(P->pcm_handle);
  for (j = 0; j < BUFFER_LEN; j++){
    P->buffer[j] = 0;
    for (i=0; i<4;i++){P->buffer[j]+= VOL*(AMPL[i])
	*( sin((2*M_PI*TYPE[i]*FREQ*(float)j/(float)RATE)+PHASE[i]));}
  }
  snd_pcm_prepare(P->pcm_handle);
  snd_pcm_writei(P->pcm_handle, P->buffer, 2*PERIOD_SIZE);
  for (j=0; j<4; j++){
    PHASE[j] += 2*M_PI*TYPE[j]*FREQ*BUFFER_LEN/RATE;
    if (PHASE[j] > 2*M_PI){PHASE[j]-= 2*M_PI;}
  }
}

void volumeALSA(int inc_volume)
{
  long min, max, value;
    snd_mixer_t *handle;
    snd_mixer_selem_id_t *sid;
    const char *card = "default";
    const char *selem_name = "Master";

    snd_mixer_open(&handle, 0);
    snd_mixer_attach(handle, card);
    snd_mixer_selem_register(handle, NULL, NULL);
    snd_mixer_load(handle);

    snd_mixer_selem_id_alloca(&sid);
    snd_mixer_selem_id_set_index(sid, 0);
    snd_mixer_selem_id_set_name(sid, selem_name);
    snd_mixer_elem_t* elem = snd_mixer_find_selem(handle, sid);

    snd_mixer_selem_get_playback_volume_range(elem, &min, &max);
    snd_mixer_selem_get_playback_volume (elem, 0, &value);

    if(inc_volume == 1){
      snd_mixer_selem_set_playback_volume_all(elem, value + 1.0);
    }
    if(inc_volume == 0){
      snd_mixer_selem_set_playback_volume_all(elem, value - 1.0);
    }
    snd_mixer_close(handle);
}
