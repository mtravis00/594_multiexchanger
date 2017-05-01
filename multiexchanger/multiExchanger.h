#include "Memory.h"
#include "exchanger.h"


SC_MODULE(multiExchanger)
{
	sc_signal_rv<WORD_LENGTH> databusin1, databusin2, databusin3, databusin4, 
								databusout1, databusout2, databusout3, databusout4;
	sc_signal_rv<ADDRESS> addrbus1, addrbus2, addrbus3, addrbus4;
	sc_signal_resolved cs, rd_en1, rd_en2, rd_en3, rd_en4, wr_en1,
						wr_en2, wr_en3, wr_en4;

	sc_mutex memWR;
	
	sc_semaphore* memRD;

	meminterface* thismem;

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
		thismem = new meminterface;

		memRD = new sc_semaphore(3);

		EXC1 = new exchanger("EXC1_Instance", 11, 5, 10); 
			EXC1->cs(cs);
			EXC1->rd_en(rd_en1);
			EXC1->wr_en(wr_en1);
			EXC1->datain(databusin1);
			EXC1->dataout(databusout1);
			EXC1->addr(addrbus1);
			EXC1->permit_wr=&memWR;		// Pass write mutex reference
			EXC1->permit_rd = memRD;	// Pass read semaphore reference

		EXC2 = new exchanger("EXC2_Instance", 22, 5, 20);
			EXC2->cs(cs);
			EXC2->rd_en(rd_en2);
			EXC2->wr_en(wr_en2);
			EXC2->datain(databusin2);
			EXC2->dataout(databusout2);
			EXC2->addr(addrbus2);
			EXC2->permit_wr=&memWR;  // Pass mutex reference
			EXC2->permit_rd = memRD;

		EXC3 = new exchanger("EXC3_Instance", 33, 5, 30);
			EXC3->cs(cs);
			EXC3->rd_en(rd_en3);
			EXC3->wr_en(wr_en3);
			EXC3->datain(databusin3);
			EXC3->dataout(databusout3);
			EXC3->addr(addrbus3);
			EXC3->permit_wr = &memWR;  // Pass mutex reference
			EXC3->permit_rd = memRD;

		EXC4 = new exchanger("EXC4_Instance", 44, 5, 40);
			EXC4->cs(cs);
			EXC4->rd_en(rd_en4);
			EXC4->wr_en(wr_en4);
			EXC4->datain(databusin4);
			EXC4->dataout(databusout4);
			EXC4->addr(addrbus4);
			EXC4->permit_wr = &memWR;  // Pass mutex reference
			EXC4->permit_rd = memRD;

		

		MEM = new Memory("MEM_Instance");
			(*MEM) (addrbus1, databusin1, databusout1, cs,wr_en1 ,rd_en1);
	}
};
 