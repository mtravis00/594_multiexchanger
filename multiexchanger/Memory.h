#include <systemc.h>
#include <iostream>

#define WORD_LENGTH 8 
#define ADDRESS 10 
#define ADDR_SPACE 1024


struct meminterface {
	sc_in_rv <ADDRESS> addr;
	sc_in_rv <WORD_LENGTH> datain;
	sc_out_rv <WORD_LENGTH> dataout;
};

 
SC_MODULE (Memory) {
//	sc_in_rv <ADDRESS> addr;
//	sc_in_rv <WORD_LENGTH> datain;
//	sc_out_rv <WORD_LENGTH> dataout;
//	sc_in_resolved cs, wr_en, rd_en;
	meminterface* mem_interface;

	sc_uint <WORD_LENGTH> mem [ADDR_SPACE];

	void meminit ();
	//void memread ();
	//void memwrite ();
	void memdump ();
	void memrd();
	void memwr();

	SC_CTOR(Memory) {
		SC_THREAD (meminit);
	//	SC_METHOD (memread);
	//		sensitive << addr << cs << rd_en ;
	//	SC_METHOD (memwrite);
	//		sensitive << addr << datain << cs << wr_en;
		SC_METHOD(memrd);
			sensitive << mem_interface->addr;
		SC_METHOD(memwr);
			sensitive << mem_interface->datain;
		SC_THREAD (memdump);


	}
};
