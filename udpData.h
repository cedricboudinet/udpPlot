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
typedef enum {
	TRIGGER_SLOPE_NONE=0,
	TRIGGER_SLOPE_RISING=1,
	TRIGGER_SLOPE_FALLING=2,
	TRIGGER_SLOPE_BOTH=3
}trigger_slope_t ;
class udpData_t
{
	UDP_DATA_TEST_FRIENDS
	public:
		void push_back(double *);
		void reinit(size_t seriesCount); 
		void getData(std::vector<double> & vectorX, std::vector< std::vector<double> > & vectorsY);
		void setMaxBufferSize(size_t);
		size_t getMaxBufferSize();
		void setTrigger(double level, int channel, trigger_slope_t trigger_slope);

	private:
		size_t _seriesCount;
		std::deque< std::vector<double> > _data;
		size_t _maxBufferSize = 10000; //TODO
		bool _lockDeletion=false;
		bool _trigged=false;
		double _triggerLevel=0.0;
		size_t _triggerChannel=0;
		trigger_slope_t _triggerSlope = TRIGGER_SLOPE_RISING;
};

#endif // UDPDATA_H
