#include <avr/io.h>
#include <util/delay.h>

#define LED PB0
#define BUZZER PB2
#define BUTTON3 PB3 // For 3 minutes
#define BUTTON5 PB4 // For 5 minutes

#define THREE_MINUTES_IN_SECONDS 180
#define FIVE_MINUTES_IN_SECONDS  300

int main(void)
{
  DDRB |= 1 << LED | 1 << BUZZER; // Outputs declarations.
  PORTB |= 1 << LED;              // Switch on the LED.
  PORTB &= ~(1 << BUZZER);        // Switch off the buzzer.

  DDRB &= ~(1 << BUTTON3 | 1 << BUTTON5); // Inputs declarations.
  PORTB |= (1 << BUTTON3 | 1 << BUTTON5); // Pull up for inputs.

  // Number of seconds for the timer to buzz.
  int g_timer = 0;

  // Give enough time to enable pull ups.
  _delay_ms(100);

  while(1) {

    // Button for 3 minutes pressed?
    if(!(PINB & (1 << BUTTON3))) {
      _delay_ms(10); // Useful?
      g_timer = THREE_MINUTES_IN_SECONDS;
      break;
    }

    // Button for 5 minutes pressed?
    if(!(PINB & (1 << BUTTON5))) {
      _delay_ms(10); // Useful?
      g_timer = FIVE_MINUTES_IN_SECONDS;
      break;
    }
  }

  // Each cycle is approximately 1 second, but this is not really
  // accurate.
  while(g_timer > 0) {
    PORTB ^= 1 << LED; // LED off cause it was set up to on.
    _delay_ms(500);
    PORTB ^= 1 << LED; // LED on.
    _delay_ms(500);
    g_timer--;
  }

  // Now it's time to bip and blink forever.
  while(1) {

    int i;

    for(i = 0; i < 3; i++) {
      PORTB |= 1 << BUZZER;
      _delay_ms(100);
      PORTB &= ~(1 << BUZZER);
      _delay_ms(100);
    }

    for(i = 0; i < 3; i++) {
      PORTB |= 1 << LED;
      _delay_ms(100);
      PORTB &= ~(1 << LED);
      _delay_ms(100);
    }
  }
}
