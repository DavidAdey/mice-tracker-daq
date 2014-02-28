#include "MDEVLSBMaster.hh"
#include "MiceDAQMessanger.hh"
#include <iomanip>

bool MDEVLSBMaster::Arm() {
	controller.setup((*this)["BaseAddress"]);
	controller.initialise("external"); /*! External trigger */
}

int MDEVLSBMaster::ReadEventVLSBMaster() {
	controller.disableTrigger();
	return 0;
}

int MDEVLSBMaster::EventArrivedVLSBMaster() {return 0;}
bool MDEVLSBMaster::DisArmVLSBMaster() {}	

bool MDEVLSBMaster::DisArmVLSBMasterTrailer() {}

int MDEVLSBMaster::ReadEventVLSBMasterTrailer(return 0;) {
	controller.enableTrigger();
	//get number triggers, tdc, crc
}

int MDEVLSBMaster::EventArrivedVLSBMasterTrailer() {return 0;}
