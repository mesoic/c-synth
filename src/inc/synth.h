float F = 200.0;
float t = 1.0;    
float PHASE[4];
float SILENCE[4] = {0.0,0.0,0.0,0.0};
float A_SILENCE[4] = {1.0,0.8,1.0,0.3};

// Chord Vectors
float MAJOR[4] = {1.0,1.25,1.5,2.0};
float MINOR[4] = {1.0,1.20,1.5,0.0};
float NINTH[4] = {1.0,1.20,1.5,2.0};
float MAJ_7[4] = {1.0,1.25,1.5,1.875};
float MIN_7[4] = {1.0,1.20,1.5,1.778};
float MAJ_M[4] = {1.0,1.25,1.5,0.0};
float MIN_M[4] = {1.0,1.20,1.5,2.0};  
float MN7b5[4] = {1.0,1.20,1.422,1.778};

// Mixing Vectors
float A_MAJOR[4] = {1.0,0.8,1.0,0.3};
float A_MINOR[4] = {1.0,1.0,1.0,0.0};
float A_NINTH[4] = {1.0,0.8,1.0,0.3};
float A_MAJ_7[4] = {1.0,0.8,1.0,0.8};
float A_MIN_7[4] = {1.0,0.8,1.0,0.8};
float A_MAJ_M[4] = {1.0,0.8,1.0,0.0};
float A_MIN_M[4] = {1.0,1.0,1.0,0.8};
float A_MN7b5[4] = {1.0,0.8,0.8,0.7};

// Ratio Vector for Chords
float RATIO_MA[9] = {1.0, 10.0/9.0, 5.0/4.0, 4.0/3.0, 3.0/2.0, 27.0/16.0, 15.0/8.0, 2.0, 20.0/9.0};
float RATIO_MI[9] = {1.0, 10.0/9.0, 6.0/5.0, 4.0/3.0, 3.0/2.0, 8.00/5.00, 9.00/5.0, 2.0, 20.0/9.0};
float VOL = 0.02;
