#pragma once

#include <stdio.h>

enum { ST_ON, ST_OFF, ST_ON_SYNC, ST_SEL };

class Unit
{
public:
	Unit(int _id);

	int getId() { return m_Id; }

	virtual void doON(){ m_Status = ST_ON; }
	virtual void doOFF() { m_Status = ST_OFF; }

	virtual void doSELECT() { m_oldStatus = m_Status; m_Status = ST_SEL; }
	virtual void doOTM() { m_Status = m_oldStatus; }

	virtual bool ON() { return (m_Status == ST_ON) ? true : false; }
	virtual bool OFF() { return (m_Status == ST_OFF) ? true : false; }
	virtual bool SEL() { return (m_Status == ST_SEL) ? true : false; }

	virtual void CLK() 
	{ 
		//printf("Unit[%d]::CLK()\n", m_Id); fflush(stdout); 
	}
	
private:
	int m_Status;
	int m_oldStatus;
	int m_Id;
};
