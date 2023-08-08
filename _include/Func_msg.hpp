#ifndef _FUNC_MSG_H
#define _FUNC_MSG_H


#include <iomanip>
#include <unistd.h> 
#include "Basic_config.hpp"

extern zcm::ZCM zcmCAN;

class Handler
{
public:
	~Handler() {}

	void zcm_msg_publish(const zcm::ReceiveBuffer* rbuf, const std::string& chan, const SCU_CAN_STS* msg) 
    {
        memcpy(&can_sts, msg, sizeof(SCU_CAN_STS));
    }
};

extern Handler handlerObject;

void msg_running();
void zcm_msg_publish();

#endif