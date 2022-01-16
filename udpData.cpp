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
	if(_lockDeletion==false)
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
