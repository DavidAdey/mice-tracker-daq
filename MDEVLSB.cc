#include "MDEVLSB.hh"

/*! Constructor */
MDEVLSB::MDEVLSB() {}

bool MDEVLSB::Arm() {
	/*! Sets up the address map */
	controller.initialise((*this)["BaseAddress"];
}

int MDEVLSB::ReadEvent(std::string mode) {
	int dataStored = 0;	
	/*! ACQUIRE mode puts LVDS into data accept
	* should happen before any triggers arrive
	* called at START_OF_BURST DAQ event */
	if (mode == "ACQUIRE") {
		controller.setDataMode();
	}
	/*! READOUT mode stops LVDS acquire and opens VME access
	* called at end of spill gate by PHYSICS_EVENT DAQ event */
	else if (mode == "READOUT") {
		controller.setReadoutMode();
	}
	/*! VLSB doesn't return data - the banks do*/
	return dataStored;
}

int MDEVLSB::EventArrived() {}
bool MDEVLSB::DisArm() {}
