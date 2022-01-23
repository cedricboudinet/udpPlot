/***************************************************************
 * Name:      udpDataTest.cpp
 * Author:    Cedric Boudinet ()
 * Created:   2022-01-07
 * Copyright: Cedric Boudinet ()
 * License:
 **************************************************************/
#include "CppUTest/CommandLineTestRunner.h"
#define UDP_DATA_TEST_FRIENDS \
	friend class TEST_UDP_DATA_TEST_FirstTest_Test; \
	friend class TEST_UDP_DATA_TEST_Trigger_Test;
#include "../udpData.h"
#include <stdio.h>
#include <iostream>
TEST_GROUP(UDP_DATA_TEST)
{
};

TEST(UDP_DATA_TEST, FirstTest)
{
	//std::cout<<"basic test"<<std::endl;
	udpData_t udpData;
	udpData.reinit(5);
	double buffer[5];
	for(size_t i=0; i<10;i++)
	{
		for(size_t j=0;j<5;j++)
		{
			buffer[j]=i+.1*j;
			//printf("%.3f\n", buffer[j]);
		}
		udpData.push_back(buffer);
	}
	CHECK_EQUAL(10, udpData._data.size());
	CHECK_EQUAL(5, udpData._data.front().size());
	DOUBLES_EQUAL(0, udpData._data.front().at(0), 0.01);
	DOUBLES_EQUAL(.1, udpData._data.front().at(1), 0.01);
	DOUBLES_EQUAL(1.1, udpData._data[1].at(1), 0.01);

	std::vector< std::vector<double> > valsYs;
	std::vector<double> valsX;
	valsYs.resize(5);
	udpData.getData(valsX, valsYs);
	
	//checking buffer size
	udpData.getData(valsX, valsYs);
	CHECK_EQUAL(10, valsX.size());
	udpData.setMaxBufferSize(2);
	udpData.push_back(buffer);
	udpData.getData(valsX, valsYs);
	CHECK_EQUAL(2, valsX.size());
	udpData._lockDeletion=true; //setting up deletion protection
	udpData.push_back(buffer);
	udpData.push_back(buffer);
	CHECK_EQUAL(4, udpData._data.size());
	udpData._lockDeletion=false; //unsetting protection
	udpData.push_back(buffer);
	CHECK_EQUAL(2, udpData._data.size());
}

TEST(UDP_DATA_TEST, Trigger)
{
	//std::cout<<"trigger test"<<std::endl;
	udpData_t udpData;
	udpData.reinit(5);
	double buffer[5];
	//checking trigger rising
	buffer[0]=0; udpData.push_back(buffer);
	CHECK_EQUAL(false, udpData._trigged);
	buffer[0]=-1; udpData.push_back(buffer);
	CHECK_EQUAL(false, udpData._trigged);
	buffer[0]= 1; udpData.push_back(buffer);
	CHECK_EQUAL(true, udpData._trigged);
	udpData._trigged=false;
	buffer[0]=-1; udpData.push_back(buffer);
	CHECK_EQUAL(false, udpData._trigged);
	
	//trigger falling
	udpData._triggerSlope=TRIGGER_SLOPE_FALLING;
	buffer[0]=1; udpData.push_back(buffer);
	CHECK_EQUAL(false, udpData._trigged);
	buffer[0]=-1; udpData.push_back(buffer);
	CHECK_EQUAL(true, udpData._trigged);

	//trigger both
	udpData._trigged=false;
	udpData._triggerSlope=TRIGGER_SLOPE_BOTH;
	buffer[0]=1;udpData.push_back(buffer);
	CHECK_EQUAL(true, udpData._trigged);
	udpData._trigged=false;
	buffer[0]=-1;udpData.push_back(buffer);
	CHECK_EQUAL(true, udpData._trigged);

	//trigger level
	buffer[0]=1;udpData.push_back(buffer);
	udpData._trigged=false;
	udpData._triggerLevel=10;
	buffer[0]=1; udpData.push_back(buffer);
	CHECK_EQUAL(false, udpData._trigged);
	buffer[0]=11;udpData.push_back(buffer);
	CHECK_EQUAL(true, udpData._trigged);
	
	//trigger channel
	udpData.setTrigger(50.0, 1, TRIGGER_SLOPE_RISING);
	udpData._trigged=false;
	buffer[0]=100; udpData.push_back(buffer);
	CHECK_EQUAL(false, udpData._trigged);
	buffer[1]=100; udpData.push_back(buffer);
	CHECK_EQUAL(true, udpData._trigged);

}

int main(int ac, char** av)
{
    return CommandLineTestRunner::RunAllTests(ac, av);
}

