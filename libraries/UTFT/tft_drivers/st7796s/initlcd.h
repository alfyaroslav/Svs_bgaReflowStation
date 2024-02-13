case ST7796S:
	//LCD_Write_COM(0x11);//Sleep exit 
	delay(120);
 
	//ST7796S Frame Rate
	LCD_Write_COM(0xF0); 
	LCD_Write_DATA(0xC3);
	LCD_Write_COM(0xF0); 
	LCD_Write_DATA(0x96);
	LCD_Write_COM(0x36); 
	LCD_Write_DATA(0x68); 
	LCD_Write_COM(0x3A); 
	LCD_Write_DATA(0x05);
	LCD_Write_COM(0xB0); 
	LCD_Write_DATA(0x80);
	LCD_Write_COM(0xB6); 
	LCD_Write_DATA(0x20); 
	LCD_Write_DATA(0x22);
	LCD_Write_COM(0xB5); 
	LCD_Write_DATA(0x02);
	LCD_Write_DATA(0x03);
	LCD_Write_DATA(0x00); 
	LCD_Write_DATA(0x04);
	LCD_Write_COM(0xB1); 
	LCD_Write_DATA(0x80);
	LCD_Write_DATA(0x10); 
	LCD_Write_COM(0xB4); 
	LCD_Write_DATA(0x00); 
 
	LCD_Write_COM(0xB7); 
	LCD_Write_DATA(0xC6);
	LCD_Write_COM(0xC5);
	LCD_Write_DATA(0x24);
	LCD_Write_COM(0xE4);
	LCD_Write_DATA(0x31); 
	LCD_Write_COM(0xE8);
	LCD_Write_DATA(0x40);
	LCD_Write_DATA(0x8A);
	LCD_Write_DATA(0x00);
	LCD_Write_DATA(0x00);
	LCD_Write_DATA(0x29);
	LCD_Write_DATA(0x19);
	LCD_Write_DATA(0xA5);
	LCD_Write_DATA(0x33);
	LCD_Write_COM(0xC2); 
	
	LCD_Write_COM(0xA7); 

	LCD_Write_COM(0xE0); 
	LCD_Write_DATA(0xF0);
	LCD_Write_DATA(0x09); 
	LCD_Write_DATA(0x13);
	LCD_Write_DATA(0x12); 
	LCD_Write_DATA(0x12);
	LCD_Write_DATA(0x2B); 
	LCD_Write_DATA(0x3C);
	LCD_Write_DATA(0x44); 
	LCD_Write_DATA(0x4B);
	LCD_Write_DATA(0x1B); 
	LCD_Write_DATA(0x18);
	LCD_Write_DATA(0x17);
	LCD_Write_DATA(0x1D); 
	LCD_Write_DATA(0x21); 
 
    LCD_Write_COM(0xE1); 
	LCD_Write_DATA(0xF0);
	LCD_Write_DATA(0x09); 
	LCD_Write_DATA(0x13);
	LCD_Write_DATA(0x0C); 
	LCD_Write_DATA(0x0D);
	LCD_Write_DATA(0x27); 
	LCD_Write_DATA(0x3B);
	LCD_Write_DATA(0x44); 
	LCD_Write_DATA(0x4D);
	LCD_Write_DATA(0x0B); 
	LCD_Write_DATA(0x17);
	LCD_Write_DATA(0x17); 
	LCD_Write_DATA(0x1D);
	LCD_Write_DATA(0x21); 

	LCD_Write_COM(0x36);
	LCD_Write_DATA(0x08);
	
	LCD_Write_COM(0xF0);
	LCD_Write_DATA(0xC3);
	LCD_Write_COM(0xF0);
	LCD_Write_DATA(0x69);

	LCD_Write_COM(0x13); 
	LCD_Write_COM(0x11); 
	LCD_Write_COM(0x29);//Display on
	break;
