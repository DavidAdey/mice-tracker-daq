#include "VLSBMaster.hh"

MDEVLSBMaster *master = new MDEVLSBMaster();

void ArmVLSBMaster(char *parPtr) {
	/*! Get the parameter pointer */
	VLSBMaster_ParType *vmParam = (VLSBMaster_ParType*) parPtr;
	/*! Fill the master with the parameters */
	master->setParams("BaseAddress", getBA(vmParam->BaseAddress));
	/*! Call the arm (setup addresses) function */
	master->Arm();
}

void DisArmVLSBMaster(char *parPtr) {
	master->DisArm();
}

void AsynchReadVLSBMaster(char *parPtr) {}

int ReadEventVLSBMaster(char *parPtr, struct eventHeaderStruct *header_ptr, struct equipmentHeaderStruct *eq_header_ptrs, datePointer *data_ptr) {

	int dataStored = 0;
	/*! Check the DAQ Event type */
	if (header_ptr->eventType == PHYSICS_EVENT) {
		/*! Enable the vlsb master triggers */
		master->ReadEventVLSBMaster();
	}
	/*! No data returned */
	return dataStored;
}

int EventArrivedVLSBMaster(char *parPtr) {return 0;}

void PauseArmVLSBMaster(char *parPtr) {}

void PauseDisArmVLSBMaster(char *parPtr) {}
