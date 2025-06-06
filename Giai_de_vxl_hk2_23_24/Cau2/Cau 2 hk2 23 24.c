#include <16f887.h>
#fuses intrc_io
#use delay(clock=8M)

#define run_pause    pin_b0

const unsigned int8 m7d[10]={0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x90};
unsigned int16 count=0;
int1 mode=0;

void phim_run_pause()
{
   if(input(run_pause)==0)
   {
      delay_ms(20);
      if(input(run_pause)==0)
      {
         mode =~ mode;
         while(input(run_pause)==0); // cho nha phim
      }
   }
}

void trangthai()
{
   if(mode==1)
   {
      output_d(m7d[count]);
      count++;
      delay_ms(1000);
      if(count>9) count=0;
   }
   else
   {
      count=count;
      output_d(m7d[count]);
   }
}

void main()
{
   set_tris_d(0x00);
   set_tris_b(0x01);
   
   output_d(m7d[0]);
   
   while(true)
   {
      phim_run_pause();
      trangthai();
   }
}

