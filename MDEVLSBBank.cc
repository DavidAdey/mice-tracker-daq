#include "MDEVLSBBank.hh"

/*! Constructor */
MDEVLSBBank::MDEVLSBBank() {}

bool MDEVLSBBank::Arm() {
	controller.initialise((*this)["BaseAddress"];
}

int MDEVLSBBank::ReadEvent() {
	controller.getBankLengths();
	dataStored = controller.readBank((*this)["BankNumber"],0,mde_dataPtr;
	return dataStored;
}

int MDEVLSBBank::EventArrived() {}
bool MDEVLSBBank::DisArm() {}
