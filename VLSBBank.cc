#include "VLSBBank.hh"

MDEVLSBBank *bank = new MDEVLSBBank();

void ArmVLSBBank(char *parPtr) {
	/*! Get the parameter pointer */
	VLSBBank_ParType *vbParam = (VLSBBank_ParType*) parPtr;
	/*! Fill the parameters */
	bank->SetParams("BaseAddress", getBA(vbParam->BaseAddress));
	bank->SetParams("BankNumber", getBA(vbParam->BankNumber));
	/*! Call the MDEVLSBBank Arm */
	bank->Arm();
}

int ReadEventVLSBBank(char *parPtr, struct eventHeaderStruct *header_ptr, struct equipmentHeaderStruct *eq_header_ptrs, datePointer *data_ptr) {

	int dataStored = 0;
	/*! Cast the pointer as 32bit because that's what all the data is */
	MDE_Pointer *data_ptr_32 = reinterpret_cast<MDE_Pointer *>(data_ptr);
	/*! Give the data pointer to the VLSBBank */
	bank->setDataPtr(data_ptr_32);
	/*! Only readout at end of spill gate */
	if (header_ptr->eventType == PHYSICS_EVENT) {
		/*! Call the read bank function from the MDEVLSBBank class */
		dataStored += bank->ReadEvent();
	}
	/*! Returns the number of bytes read - need to increment data pointer accordinly
	* All values are 32bit so must increment by dataStored/4 not sizeof(int) */
	return dataStored;
}

/*! Nothing is ever done here */
int EventArrivedVLSBBank(char *parPtr) {return 0;}
void PauseArmVLSBBank(char *parPtr) {}
void PauseDisArmVLSBBank(char *parPtr) {}
