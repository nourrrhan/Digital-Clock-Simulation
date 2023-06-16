// digital clock with alarm
#include <mega16.h>
#include <delay.h>

unsigned char hours, min, sec;  // for current time

int on = 0;  // flag sound on or off
unsigned char alarm_hours = 0, alarm_minutes = 1; // set alarm


int dec2bcd(int decimal)
{
    // convert decimal number to binary
   return (((decimal / 10) << 4) | (decimal % 10));
} 

void main(void)                                           
{
    DDRD=0xFF; // output hours
    DDRC=0xFF; // output minutes
    DDRB=0xFF; // output seconds
    
    
    DDRA.0=0; // input button to close alarm
    PORTA.0=1; // pull up button    
    DDRA.7=1;  // output sound for alarm
    PORTA.7=0; // turn off sound

while (1)
    {
         for(hours = 0; hours < 24; hours++)
         {
            PORTD = dec2bcd(hours);    // output hour in 7 segamnt
                                    
            for(min = 0; min < 60; min++)
            {
                PORTC = dec2bcd(min);  // output minutes in 7 segmant
                                        
                // if current time = alarm time and sound is off
                if(hours == alarm_hours && min == alarm_minutes && on == 0)
                {
                    PORTA.7=1;   // sound on
                    on = 1;     // flag sound on
                }
                                        
                for(sec = 0; sec < 60; sec++)
                {
                    PORTB = dec2bcd(sec); // output seconds in 7 segmant 
                    delay_ms(100);     // delay for 1 second     
                                            
                    if(PINA.0 == 0)  // when button is pushed
                    {
                        PORTA.7=0;  // sound off
                    }
                } 
                                        
                if(min != alarm_minutes)  //  if current minute != alarm minute
                {   
                    PORTA.7=0;  // sound off
                    on = 0;    // flag sound off
                }
            }
         }
    }
}
