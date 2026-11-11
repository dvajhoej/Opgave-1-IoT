
/**
 * @file main.c
 * @author dvajhoej
 * @date 2026-11-10
 * @brief LED blink med Timer1 og bogstavkonvertering med UART0
 */

#define F_CPU 16000000UL

#include <avr/interrupt.h>
#include <avr/io.h>

// Opsætning af Timer1
void timer1_init(void) {
  // Nulstiller timerens indstillinger og tæller
  TCCR1A = 0;
  TCCR1B = 0;
  TCNT1 = 0;

  // Timeren skal give interrupt hvert 500 ms
  OCR1A = 31249;

  // CTC mode, så timeren starter forfra
  TCCR1B |= (1 << WGM12);

  // Sætter prescaler til 256
  TCCR1B |= (1 << CS12);

  // Aktiverer interrupt for Timer1
  TIMSK1 |= (1 << OCIE1A);
}

// Opsætning af UART0
void uart0_init(void) {
  // Indstiller baudrate til 9600 ved 16 MHz
  UCSR0A = 0;
  UBRR0H = 0;
  UBRR0L = 103;

  // Gør det muligt at modtage og sende tegn
  // Aktiverer også interrupt ved modtagelse
  UCSR0B = (1 << RXEN0) | (1 << TXEN0) | (1 << RXCIE0);

  // 8 databits, ingen paritet og 1 stopbit
  UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);
}

// Bliver kørt hver gang Timer1 giver interrupt
ISR(TIMER1_COMPA_vect) {
  // Skifter LED mellem tændt og slukket
  PORTB ^= (1 << PB0);
}

// Bliver kørt når UART0 modtager et tegn
ISR(USART0_RX_vect) {
  // Gemmer det modtagne tegn
  char c = UDR0;

  // Hvis det er et stort bogstav, laves det til et lille
  if (c >= 'A' && c <= 'Z') {
    c += ('a' - 'A');
  }
  // Hvis det er et lille bogstav, laves det til et stort
  else if (c >= 'a' && c <= 'z') {
    c -= ('a' - 'A');
  }

  // Venter til UART er klar til at sende
  while (!(UCSR0A & (1 << UDRE0))) {
  }

  // Sender tegnet tilbage til PC'en
  UDR0 = c;
}

int main(void) {
  // Sætter PB0 som output til LED'en
  DDRB |= (1 << PB0);

  // Starter opsætningen af timer og UART
  timer1_init();
  uart0_init();

  // Aktiverer interrupts
  sei();

  // Programmet kører videre, mens interrupts klarer opgaverne
  while (1) {
  }

  return 0;
}
