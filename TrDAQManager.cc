#include "TrDAQManager.hh"
#include <time.h>

TrDAQManager::TrDAQManager(std::string file, std::vector<int> addresses, int masterAddress) {

	goCommands.insert(std::pair<std::string, int> ("getData",0x0));
        goCommands.insert(std::pair<std::string, int> ("getDataSize",0x1));
        goCommands.insert(std::pair<std::string, int> ("trigger",0x2));
        goCommands.insert(std::pair<std::string, int> ("dataMode",0x3));
	goCommands.insert(std::pair<std::string, int> ("readoutMode",0x4));
	dataBuffer = new TrRunData();
	fileName = file;
	setupBoards(addresses, masterAddress);
}

int TrDAQManager::setupStorage(std::string file) {
	fileName = file;
	return 0;
}

int TrDAQManager::setupBoards(std::vector<int> addresses, int masterAddress) {	
	readoutController.setupVLSB(addresses, masterAddress);
	readoutController.initialiseVME();
	readoutController.initialiseBoards("external",100,500);
	return 0;
}

int TrDAQManager::setNumberOfTriggers(int triggers) {
	nSpills = 1;
	if (triggers > 100) {
		nSpills = int((triggers / 100) + 1.5);
	}
	std::cout << "Running with " << nSpills << " spills" << std::endl;
	
	return 0;
}

int TrDAQManager::setTriggerMode() {
	readoutController.setDataMode();
	return 0;
}

int TrDAQManager::setReadoutMode() {
	readoutController.setReadoutMode();
	return 0;
}

int TrDAQManager::trigger(double bias) {
	generator.setBias(bias);
	//std::cout << "Triggering" << std::endl;
	return 0;
}

int TrDAQManager::trigger() {
	readoutController.enableTrigger();
	status = 1;
	return 0;
}

int TrDAQManager::stopTrigger() {
	readoutController.disableTrigger();
	return 0;
}

int TrDAQManager::waitForSpill() {
	readoutController.pollSpillDone();
}

int TrDAQManager::readout() {
	
	for (unsigned int s=0; s<1; s++) {
		//std::cout << "Reading spill " << s << std::endl;
		TrSpillData *newSpill = readoutController.readout();
		currentSpills.push_back(*newSpill);
	}
	return 0;
}

int TrDAQManager::build() {	
	status = 3; 	
	for (unsigned int spill=0; spill<currentSpills.size(); spill++) {	
		dataBuffer->addSpill(currentSpills[spill],0);	
	}
	currentSpills.clear();
	return 0;
}

int TrDAQManager::write() {
	status = 4;
	std::ofstream stream;
	stream.open (fileName.c_str(), std::ios::out | std::ios::binary);
	for (unsigned int board=0; board <BOARDS; board++) {
		for (unsigned int bank=0; bank<BANKS; bank++) {
			for (unsigned int channel=0; channel<CHANNELS; channel++){	
				int *histPointer = dataBuffer->getHistogram(board,bank,channel)->convertToBuffer();
				//TrHistogram* hist = dataBuffer->getHistogram(board,bank,channel);
				//TrHistogramHeader* header = hist->getHeader();
				//int info = header->getChannelInfo();
				//std::cout << info << std::endl;
				//stream.write((char*)&headerIndicator,sizeof(int));
				//stream.write((char*)&info,sizeof(int));
				stream.write((char*)histPointer,sizeof(int)*HISTOGRAMRANGE);
			}
		}
	}
	stream.close();
	return 0;
}

TrRunData* TrDAQManager::getRunData() {
	return dataBuffer;
}

int TrDAQManager::getCommands() {
	int command = socket.receiveData();
	switch(command) {
		case 0: //get the data
			go();
			transmit();
	//	case 1: //get the datasize
	//	case 2: //trigger
	}
	return 0;	
}	

int TrDAQManager::transmit() {
	int *dataPointer = dataBuffer->getData();
	int dataSize = BOARDS*BANKS*CHANNELS*BINS;
	socket.sendData(dataPointer, dataSize);
	return 0;
}

void TrDAQManager::go() {
	for (int spill=0; spill<nSpills; spill++) {
		//if ((spill % 1) == 0) {
		std::cout << "Generated " << spill << " spills" << std::endl;
		//}
		setTriggerMode();
		sleep(1);
		trigger();
		//sleep(1);
		waitForSpill();
		stopTrigger();	
		setReadoutMode();
		sleep(1);
		readout();
		build();
	}
	write();
}
