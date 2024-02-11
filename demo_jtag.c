#include "system.h"
#include "gpio.h"
#include "uart.h"
#include "timer.h"

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
void exitSBWMode(JTAGInterface *jtag);

void initTimers(){
	timer0Init();
	timer1InitMicrosecond();
}
void delay_ms(int duration){
	delayMillisecondTimer0(duration);
}
void delay_us(int duration){
	delayMicrosecondTimer1(duration);
}
void main(){
	systemInit();	
	uartInit();
	uartPrintln("JTAG Demo");	
	initTimers();	

	JTAGInterface jtag;
	jtag_init(&jtag);
	char cmd = ' ';
	while(cmd != 'q'){
		if(uartCharReceived()){
			cmd = uartReadChar();
			uartWriteChar(cmd);
			switch(cmd){
				case 'i':
					uartPrintln("Entering SbW Mode");
					enterSBWMode(&jtag);
					break;
				case 'x':
					uartPrintln("Exit SBW Mode");
					exitSBWMode(&jtag);
					break;
				default:
					uartPrintln("NA");
					break;
			}
		}
	}
	uartPrintln("Stop.");
}



void exitSBWMode(JTAGInterface *jtag){
 	resetTCK(jtag);
	delay_us(200);
	setTDIO(jtag);
}
void enterSBWMode(JTAGInterface *jtag){
	resetTCK(jtag);
	setTDIO(jtag);
	delay_ms(20);
	setTCK(jtag);
	delay_ms(20);
	resetTCK(jtag);
	delay_us(1);
	setTCK(jtag);
	delay_ms(5);
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


