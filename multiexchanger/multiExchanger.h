#include "Memory.h"
#include "exchanger.h"


SC_MODULE(multiExchanger)
{
	sc_signal_rv<WORD_LENGTH> databusin1, databusin2, databusin3, databusin4, 
								databusout1, databusout2, databusout3, databusout4;
	sc_signal_rv<ADDRESS> addrbus1, addrbus2, addrbus3, addrbus4;
	sc_signal_resolved cs1, cs2, cs3, cs4, rd_en1, rd_en2, rd_en3, rd_en4, wr_en1,
						wr_en2, wr_en3, wr_en4;

	
	
	sc_mutex memWR;  // mutex definition
	
	sc_semaphore* memRD; // semaphore definition



	exchanger* P1;
	exchanger* P2;
	exchanger* P3;
	exchanger* P4;

	Memory* MEM;

	void resetting();
	void clocking();
	void displaying();

	SC_CTOR(multiExchanger)
	{
	

		memRD = new sc_semaphore(3);  // semaphore constructor

		P1 = new exchanger("P1_Instance", 1, 5, 10); 
			P1->cs(cs1);
			P1->rd_en(rd_en1);
			P1->wr_en(wr_en1);
			P1->datain(databusin1);
			P1->dataout(databusout1);
			P1->addr(addrbus1);
			P1->permit_wr=&memWR;		// Pass write mutex reference
			P1->permit_rd = memRD;	// Pass read semaphore 

		P2 = new exchanger("P2_Instance", 2, 5, 20);
			P2->cs(cs2);
			P2->rd_en(rd_en2);
			P2->wr_en(wr_en2);
			P2->datain(databusin2);
			P2->dataout(databusout2);
			P2->addr(addrbus2);
			P2->permit_wr=&memWR;  // Pass mutex reference
			P2->permit_rd = memRD;// Pass read semaphore 

		P3 = new exchanger("P3_Instance", 3, 5, 30);
			P3->cs(cs3);
			P3->rd_en(rd_en3);
			P3->wr_en(wr_en3);
			P3->datain(databusin3);
			P3->dataout(databusout3);
			P3->addr(addrbus3);
			P3->permit_wr = &memWR;  // Pass mutex reference
			P3->permit_rd = memRD;// Pass read semaphore 

		P4 = new exchanger("P4_Instance", 4, 5, 40);
			P4->cs(cs4);
			P4->rd_en(rd_en4);
			P4->wr_en(wr_en4);
			P4->datain(databusin4);
			P4->dataout(databusout4);
			P4->addr(addrbus4);
			P4->permit_wr = &memWR;  // Pass mutex reference
			P4->permit_rd = memRD;// Pass read semaphore 

		

		MEM = new Memory("MEM_Instance");
			(*MEM) (addrbus1, addrbus2, addrbus3, addrbus4, 
				databusin1, databusin2, databusin3, databusin4,				
				databusout1, databusout2, databusout3, databusout4,
				cs1, cs2, cs3, cs4, 
				wr_en1, wr_en2, wr_en3, wr_en4, 
				rd_en1, rd_en2, rd_en3, rd_en4);
	}
};
 