#include "udpData.h"

void udpData_t::reinit(size_t seriesCount)
{
	_data={};
	_seriesCount = seriesCount;
}

void udpData_t::push_back(double * buffer)
{
	std::vector<double> row(buffer, buffer+_seriesCount);
	_data.push_back(row);

}
void udpData_t::getData(std::vector<double> & vectorX, std::vector< std::vector<double> > & vectorsY)
{
	int nbVals=_data.size();
	vectorX.resize(nbVals);
	for(size_t i=0;i<_seriesCount;i++)
		vectorsY[i].resize(nbVals);
	for(size_t i=0;i<nbVals;i++)
	{
		vectorX[i]=i;
		for(size_t j=0;j<_seriesCount;j++)
			vectorsY[j][i]=_data[i][j];
	}
}
