/*
SS = (Vref+ - Vref-)/(2^n - 1) = 4.887 mV

PR2 = [(T*Fosc)/(4*T2_prescale)] - 1 = 249
HSCK_max = (PR2 + 1)*4 = 1000
HSCK_25% = 25%*HSCK_max = 250
HSCK_50% = 50%*HSCK_max = 500
HSCK_75% = 75%*HSCK_max = 750
*/
#include<16f887.h>
#fuses hs
#use delay(clock=20M)
#use rs232 (baud=9600, xmit=pin_c6, rcv=pin_c7)

#define BTB    pin_e1

const unsigned int8 m7d[10]={0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x90};
unsigned int16 bdt=0, giay=0, duty=0, rcv_data;

void dem_giay()
{
   if(bdt == 10)
   {
      bdt=0;
      if(giay < 59)  giay++;
      else           giay = 0;
   }
   
   output_d(m7d[giay/1%10]);
   output_b(m7d[giay/10%10]);
}

#int_timer1
void interrupts_timer1()
{
   bdt++;
   set_timer1(3036);
}

void nut_nhan()
{
   if(input(BTB) == 0)  putc(0xBB);
}

void main()
{
   set_tris_c(0x80);
   set_tris_b(0);
   set_tris_d(0);
   set_tris_e(0xff);
   
   setup_timer_1(t1_internal | t1_div_by_8);
   set_timer1(3036);
   
   enable_interrupts(global);
   enable_interrupts(int_timer1);
   enable_interrupts(int_rda);
   
   setup_timer_2(t2_div_by_16, 249, 1);
   setup_ccp1(CCP_PWM);
   set_pwm1_duty(duty);
   
   while(true)
   {
      dem_giay();
      nut_nhan();
   }
}

#int_rda
void rcv_data_interrupt()
{
   rcv_data = getc();
   if(rcv_data == 0xA0)    duty=0;
   if(rcv_data == 0xA1)    duty=250;
   if(rcv_data == 0xA2)    duty=500;
   if(rcv_data == 0xA3)    duty=750;
   
   set_pwm1_duty(duty);
}

