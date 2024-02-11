#include "system.h"
#include "gpio.h"
#include "uart.h"

//#include "JTAGfunc430.h"           // JTAG functions
#define TCK_PORT 2
#define TCK_PIN 0
#define TDIO_PORT 2
#define TDIO_PIN 1

struct JTAGInterface{
	unsigned char tck_port;
	unsigned char tck_pin;
	unsigned char tdio_port;
	unsigned char tdio_pin;
};
typedef struct JTAGInterface JTAGInterface;

void jtag_init();
void setTCK(JTAGInterface *jtag);
void resetTCK(JTAGInterface *jtag);
void setTDIO(JTAGInterface *jtag);
void resetTDIO(JTAGInterface *jtag);
void enterSBWMode(JTAGInterface *jtag);

void main(){
	systemInit();	
	uartInit();
	uartPrintln("JTAG Demo");	

	JTAGInterface jtag;
	jtag_init(&jtag);
	char cmd = ' ';
	while(cmd != 'q'){
		if(uartCharReceived()){
			cmd = uartReadChar();
			uartWriteChar(cmd);
			switch(cmd){
				case 'i':
					uartPrintln("Entering SPW Mode");
					enterSBWMode(&jtag);
					break;
				default:
					uartPrintln("NA");
			}
		}
	}
	uartPrintln("Stop.");
}



void enterSBWMode(JTAGInterface *jtag){

}
void jtag_init(JTAGInterface *jtag){
	jtag->tck_port = 2;
	jtag->tck_pin = 0;
	jtag->tdio_port = 2;
	jtag->tdio_pin = 1;
	setPinMode(jtag->tck_port, jtag->tck_pin, OUTPUT);
	setPinMode(jtag->tdio_port, jtag->tdio_pin, OUTPUT);
	resetTCK(jtag);
	setTDIO(jtag);

}
void setTCK(JTAGInterface *jtag){
	writePinOutput(jtag->tck_port, jtag->tck_pin, HIGH);
}
void resetTCK(JTAGInterface *jtag){
	writePinOutput(jtag->tck_port, jtag->tck_pin, LOW);
}
void setTDIO(JTAGInterface *jtag){
	writePinOutput(jtag->tdio_port, jtag->tdio_pin, HIGH);
}
void resetTDIO(JTAGInterface *jtag){
	writePinOutput(jtag->tdio_port, jtag->tdio_pin, LOW);
}


