#include "multiExchanger.h"

int sc_main(int argc, char* argv[])
{
	multiExchanger EXC1 ("EXC_Instance");
//	multiExchanger EXC2("EXC_Instance_2");

	sc_trace_file* VCDFile;
	VCDFile = sc_create_vcd_trace_file("dataExchange");
		sc_trace(VCDFile, EXC1.databusin, "inb");
		sc_trace(VCDFile, EXC1.databusout, "oub");
		sc_trace(VCDFile, EXC1.addrbus, "adb");
		sc_trace(VCDFile, EXC1.cs, "cs");
		sc_trace(VCDFile, EXC1.rd_en, "rd_en");
		sc_trace(VCDFile, EXC1.wr_en, "wr_en");
		




	sc_start(2100,SC_NS);
	return 0;
}


