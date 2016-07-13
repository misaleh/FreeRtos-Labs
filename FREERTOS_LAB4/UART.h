#ifndef UART_H
#define UART_H
#define TERMINATE_STRING '\r'
#define UART_LCRH_WLEN_8        0x00000060  // 8 bits
#define UART_LCRH_FEN           0x00000010  // UART Enable FIFOs
#define UART_CTL_UARTEN         0x00000001  // UART Enable
#define UART_FR_TXFE            0x00000080  // UART Transmit FIFO Empty
#define UART_FR_RXFF            0x00000040  // UART Receive FIFO Full
#define UART_FR_TXFF            0x00000020  // UART Transmit FIFO Full
#define UART_FR_RXFE            0x00000010  // UART Receive FIFO Empty
#define UART_FR_BUSY            0x00000008  // UART Busy
#define UART_FR_CTS             0x00000001  // Clear To Send
#define SYSCTL_RCGC2_GPIOA      0x00000001  // Port A Clock Gating Control
#define SYSCTL_RCGC1_UART0      0x00000001  // UART0 Clock Gating Control
#define UART0_Println()   UART0_SendString( "\r\n")
void UART0_Init(int,int);
void UART0_SendString(char *);
void UART0_SendInt(int);
void UART0_SendChr(char);
char UART0_ReadChr(void);
void UART0_ReadString(char*);
#endif
