void lcd_command(int8 a)
{
      output_low(lcd_rw);
      output_low(lcd_rs);
      output_lcd(a);
      output_high(lcd_e);
      output_low(lcd_e);
      delay_us(200);
}
void lcd_data(int8 a)
{
      output_low(lcd_rw);
      output_high(lcd_rs);
      output_lcd(a);
      output_high(lcd_e);
      output_low(lcd_e);
      delay_us(200);
}
void lcd_setup()
{
      lcd_command(0x38); delay_ms(5);
      lcd_command(0x0c); 
      lcd_command(0x01); delay_ms(2);
}
