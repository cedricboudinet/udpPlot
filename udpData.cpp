#include "udpData.h"
#include <iostream>

void udpData_t::reinit(size_t seriesCount)
{
	_data={};
	_seriesCount = seriesCount;
}

void udpData_t::push_back(double * buffer)
{
	std::vector<double> row(buffer, buffer+_seriesCount);
	_data.push_back(row);
	size_t size=_data.size();
	if((size>1) && (!_trigged))
	{
		double before = (*(_data.end()-2))[_triggerChannel];
		double after = buffer[_triggerChannel];
		trigger_slope_t signal_slope= TRIGGER_SLOPE_NONE;
		if((before<_triggerLevel) && (after>_triggerLevel))
			signal_slope=TRIGGER_SLOPE_RISING;
		if((before>_triggerLevel) && (after<_triggerLevel))
			signal_slope=TRIGGER_SLOPE_FALLING;
		
		if(signal_slope & _triggerSlope)
		{
			_triggerIndex=_data.size();
			_trigged=true; 
		}
		//printf("%.3f %.3f %.3f %d\n", before, after, _triggerLevel, signal_slope);
	}
	if((_lockDeletion==false) && (_trigged==false)) //also check if trigger is false
		if(size > _maxBufferSize)
		{
			_data.erase(_data.begin(), _data.begin()+size-_maxBufferSize);
		}
	//while(_data.size() > _maxBufferSize) _data.pop_front();
}
void udpData_t::getData(std::vector<double> & vectorX, std::vector< std::vector<double> > & vectorsY)
{
	int nbVals=_data.size();
	vectorX.resize(nbVals);
	for(size_t i=0;i<_seriesCount;i++)
		vectorsY[i].resize(nbVals);
	_lockDeletion=true;
	for(size_t i=0;i<nbVals;i++)
	{
		vectorX[i]=i;
		for(size_t j=0;j<_seriesCount;j++)
			vectorsY[j][i]=_data[i][j];
	}
	_lockDeletion=false;
}
void udpData_t::setMaxBufferSize(size_t size)
{
	_maxBufferSize = size;
}
size_t udpData_t::getMaxBufferSize()
{
	return _maxBufferSize;
}

void udpData_t::setTrigger(double level, int channel, trigger_slope_t trigger_slope)
{
	_triggerLevel = level;
	_triggerChannel = channel;
	_triggerSlope =trigger_slope;
}

void udpData_t::getTrigger(double * level, int * channel, trigger_slope_t * trigger_slope)
{
	*level = _triggerLevel;
	*channel = _triggerChannel;
	*trigger_slope = _triggerSlope;
}
