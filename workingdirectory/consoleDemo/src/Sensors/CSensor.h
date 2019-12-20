#ifndef _SENSOR_H
#define _SENSOR_H

#include <modbus.h>

class CSensor
{
public:
	CSensor(){};
	~CSensor(){};
public:
	int m_WarnValue;
	int m_MaxValue;
	int m_MinValue;
	bool m_Warning;
	
	virtual int get_SensorValue(void) = 0;
	virtual bool check_SensorBeWarning(void) = 0;
	virtual void set_WarnValue(int warnvalue) = 0;
	virtual void set_RangeValue(int minvalue, int maxvalue) = 0;
	
	void set_DevFile(char *devname);
	void set_Baudrate(int baudrate);
	void set_Datawidth(int datawidth);
	void set_Stopbits(int stopbits);
	void set_Parity(int parity);
};

#endif
