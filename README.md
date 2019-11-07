# zmb
A very simple modbus slave library.

把之前某设备里的modbus库整理了一下, 硬件相关的部分抽象出来, 方便将来在其他设备上使用.

目前只实现了04功能(读取数据寄存器), 将来再添加.

## 开发环境
arm-none-eabi-gcc 4.9.3, STM32F072CB.

## 使用方法
把zmb.h和zmb.c两个文件加入工程. 使用前先用ZMB_Init初始化, 需要提供寄存器的缓冲区, 寄存器数量和从机地址:
```
#define NUM_OF_REGS 32
static unsigned short regs[NUM_OF_REGS];    
ZMB_Init(regs, NUM_OF_REGS, device_addr);
```

之后在串口通讯接收处理部分, 先检查modbus数据帧完整性:

```
if(ZMB_IntegrityCheck((unsigned char*)msg, size) == ZMB_CHECK_OK) {
    frame_type = FRAME_TYPE_MODBUS;
}
```

然后调用ZMB_Parse即可, 需要提供向串口输出数据的回调函数, 这样在同时使用多个串口时也能分别向不同串口输出.

```
void uwrite_usb(const void* msg, int size)
{
    USART_WriteData(USART_USB, msg, size);
}

void uwrite_485(const void* msg, int size)
{
    USART_WriteData(USART_485, msg, size);
}
...
    if(USARTx == USART_485)
        ZMB_Parse(msg, size, uwrite_485);
    else
        ZMB_Parse(msg, size, uwrite_usb);
    break;
```

ZMB_IntegrityCheck和ZMB_Parse会自动根据msg首字节是否为':'来判断是ASCII帧还是二进制帧. 

不过这种方式有个缺点, 当二进制帧的首字节正好是0x3A(其实就是':')时, 会被当作ASCII帧, 然后会判断为帧格式不正确. 好在0x3A=58, 一般也不至于在485总线上挂这么多从设备. 以后再改吧.

ZMB_WriteReg和ZMB_ReadReg用于程序中读写Modbus寄存器. 目前只有ZMB_WriteReg有用.
