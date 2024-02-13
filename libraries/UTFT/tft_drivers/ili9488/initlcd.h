case ILI9488:

  LCD_Write_COM(0xE0); // Positive Gamma Control
    LCD_Write_DATA(0x00);
    LCD_Write_DATA(0x03);
    LCD_Write_DATA(0x09);
    LCD_Write_DATA(0x08);
    LCD_Write_DATA(0x16);
    LCD_Write_DATA(0x0A);
    LCD_Write_DATA(0x3F);
    LCD_Write_DATA(0x78);
    LCD_Write_DATA(0x4C);
    LCD_Write_DATA(0x09);
    LCD_Write_DATA(0x0A);
    LCD_Write_DATA(0x08);
    LCD_Write_DATA(0x16);
    LCD_Write_DATA(0x1A);
    LCD_Write_DATA(0x0F);

    LCD_Write_COM(0XE1); // Negative Gamma Control
    LCD_Write_DATA(0x00);
    LCD_Write_DATA(0x16);
    LCD_Write_DATA(0x19);
    LCD_Write_DATA(0x03);
    LCD_Write_DATA(0x0F);
    LCD_Write_DATA(0x05);
    LCD_Write_DATA(0x32);
    LCD_Write_DATA(0x45);
    LCD_Write_DATA(0x46);
    LCD_Write_DATA(0x04);
    LCD_Write_DATA(0x0E);
    LCD_Write_DATA(0x0D);
    LCD_Write_DATA(0x35);
    LCD_Write_DATA(0x37);
    LCD_Write_DATA(0x0F);

    LCD_Write_COM(0XC0); // Power Control 1
    LCD_Write_DATA(0x17);
    LCD_Write_DATA(0x15);

    LCD_Write_COM(0xC1); // Power Control 2
    LCD_Write_DATA(0x41);

    LCD_Write_COM(0xC5); // VCOM Control
    LCD_Write_DATA(0x00);
    LCD_Write_DATA(0x12);
    LCD_Write_DATA(0x80);

    LCD_Write_COM(0x36); // Memory Access Control
    LCD_Write_DATA(0x48);          // MX, BGR

    LCD_Write_COM(0x3A); // Pixel Interface Format

    LCD_Write_DATA(0x66);  // 18 bit colour for SPI

    LCD_Write_COM(0xB0); // Interface Mode Control
    LCD_Write_DATA(0x00);

    LCD_Write_COM(0xB1); // Frame Rate Control
    LCD_Write_DATA(0xA0);

    LCD_Write_COM(0xB4); // Display Inversion Control
    LCD_Write_DATA(0x02);

    LCD_Write_COM(0xB6); // Display Function Control
    LCD_Write_DATA(0x02);
    LCD_Write_DATA(0x02);
    LCD_Write_DATA(0x3B);

    LCD_Write_COM(0xB7); // Entry Mode Set
    LCD_Write_DATA(0xC6);

    LCD_Write_COM(0xF7); // Adjust Control 3
    LCD_Write_DATA(0xA9);
    LCD_Write_DATA(0x51);
    LCD_Write_DATA(0x2C);
    LCD_Write_DATA(0x82);

    LCD_Write_COM(0x11);  //Exit Sleep
    delay(120);

    LCD_Write_COM(0x29);  //Display on
    delay(25);

	break;
