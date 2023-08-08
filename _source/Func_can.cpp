#include "Func_can.hpp"


bool CANbus_init()
{
    //  1.打开CAN通道
    if(!VCI_OpenDevice(4, 0, 0))
    {
        std::cout << "failed to open CAN" << std::endl;
        return false;
    }

    //  2.配置CAN信息
    VCI_INIT_CONFIG config;
    config.Mode = 0;                    //1为只读
    config.Filter = 1;
    config.AccCode = 0;
    UINT gBand = 0x1c00;                //波特率500K
    config.Timing1 = gBand >> 8;
    config.AccMask = 0xffffffff;        //全部接收
    config.Timing0 = gBand & 0xff;
     
    //  3.初始化CAN信息
    if(!VCI_InitCAN(VCI_USBCAN2, 0/*ID*/, 0/*CAN0*/, &config))  //初始化一个USBCANII，ID是第一个（插了两个U转CAN另一个就是1）的CAN0通道
    {
        std::cout << "failed to init CAN" << std::endl;
        return false;
    }

    //  4.开始CAN通信
    if(!VCI_StartCAN(VCI_USBCAN2, 0, 0))  //开始CAN通信 ID为0 的CAN0通道
    {
        std::cout << "CAN communication failure" << std::endl;
        return false;
    }
    return true;
}

void CAN_recv_msg()
{
    double sign_num = 0.;
    while(1)
    {
        VCI_CAN_OBJ data[200];
		DWORD nbytes = 0;
		nbytes = VCI_Receive(4, 0, 0, data, 200, 20);

        if(nbytes == 0xFFFFFFFF)
		{
			std::cout << "CAN0 Recv Error"<<std::endl;
			return;
        }

        mtx_can0_sts.lock();
		for(int i = 0; i < nbytes; i++)	
		{
			switch(data[i].ID)
			{
                case SCU_1:
                    can_sts.VehSpd = 0.05625 * ((data[i].Data[5] & 0xff) | ((data[i].Data[4] & 0x1f) << 8));
                    can_sts.ABSActiveSt = (data[i].Data[0] >> 1) & 0x01;
                    break;
                case SCU_3:
                    can_sts.YawRate = (data[i].Data[0] >> 4) & 0x01;
                    can_sts.YawRateOffset = 0.0009765625 * ((data[i].Data[3] & 0xff) | ((data[i].Data[2] & 0x0f) << 8)) - 0.13;
                    break;
                case SCU_5:
                    can_sts.CDDAvailable = (data[i].Data[4] >> 7) & 0x01;
                    can_sts.AEBAvailable = (data[i].Data[4] >> 3) & 0x01;
                    can_sts.CDDFail = (data[i].Data[5] >> 7) & 0x01;
                    can_sts.CDDActive = (data[i].Data[4] >> 6) & 0x01;
                    can_sts.AEBActive = (data[i].Data[4] >> 2) & 0x01;
                    can_sts.VehicleStandStillSt = (data[i].Data[5] >> 1) & 0x03;
                    break;
                case SCU_8:
                    can_sts.ActVehLongAccel = 0.027126736 * (((data[i].Data[1] >> 4) & 0x0f) | ((data[i].Data[4] & 0xff) << 4)) - 21.593;
                    can_sts.VehLongAccelOffset = 0.027126736 * ((data[i].Data[2] & 0xff) | ((data[i].Data[1] & 0x0f) << 8)) - 21.593;
                    can_sts.ActVeLaltrlAccel = 0.027126736 * (((data[i].Data[4] >> 4) & 0x0f) | ((data[i].Data[3] & 0xff) << 4)) - 21.593;
                    can_sts.VehLaltrlAccelOffset = 0.027126736 * ((data[i].Data[5] & 0xff) | ((data[i].Data[4] & 0x0f) << 8)) - 21.593;
                    break;
                case SCU_9:
                    can_sts.SysSt = data[i].Data[1] & 0x07;
                    can_sts.SwitchSt = data[i].Data[0] & 0x03;
                    can_sts.FailSt = (data[i].Data[5] >> 7) & 0x01;
                    break;
                case SCU_10:
                    can_sts.SteeringAngle = 0.1 * (((data[i].Data[1] & 0xff) << 8) | (data[i].Data[2] & 0xff)) - 780;
                    can_sts.SteeringAngleVD = (data[i].Data[4] >> 3) & 0x01;
                    can_sts.SteeringAngleSpd = 4 * (((data[i].Data[4] >> 6) & 0x03) | ((data[i].Data[3] << 2) & 0x7c));
                    can_sts.SteeringAngleSpdVD = (data[i].Data[0] >> 7) & 0x01;
                    can_sts.StrngWhlTorq = 0.1 * (data[i].Data[5] & 0xff) - 12.7;
                    can_sts.StrngWhlTorqVD = data[i].Data[0] & 0x01;
                    can_sts.WarnLamp = (data[i].Data[0] >> 1) & 0x01;
                    break;
                case SCU_13:
                    can_sts.LngCtrlMode = data[i].Data[0] & 0x03;
                    can_sts.LngAutoCheckReport = (data[i].Data[4] << 8) | (data[i].Data[5] & 0xff);
                    can_sts.LngQuitReport = (data[i].Data[1] << 8) | (data[i].Data[2] & 0xff);
                    can_sts.GearLeverIntv = (data[i].Data[0] >> 6) & 0x01;
                    can_sts.LatCtrlMode = (data[i].Data[0] >> 2) & 0x03;
                    can_sts.LatAutoCheckReport = (data[i].Data[6] >> 4) & 0x0f;
                    can_sts.LatQuitReport = data[i].Data[3] & 0xff;
                    can_sts.StrngWhlIntv = (data[i].Data[0] >> 7) & 0x01;
                    break;
                case SCU_14:
                    can_sts.VehRdySt = (data[i].Data[1] >> 2) & 0x01;
                    can_sts.VehDrvMod = (data[i].Data[1] >> 3) & 0x07;
                    can_sts.VehRng = (data[i].Data[0] << 8) | (data[i].Data[1] >> 6);
                    break;
                case SCU_15:
                    can_sts.CrntGearLvl = (data[i].Data[1] >> 4) & 0x07;
                    break;
                case SCU_16:
                    can_sts.ActVehWheelTorq = ((data[i].Data[4] << 8) & 0xff) | ((data[i].Data[5] >> 2) & 0x3f);
                    break;
                case SCU_17:
                    can_sts.VehWheelTorqMax = (((data[i].Data[1] >> 2) & 0x3f) | (data[i].Data[0] & 0xff));
                    can_sts.GasPedalAcPst = 0.392 * (data[i].Data[5] & 0xff);
                    can_sts.AccElecECFail = (data[i].Data[4] >> 6) & 0x01;
                    break;
                case SCU_18:
                    can_sts.BrkPedalSt = (data[i].Data[6] >> 5) & 0x01;
                    break;
            }
        }
        mtx_can0_sts.unlock();
		usleep(20*1000);	
    }    
}


