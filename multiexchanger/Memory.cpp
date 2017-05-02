#include "Memory.h"

void Memory::meminit() {
	int i;
	for(i=0;i<ADDR_SPACE;i++) {
		mem[i] = i;
	}
}

void Memory::memwrite() {
	int ad;
	//if(cs == SC_LOGIC_1) {
		if(wr_en1 == SC_LOGIC_1) {
			ad=(sc_uint<ADDRESS>)addr1;
			mem[ad] = datain1;
		}
		else if (wr_en2 == SC_LOGIC_1) {
			ad = (sc_uint<ADDRESS>)addr2;
			mem[ad] = datain2;
		}
		else if (wr_en3 == SC_LOGIC_1) {
			ad = (sc_uint<ADDRESS>)addr3;
			mem[ad] = datain3;
		}
		else if (wr_en4 == SC_LOGIC_1) {
			ad = (sc_uint<ADDRESS>)addr4;
			mem[ad] = datain4;
		}
	//}
}

void Memory::memread() {
	int ad;
	//if (cs == SC_LOGIC_1) {
	if (rd_en1 == SC_LOGIC_1) {
		ad = sc_uint<ADDRESS>(addr1);
		dataout1 = sc_uint<ADDRESS>(mem[ad]);
				}
	else if (rd_en2 == SC_LOGIC_1) {
		ad = sc_uint<ADDRESS>(addr2);
		dataout2 = sc_uint<ADDRESS>(mem[ad]);
	}
	else if (rd_en3 == SC_LOGIC_1) {
		ad = sc_uint<ADDRESS>(addr3);
		dataout3 = sc_uint<ADDRESS>(mem[ad]);
	}
	else if (rd_en4 == SC_LOGIC_1) {
		ad = sc_uint<ADDRESS>(addr4);
		dataout4 = sc_uint<ADDRESS>(mem[ad]);
	}
	//}
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
