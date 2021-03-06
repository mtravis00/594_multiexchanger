#include <systemc.h>

#define WORD_LENGTH 8 
#define ADDRESS 10 
#define ADDR_SPACE 1024
#define BURST_SIZE 128



#define WORD_LENGTH 8 
#define ADDRESS 10 
#define ADDR_SPACE 1024

SC_MODULE(exchanger)
{

	struct meminterface {
		sc_in_rv <ADDRESS> addr;
		sc_in_rv <WORD_LENGTH> datain;
		sc_out_rv <WORD_LENGTH> dataout;
	};



	sc_out_rv <ADDRESS> addr;
	sc_out_rv <WORD_LENGTH> datain;
	sc_in_rv <WORD_LENGTH> dataout;
	sc_out_resolved cs, rd_en, wr_en;
	sc_semaphore * permit_rd;
	sc_mutex* permit_wr;

	meminterface mem_if;


	SC_HAS_PROCESS(exchanger);

	exchanger::exchanger (sc_module_name NAME, int NUM, int TIM, int BRST) : sc_module(NAME), device(NUM), delay(TIM) , burst(BRST)
	{
		cout << "Device: " << device << " has started.\n";
		SC_THREAD(exchanging);
	}

	void exchanging();

	private:
		int device;
		int delay;
		int burst;
};
