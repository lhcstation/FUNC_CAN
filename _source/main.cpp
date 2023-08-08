#include "Func_can.hpp"
#include "Func_msg.hpp"

#include <thread>
#include <iostream>


int main()
{
    if(CANbus_init() == false)
		return 0;

	if (!zcmCAN.good())
		return 0;

    std::cout<<"CAN Running"<<std::endl;

	zcmCAN.subscribe("CAN0_CMD", &Handler::zcm_msg_publish, &handlerObject);

	std::thread msg_rung_thread(msg_running);
	std::thread can_recv_thread(CAN_recv_msg);
	std::thread can_send_thread(CAN_send_msg);

	std::thread zcm_recv_thread(zcm_msg_publish);


    msg_rung_thread.join();
	can_recv_thread.join();
	can_send_thread.join();

	zcm_recv_thread.join();

	return 1;
}