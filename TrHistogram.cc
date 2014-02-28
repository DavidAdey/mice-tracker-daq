#include "TrHistogram.hh"

TrHistogram::TrHistogram() : bins(256) {
	//for (int b=0; b<256; ++b) {
	//	bins.push_back(0);
	//}
	//std::cout << bins.size() << " new bins" << std::endl;
}

void TrHistogram::setBinValue(int bin, int value) {
	bins[bin] = value;
}

int TrHistogram::getBinValue(int bin) {
	//std::cout << "avail" << std::endl;
	//std::cout << bins.size() << std::endl;
	/*std::cout << "Tring to get value" << std::endl;
	std::cout << "Bin no " << bin << std::endl;
	std::cout << "avail " << std::endl;
	std::cout << bins.size() << std::endl;*/
	return bins[bin];
}

void TrHistogram::fill(int bin) {
	bins[bin]++;
}

void TrHistogram::convertFromBuffer(int* bufferPtr, int size) {

	if (size != 256) {
	}
	else {
		for (int i=0; i<size; i++) {
			int word = (int)*bufferPtr;
			bins[i] = word;
			bufferPtr++;	
		}	
	}
}

int* TrHistogram::convertToBuffer() {

	int *buffer = (int*)malloc(sizeof(int)*HISTOGRAMRANGE);
	int *bufferStart = buffer;
	for (unsigned int bin=0; bin<HISTOGRAMRANGE; bin++) {
		*bufferStart = bins[bin];
		++bufferStart;
	}
	return buffer;	

}

void TrHistogram::add(TrHistogram* other) {

	for (int i=0; i<256; i++){
		//int otherValue = other->getBinValue(i);
		//std::cout << "got other bin" << std::endl;
		bins[i] += other->getBinValue(i);
	}
	/*if (header.getChannelInfo() != other->getHeader()->getChannelInfo()) {
		header.copy(other->getHeader());
		//std::cout << "Had to copy header" << std::endl;
	}*/
}

void TrHistogram::addHeader(TrHistogramHeader headerIn) {
	header = headerIn;
	//std::cout << std::hex << header.getChannelInfo() << " was added as a header " << std::endl;
}
