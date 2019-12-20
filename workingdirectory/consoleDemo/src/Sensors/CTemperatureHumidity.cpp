#include <stdint.h>
#include "CTemperatureHumidity.h"

#define  TEMPRATURE_HUMIDITY_DEVICENAME		"/dev/ttyUSB0"


CTemperatureHumidity::CTemperatureHumidity()
{
	m_MB = NULL;
	m_pDevName = (char*)TEMPRATURE_HUMIDITY_DEVICENAME;
	m_TemperatureValue = 0;
	m_HumidityValue = 0;
	m_TemperatureWarnValue = 0;
	m_TemperatureMaxValue = 0;
	m_TemperatureMinValue = 0;
	
	m_HumidityWarnValue = 0;
	m_HumidityMaxValue = 0;
	m_HumidityMinValue = 0;	
	m_Warning = false;	
	this->m_TemperatureWarning = false;
	this->m_HumidityWarning = false;
	
	this->init_Sensor();
}

CTemperatureHumidity::~CTemperatureHumidity()
{
    if(m_MB == NULL){
		modbus_free(m_MB);
        return ;
	}

    //7-关闭modbus端口
    modbus_close(m_MB);
    //8-释放modbus资源
    modbus_free(m_MB);	
}


bool CTemperatureHumidity::init_Sensor(void)
{
	uint32_t sec = 0;
	uint32_t usec = 1000000;
    //1-打开端口
    if(NULL == (m_MB = modbus_new_rtu(m_pDevName, 9600,'N',8, 1)))
    {
         return false;
    }
    //2-设置从地址
    modbus_set_slave(m_MB, 1);
    //3-建立连接
    modbus_connect(m_MB);
    //4-设置应答延时
    modbus_set_response_timeout(m_MB, sec, usec);

    return true;
}

/* 获取传感器数值
 *
 */
int CTemperatureHumidity::get_SensorValue(void)
{
	return 0;
	
}

/* 获取湿度值
 *
 */
int CTemperatureHumidity::get_TemperatureValue(void)
{
    uint16_t tab_reg[2] = {0};

    //6-读寄存器设置：寄存器地址、数量、数据缓冲
    modbus_read_registers(m_MB, 0, 2, tab_reg);
	
	if(m_TemperatureMinValue >= tab_reg[0] || m_TemperatureMaxValue <= tab_reg[0]){
		m_TemperatureWarning = true;
	}else{
		m_TemperatureValue = tab_reg[0];
		m_TemperatureWarning = false;
	}	
	return m_TemperatureValue;
}

/* 获取温度值
 *
 */
int CTemperatureHumidity::get_HumidityValue(void)
{
    uint16_t tab_reg[2] = {0};

    //6-读寄存器设置：寄存器地址、数量、数据缓冲
    modbus_read_registers(m_MB, 0, 2, tab_reg);
	
	if(m_HumidityMinValue >= tab_reg[1] || m_HumidityMaxValue <= tab_reg[1]){
		m_HumidityWarning = true;
	}else{
		m_HumidityValue = tab_reg[1];
		m_HumidityWarning = false;
	}	
	
	return m_HumidityValue;
}

/* 检查温度预警事件
 *
 */
bool CTemperatureHumidity::check_TemperatureBeWarning(void)
{
	return this->m_TemperatureWarning;
}

/* 检查湿度预警事件
 *
 */
bool CTemperatureHumidity::check_HumidityBeWarning(void)
{
	return this->m_HumidityWarning;
}


/* 检查预警事件
 *
 */
bool CTemperatureHumidity::check_SensorBeWarning(void)
{
	return this->m_Warning;
}

/* 设置预警值
 *
 */
void CTemperatureHumidity::set_TemperatureWarnValue(int warnvalue)
{
    //如果设置预警值等于预警值则不设置
    if (warnvalue == this->m_TemperatureWarnValue) {
        return;
    }

    this->m_TemperatureWarnValue = warnvalue;	
}

/* 设置预警值
 *
 */
void CTemperatureHumidity::set_HumidityWarnValue(int warnvalue)
{
    //如果设置预警值等于预警值则不设置
    if (warnvalue == this->m_HumidityWarnValue) {
        return;
    }

    this->m_HumidityWarnValue = warnvalue;	
}

/* 设置温度最范围值
 *
 */
void CTemperatureHumidity::set_TemperatureRangeValue(int minvalue,int maxvalue)
{
    if (maxvalue <= minvalue) {
        return;
    }

	this->m_TemperatureMinValue = minvalue;	
    this->m_TemperatureMaxValue = maxvalue;	
}

/* 设置湿度范围值
 *
 */
void CTemperatureHumidity::set_HumidityRangeValue(int minvalue,int maxvalue)
{
    if (maxvalue <= minvalue) {
        return;
    }

	this->m_HumidityMinValue = minvalue;	
    this->m_HumidityMaxValue = maxvalue;			
}



















