/*
 * Copyright (c) 2018 Alibaba Group. All rights reserved.
 * License-Identifier: Apache-2.0
 *
 * Licensed under the Apache License, Version 2.0 (the "License"); you may
 * not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *    http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */

#include <string.h>
#include <stdlib.h>
#include "utilities.h"
#include "at_cmd.h"
#include "bsp_uart.h"
#include "usart.h"

#define ATCMD_SIZE   160
#define ATQUERY_SIZE 128

#define LWAN_SUCCESS      (0)
#define AT_ERRNO_NOSUPP   (1)
#define AT_ERRNO_NOALLOW  (2)
#define AT_ERRNO_PARA_VAL (5)
#define AT_ERRNO_PARA_NUM (6)
#define AT_ERRNO_SYS      (8)
#define AT_CB_PRINT       (0xFF)

#define LORAWAN_APP_DATA_MAX_SIZE                   (242)

//static char atcmd[ATCMD_SIZE];
//static uint16_t atcmd_index = 0;
static char g_at_query_buf[ATQUERY_SIZE];

typedef struct atcmd_s {
    const char *cmd_name;
    const char *test_cmd_str;
    int (*query_cmd)(void);
    int (*exec_cmd)(char *str);
    int (*exec_cmd_no_para)(void);
} atcmd_t;

static uint16_t FREQ_MOVE=22;

void set_freq_move(uint16_t freq_move)
{
    FREQ_MOVE=freq_move;
};

uint16_t get_freq_move(void)
{
    return FREQ_MOVE;
};

static int hex2bin(const char *hex, uint8_t *bin, uint16_t bin_length)
{
    uint16_t hex_length = strlen(hex);
    const char *hex_end    = hex + hex_length;
    uint8_t *cur        = bin;
    uint8_t num_chars  = hex_length & 1;
    uint8_t byte       = 0;

    if (hex_length % 2 != 0) {
        return -1;
    }

    if (hex_length / 2 > bin_length) {
        return -1;
    }

    while (hex < hex_end) {
        if ('A' <= *hex && *hex <= 'F') {
            byte |= 10 + (*hex - 'A');
        } else if ('a' <= *hex && *hex <= 'f') {
            byte |= 10 + (*hex - 'a');
        } else if ('0' <= *hex && *hex <= '9') {
            byte |= *hex - '0';
        } else {
            return -1;
        }
        hex++;
        num_chars++;

        if (num_chars >= 2) {
            num_chars = 0;
            *cur++    = byte;
            byte      = 0;
        } else {
            byte <<= 4;
        }
    }
    return cur - bin;
}

void para_cmd(char *ptr,int *argc,char *argv[])
{
    char *str;
    int cnt=0;
    str = strstr((char *)ptr, ",");
    if (str == NULL)
    {
        argv[cnt++] = ptr;
    }
    else
    {
        while(str) {
            argv[cnt++] = ptr;
            *str = '\0';
            ptr = str + 1;
            str = strstr((char *)ptr, ",");
        }
            argv[cnt++] = ptr;
    }
    *argc=cnt;
}


#ifdef CONFIG_ASR650X_TEST_DISABLE

static int at_freq_cmove(char *str)
{
    int ret;
    uint16_t freq_move;
    char *param;
    param = strtok(str, ",");
    freq_move = strtol(param, NULL, 0);
    set_freq_move(freq_move);
    printf("%d\r\n",freq_move);
    return 0;
}

static int at_ctxcw_func(char *str)
{
    int ret = AT_ERRNO_PARA_VAL;
    int argc;
    char *argv[5];

    para_cmd(str,&argc,argv);

    if(argc < 1) return AT_ERRNO_PARA_VAL;
//    if(LoRaTestTxcw(argc,argv)) {
//        ret = LWAN_SUCCESS;
//    }
    return ret;
}

static int at_crx_func(char *str)
{
    int ret = AT_ERRNO_PARA_VAL;
    int argc;
    char *argv[5];

    para_cmd(str,&argc,argv);

    if(argc < 2) return AT_ERRNO_PARA_VAL;
//    if(LoRaTestRx(argc,argv)) {
//        ret = LWAN_SUCCESS;
//    }

    return ret;
}

static int at_ctx_func(char *str)
{
    int ret = AT_ERRNO_PARA_VAL;
    int argc;
    char *argv[16];

    para_cmd(str,&argc,argv);

    if(argc < 3) return AT_ERRNO_PARA_VAL;
//    if(LoRaTestTx(argc,argv)) {
//        ret = LWAN_SUCCESS;
//    }

    return ret;
}

