#include <systemc.h>
#include <iostream>

#define WORD_LENGTH 8 
#define ADDRESS 10 
#define ADDR_SPACE 1024
 
SC_MODULE (Memory) {
	sc_in_rv <ADDRESS> addr1, addr2, addr3, addr4;
	sc_in_rv <WORD_LENGTH> datain1, datain2, datain3, datain4;
	sc_out_rv <WORD_LENGTH> dataout1, dataout2, dataout3, dataout4;
	sc_in_resolved cs1, cs2, cs3, cs4, wr_en1, wr_en2, wr_en3, wr_en4; 
	sc_in_resolved rd_en1, rd_en2, rd_en3, rd_en4;


	sc_uint <WORD_LENGTH> mem [ADDR_SPACE];

	void meminit ();
	void memread ();
	void memwrite ();
	void memdump ();

	SC_CTOR(Memory) {
		SC_THREAD (meminit);
		SC_METHOD (memread);
			sensitive << addr1 << addr2 << addr3 << addr4 << cs1 << cs2 << cs3 <<cs4 << rd_en1 << rd_en2 << rd_en3 << rd_en4;
		SC_METHOD (memwrite);
			sensitive << addr1 << addr2 << addr3 << addr4 << datain1 << datain2 << datain3 << datain4 << cs1 << cs2 << cs3 << cs4 << wr_en1 << wr_en2 << wr_en3 << wr_en4;
		SC_THREAD (memdump);
	}
};
