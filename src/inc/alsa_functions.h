typedef struct{
  int rate;
  int frames;
  int periods;
  
  char* pcm_name;
  snd_pcm_t *pcm_handle;
  snd_pcm_stream_t stream;
  snd_pcm_uframes_t periodsize;
  snd_async_handler_t *pcm_callback;

  float* buffer;

}ALSA_params;

ALSA_params* initALSA(void);
void genChord(ALSA_params* P, float FREQ, float* TYPE, float* AMPL, float* PHASE, float VOL);
void volumeALSA(int inc_volume);
