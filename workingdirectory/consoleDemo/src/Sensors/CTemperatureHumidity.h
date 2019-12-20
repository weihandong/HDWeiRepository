#ifndef _TEMPRATURE_HUMIDITY_H
#define _TEMPRATURE_HUMIDITY_H

#include "CSensor.h"

class CTemperatureHumidity : public CSensor
{
public:
	CTemperatureHumidity();
	~CTemperatureHumidity();
	
	bool init_Sensor(void);
	int get_SensorValue(void);
	
	bool check_SensorBeWarning(void);
    void set_WarnValue(int warnvalue){}
    void set_RangeValue(int minvalue, int maxvalue){}


    void set_TemperatureWarnValue(int warnvalue);
	void set_HumidityWarnValue(int warnvalue);
	void set_TemperatureRangeValue(int minvalue,int maxvalue);
	void set_HumidityRangeValue(int minvalue,int maxvalue);
	
	bool check_TemperatureBeWarning(void);
	bool check_HumidityBeWarning(void);
	int get_TemperatureValue(void);
	int get_HumidityValue(void);
private:
	modbus_t *m_MB;
	char *m_pDevName;
	int m_TemperatureValue;
	int m_HumidityValue;

	int m_TemperatureWarnValue;
	int m_HumidityWarnValue;
	int m_TemperatureMaxValue;
	int m_HumidityMaxValue;
	int m_TemperatureMinValue;
	int m_HumidityMinValue;
	bool m_TemperatureWarning;
	bool m_HumidityWarning;	
};

#endif
