#include <16f887.h>
#fuses intrc_io
#use delay(clock=8M)

#define SW pin_e0
#define BT pin_b7
#define L1 pin_c0

int mode = 0;
void button()
{
   if(input(SW) == 1)    
   {
      mode = 0;
   }
   else if(input(SW) == 0)
   {
      if(input(BT) == 0)
      {
         delay_ms(20);
         if(input(BT) == 0)
         {
            mode = 1;
         }
      }while(input(BT) == 0);
   } 
}

void sel_mode()
{
   if(mode == 0)
   {
      output_low(L1);
   }
   else if(mode == 1)
   {
      output_toggle(L1);
      delay_ms(100);
   }
}

void main()
{
   set_tris_c(0);
   set_tris_b(0xff);
   set_tris_e(0xff);
   
   output_low(L1);
   
   while(true)
   {
      button();
      sel_mode();
   }
}
