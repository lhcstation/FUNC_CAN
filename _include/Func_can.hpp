#ifndef _FUNC_CANBUS_H
#define _FUNC_CANBUS_H

#include "Basic_config.hpp"
#include <iostream>
#include <unistd.h>

extern "C" {
	#include "controlcan.h"
}

bool CANbus_init();
void CAN_send_msg();
void CAN_recv_msg();

#endif
