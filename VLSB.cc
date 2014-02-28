#include "VLSB.hh"

MDEVLSB *vlsb = new MDEVLSB();

void ArmVLSB(char *parPtr) {
	/*! Get the parameter pointer */
	VLSB_ParType *vbParam = (VLSB_ParType*) parPtr;
	/*! Use it to set the parameters of the VLSB */
	vlsb->SetParams("BaseAddress", getBA(vbParam->BaseAddress));
	/*! Call the VLSB Arm function */
	vlsb->Arm();
}

int ReadEventVLSB(char *parPtr, struct eventHeaderStruct *header_ptr, struct equipmentHeaderStruct *eq_header_ptrs, datePointer *data_ptr) {

	int dataStored = 0;
	/*! Cast the pointer as 32bit because that's what all the data is 
	* and give it to the VLSB */
	MDE_Pointer *data_ptr_32 = reinterpret_cast<MDE_Pointer *>(data_ptr);
	vlsb->setDataPtr(data_ptr_32);

	/*! Get what stage of the spill we're in and put the VLSB into the relevent mode */
	if (header_ptr->eventType == START_OF_BURST) {
		dataStored = vlsb->ReadEvent("ACQUIRE");
	}
	else if (header_ptr->eventType == PHYSICS_EVENT) {
		dataStored = vlsb->ReadEvent("READOUT");
	}
	/*! VLSBs do not return data */
	return dataStored;
}

/*! Never called */
int EventArrivedVLSB(char *parPtr) {return 0;}
void PauseArmVLSB(char *parPtr) {}
void PauseDisArmVLSB(char *parPtr) {}