// static int at_csleep_func(char *str)
// {
//     int ret = AT_ERRNO_PARA_VAL;
//     int argc;
//     char *argv[5];

//     para_cmd(str,&argc,argv);

//     if(argc < 1) return AT_ERRNO_PARA_VAL;
//     if(LoRaTestSleep(argc,argv)) {
//         ret = LWAN_SUCCESS;
//     }

//     return ret;
// }

// static int at_cmcu_func(char *str)
// {
//     int ret = AT_ERRNO_PARA_VAL;
//     int argc;
//     char *argv[5];

//     para_cmd(str,&argc,argv);

//     if(argc < 1) return AT_ERRNO_PARA_VAL;
//     if(LoRaTestMcu(argc,argv)) {
//         ret = LWAN_SUCCESS;
//     }

//     return ret;
// }

// static int at_crxs_func(char *str)
// {
//     int ret = AT_ERRNO_PARA_VAL;
//     int argc;
//     char *argv[5];

//     para_cmd(str,&argc,argv);
//     if(argc < 2) return AT_ERRNO_PARA_VAL;
//     if(LoRaTestRxs(argc,argv)) {
//         ret = LWAN_SUCCESS;
//     }

//     return ret;
// }

// static int at_cstdby_func(char *str)
// {
//     int ret = AT_ERRNO_PARA_VAL;
//     int argc;
//     char *argv[5];

//     para_cmd(str,&argc,argv);
//     if(argc < 1) return AT_ERRNO_PARA_VAL;
//     if(LoRaTestStdby(argc,argv)) {
//         ret = LWAN_SUCCESS;
//     }
//     return ret;
// }
#endif

static int at_exec_ireboot(char *str)
{
    int8_t mode = strtol(str, NULL, 0);

    if (mode != 0 && mode != 1) {
        return AT_ERRNO_PARA_VAL;
    }

    NVIC_SystemReset( );
    return 0;
}

static atcmd_t g_at_cmd_list[] = {
    #ifdef CONFIG_ASR650X_TEST_DISABLE
    {LORA_AT_CTXCW,NULL, NULL, at_ctxcw_func, NULL},
    {LORA_AT_CRX,NULL, NULL, at_crx_func, NULL},
    {LORA_AT_CTX,NULL, NULL, at_ctx_func, NULL},
    {LORA_AT_CFM,NULL, NULL, at_freq_cmove, NULL},
    // {LORA_AT_CMCU,NULL, NULL,  at_cmcu_func, NULL},
    // {LORA_AT_CSTDBY,NULL, NULL,  at_cstdby_func, NULL},
    // {LORA_AT_CRXS,NULL, NULL, at_crxs_func, NULL},
    // {LORA_AT_CSLEEP,NULL, NULL, at_csleep_func, NULL},
    #endif
	{ LORA_AT_IREBOOT, "OK", NULL, at_exec_ireboot, NULL }
};

