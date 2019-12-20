#ifndef _SENSOR_CO2_H
#define _SENSOR_CO2_H

#include "CSensor.h"

class CCO2 : public CSensor
{
public:
	CCO2();
	~CCO2();
	
	bool init_Sensor(void);
	int  get_SensorValue(void);

    bool check_SensorBeWarning(void);
    void set_WarnValue(int warnvalue);
    void set_RangeValue(int minvalue, int maxvalue);
private:
	modbus_t *m_MB;
	char *m_pDevName;
	int m_CO2Value;
};



#endif
