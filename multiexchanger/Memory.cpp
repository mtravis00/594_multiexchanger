#include "Memory.h"

void Memory::meminit() {
	int i;
	for(i=0;i<ADDR_SPACE;i++) {
		mem[i] = i;
	}
}

void Memory::memwrite() {
	int ad;
	if(cs == SC_LOGIC_1) {
		if(wr_en == SC_LOGIC_1) {
			ad=(sc_uint<ADDRESS>)addr;
			mem[ad] = datain;
		}
	}
}

void Memory::memread() {
	int ad;
	if (cs == SC_LOGIC_1) {
		if(rd_en == SC_LOGIC_1) {
			ad=sc_uint<ADDRESS>(addr);
			dataout=sc_uint<ADDRESS>(mem[ad]);
		}
	}
}

void Memory::memdump() {
	int i;
	sc_lv<WORD_LENGTH> data;
	ofstream out ("memout.txt");
	wait(2000,SC_NS);
	for (i=0;i<ADDR_SPACE;i++) {
		data=mem[i];
		out << i <<":\t" << data << "\n";
	}
}
