#include "MiceDAQEquipment.hh"
#include "TrVLSBMasterController.hh"

#ifndef MDEVLSBMASTER
#define MDEVLSBMASTER

class MDEVLSBMaster : public MiceDAQEquipment {
	private:
		/*! The controller which understands all
		* the registers in the VLSBMaster */
		TrVLSBMasterController controller;

	public:
		MDEVLSBMaster();
		~MDEVLSBMaster();
		
 		bool Arm();
 		bool DisArmVLSBMaster();
		int ReadEventVLSBMaster();
  		int EventArrivedVLSBMaster();
	
  		bool DisArmVLSBMasterTrailer();
  		int ReadEventVLSBMasterTrailer();
  		int EventArrivedVLSBMasterTrailer();

};

#endif
