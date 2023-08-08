#ifndef BASIC_CONFIG_H_ 
#define BASIC_CONFIG_H_ 

#include <mutex>
#include <thread>
#include <iostream> 
#include <zcm/zcm-cpp.hpp>

#include "ADCU_CAN_CMD.hpp"
#include "SCU_CAN_STS.hpp"

#define ADCU_1 0x220
#define ADCU_2 0x221

#define SCU_1 0x180
#define SCU_2 0x222
#define SCU_3 0x223
#define SCU_4 0x224
#define SCU_5 0x181
#define SCU_6 0x225
#define SCU_7 0x226
#define SCU_8 0x227
#define SCU_9 0x228
#define SCU_10 0x229
#define SCU_11 0x2C0
#define SCU_12 0x2C1
#define SCU_13 0x22A
#define SCU_14 0x2C2
#define SCU_15 0x22B
#define SCU_16 0x22C
#define SCU_17 0x22D
#define SCU_18 0x22F
#define SCU_19 0x390
#define SCU_20 0x2C3
#define SCU_21 0x2C4
#define SCU_22 0x2C5
#define SCU_23 0x2C6
#define SCU_24 0x2C7
#define SCU_25 0x2C8

extern SCU_CAN_STS can_sts;
extern ADCU_CAN_CMD can_cmd;

extern std::mutex mtx_can0_sts;
extern std::mutex mtx_can0_cmd;



#endif