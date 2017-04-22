#include "multiExchanger.h"

int sc_main(int argc, char* argv[])
{
	multiExchanger EXC1 ("EXC_Instance");

	sc_trace_file* VCDFile;
	VCDFile = sc_create_vcd_trace_file("dataExchange");
		sc_trace(VCDFile, EXC1.databusin, "inb");
		sc_trace(VCDFile, EXC1.databusout, "oub");
		sc_trace(VCDFile, EXC1.addrbus, "adb");
		sc_trace(VCDFile, EXC1.cs, "cs");
		sc_trace(VCDFile, EXC1.rwbar, "rwb");

	sc_start(2100,SC_NS);
	return 0;
}


