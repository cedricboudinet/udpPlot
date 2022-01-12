/***************************************************************
 * Name:      udpData.h
 * Author:    Cedric Boudinet ()
 * Created:   2022-01-07
 * Copyright: Cedric Boudinet ()
 * License:
 **************************************************************/

#ifndef UDPDATA_H
#define UDPDATA_H
#include <deque>
#include <vector>
#ifndef UDP_DATA_TEST_FRIENDS
#define UDP_DATA_TEST_FRIENDS
#endif
class udpData_t
{
	UDP_DATA_TEST_FRIENDS;
	public:
		void push_back(double *);
		void reinit(size_t seriesCount); 
		void getData(std::vector<double> & vectorX, std::vector< std::vector<double> > & vectorsY);
		size_t maxBufferSize = 10000; //TODO

	private:
		size_t _seriesCount;
		std::deque< std::vector<double> > _data;
		
};

#endif // UDPDATA_H
