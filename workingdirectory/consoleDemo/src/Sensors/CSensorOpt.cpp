#include "CTemperatureHumidity.h"
#include "CSensorNoise.h"
#include "CCO2.h"
#include <stddef.h>
#include "CSensorOpt.h"

CSensorOpt::CSensorOpt()
{
    m_pCCO2 = new CCO2;
	m_pSensorNoise = new CSensorNoise;
	m_pTemperatureHumidity = new CTemperatureHumidity;
/*    
    if(m_pCCO2 != NULL)
        m_pCCO2->init_Sensor();

	if(m_pSensorNoise != NULL)
		m_pSensorNoise->init_Sensor();
	
	if(m_pTemperatureHumidity != NULL)
		m_pTemperatureHumidity->init_Sensor();
*/
}

CSensorOpt::~CSensorOpt()
{
    if(m_pCCO2 != NULL)
    {
        delete m_pCCO2;
        m_pCCO2 = NULL;
    }
    
	if(m_pSensorNoise != NULL)
	{
		delete m_pSensorNoise;
		m_pSensorNoise = NULL;
	}
	
	if(m_pTemperatureHumidity != NULL)
	{
		delete m_pTemperatureHumidity;
		m_pTemperatureHumidity =NULL;
	}
}

/* 获取噪声数值
 *
 */
int CSensorOpt::get_NoiseValue(void)
{
	return m_pSensorNoise->get_SensorValue();
}

/* 获取温度数值
 *
 */
int CSensorOpt::get_HumidityValue(void)
{
	return m_pTemperatureHumidity->get_TemperatureValue();
}

/* 获取湿度数值
 *
 */
int CSensorOpt::get_TemperatureValue(void)
{
	return m_pTemperatureHumidity->get_HumidityValue();
}


/* 获取湿度数值
 *
 */
int CSensorOpt::get_CO2Value(void)
{
	return m_pCCO2->get_SensorValue();
}
