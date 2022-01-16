/***************************************************************
 * Name:      udpDataTest.cpp
 * Author:    Cedric Boudinet ()
 * Created:   2022-01-07
 * Copyright: Cedric Boudinet ()
 * License:
 **************************************************************/
#include "CppUTest/CommandLineTestRunner.h"
#define UDP_DATA_TEST_FRIENDS friend class TEST_UDP_DATA_TEST_FirstTest_Test
#include "../udpData.h"
#include <stdio.h>
TEST_GROUP(UDP_DATA_TEST)
{
};

TEST(UDP_DATA_TEST, FirstTest)
{
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

int main(int ac, char** av)
{
    return CommandLineTestRunner::RunAllTests(ac, av);
}

