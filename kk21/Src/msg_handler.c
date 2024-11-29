/**
 ******************************************************************************
 * File Name          : msg_handler.c
 * Description        : This file provides code for the RTOS tasks functions.
 ******************************************************************************
 */
#include "api.h"
#include "err.h"
#include "lwip.h"
#include "mot_x.h"
#include "mot_y.h"
#include "mot_z.h"
#include "movements.h"
#include "new_hran.h"
#include "new_km.h"
#include "outlet.h"
#include "sensors.h"
#include "servo.h"
#include "settings.h"
#include "structs.h"
#include "water.h"

extern volatile _Bool isConn;
extern osThreadId netTaskHandle;
extern State States;
extern Settings Sets;
extern ReadSet outset;

/* USER CODE BEGIN Header_StartDefaultTask */
/**
 * @brief  Function implementing the defaultTask thread.
 * @param  argument: Not used
 * @retval None
 */
/* USER CODE END Header_StartDefaultTask */
void StartDefaultTask(void const *argument) {
    /* init code for LWIP */
    printf("MX_LWIP_Init!\r\n");
    MX_LWIP_Init();
    /* USER CODE BEGIN 5 */
    struct netconn *nc;
    struct netconn *in_nc;
    volatile err_t res;
    char *buffer = pvPortMalloc(2048);
    char *buffer2 = pvPortMalloc(2048);
    /* init code for LWIP */
    printf("Hellow WorlD!\r\n");
    //    go connect to stm
    printf("start new con\n");
    nc = netconn_new(NETCONN_TCP);
    if (nc == NULL) {
        while (1) osDelay(1);
    }
    printf("start bind con\n");
    res = netconn_bind(nc, IP_ADDR_ANY, 81);
    if (res != 0) {
        printf("bind error: %d\r\n", res);
        while (1) osDelay(1);
    }
    printf("start listen con\n");
    res = netconn_listen(nc);
    if (res != 0) {
        printf("listen error: %d\r\n", res);
        while (1) osDelay(1);
    }

    /* Infinite loop */
    for (;;) {
        printf("start accept con\n");
        res = netconn_accept(nc, &in_nc);
        if (res != 0) {
            printf("accept error: %d\r\n", res);
        } else {
            isConn = 1;
            printf("start task con\n");
            osThreadDef(netTask, StartNetTask, osPriorityHigh, 0, 256);
            netTaskHandle = osThreadCreate(osThread(netTask), (void *) in_nc);
        }
    }
    /* USER CODE END 5 */
}

/* USER CODE BEGIN Header_StartNetTask */
/**
 * @brief Function implementing the netTask thread.
 * @param argument: Not used
 * @retval None
 */
/* USER CODE END Header_StartNetTask */

