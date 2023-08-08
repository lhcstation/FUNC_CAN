#include "Basic_config.hpp"


// ***************** 纵向控制 ***************** //
// 发送 ADCU_1
/*****************
 * Message_Name         Signal_Name         Signal_Comment
 * ADCU_1               LngCtrlReq          纵向控制请求  
 * ADCU_1               AutoTrqWhlReq       扭矩请求
 * ADCU_1               BrakeReq            减速度请求
 * ADCU_1               GearLvlReq          档位请求
 * ADCU_1               GearLvlReqVD        档位请求有效
*****************/
// 接收
/*****************
 * Message_Name         Signal_Name         Signal_Comment
 * ****** ****** 纵向控制状态信号 ****** ******
 * SCU_13               LngCtrlMode         纵向控制功能状态
 * SCU_13               LngAutoCheckReport  纵向总控激活条件满足反馈
 * SCU_13               LngQuitReport       纵向控制非预期退出反馈
 * SCU_13               GearLeverIntv       档位干预
 * SCU_18               BrkPedalSt          制动踏板被踩下
 * ****** ****** 驱动系统状态信号 ****** ******
 * SCU_16               ActVehWheelTorq     实际轮端扭矩
 * SCU_17               VehWheelTorqMax     驱动系统允许的最大扭矩
 * SCU_17               GasPedalAcPst       当前油门踏板实际位置
 * SCU_17               AccElecECFail       驱动系统故障
 * SCU_14               VehRdySt            整车 Ready
 * SCU_14               VehDrvMod           车辆行驶模式
 * SCU_14               VehRng              续航里程
 * ****** ****** 档位状态信号 ****** ******
 * SCU_15               CrntGearLvl         实际档位信号
 * ****** ****** 制动系统信号 ****** ******
 * SCU_1                VehSpd              车辆当前实际车速
 * SCU_1                ABSActiveSt         ABS 激活
 * SCU_5                CDDAvailable        CDD 制动可用,制动减速度范围[-5,0]
 * SCU_5                AEBAvailable        AEB 制动可用,制动减速度范围[-10,-5]
 * SCU_5                CDDFail             CDD 制动失效
 * SCU_5                CDDActive           CDD 制动激活
 * SCU_5                AEBActive           AEB 制动激活
 * SCU_5                VehicleStandStillSt 制动系统保压保持车辆静止
 * SCU_8                ActVehLongAccel     纵向加速度+纵向加速度补偿值即为实际加速度
 * SCU_8                VehLongAccelOffset  纵向加速度补偿值
 * ****** ****** 驻车系统状态 ****** ******
 * SCU_9                SysSt               EPB 状态
 * SCU_9                SwitchSt            EPB 开关状态
 * SCU_9                FailSt              EPB 故障状态
*****************/

// ***************** 横向控制 ***************** //
// 发送 ADCU_2
/*****************
 * Message_Name         Signal_Name         Signal_Comment
 * ADCU_2               LatCtrlReq          横向控制请求 
 * ADCU_2               SteerWhlTorqReq     助力扭矩请求
 * ADCU_2               SteerAngReq         方向盘转角请求
*****************/
// 接收
/*****************
 * Message_Name         Signal_Name         Signal_Comment
 * SCU_13               LatCtrlMode         横向控制功能状态
 * SCU_13               LatAutoCheckReport  纵向总控激活条件满足反馈
 * SCU_13               LatQuitReport       横向控制退出反馈
 * SCU_13               StrngWhlIntv        方向盘干预
 * SCU_10               SteeringAngle       方向盘转角
 * SCU_10               SteeringAngleVD     方向盘转角有效
 * SCU_10               SteeringAngleSpd    方向盘转角速度
 * SCU_10               SteeringAngleSpdVD  方向盘转角速度有效
 * SCU_10               StrngWhlTorq        助力扭矩
 * SCU_10               StrngWhlTorqVD      助力扭矩有效
 * SCU_10               WarnLamp            EPS 故障
 * SCU_8                ActVeLaltrlAccel    横向加速度+横向加速度补偿值即为实际加速度
 * SCU_8                VehLaltrlAccelOffset横向加速度补偿值
 * SCU_3                YawRate             Yaw rate+offset 即为实际 yaw rate    
 * SCU_3                YawRateOffset       Yaw rate offset    
*****************/

SCU_CAN_STS can_sts;
ADCU_CAN_CMD can_cmd;

std::mutex mtx_can0_sts;
std::mutex mtx_can0_cmd;


