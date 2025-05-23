#include<16f887.h>
#fuses intrc_io
#use delay(clock=8M)

#define SW pin_b0
#define BT pin_b1

int1 led;

void main()
{
   set_tris_b(0xff);
   set_tris_d(1);
   
   output_d(0);//moi bat nguon led tat
   
   while(true)
   {
      //switch
      if(input(SW)==1)
      {
         output_d(0);
      }
      else if(input(SW)==0)
      {         
         //button
         if(input(BT)==0)
         {
            delay_ms(20);
            if(input(BT)==0)
            {
               led = !led;
               output_d(led);
               while(input(BT)==0);
            }
         }
      }
   }
}
