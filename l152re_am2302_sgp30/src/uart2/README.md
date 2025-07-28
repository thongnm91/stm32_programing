---

## `void USART2_Init(void)`

**Short list of steps:**

1. Enable USART2 and GPIOA clocks.
2. Set PA2 (TX) and PA3 (RX) to alternate function mode.
3. Configure alternate function registers for USART2.
4. Set baud rate to 9600 (for 32 MHz clock).
5. Enable USART2 transmitter and receiver.
6. Enable USART2 peripheral.

**Reason why it is needed:**
Initializes the USART2 hardware for serial communication, allowing the microcontroller to send and receive data over UART (e.g., to a PC or another device).

---

## `void USART2_write(char data)`

**Short list of steps:**

1. Wait until the USART2 transmit data register is empty.
2. Write the data byte to the USART2 data register.

**Reason why it is needed:**
Sends a single character over the serial port, enabling communication from the microcontroller to a PC or other device via UART.

---
