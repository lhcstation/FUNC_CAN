#include "Func_msg.hpp"


zcm::ZCM zcmCAN{"ipc"};

Handler handlerObject;


void msg_running()
{
	while(1)
	{
		zcmCAN.handle();
	}
}


void zcm_msg_publish()
{
	while (1)
	{
		SCU_CAN_STS can_sts_tmp;

		mtx_can0_sts.lock();
		can_sts_tmp = can_sts;	
		mtx_can0_sts.unlock();
		zcmCAN.publish("CAN_STS", &can_sts_tmp);
		usleep(20*1000);
	}
}