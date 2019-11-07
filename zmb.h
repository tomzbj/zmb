#ifndef _ZMB_H
#define _ZMB_H

#define ZMB_CHECK_FRAME_TOO_SHORT -1
#define ZMB_CHECK_FRAME_NOT_START_WITH_COLON -2
#define ZMB_CHECK_LRC_CHECK_FAILED -3
#define ZMB_CHECK_ADDRESS_MISMATCH -4
#define ZMB_CHECK_CRC_CHECK_FAILED -5
#define ZMB_CHECK_OK 0

#define ZMB_EXCEPTION_ILLEGAL_FUNCTION 1
// Function code received in the query is not recognized or allowed by slave
#define ZMB_EXCEPTION_ILLEGAL_DATA_ADDRESS 2
// Data address not allowed or do not exist in slave 
#define ZMB_EXCEPTION_ILLEGAL_DATA_VALUE 3
// Value is not accepted by slave
#define ZMB_EXCEPTION_SLAVE_DEVICE_FAILURE 4
// Unrecoverable error occurred 
#define ZMB_EXCEPTION_ACKNOWLEDGE 5
// Slave has accepted request but a long duration of time is required. 
#define ZMB_EXCEPTION_SLAVE_DEVICE_BUSY 6
// Slave is engaged in processing a long-duration command. Retry later.
// Slave cannot perform the programming functions.
#define ZMB_EXCEPTION_NEGATIVE_ACKNOWLEDGE 7
// Master should request diagnostic or error information from slave.
#define ZMB_EXCEPTION_MEMORY_PARITY_ERROR 8
// Slave detected a parity error in memory. Master can retry the request.
#define ZMB_EXCEPTION_GATEWAY_PATH_UNAVAILABLE 10
// Specialized for Modbus gateways. Indicates a misconfigured gateway
#define ZMB_EXCEPTION_GATEWAY_TARGET_DEVICE_FAILED_TO_RESPOND 11
// Specialized for Modbus gateways. Sent when slave fails to respond
#define ZMB_EXCEPTION_OK 0

void ZMB_Init(unsigned short* regs, int n_regs, unsigned char addr);
void ZMB_Parse(const void* msg, int size, void (*write_f)(const void*, int));
int ZMB_IntegrityCheck(const void* msg, int size);
void ZMB_WriteReg(int regid, int val);
unsigned short ZMB_ReadReg(int regid);

#endif
