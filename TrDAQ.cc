#include "TrDAQ.hh"
#include "TrHistogram.hh"
#include "TrVMEModeChanger.hh"
#include "TrSpillData.hh"
#include "TrRunData.hh"
#include "TrGenerator.hh"
#include "TrReadout.hh"
#include "TrDAQManager.hh"
#include <iostream>
#include <fstream>
#include <time.h>
//#include "TrMySQLConnect.hh"
//#include "TROOT.h"
//#include "TH1F.h"
//#include <mysql/mysql.h>
#//include <sys/socket.h>

#define SERVER "localhost"
#define USER "daq"
#define PASSWORD "daq"
#define DATABASE "Calibrations"

void writeRunToFile(TrRunData*);

int main( int argc, char *argv[]) {
/*
	printf("works\n");
	std::cout << "in c++" << std::endl;
	
	TrReadout readout = TrReadout();
	TrGenerator generator = TrGenerator();
	TrRunData run = TrRunData();

	for (int r=0; r<5; r++) {	
		run.addSpill(*readout.readout(generator),0);
	}

	//run.print();
	writeRunToFile(&run);
	TrVMEModeChanger mChange = TrVMEModeChanger();
	mChange.setVMEAccess();
	mChange.setDataAccess();
*/
	std::vector<int> addresses;
	addresses.push_back(0x20000000);
	double bias = atof(argv[2]);
	std::string file = argv[1];
	//TH1F h1 = TH1F("a","a",10,0,10);
	TrDAQManager manager = TrDAQManager(argv[1], addresses, 0x10000000);
	manager.setNumberOfTriggers(500);
	//sleep(5);
	manager.go();
	/*for (int spill=0; spill<5; spill++) {
		if ((spill % 1) == 0) {
			std::cout << "Generated " << spill << " spills" << std::endl;
		}
		manager.setTriggerMode();
		manager.trigger(bias);
		manager.setReadoutMode();
		manager.readout();
		manager.build();
	}*/
	manager.write();
	//writeRunToFile(manager.getRunData());
}
