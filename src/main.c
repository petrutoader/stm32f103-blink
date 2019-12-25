#include <errno.h>
#include <stdio.h>
#include <inttypes.h>
#include <unistd.h>

#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/gpio.h>
#include <libopencm3/stm32/usart.h>
#include <libopencm3/cm3/systick.h>

void sys_tick_handler(void);
ssize_t _write(int file, const char *ptr, ssize_t len);

uint32_t millis(void);

static void usart_setup(void);
static void clock_setup(void);
void uart_puts(char *string);
void uart_putln(char *string);
void delay(uint32_t duration);

static volatile uint32_t _millis = 0;

int _write(int file, const char *ptr, ssize_t len) {
  if (file != STDOUT_FILENO && file != STDERR_FILENO) {
    errno = EIO;
    return -1;
  }

  int i;
  for (i = 0; i < len; i++) {
    if (ptr[i] == '\n') {
      usart_send_blocking(USART2, '\r');
    }
    usart_send_blocking(USART2, ptr[i]);
  }
  return i;
}


static void systick_setup(void) {
  // Set the systick clock source to our main clock
  systick_set_clocksource(STK_CSR_CLKSOURCE_AHB);
  // Clear the Current Value Register so that we start at 0
  STK_CVR = 0;
  // In order to trigger an interrupt every millisecond, we can set the reload
  // value to be the speed of the processor / 1000 - 1
  systick_set_reload(rcc_ahb_frequency / 1000 - 1);
  // Enable interrupts from the system tick clock
  systick_interrupt_enable();
  // Enable the system tick counter
  systick_counter_enable();
}

void sys_tick_handler(void) {
  // Increment our monotonic clock
  _millis++;
}

uint32_t millis(void) {
  return _millis;
}

void delay(uint32_t duration) {
  const uint32_t until = millis() + duration;
  while (millis() < until);
}

static void usart_setup(void) {
  gpio_set_mode(GPIOA, GPIO_MODE_OUTPUT_2_MHZ, GPIO_CNF_OUTPUT_ALTFN_PUSHPULL, GPIO_USART2_TX);

	usart_set_baudrate(USART2, 115200);
	usart_set_databits(USART2, 8);
	usart_set_stopbits(USART2, USART_STOPBITS_1);
	usart_set_mode(USART2, USART_MODE_TX);
	usart_set_parity(USART2, USART_PARITY_NONE);
	usart_set_flow_control(USART2, USART_FLOWCONTROL_NONE);

	usart_enable(USART2);
}

static void clock_setup(void) {
  rcc_clock_setup_in_hsi_out_64mhz();

  rcc_periph_clock_enable(RCC_GPIOA);
  rcc_periph_clock_enable(RCC_USART2);
}

void uart_puts(char *string) {
  while (*string) {
    usart_send_blocking(USART2, *string);
    string++;
  }
}

void uart_putln(char *string) {
  uart_puts(string);
  uart_puts("\r\n");
}

int main(void) {
  clock_setup();
  usart_setup();

  systick_setup();

  gpio_set_mode(GPIOA, GPIO_MODE_OUTPUT_2_MHZ, GPIO_CNF_OUTPUT_PUSHPULL, GPIO5);

  while (true) {
		printf("[%ld] LED on\n", millis());
    gpio_set(GPIOA, GPIO5);
    delay(1000);
		printf("[%ld] LED off\n", millis());
    gpio_clear(GPIOA, GPIO5);
    delay(1000);
  }

  return 0;
}
