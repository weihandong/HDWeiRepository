#ifndef _SENSOR_NOISE_H
#define _SENSOR_NOISE_H

#include "CSensor.h"

class CSensorNoise : public CSensor
{
public:
	CSensorNoise();
	~CSensorNoise();
	
	bool init_Sensor(void);
	int  get_SensorValue(void);

    bool check_SensorBeWarning(void);
    void set_WarnValue(int warnvalue);
    void set_RangeValue(int minvalue, int maxvalue);
private:
	modbus_t *m_MB;
	char *m_pDevName;
	int m_NoiseValue;
};



#endif
