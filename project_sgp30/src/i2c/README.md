### Short List of Steps in `void I2C1_init(void)`:

1.  Enable GPIOB and I2C1 peripheral clocks.
2.  Configure PB8 and PB9 for I2C alternate function, open-drain, no pull-up.
3.  Reset and release I2C1.
4.  Set I2C1 peripheral clock frequency (CR2).
5.  Set clock control register (CCR) for 100kHz I2C speed.
    * **How to calculate CCR:**
        * $TPCLK1 = 1 / 32 \text{MHz} = 31.25 \text{ns}$
        * $tI2C\_bus = 1 / 100 \text{kHz} = 10 \mu\text{s} = 10000 \text{ns}$
        * $tI2C\_bus\_div2 = 10000 \text{ns} / 2 = 5000 \text{ns}$
        * $\text{CCR value} = tI2C\_bus\_div2 / TPCLK1 = 5000 \text{ns} / 31.25 \text{ns} = 160$
        * (p. 692 of reference)
6.  Set maximum rise time (TRISE).
    * Maximum rise time in SM mode = 1000 ns.
    * Equation: $1000 \text{ns} / TPCLK1 = 1000 \text{ns} / 31.25 \text{ns} = 32$
    * (p. 693 of reference)
7.  Enable I2C1 peripheral.

**Reason why it is needed:**

1.  It initializes the I2C1 hardware for communication, setting up pins, speed, and enabling the peripheral so the microcontroller can use I2C to communicate with external devices.

---

### Short List of Steps in `void I2C1_Write(uint8_t address, uint8_t command, int n, uint8_t* data)`:

1.  Wait until the I2C bus is free.
2.  Clear acknowledge bit.
3.  Generate START condition.
4.  Send slave address (write mode).
5.  Wait for address transmission to complete.
6.  Send command byte.
7.  Send data bytes (loop for n bytes).
8.  Wait for byte transfer to finish.
9.  Generate STOP condition.

**Reason why it is needed:**

It sends a command and data bytes to an I2C slave device, enabling communication and control of peripherals like sensors or EEPROMs.

---

### Short List of Steps in `void I2C1_ByteWrite(uint8_t address, uint8_t command)`:

1.  Wait until the I2C bus is free.
2.  Clear acknowledge bit.
3.  Generate START condition.
4.  Send slave address (write mode).
5.  Wait for address transmission to complete.
6.  Send command byte.
7.  Wait for byte transfer to finish.
8.  Generate STOP condition.

**Reason why it is needed:**

It sends a single command byte to an I2C slave device, useful for simple control operations like starting a conversion or setting a register.

---

### Short List of Steps in `void I2C1_Read(uint8_t address, uint8_t command, int n, uint8_t* data)`:

1.  Wait until the I2C bus is free.
2.  Clear acknowledge bit.
3.  Generate START condition.
4.  Send slave address (write mode).
5.  Wait for address transmission to complete.
6.  Send command byte.
7.  Generate repeated START condition.
8.  Send slave address (read mode).
9.  Enable acknowledge.
10. Read n data bytes from slave into buffer.
11. Generate STOP condition.
12. Disable acknowledge.

**Reason why it is needed:**

It reads multiple bytes from an I2C slave device after sending a command, allowing the microcontroller to receive data such as sensor measurements or memory contents.