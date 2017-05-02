#include "multiExchanger.h"

int sc_main(int argc, char* argv[])
{
	multiExchanger EXC1 ("EXC_Instance");
//	multiExchanger EXC2("EXC_Instance_2");

	sc_trace_file* VCDFile;
	VCDFile = sc_create_vcd_trace_file("dataExchange");
		sc_trace(VCDFile, EXC1.databusin1, "inb1");
		sc_trace(VCDFile, EXC1.databusout1, "oub1");
		sc_trace(VCDFile, EXC1.addrbus1, "adb1");
		//sc_trace(VCDFile, EXC1.cs, "cs1");
		sc_trace(VCDFile, EXC1.rd_en1, "rd_en1");
		sc_trace(VCDFile, EXC1.wr_en1, "wr_en1");
		

		sc_trace(VCDFile, EXC1.databusin2, "inb2");
		sc_trace(VCDFile, EXC1.databusout2, "oub2");
		sc_trace(VCDFile, EXC1.addrbus2, "adb2");
		//sc_trace(VCDFile, EXC1.cs, "cs2");
		sc_trace(VCDFile, EXC1.rd_en2, "rd_en2");
		sc_trace(VCDFile, EXC1.wr_en2, "wr_en2");


		sc_trace(VCDFile, EXC1.databusin3, "inb3");
		sc_trace(VCDFile, EXC1.databusout3, "oub3");
		sc_trace(VCDFile, EXC1.addrbus3, "adb3");
		//sc_trace(VCDFile, EXC1.cs, "cs3");
		sc_trace(VCDFile, EXC1.rd_en3, "rd_en3");
		sc_trace(VCDFile, EXC1.wr_en3, "wr_en3");

		sc_trace(VCDFile, EXC1.databusin4, "inb4");
		sc_trace(VCDFile, EXC1.databusout4, "oub4");
		sc_trace(VCDFile, EXC1.addrbus4, "adb4");
		//sc_trace(VCDFile, EXC1.cs, "cs4");
		sc_trace(VCDFile, EXC1.rd_en4, "rd_en4");
		sc_trace(VCDFile, EXC1.wr_en4, "wr_en4");



	sc_start(2100,SC_NS);
	return 0;
}


