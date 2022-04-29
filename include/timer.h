#ifndef	_TIMER_H
#define	_TIMER_H

void timer_init( void );
void timer_add_hour( void );
void timer_add_minute( void );
void timer_print( void );
void handle_timer_irq( void );

#endif  /*_TIMER_H */
