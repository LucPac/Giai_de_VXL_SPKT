/*
SS = (Vref+ - Vref-)/(2^n - 1) = 4.887 mV

PR2 = [(T*Fosc)/(4*T2_prescale)] - 1 = 249
HSCK_max = (PR2 + 1)*4 = 1000
HSCK_25% = 25%*HSCK_max = 250
HSCK_50% = 50%*HSCK_max = 500
HSCK_75% = 75%*HSCK_max = 750
*/
#include<16f887.h>
#device adc=10
#fuses hs
#use delay(clock=20M)
#use RS232 (baud =9600,xmit=pin_c6, rcv=pin_c7)

#define BTA0   pin_b0
#define BTA1   pin_b1
#define BTA2   pin_b2
#define BTA3   pin_b3

const unsigned int8 m7d[10]={0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x90};
unsigned int16 temp, i, sum_temp, counter, counter_chuc, counter_dvi, rcv_data;

void do_nhiet_do()
{
   sum_temp=0;
   for(i=0;i<10;i++)//do nhiet do trung binh 10 lan
   {
      sum_temp = sum_temp + read_adc()*0.4887;
      delay_ms(1);
   }
   temp = sum_temp/10;
   
   output_d(m7d[temp/1%10]);
   output_low(pin_c3);
   delay_ms(1);
   output_high(pin_c3);
   
   output_d(m7d[temp/10%10]);
   output_low(pin_c2);
   delay_ms(1);
   output_high(pin_c2);
}

void dem_san_pham()
{
   counter = get_timer0();
   if(counter>99)    set_timer0(0);
   
   counter_chuc = m7d[counter/10%10];
   counter_dvi = m7d[counter/1%10];
   if(counter_chuc == 0xc0)   counter_chuc = 0xff;
   
   output_d(counter_dvi);
   output_low(pin_c1);
   delay_ms(1);
   output_high(pin_c1);
   
   output_d(counter_chuc);
   output_low(pin_c0);
   delay_ms(1);
   output_high(pin_c0);
}

void nut_nhan()
{
   if(input(BTA0) == 0)    putc(0xA0);
   if(input(BTA1) == 0)    putc(0xA1);
   if(input(BTA2) == 0)    putc(0xA2);
   if(input(BTA3) == 0)    putc(0xA3);
}

void main()
{
   set_tris_c(0x80);
   set_tris_d(0);
   set_tris_a(0xff);
   set_tris_b(0xff);
   
   setup_adc(adc_clock_div_32);
   setup_adc_ports(san0 | vss_vdd);
   
   setup_timer_0(T0_EXT_H_TO_L | T0_DIV_1);
   set_timer0(0);
   
   enable_interrupts(global);
   enable_interrupts(int_rda);
   
   while(true)
   {
      do_nhiet_do();
      dem_san_pham();
      nut_nhan();
   }
}

#int_rda
void rcv_data_interrupt()
{
   rcv_data = getc();
   if(rcv_data==0xBB) set_timer0(0); 
}