void StartNetTask(void const *argument) {
    /* USER CODE BEGIN StartNetTask */

    printf("Conn: new connection in StartNetTask %d\r\n", isConn);

    struct netconn *nc = (struct netconn *) argument;
    struct netbuf *nb;
    Message msg;
    uint16_t len;
    err_t err;
    enum ErrorCode errCode;

    /* Infinite loop */
    for (;;) {
        err = netconn_recv(nc, &nb);

        // socket err
        if (err != ERR_OK) {
            printf("Conn: closed %d\r\n", err);
            netconn_close(nc);
            netbuf_delete(nb);
            netconn_delete(nc);
            isConn = 0;
            vTaskDelete(NULL);
            break;
        }

        // message length check
        len = netbuf_len(nb);
        ReadSet inset;
        // if (len != sizeof(msg))
        /*------------------------!!! DANGER !!!---------------------------*/
        if (len == sizeof(inset)) {
            netbuf_copy(nb, (char *) (&inset), sizeof(inset));
        } else if (len != sizeof(msg)) {
            printf("Conn: unexpected netbuf length: %d\r\n", len);
            netconn_close(nc);
            netbuf_delete(nb);
            netconn_delete(nc);
            isConn = 0;
            vTaskDelete(NULL);
            break;
        }
        // copy message
        netbuf_copy(nb, (char *) (&msg), sizeof(msg));
        netbuf_delete(nb);

        // unexpected message type
        if (msg.type != 1) {
            printf("Conn: unecpected message type %d\r\n", msg.type);
        }
            // try to perform
        else {
            printf("Conn: command #%d begin\r\n", msg.id);

            // write ack back
            netconn_write(nc, (char *) (&msg), sizeof(msg), NETCONN_COPY);

            errCode = ECUnknownCommand;

            if (msg.id == Unknown) {
                // does nothing, useful for ping command
                errCode = ECOK;
            }

                /* --------------------- PAWN ---------------------*/

            else if (msg.id == PawnCal) {
                errCode = PawnCalibrationCCW();
            } else if (msg.id == DropPawn) {
                errCode = DropPawnFunc();
            }
                /*----------------------HRAN------------------------------------*/
            else if (msg.id == RevolvZOpen) {
                errCode = revolvZOpen();
            } else if (msg.id == RevolvZClose) {
                errCode = revolvZClose();
            } else if (msg.id == RevolvCalibration) {
                errCode = revolvCalibration();
            } else if (msg.id == RevolvZStp) {
                errCode = revolvZStp(msg.arg1);
            }
                /*----------------------------------------------------------*/

            else if (msg.id == MotXSt2) {
                errCode = motXSt2();
            } else if (msg.id == MotXSt1) {
                errCode = motXSt1();
            } else if (msg.id == MotYSt2) {
                errCode = motYSt2();
            } else if (msg.id == MotYSt1) {
                errCode = motYSt1();
            } else if (msg.id == TStFind) {
                errCode = tStFind();
            } else if (msg.id == StaXCal) {
                errCode = staXCal();
            } else if (msg.id == StaYCal) {
                errCode = staYCal();
            } else if (msg.id == StaZCal) {
                errCode = staZCal();
            } else if (msg.id == StaZTDown) {
                errCode = staZTDown();
            } else if (msg.id == StaZTUp) {
                errCode = staZTUp();
            } else if (msg.id == FSpToVe) {
                errCode = fSpToVe();
            } else if (msg.id == MotXStp) {
                // printf("%d",msg.arg1);
                errCode = motXStp(msg.arg1);
            } else if (msg.id == MotYStp) {
                // printf("%d",msg.arg1);
                errCode = motYStp(msg.arg1);
            } else if (msg.id == KarTurn) {
                errCode = karTurn();
            } else if (msg.id == VUpTurn) {
                errCode = vUpTurn();
            } else if (msg.id == VodTurn) {
                errCode = vodTurn();
            } else if (msg.id == VodOpen) {
                errCode = vodOpen();
            } else if (msg.id == VodClos) {
                errCode = vodClos();
            } else if (msg.id == MokTurn) {
                errCode = mokTurn();
            } else if (msg.id == MokFree) {
                errCode = mokFree();
            } else if (msg.id == MokClos) {
                errCode = mokClos();
            } else if (msg.id == MokOslb) {
                errCode = mokOslb();
            } else if (msg.id == MokSetA) {
                errCode = mokSetA();
            } else if (msg.id == PriTest) {
                errCode = priTest();
            } else if (msg.id == PomUSta) {
                errCode = pomUSta();
            } else if (msg.id == PomUSto) {
                errCode = pomUSto();
            } else if (msg.id == PomDSta) {
                errCode = pomDSta();
            } else if (msg.id == PomDSto) {
                errCode = pomDSto();

            } else if (msg.id == ViBOpen) {
                errCode = viBOpen();
            } else if (msg.id == ViBClos) {
                errCode = viBClos();
            } else if (msg.id == ViDOpen) {
                errCode = viDOpen();
            } else if (msg.id == ViDClos) {
                errCode = viDClos();
            } else if (msg.id == ViDOpenNew) {
                errCode = viDOpenNew();
            } else if (msg.id == ViDClosNew) {
                errCode = viDClosNew();
            } else if (msg.id == AlrmSta) {
                errCode = alrmSta();
            } else if (msg.id == AlrmSto) {
                errCode = alrmSto();
            } else if (msg.id == DorLOpe) {
                errCode = dorLOpe();
            } else if (msg.id == DorLClo) {
                errCode = dorLClo();
            } else if (msg.id == DatUdar) {
                errCode = datUdar();
            } else if (msg.id == PriOpen) {
                errCode = priOpen();
            } else if (msg.id == PriClos) {
                errCode = priClos();
            } else if (msg.id == TurnOnn) {
                errCode = turnOnn();
            } else if (msg.id == TurnOff) {
                errCode = turnOff();
                // errCode = kingCalibrAfterHranGet();
            } else if (msg.id == MotXStepTo2) {
                errCode = motXStepTo2();
            } else if (msg.id == MotXStepTo1) {
                errCode = motXStepTo1();
            } else if (msg.id == StaZUpStp) {
                errCode = staZUpStp();
            } else if (msg.id == StaZDownStp) {
                errCode = staZDownStp();
            } else if (msg.id == KaretkaSetAngle) {
                errCode = karetkaSetAngle(msg.arg1);
            } else if (msg.id == FVeToSp) {
                errCode = fVeToSp();
            } else if (msg.id == FSpToPr) {
                errCode = fSpToPr();
            } else if (msg.id == ResetStateFlags) {
                errCode = resetStateFlags();
            } else if (msg.id == LedsOn) {
                errCode = ledsOn();
            } else if (msg.id == LedsOff) {
                errCode = ledsOff();
            } else if (msg.id == KaterShake) {
                errCode = katerShake();
            } else if (msg.id == PriClosNew) {
                errCode = priClosNew();
            }

                // new king
            else if (msg.id == KingLRst) {
                errCode = kingFromSideToSide(1);
            } else if (msg.id == KingRLst) {
                errCode = kingFromSideToSide(0);
            } else if (msg.id == KingLD) {
                errCode = kingFromLeftToPos(Sets.hand_left_to_disp_steps);
            } else if (msg.id == KingDL) {
                errCode = kingFromPosToStop(Sets.hand_left_to_disp_steps, 0);
            } else if (msg.id == KingLW) {
                errCode = kingFromLeftToPos(Sets.hand_left_to_water_steps);
            } else if (msg.id == KingWL) {
                errCode = kingFromPosToStop(Sets.hand_left_to_water_steps, 0);
            } else if (msg.id == KingDR) {
                errCode = kingFromPosToStop(Sets.hand_disp_to_right_steps, 1);
            } else if (msg.id == KingWR) {
                errCode = kingFromPosToStop(Sets.hand_water_to_right_steps, 1);
            } else if (msg.id == KingCal) {
                errCode = kingCalibrateToLeft();
            } else if (msg.id == WriteSettings) {
                if (sizeof(inset.set) == sizeof(Sets)) {
                    errCode = writeSettings(&inset.set);
                } else {
                    errCode = ECInvalidArg;
                    // printf("Conn: readsettings Error");
                }
            }

            if (msg.id == ReadSettings) {
                outset.set = Sets;
                outset.mess.type = 2;  // result type
                outset.mess.id = msg.id;
                outset.mess.arg1 = (int32_t) (errCode);
                outset.mess.arg2 = sizeof(outset.set);
                netconn_write(nc, (char *) (&outset), sizeof(outset), NETCONN_COPY);
            } else {
                // write command result
                msg.type = 2;  // result type
                msg.arg1 = (int32_t) (errCode);
                msg.arg2 = 0;
                netconn_write(nc, (char *) (&msg), sizeof(msg), NETCONN_COPY);
            }
            printf("Conn: command #%d end\r\n", msg.id);
        }
    }

    netconn_close(nc);
    netbuf_delete(nb);
    netconn_delete(nc);
    isConn = 0;
    vTaskDelete(NULL);
    /* USER CODE END StartNetTask */
}
