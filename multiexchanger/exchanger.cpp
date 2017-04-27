#include "exchanger.h"
#include <time.h>

void exchanger::exchanging() {
	int i, dval, startaddr;
	int numberofsem;
	srand(device*(unsigned)time(NULL));

	while(true) {
		cout << "Device: "<< device <<" at " << sc_time_stamp() <<" is idle ...\n";
		wait(delay*30,SC_NS);
		cout << "Device: "<< device <<" at " << sc_time_stamp() <<" has requested ...\n";
		numberofsem = permit_rd->get_value();
		cout << "!!! you have "<< numberofsem << " semahores"<< endl;
		permit_rd->wait();
		numberofsem = permit_rd->get_value();
		cout << "!!! you have " << numberofsem << " semahores after wait" << endl;
		

		permit->lock();
		permit_rd->get_value();

		cout << "Device: "<< device <<" at " << sc_time_stamp() <<" is granted the use of memory ...\n";

		startaddr = rand() % ADDR_SPACE;

		for(i=0;i<=burst;i++) {
			dval = rand() % WORD_LENGTH;
			datain = (sc_lv<WORD_LENGTH>)dval;
			addr = (sc_lv<ADDRESS>)(startaddr+i);
			cs = (sc_logic)'1';
			rwbar = (sc_logic)'0';
			wait(delay,SC_NS);
		}

		cs = (sc_logic)'Z';
		rwbar = (sc_logic)'Z';
		datain = (sc_lv<WORD_LENGTH>)"ZZZZZZZZ";
		addr = (sc_lv<ADDRESS>)"ZZZZZZZZZZ";
				
		cout << "Device: "<< device <<" wrote in the memory starting at: " << startaddr << "\n";
		cout << "Device: "<< device <<" at " << sc_time_stamp() <<" completes its exchange.\n";
		cout << "Device: " << burst << " number of transactions\n";
		cout << "Device: "<< device <<" is done.\n";
		permit_rd->post();
		numberofsem = permit_rd->get_value();
		cout << "!!! you have " << numberofsem << " semahores after post" << endl;
		permit->unlock();
	}
}
