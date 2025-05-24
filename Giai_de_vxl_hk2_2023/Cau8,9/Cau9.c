/*
Tinh toan PMW: T=0.8(ms), Fosc=8(MHz)
   chon T2_prescale = 16 => PR2 = [(T*Fosc)/(4*T2_prescale)] - 1 = 99
                            HSCK_10% = 10% * HSCK_max = 10% * (99+1)*4 = 40
                            HSCK_20% = 20% * HSCK_max = 20% * (99+1)*4 = 80
                            HSCK_50% = 50% * HSCK_max = 50% * (99+1)*4 = 200
                            HSCK_80% = 80% * HSCK_max = 80% * (99+1)*4 = 320
                            HSCK_100% = 100% * HSCK_max = 100% * (99+1)*4 = 400
*/
#include<16f887.h>
#fuses intrc_io
#use delay(clock=8M)

#define ON_OFF pin_e0
#define SPEED  pin_e1

unsigned int16 duty=0, mode=1;
int1 onoff = 0;

void SPEED_button();
void select_mode();

void ON_OFF_button()
{
   if(input(ON_OFF)==0)
   {
      delay_ms(20);
      if(input(ON_OFF)==0)
      {
         onoff = !onoff;
         while(input(ON_OFF)==0);
      }
   }
   if(onoff==1)
   {
      SPEED_button();
      select_mode();
   }
   else
   {
      duty=0;
      set_pwm1_duty(duty);
   }
}

void SPEED_button()
{
   if(input(SPEED) == 0)
   {
      delay_ms(20);
      if(input(SPEED)==0)
      {
         if(mode<5)  mode++;
         else        mode=1;
         while(input(SPEED) == 0);
      }
   }
}

void select_mode()
{
   if(mode==1) {duty = 40;set_pwm1_duty(duty);}
   else if(mode==2) {duty = 80;set_pwm1_duty(duty);}
   else if(mode==3) {duty = 200;set_pwm1_duty(duty);}
   else if(mode==4) {duty = 320;set_pwm1_duty(duty);}
   else if(mode==5) {duty = 400;set_pwm1_duty(duty);}
}

void main()
{
   set_tris_c(0);
   set_tris_e(0xff);
   
   setup_timer_2(T2_DIV_BY_16,99,1);
   
   setup_ccp1(CCP_PWM);
   set_pwm1_duty(duty);  

   while(true)
   {
      ON_OFF_button();
   }
}


