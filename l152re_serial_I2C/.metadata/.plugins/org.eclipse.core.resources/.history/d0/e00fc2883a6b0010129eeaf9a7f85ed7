### `SetSysClock` Function Steps:

1.  Enable HSI oscillator.
2.  Wait for HSI to stabilize.
3.  If HSI is ready, configure PLL for 32 MHz (HSI * 4 / 2).
4.  Configure Flash for 64-bit access, prefetch, and one wait state.
5.  Enable power interface clock and set voltage scaling to 1.8V.
6.  Wait for voltage regulator to stabilize.
7.  Set AHB and APB prescalers to no division.
8.  Enable PLL and wait for it to be ready.
9.  Switch system clock source to PLL.
10. Wait until PLL is confirmed as system clock.

---

### Short List of Steps in `void SystemCoreClockUpdate(void)`:

1.  Read the current system clock source from `RCC->CFGR`.
2.  If MSI is used, calculate frequency from MSI range.
3.  If HSI is used, set frequency to `HSI_VALUE`.
4.  If HSE is used, set frequency to `HSE_VALUE`.
5.  If PLL is used, read PLL source, multiplier, and divider; calculate frequency.
6.  Apply AHB prescaler to get final HCLK frequency.
7.  Update the global `SystemCoreClock` variable.

**Reason why it is needed:**

1.  It updates the `SystemCoreClock` variable to reflect the actual core clock frequency after any change in clock configuration, ensuring correct timing for peripherals and functions like SysTick.