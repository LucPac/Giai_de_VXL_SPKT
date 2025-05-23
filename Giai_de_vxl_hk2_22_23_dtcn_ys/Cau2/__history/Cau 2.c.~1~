#include <16f887.h>
#device adc=10
#fuses intrc_io
#use delay (clock=8m)

const unsigned char m7d[16]={0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x90,0x88,0x83,0xc6,0xa1,0x86,0x8e};    
signed int16 temp;

void main ()
{
   set_tris_c(0);
   set_tris_d(0);
   set_tris_e(0x01);
   
   setup_adc(adc_clock_div_32);
   setup_adc_ports(san5|VSS_VDD);
   set_adc_channel (5);
   
   while(true)
   {
      temp = read_adc()*0.4887;
      if(temp < 0)
      {
         output_d(0xff);
         output_c(0xff);
      }
      else if(temp > 99)
      {
         output_d(0xff);
         output_c(0xff);
      }
      else
      {
         output_d(m7d[temp%10]);
         output_c(m7d[temp/10%10]);
      }
   }
}
