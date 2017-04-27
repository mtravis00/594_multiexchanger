#include "Memory.h"
#include "exchanger.h"


SC_MODULE(multiExchanger)
{
	sc_signal_rv<WORD_LENGTH> databusin, databusout;
	sc_signal_rv<ADDRESS> addrbus;
	sc_signal_resolved cs, rwbar;

	sc_mutex memBusses;
	
	sc_semaphore* memrd;


	exchanger* EXC1;
	exchanger* EXC2;
	Memory* MEM;

	void resetting();
	void clocking();
	void displaying();

	SC_CTOR(multiExchanger)
	{
		memrd = new sc_semaphore(3);

		EXC1 = new exchanger("EXC1_Instance", 235, 3, 10); 
			EXC1->cs(cs);
			EXC1->rwbar(rwbar);
			EXC1->datain(databusin);
			EXC1->dataout(databusout);
			EXC1->addr(addrbus);
			EXC1->permit=&memBusses;  // Pass mutex reference

		EXC2 = new exchanger("EXC2_Instance", 67, 3, 20);
			EXC2->cs(cs);
			EXC2->rwbar(rwbar);
			EXC2->datain(databusin);
			EXC2->dataout(databusout);
			EXC2->addr(addrbus);
			EXC2->permit=&memBusses;  // Pass mutex reference

		MEM = new Memory("MEM_Instance");
			(*MEM) (addrbus, databusin, databusout, cs, rwbar);
	}
};
 