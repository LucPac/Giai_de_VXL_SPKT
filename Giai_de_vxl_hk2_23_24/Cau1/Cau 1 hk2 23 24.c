#include <16f887.h>
#fuses intrc_io
#use delay(clock=8M)

#define sw pin_b1
#define on pin_b2
#define off pin_b3

int i; 

void main ()
{
   set_tris_b(0x0e);
   output_low(pin_b0);
   while(true)
   {
      if(!input(sw))
      {
         if(!input(on))
         do
         {
             output_high(pin_b0);
             delay_ms(500);
             output_low(pin_b0);
             delay_ms(500);
         }while(input(off));
          output_low(pin_b0);  
      }
      else
      {
         if(!input(on))
         {
            do
            {
               output_high(pin_b0);
            }while(input(off));
             output_low(pin_b0);
         }
      }
   }
}
