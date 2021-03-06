#include "exchanger.h"
#include <time.h>

void exchanger::exchanging() {
	int i, dval, startaddr;
	int numberofsem;
	srand(device*(unsigned)time(NULL));
	unsigned int random_rd_wr;

	meminterface* mem_if;

	while (true) {

		random_rd_wr = 1;// rand() % 2;  // 1 will be a write function and 0 will be a read
		//cout << " random write or read value " << random_rd_wr << endl;
		

		cout << "Device: " << device << " at " << sc_time_stamp() << " is idle ...\n";

		wait(delay * 30, SC_NS);

		if (random_rd_wr == 1) { // write process
			cout << "Device: " << device << " at " << sc_time_stamp() << " has requested to write...\n";
			permit_wr->lock();
			//wait(delay * 30, SC_NS);
			cout << "Device: " << device << " at " << sc_time_stamp() << " is granted write access to memory ...\n";

			startaddr = rand() % ADDR_SPACE;

		/*	for (i = 0; i <= burst; i++) {
				dval = rand() % WORD_LENGTH;
				datain = (sc_lv<WORD_LENGTH>)dval;
				addr = (sc_lv<ADDRESS>)(startaddr + i);
				cs = (sc_logic)'1';
				wr_en = (sc_logic)'1';
				wait(delay, SC_NS);
			}*/

			for (i = 0; i <= burst; i++) {
				dval = rand() % WORD_LENGTH;
				mem_if->addr  = (sc_lv<ADDRESS>)(startaddr + i);
				mem_if->datain = (sc_lv<WORD_LENGTH>)dval;
				 
				cs = (sc_logic)'1';
				wr_en = (sc_logic)'1';
				wait(delay, SC_NS);
			}


			cs = (sc_logic)'Z';
			wr_en = (sc_logic)'Z';
			datain = (sc_lv<WORD_LENGTH>)"ZZZZZZZZ";
			addr = (sc_lv<ADDRESS>)"ZZZZZZZZZZ";

			cout << "Device: " << device << ">>>>>> wrote in the memory starting at: " << startaddr << "\n";
			cout << "Device: " << device << " at " << sc_time_stamp() << " completes its exchange.\n";
			cout << "Device: " << burst << " number of transactions were completed\n";
			cout << "Device: " << device << " is done.\n";
			permit_wr->unlock();
			wait(delay * 100, SC_NS);
		}

		else { // read process

			cout << "Device: " << device << " at " << sc_time_stamp() << " has requested to read...\n";
			
			permit_rd->wait();  // request a token block if not available
			numberofsem = permit_rd->get_value();  // get total number of semephore tokens

			cout << "Device: " << device << " at " << sc_time_stamp() << " is granted read access to memory ...\n";
			cout << "There are " << numberofsem << " read tokens remaining" << endl;
			startaddr = rand() % ADDR_SPACE;

			for (i = 0; i <= burst; i++) {
				//dval = rand() % WORD_LENGTH;
				addr = (sc_lv<ADDRESS>)(startaddr + i);
				cs = sc_logic_1;
				rd_en = sc_logic_1;
				wait(delay, SC_NS);
			}
			
			cs = SC_LOGIC_Z;
			rd_en = (sc_logic)'Z';
			datain = (sc_lv<WORD_LENGTH>)"ZZZZZZZZ";
			addr = (sc_lv<ADDRESS>)"ZZZZZZZZZZ";

			cout << "Device: " << device << "<<<<<< read from memory starting at: " << startaddr << "\n";
			cout << "Device: " << device << " at " << sc_time_stamp() << " completes its read.\n";
			cout << "Device: " << burst << " number of transactions were completed\n";
			cout << "Device: " << device << " is done.\n";
			
			permit_rd->post();  // release token
			


		}
	}
}