void lorawan_at_process(void)
{
    uint8_t i;
    int ret = 0;
    const char *cmd_name;
    USART_RECEIVETYPE *ucQueueMsgValue;
    char *atcmd;
    char *rxcmd;
    int16_t tmp;
    uint16_t rxcmd_index;
    printf("aaaaaaa....\r\n");
    while(1)
    {
        xQueueReceive(xRS232SendQueue3,(USART_RECEIVETYPE *)&ucQueueMsgValue,(TickType_t)portMAX_DELAY); //portMAX_DELAY
        if(ucQueueMsgValue->rx_len==1)
            HAL_UART_Receive_DMA(&huart1,ucQueueMsgValue->usartDMA_rxBuf,RECEIVELEN);
        atcmd=(char *)ucQueueMsgValue->usartDMA_rxBuf;
        rxcmd = atcmd + 2;
        tmp = ucQueueMsgValue->rx_len - 2;
        if(atcmd[ucQueueMsgValue->rx_len-1] == '\n' && atcmd[ucQueueMsgValue->rx_len-2] == '\r')
        {
            rxcmd_index = tmp;
            for (i = 0; i < sizeof(g_at_cmd_list) / sizeof(atcmd_t); i++) {
                cmd_name = g_at_cmd_list[i].cmd_name;
                if (strncmp(rxcmd, cmd_name, strlen(cmd_name)) != 0) {
                    continue;
                }

                if (rxcmd_index == (strlen(cmd_name) + 2) &&
                    strcmp(&rxcmd[strlen(cmd_name)], "=?") == 0) {
                    /* test cmd */
                    if (g_at_cmd_list[i].test_cmd_str) {
                        if (strncmp(g_at_cmd_list[i].test_cmd_str, "OK", 2) == 0) {
                            snprintf(atcmd, ATCMD_SIZE, "\r\nOK\r\n");
                        } else {
                            snprintf(atcmd, ATCMD_SIZE, "\r\n%s:\"%s\"\r\nOK\r\n",
                                    cmd_name, g_at_cmd_list[i].test_cmd_str);
                        }
                    } else {
                        snprintf(atcmd, ATCMD_SIZE, "\r\n%s\r\nOK\r\n", cmd_name);
                    }
                } else if (rxcmd_index == (strlen(cmd_name) + 1) &&
                        rxcmd[strlen(cmd_name)] == '?') {
                    /* query cmd */
                    if (g_at_cmd_list[i].query_cmd != NULL) {
                        ret = g_at_cmd_list[i].query_cmd();

                        if (ret == 0) {
                            snprintf(atcmd, ATCMD_SIZE, "\r\n%s:%s\r\nOK\r\n",
                                    cmd_name, g_at_query_buf);
                        }
                    } else {
                        ret = AT_ERRNO_NOALLOW;
                    }
                } else if (rxcmd_index > (strlen(cmd_name) + 1) &&
                        rxcmd[strlen(cmd_name)] == '=') {
                    /* exec cmd */
                    if (g_at_cmd_list[i].exec_cmd != NULL) {
                        ret = g_at_cmd_list[i].exec_cmd(rxcmd + strlen(cmd_name) + 1);
                        if (ret == 0) {
                            snprintf(atcmd, ATCMD_SIZE, "\r\nOK\r\n");
                        } else if (ret == -1) {
                            ret = AT_ERRNO_SYS;
                        }
                    } else {
                        ret = AT_ERRNO_NOALLOW;
                    }
                } else if (rxcmd_index == strlen(cmd_name)) {
                    /* exec cmd without parameter*/
                    if (g_at_cmd_list[i].exec_cmd_no_para != NULL) {
                        ret = g_at_cmd_list[i].exec_cmd_no_para();
                        if (ret == 0) {
                            snprintf(atcmd, ATCMD_SIZE, "\r\nOK\r\n");
                        } else if (ret == -1) {
                            ret = AT_ERRNO_SYS;
                        }
                    } else {
                        ret = AT_ERRNO_NOALLOW;
                    }
                }
                break;
            }

            if (i == sizeof(g_at_cmd_list) / sizeof(atcmd_t)) {
                ret = AT_ERRNO_NOSUPP;
            }

            if (ret != 0 && ret != AT_CB_PRINT) {
                snprintf(atcmd, ATCMD_SIZE, "\r\n%s%x\r\n", AT_ERROR, ret);
            }

            if (ret != AT_CB_PRINT) {
                LORA_AT_PRINTF(atcmd);
            }
        }
        //atcmd_index = 0;
        memset(atcmd, 0, ucQueueMsgValue->rx_len);
        ucQueueMsgValue->receive_flag=0;
    }
}

// this can be in irq context
#if 0
void lorawan_at_serial_input(uint8_t cmd)
{
    if ((cmd >= '0' && cmd <= '9') || (cmd >= 'a' && cmd <= 'z') ||
        (cmd >= 'A' && cmd <= 'Z') || cmd == '?' || cmd == '+' || cmd == ':' ||
        cmd == '=' || cmd == ' ' || cmd == ',') {
        atcmd[atcmd_index++] = cmd;
    } else if (cmd == '\r' || cmd == '\n') {
        atcmd[atcmd_index] = '\0';
    }
    //  atcmd[atcmd_index++] = cmd;
    //  if (atcmd_index>1 && atcmd[atcmd_index-1] == '\r' || cmd == '\n')
    //  {
    //      rec_flag=1;
    //      atcmd[atcmd_index]=0;
    //  }

     if (atcmd_index > ATCMD_SIZE) {
         atcmd_index = 0;
         rec_flag=0;
     }
}
void lorawan_at_init(void)
{
    atcmd_index = 0;
    memset(atcmd, 0xff, ATCMD_SIZE);
}

#endif
