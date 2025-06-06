#include<16f887.h>
#fuses intrc_io
#use delay(clock=8M)

const unsigned int8 m7d[10]={0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x90};
unsigned int8 i=0;

void main()
{
   set_tris_b(0);
   set_tris_d(0);
   
   while(true)
   {
      for(i=0;i<100;i++)
      {
         //hang don vi
         output_b(m7d[0]);
         output_low(pin_d0);
         delay_ms(1);
         output_high(pin_d0);
         
         //hang chuc
         output_b(m7d[1]);
         output_low(pin_d1);
         delay_ms(1);
         output_high(pin_d1); 
         
         //hang tram
         output_b(m7d[1]);
         output_low(pin_d2);
         delay_ms(1);
         output_high(pin_d2); 
      }
   }
}
