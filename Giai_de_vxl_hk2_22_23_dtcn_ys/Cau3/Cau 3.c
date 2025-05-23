#include <16f887.h>
#fuses hs
#use delay(clock=16M)

#define lcd_rs       pin_e0
#define lcd_rw       pin_e1
#define lcd_e        pin_e2
#define output_lcd   output_d
#include <tv_lcd.c>

unsigned int16 sp=0, box=1975;

void main ()
{
   set_tris_d(0);
   set_tris_e(0); 
   set_tris_a(0xff);
   
   lcd_setup();
   
   setup_timer_0(t0_ext_l_to_h | t0_div_1);
   set_timer0(0);
   
   while(true)
   {
      sp = get_timer0();
      if(sp>12)   {set_timer0(1); sp=1; box++;}
      lcd_command(0x80);
      printf(lcd_data, "Product=%02lu ",sp);
      lcd_command(0xc0);
      printf(lcd_data, "Box=%05lu",box);
   }
}
