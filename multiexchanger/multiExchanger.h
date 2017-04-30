#include "Memory.h"
#include "exchanger.h"


SC_MODULE(multiExchanger)
{
	sc_signal_rv<WORD_LENGTH> databusin, databusout;
	sc_signal_rv<ADDRESS> addrbus;
	sc_signal_resolved cs, rd_en, wr_en;

	meminterface* memory_if;

	sc_mutex memWR;
	
	sc_semaphore* memRD;

//	meminterface* thismem;

	exchanger* EXC1;
	exchanger* EXC2;
	exchanger* EXC3;
	exchanger* EXC4;

	Memory* MEM;

	void resetting();
	void clocking();
	void displaying();

	SC_CTOR(multiExchanger)
	{
		//thismem = new meminterface;

		memRD = new sc_semaphore(3);

		EXC1 = new exchanger("EXC1_Instance", 11, 5, 10); 
		//	EXC1->mem_if(MEM);
	//		EXC1->cs(cs);
	//		EXC1->rd_en(rd_en);
//			EXC1->wr_en(wr_en);
	//		EXC1->datain(databusin);
	//		EXC1->dataout(databusout);
	//		EXC1->addr(addrbus);
//			EXC1->permit_wr=&memWR;		// Pass write mutex reference
	//		EXC1->permit_rd = memRD;	// Pass read semaphore reference
/*
		EXC2 = new exchanger("EXC2_Instance", 22, 5, 20);
			EXC2->cs(cs);
			EXC2->rd_en(rd_en);
			EXC2->wr_en(wr_en);
			EXC2->datain(databusin);
			EXC2->dataout(databusout);
			EXC2->addr(addrbus);
			EXC2->permit_wr=&memWR;  // Pass mutex reference
			EXC2->permit_rd = memRD;

		EXC3 = new exchanger("EXC3_Instance", 33, 5, 30);
			EXC3->cs(cs);
			EXC3->rd_en(rd_en);
			EXC3->wr_en(wr_en);
			EXC3->datain(databusin);
			EXC3->dataout(databusout);
			EXC3->addr(addrbus);
			EXC3->permit_wr = &memWR;  // Pass mutex reference
			EXC3->permit_rd = memRD;

		EXC4 = new exchanger("EXC4_Instance", 44, 5, 40);
			EXC4->cs(cs);
			EXC4->rd_en(rd_en);
			EXC4->wr_en(wr_en);
			EXC4->datain(databusin);
			EXC4->dataout(databusout);
			EXC4->addr(addrbus);
			EXC4->permit_wr = &memWR;  // Pass mutex reference
			EXC4->permit_rd = memRD;
			*/
		

		MEM = new Memory("MEM_Instance");
			MEM->mem_interface(&memory_if);
			//MEM-> mem_interface(memory_if);
		//	MEM->cs(cs);
		//	MEM->wr_en(wr_en);
		//	MEM->rd_en(rd_en);
		//	MEM->mem_struct(&thismem);
		//	MEM->addr(addrbus);
		//	MEM->datain(databusin);
		//	MEM->dataout(databusout);
			
		//	(*MEM) (addrbus, databusin, databusout, cs,wr_en ,rd_en);
	}
};
 