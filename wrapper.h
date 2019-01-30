void StartADDA(int, int, int);
void StopADDA(void);
void ReadADC(void);
long int GetChannelRaw(int);
double GetChannelVolts(int);
void GetAllChannelsVolts(double *);
void GetAllChannelsRaw(long int *);
void WriteVolts(int, float, float);
