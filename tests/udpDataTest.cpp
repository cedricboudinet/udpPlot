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

class CallBackClass_t
{
	public:
		void OnTrig() {
			called=true;
			//std::cout<<"triggCallback"<<std::endl;
		}
		bool called=false;
};
void CallBackFunction(CallBackClass_t * cbc)
{
	cbc->OnTrig();
}

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
	udpData.setMaxBufferSize(10);
	//checking trigger rising
	buffer[0]=0; udpData.push_back(buffer);
	CHECK_EQUAL(false, udpData.trigged());
	buffer[0]=-1; udpData.push_back(buffer);
	CHECK_EQUAL(false, udpData.trigged());
	buffer[0]= 1; udpData.push_back(buffer);
	CHECK_EQUAL(true, udpData.trigged());
	udpData.resetTrigger();
	buffer[0]=-1; udpData.push_back(buffer);
	CHECK_EQUAL(false, udpData.trigged());
	
	//trigger falling
	udpData.setTrigger(0,0, TRIGGER_SLOPE_FALLING);
	buffer[0]=1; udpData.push_back(buffer);
	CHECK_EQUAL(false, udpData.trigged());
	buffer[0]=-1; udpData.push_back(buffer);
	CHECK_EQUAL(true, udpData.trigged());

	//trigger both
	udpData.resetTrigger();
	udpData.setTrigger(0,0, TRIGGER_SLOPE_BOTH);
	buffer[0]=1;udpData.push_back(buffer);
	CHECK_EQUAL(true, udpData.trigged());
	udpData.resetTrigger();
	buffer[0]=-1;udpData.push_back(buffer);
	CHECK_EQUAL(true, udpData.trigged());

	//trigger level
	buffer[0]=1;udpData.push_back(buffer);
	udpData.resetTrigger();
	udpData.setTrigger(10, 0, TRIGGER_SLOPE_RISING);
	buffer[0]=1; udpData.push_back(buffer);
	CHECK_EQUAL(false, udpData.trigged());
	buffer[0]=11;udpData.push_back(buffer);
	CHECK_EQUAL(true, udpData.trigged());
	
	//trigger channel
	udpData.setTrigger(50.0, 1, TRIGGER_SLOPE_RISING);
	udpData.resetTrigger();
	buffer[0]=100; udpData.push_back(buffer);
	CHECK_EQUAL(false, udpData.trigged());
	buffer[1]=100; udpData.push_back(buffer);
	CHECK_EQUAL(true, udpData.trigged());

	//checking size when trigged
	udpData.resetTrigger();
	udpData.setTrigger(50.0, 0, TRIGGER_SLOPE_RISING);
	buffer[0]=0; udpData.push_back(buffer);
	CHECK_EQUAL(10, udpData._data.size());
	buffer[0]=100; udpData.push_back(buffer);
	buffer[0]=0; udpData.push_back(buffer);
	CHECK_EQUAL(12, udpData._data.size());
	udpData.resetTrigger();
	buffer[0]=0; udpData.push_back(buffer);
	CHECK_EQUAL(10, udpData._data.size());

	//checking trigger index
	udpData.resetTrigger();
	buffer[0]=0; udpData.push_back(buffer);
	buffer[0]=100; udpData.push_back(buffer);
	CHECK_EQUAL(11, udpData._triggerIndex);
	CHECK_EQUAL(11, udpData._data.size());

	//checking if double trigger doesn't overwrites the first one
	buffer[0]=0; udpData.push_back(buffer);
	buffer[0]=100; udpData.push_back(buffer);
	CHECK_EQUAL(13, udpData._data.size());
	CHECK_EQUAL(11, udpData._triggerIndex);

	//checking trigger config
	double level=0; int channel=0; trigger_slope_t triggerSlope=TRIGGER_SLOPE_RISING;
	udpData.setTrigger(25.3, 7, TRIGGER_SLOPE_BOTH);
	udpData.getTrigger(&level, &channel, &triggerSlope);
	CHECK_EQUAL(25.3, level);
	CHECK_EQUAL(7, channel);
	CHECK_EQUAL(TRIGGER_SLOPE_BOTH, triggerSlope);

	//trigger callback test
	CallBackClass_t CallBackClass;
	udpData.setTriggerCallBack((void(*)(void*))CallBackFunction, &CallBackClass);
	udpData.resetTrigger();
	udpData.setTrigger(25.3, 0, TRIGGER_SLOPE_BOTH);
	buffer[0]=0; udpData.push_back(buffer);
	buffer[0]=100; udpData.push_back(buffer);
	CHECK_EQUAL(true, udpData.trigged());
	CHECK_EQUAL(true, CallBackClass.called);

}

int main(int ac, char** av)
{
    return CommandLineTestRunner::RunAllTests(ac, av);
}

