#include "TrReadout.hh"

TrReadout::TrReadout() {
	for (int board=0; board<8; ++board) {
		for (int bank=0; bank<4; ++bank) {
			for (int channel=0; channel<128; ++channel) {
				TrHistogram h = TrHistogram();
				std::cout << h.bins.size() << " constructed bins " << std::endl;
				currentSpill.addHistogram(board, bank, channel, h);
				std::cout << "Added to current spill"<< std::endl;
			}
		}
	}
}

int TrReadout::setupVLSB(std::vector<int> vlsbAddresses, int masterAddress) {
	for (int addressNo = 0; addressNo < vlsbAddresses.size(); ++addressNo) {
		TrVLSBController vlsb = TrVLSBController();
		vlsb.initialise(vlsbAddresses[addressNo]);
		vlsbs.push_back(vlsb);
	}
	master.setup(masterAddress);
	return 0;
}

int TrReadout::initialiseVME() {
	CVBoardTypes VMEBoard;
	short Link;
	short Device;
	int32_t BHandle;
	Device = 0;//atoi((const char*) argv[2]);
        Link = 0;//atoi((const char*) argv[3]);
        VMEBoard = cvV2718;
	int init = CAENVME_Init(cvV2718, 0, 0, &BHandle);
	std::cout << init << " init" << std::endl;
	return init;
}

int TrReadout::initialiseBoards(std::string triggerMode, int numberTriggers = 0, int triggerPeriod = 0) {
	master.initialise(triggerMode, numberTriggers, triggerPeriod);
}

TrSpillData* TrReadout::readout() {

	for (unsigned int vlsb=0; vlsb<vlsbs.size(); ++vlsb) {
		vlsbs[vlsb].getBankLengths(); 
		//vlsbs[vlsb].readAllBanks();
		compress(vlsbs[vlsb].readAllBanks(), vlsbs[vlsb].getTotalDataVolume(), vlsbs[vlsb].getID());
	}
	return &currentSpill;

}

TrSpillData* TrReadout::readout(TrGenerator generator) {

	currentSpill = generator.generateSimulated();
	return &currentSpill;
}

void TrReadout::compress(int *dataPointer, int dataVolume, int id) {
	
	id = 0;//0id >> 28;
	TrSpillData spill = TrSpillData();
	int channel = 0;
	for (int word=0; word < dataVolume; ++word) {
		std::cout << word << " of " << dataVolume << std::endl;
		std::cout << "Word is " << std::hex << *dataPointer << std::endl;
		int adc = ( (*dataPointer) & 0xFF );
		int bank = int(channel / 128);
		int realChannel = ((*dataPointer) & 0xFF0000) >> 16;
		//std::cout << "Made values for " << channel << std::endl;
		//TrHistogram *histogram = currentSpill.getHistogram(id, bank, realChannel);
		//std::cout << "Got histogram" << std::endl;
		//histogram->fill(adc);
		//std::cout << "Filled with " << adc << std::endl;
		//delete histogram;
		//std::cout << "deleted pointer" << std::endl;
		

		/*TrHistogram h = TrHistogram();
		int* p = (int*)malloc(sizeof(int)*HISTOGRAMRANGE);
		int* ptr = p;
		int* ps = p;
		ptr += adc;
		*ptr += 1;	
		h.convertFromBuffer(ps, HISTOGRAMRANGE);
		h.addHeader(TrHistogramHeader(id,bank,realChannel,0));*/
		std::cout << "Getting " << id << " " << bank << " " <<realChannel << std::endl;
		std::cout << "From " << *dataPointer << std::endl;
		TrHistogram *histogram = currentSpill.getHistogram(id, bank, realChannel);
		//std::cout << "adding" << std::endl;
		histogram->fill(adc);
		//std::cout << "adding to spill" << std::endl;
		//currentSpill.addHistogram(id,bank,realChannel,*histogram);
		//std::cout << i << " " << j << " " << k << std::endl;
		//free(p);
		//std::cout << "Memory freed" << std::endl;
		++channel;
		if (channel == 512) channel = 0;	
		++dataPointer;

	}
	//return spill;
}

void TrReadout::setDataMode() {
	for (unsigned int vlsb=0; vlsb<vlsbs.size(); ++vlsb) {
		vlsbs[vlsb].setDataMode();
	}
}
void TrReadout::setReadoutMode() {	
	for (unsigned int vlsb=0; vlsb<vlsbs.size(); ++vlsb) {
		vlsbs[vlsb].setReadoutMode();
	}
}

void TrReadout::enableTrigger() {
	master.enableTrigger();
}

void TrReadout::disableTrigger() {
	master.disableTrigger();
}

int TrReadout::pollSpillDone() {
	return master.getSpillDone();
}


 
