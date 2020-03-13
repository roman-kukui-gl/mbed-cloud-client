#ifndef UNITY_CONFIG_H
#define UNITY_CONFIG_H

// RX65N serial terminal
#include "serial_term_uart.h"

#define UNITY_OUTPUT_CHAR(a)    uart_charput(a)

#endif
