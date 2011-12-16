
#include "DyIO/Debug_DyIO.h"
#include "Bowler/Bowler.h"

void printMode(BYTE mode){
	#if !defined(__AVR_ATmega324P__)
		switch(mode&0x7f){
		case NO_CHANGE:
			print("NO_CHANGE");
			break;
		case HIGH_IMPEDANCE:
			print("HIGH_IMPEDANCE");
			break;
		case IS_DI:
			print("IS_DI");
			break;
		case IS_DO:
			print("IS_DO");
			break;
		case IS_ANALOG_IN:
			print("IS_ANALOG_IN");
			break;
		case IS_ANALOG_OUT:
			print("IS_ANALOG_OUT");
			break;
		case IS_PWM:
			print("PWM");
			break;
		case IS_SERVO:
			print("SERVO");
			break;
		case IS_UART_TX:
			print("UART_TX");
			break;
		case IS_UART_RX:
			print("UART_RX");
			break;
		case IS_SPI_MOSI:
			print("SPI_MOSI");
			break;
		case IS_SPI_MISO:
			print("SPI_MISO");
			break;
		case IS_SPI_SCK:
			print("SPI_SCK");
			break;
//		case IS_SPI_SS:
//			print("SPI_SS");
//			break;
		case IS_COUNTER_INPUT_INT:
			print("COUNTER_INPUT_INT");
			break;
		case IS_COUNTER_INPUT_DIR:
			print("COUNTER_INPUT_DIR");
			break;
		case IS_COUNTER_INPUT_HOME:
			print("COUNTER_INPUT_HOME");
			break;
		case IS_COUNTER_OUTPUT_INT:
			print("COUNTER_OUTPUT_INT");
			break;
		case IS_COUNTER_OUTPUT_DIR:
			print("COUNTER_OUTPUT_DIR");
			break;
		case IS_COUNTER_OUTPUT_HOME:
			print("COUNTER_OUTPUT_HOME");
			break;
		case IS_DC_MOTOR_DIR:
			print("IS_DC_MOTOR_DIR");
			break;
		case IS_DC_MOTOR_VEL:
			print("IS_DC_MOTOR_VEL");
			break;
		case IS_PPM_IN:
			print("IS_PPM_IN");
			break;
		default:
			print("UNKNOWN");
			p_ul(mode);
		}
	#else
	p_ul(mode);
	#endif
}
