#ifndef _SENSOR_OPT_H
#define _SENSOR_OPT_H

class CTemperatureHumidity;
class CSensorNoise;
class CCO2;

class CSensorOpt
{
public:
	CSensorOpt();
	~CSensorOpt();
	
	int get_CO2Value(void);
	int get_NoiseValue(void);
	int get_HumidityValue(void);
	int get_TemperatureValue(void);
private:
    CCO2 *m_pCCO2;
	CSensorNoise *m_pSensorNoise;
	CTemperatureHumidity *m_pTemperatureHumidity;
};

#endif