void CAN_send_msg()
{
    while(1)
    {
        mtx_can0_cmd.unlock();
        ADCU_CAN_CMD can_cmd_tmp;
		can_cmd_tmp = can_cmd;
		mtx_can0_cmd.unlock();

        VCI_CAN_OBJ send_data[2];

        // 纵向控制
		send_data[0].ID = ADCU_1;
		send_data[0].TimeFlag = 1;
		send_data[0].SendType = 0;
		send_data[0].RemoteFlag = 0;
		send_data[0].ExternFlag = 0;
		send_data[0].DataLen = 8;
        
        int a = (can_cmd_tmp.BrakeReq + 16) / 0.0004882;
        send_data[0].Data[0] = (a >> 8) & 0xff;
        send_data[0].Data[1] = a & 0xff;
        a = can_cmd_tmp.AutoTrqWhlReq + 5000;
        send_data[0].Data[2] = (a >> 8) & 0xff;
        send_data[0].Data[3] = ((a << 2) & 0xfc) | can_cmd_tmp.LngCtrlReq;
        send_data[0].Data[4] = (can_cmd_tmp.GearLvlReq << 5) | (can_cmd_tmp.GearLvlReqVD << 4);

        // 横向控制
        send_data[1].ID = ADCU_2;
		send_data[1].TimeFlag = 1;
		send_data[1].SendType = 0;
		send_data[1].RemoteFlag = 0;
		send_data[1].ExternFlag = 0;
		send_data[1].DataLen = 8;

        a = (can_cmd_tmp.SteerAngReq + 780) / 0.1;
        send_data[1].Data[0] = (a >> 8) & 0xff;
        send_data[1].Data[1] = a & 0xff;
        // a = (can_cmd_tmp.SteerAngSpdLimt + 0) / 0.125;
        // send_data[1].Data[2] = (a >> 8) & 0xff;
        // send_data[1].Data[3] = a & 0xff;
        a = (can_cmd_tmp.SteerWhlTorqReq + 10.24) / 0.01;
        send_data[1].Data[4] = (a >> 3) & 0xff;
        send_data[1].Data[5] = 0x00 | (a << 5) | (can_cmd_tmp.LatCtrlReq << 3);


        DWORD nbytes = VCI_Transmit(4, 0, 0, send_data, 1);
        if(nbytes != 1)
			std::cout << "A CAN frame was not completely sent!" << std::endl;

        usleep(20*1000);
    }
}