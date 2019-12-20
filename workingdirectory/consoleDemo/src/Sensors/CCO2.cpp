#include "CCO2.h"


#define  NOISE_HUMIDITY_DEVICENAME		"/dev/ttyUSB2"

CCO2::CCO2()
{
	m_MB = NULL;
	m_pDevName = (char*)NOISE_HUMIDITY_DEVICENAME;
	m_CO2Value = 0;
	
	m_WarnValue = 0;
	m_MaxValue = 0;
	m_MinValue = 0;
	m_Warning = 0;
	
	this->init_Sensor();
}

CCO2::~CCO2()
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

/* 初始化传感器接口
 *
 */
bool CCO2::init_Sensor(void)
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
int CCO2::get_SensorValue(void)
{
	uint16_t value = 0; 
    //6-读寄存器设置：寄存器地址、数量、数据缓冲
    modbus_read_registers(m_MB, 0, 1, &value);
	
	if(m_MinValue >= value || m_MaxValue <= value){
		m_Warning = true;
	}else{
		this->m_CO2Value = value;
		m_Warning = false;
	}	
	return this->m_CO2Value;
	
}

/* 获取传感器数值
 *
 */
bool CCO2::check_SensorBeWarning(void)
{
	return m_Warning;
}

/* 获取传感器数值
 *
 */
void CCO2::set_WarnValue(int warnvalue)
{
    if (warnvalue == m_WarnValue) {
        return;
    }

    m_WarnValue = warnvalue;		
}

/* 获取传感器数值
 *
 */
void CCO2::set_RangeValue(int minvalue, int maxvalue)
{
    if (maxvalue <= minvalue) {
        return;
    }

	m_MinValue = minvalue;	
    m_MaxValue = maxvalue;	
}





