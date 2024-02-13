case OTM8009A:
	delay(10);
//************* OTM8009 инициализация **********//	
	//3.97inch OTM8009 Init 20190116
	LCD_WR_REG(0xff00);
	LCD_Write_DATA(0x80);
	LCD_WR_REG(0xff01);
	LCD_Write_DATA(0x09);
	LCD_WR_REG(0xff02);
	LCD_Write_DATA(0x01);

	LCD_WR_REG(0xff80);
	LCD_Write_DATA(0x80);
	LCD_WR_REG(0xff81);
	LCD_Write_DATA(0x09);

	LCD_WR_REG(0xff03);
	LCD_Write_DATA(0x01);

	//add ==========20131216============================//
	LCD_WR_REG(0xf5b6); 
	LCD_Write_DATA(0x06); 
	LCD_WR_REG(0xc480); 
	LCD_Write_DATA(0x30); 
	LCD_WR_REG(0xc48a); 
	LCD_Write_DATA(0x40); 
	//===================================================//
	LCD_WR_REG(0xc0a3);
	LCD_Write_DATA(0x1B);

	//LCD_WR_REG(0xc0ba);  //No
	//LCD_Write_DATA(0x50);

	LCD_WR_REG(0xc0ba); //--> (0xc0b4); // column inversion //  2013.12.16 modify
	LCD_Write_DATA(0x50); 

	LCD_WR_REG(0xc181);
	LCD_Write_DATA(0x66);

	LCD_WR_REG(0xc1a1);
	LCD_Write_DATA(0x0E);

	LCD_WR_REG(0xc481);
	LCD_Write_DATA(0x83);

	LCD_WR_REG(0xc582);
	LCD_Write_DATA(0x83);

	LCD_WR_REG(0xc590);
	LCD_Write_DATA(0x96);

	LCD_WR_REG(0xc591);
	LCD_Write_DATA(0x2B);

	LCD_WR_REG(0xc592);
	LCD_Write_DATA(0x01);


	LCD_WR_REG(0xc594);
	LCD_Write_DATA(0x33);

	LCD_WR_REG(0xc595);
	LCD_Write_DATA(0x34);


	LCD_WR_REG(0xc5b1);
	LCD_Write_DATA(0xa9);

	LCD_WR_REG(0xce80);
	LCD_Write_DATA(0x86);
	LCD_WR_REG(0xce81);
	LCD_Write_DATA(0x01); 
	LCD_WR_REG(0xce82);
	LCD_Write_DATA(0x00); 

	LCD_WR_REG(0xce83);
	LCD_Write_DATA(0x85); 
	LCD_WR_REG(0xce84);
	LCD_Write_DATA(0x01); 
	LCD_WR_REG(0xce85);
	LCD_Write_DATA(0x00);
	LCD_WR_REG(0xce86);
	LCD_Write_DATA(0x00);
	LCD_WR_REG(0xce87);
	LCD_Write_DATA(0x00);
	LCD_WR_REG(0xce88);
	LCD_Write_DATA(0x00);
	LCD_WR_REG(0xce89);
	LCD_Write_DATA(0x00);
	LCD_WR_REG(0xce8A);
	LCD_Write_DATA(0x00);
	LCD_WR_REG(0xce8B);
	LCD_Write_DATA(0x00);

	LCD_WR_REG(0xcea0);// cea1[7:0] : clka1_width[3:0], clka1_shift[11:8]                         
	LCD_Write_DATA(0x18); 
	LCD_WR_REG(0xcea1);// cea2[7:0] : clka1_shift[7:0]                                            
	LCD_Write_DATA(0x04); 
	LCD_WR_REG(0xcea2);// cea3[7:0] : clka1_sw_tg, odd_high, flat_head, flat_tail, switch[11:8]   
	LCD_Write_DATA(0x03); 
	LCD_WR_REG(0xcea3);// cea4[7:0] : clka1_switch[7:0]                                               
	LCD_Write_DATA(0x21); 
	LCD_WR_REG(0xcea4);// cea5[7:0] : clka1_extend[7:0]                                           
	LCD_Write_DATA(0x00); 
	LCD_WR_REG(0xcea5);// cea6[7:0] : clka1_tchop[7:0]                                            
	LCD_Write_DATA(0x00); 
	LCD_WR_REG(0xcea6);// cea7[7:0] : clka1_tglue[7:0]                                            
	LCD_Write_DATA(0x00); 
	LCD_WR_REG(0xcea7);// cea8[7:0] : clka2_width[3:0], clka2_shift[11:8]                         
	LCD_Write_DATA(0x18); 
	LCD_WR_REG(0xcea8);// cea9[7:0] : clka2_shift[7:0]                                            
	LCD_Write_DATA(0x03);
	LCD_WR_REG(0xcea9);// ceaa[7:0] : clka2_sw_tg, odd_high, flat_head, flat_tail, switch[11:8]   
	LCD_Write_DATA(0x03); 
	LCD_WR_REG(0xceaa);// ceab[7:0] : clka2_switch[7:0]                                                
	LCD_Write_DATA(0x22);
	LCD_WR_REG(0xceab);// ceac[7:0] : clka2_extend                                                
	LCD_Write_DATA(0x00); 
	LCD_WR_REG(0xceac);// cead[7:0] : clka2_tchop                                                 
	LCD_Write_DATA(0x00); 
	LCD_WR_REG(0xcead);// ceae[7:0] : clka2_tglue 
	LCD_Write_DATA(0x00);    

	LCD_WR_REG(0xceb0);// ceb1[7:0] : clka3_width[3:0], clka3_shift[11:8]                          
	LCD_Write_DATA(0x18);
	LCD_WR_REG(0xceb1);// ceb2[7:0] : clka3_shift[7:0]                                             
	LCD_Write_DATA(0x02); 
	LCD_WR_REG(0xceb2);// ceb3[7:0] : clka3_sw_tg, odd_high, flat_head, flat_tail, switch[11:8]    
	LCD_Write_DATA(0x03); 
	LCD_WR_REG(0xceb3);// ceb4[7:0] : clka3_switch[7:0]                                               
	LCD_Write_DATA(0x23); 
	LCD_WR_REG(0xceb4);// ceb5[7:0] : clka3_extend[7:0]                                            
	LCD_Write_DATA(0x00); 
	LCD_WR_REG(0xceb5);// ceb6[7:0] : clka3_tchop[7:0]                                             
	LCD_Write_DATA(0x00); 
	LCD_WR_REG(0xceb6);// ceb7[7:0] : clka3_tglue[7:0]                                             
	LCD_Write_DATA(0x00); 
	LCD_WR_REG(0xceb7);// ceb8[7:0] : clka4_width[3:0], clka2_shift[11:8]                          
	LCD_Write_DATA(0x18);
	LCD_WR_REG(0xceb8);// ceb9[7:0] : clka4_shift[7:0]                                             
	LCD_Write_DATA(0x01); 
	LCD_WR_REG(0xceb9);// ceba[7:0] : clka4_sw_tg, odd_high, flat_head, flat_tail, switch[11:8]    
	LCD_Write_DATA(0x03); 
	LCD_WR_REG(0xceba);// cebb[7:0] : clka4_switch[7:0]                                                
	LCD_Write_DATA(0x24); 
	LCD_WR_REG(0xcebb);// cebc[7:0] : clka4_extend                                                 
	LCD_Write_DATA(0x00); 
	LCD_WR_REG(0xcebc);// cebd[7:0] : clka4_tchop                                                  
	LCD_Write_DATA(0x00); 
	LCD_WR_REG(0xcebd);// cebe[7:0] : clka4_tglue                                                  
	LCD_Write_DATA(0x00); 


	LCD_WR_REG(0xcfc0);// cfc1[7:0] : eclk_normal_width[7:0]   
	LCD_Write_DATA(0x01); 
	LCD_WR_REG(0xcfc1);// cfc2[7:0] :eclk_partial_width[7:0]                                       
	LCD_Write_DATA(0x01); 
	LCD_WR_REG(0xcfc2);//cfc3[7:0] : all_normal_tchop[7:0]                                       
	LCD_Write_DATA(0x20); 
	LCD_WR_REG(0xcfc3);// cfc4[7:0] : all_partial_tchop[7:0]                                   
	LCD_Write_DATA(0x20); 
	LCD_WR_REG(0xcfc4);// cfc5[7:0] : eclk1_follow[3:0], eclk2_follow[3:0]                     
	LCD_Write_DATA(0x00); 
	LCD_WR_REG(0xcfc5);// cfc6[7:0] : eclk3_follow[3:0], eclk4_follow[3:0]                    
	LCD_Write_DATA(0x00); 
	LCD_WR_REG(0xcfc6);// cfc7[7:0] : 00, vstmask, vendmask, 00, dir1, dir2 (0=VGL, 1=VGH)      
	LCD_Write_DATA(0x01); 
	LCD_WR_REG(0xcfc7);// cfc8[7:0] : reg_goa_gnd_opt, reg_goa_dpgm_tail_set, reg_goa_f_gating_en, reg_goa_f_odd_gating, toggle_mod1, 2, 3, 4  
	LCD_Write_DATA(0x00);    // GND OPT1 (00-->80  2011/10/28)
	LCD_WR_REG(0xcfc8);// cfc9[7:0] : duty_block[3:0], DGPM[3:0]                                    
	LCD_Write_DATA(0x00); 
	LCD_WR_REG(0xcfc9);// cfca[7:0] : reg_goa_gnd_period[7:0]                                      
	LCD_Write_DATA(0x00);    // Gate PCH (CLK base) (00-->0a  2011/10/28)

	LCD_WR_REG(0xcfd0);// cfd1[7:0] : 0000000, reg_goa_frame_odd_high
	LCD_Write_DATA(0x00); 

	LCD_WR_REG(0xcbc0);//cbc1[7:0] : enmode H-byte of sig1  (pwrof_0, pwrof_1, norm, pwron_4 )    
	LCD_Write_DATA(0x00); 
	LCD_WR_REG(0xcbc1);//cbc2[7:0] : enmode H-byte of sig2  (pwrof_0, pwrof_1, norm, pwron_4 )    
	LCD_Write_DATA(0x04); 
	LCD_WR_REG(0xcbc2);//cbc3[7:0] : enmode H-byte of sig3  (pwrof_0, pwrof_1, norm, pwron_4 )    
	LCD_Write_DATA(0x04); 
	LCD_WR_REG(0xcbc3);//cbc4[7:0] : enmode H-byte of sig4  (pwrof_0, pwrof_1, norm, pwron_4 )    
	LCD_Write_DATA(0x04); 
	LCD_WR_REG(0xcbc4);//cbc5[7:0] : enmode H-byte of sig5  (pwrof_0, pwrof_1, norm, pwron_4 )    
	LCD_Write_DATA(0x04); 
	LCD_WR_REG(0xcbc5);//cbc6[7:0] : enmode H-byte of sig6  (pwrof_0, pwrof_1, norm, pwron_4 )    
	LCD_Write_DATA(0x04); 
	LCD_WR_REG(0xcbc6);//cbc7[7:0] : enmode H-byte of sig7  (pwrof_0, pwrof_1, norm, pwron_4 )    
	LCD_Write_DATA(0x00); 
	LCD_WR_REG(0xcbc7);//cbc8[7:0] : enmode H-byte of sig8  (pwrof_0, pwrof_1, norm, pwron_4 )    
	LCD_Write_DATA(0x00); 
	LCD_WR_REG(0xcbc8);//cbc9[7:0] : enmode H-byte of sig9  (pwrof_0, pwrof_1, norm, pwron_4 )    
	LCD_Write_DATA(0x00); 
	LCD_WR_REG(0xcbc9);//cbca[7:0] : enmode H-byte of sig10 (pwrof_0, pwrof_1, norm, pwron_4 )    
	LCD_Write_DATA(0x00); 
	LCD_WR_REG(0xcbca);//cbcb[7:0] : enmode H-byte of sig11 (pwrof_0, pwrof_1, norm, pwron_4 )    
	LCD_Write_DATA(0x00); 
	LCD_WR_REG(0xcbcb);//cbcc[7:0] : enmode H-byte of sig12 (pwrof_0, pwrof_1, norm, pwron_4 )    
	LCD_Write_DATA(0x00); 
	LCD_WR_REG(0xcbcc);//cbcd[7:0] : enmode H-byte of sig13 (pwrof_0, pwrof_1, norm, pwron_4 )    
	LCD_Write_DATA(0x00); 
	LCD_WR_REG(0xcbcd);//cbce[7:0] : enmode H-byte of sig14 (pwrof_0, pwrof_1, norm, pwron_4 ) 
	LCD_Write_DATA(0x00); 
	LCD_WR_REG(0xcbce);//cbcf[7:0] : enmode H-byte of sig15 (pwrof_0, pwrof_1, norm, pwron_4 )
	LCD_Write_DATA(0x00); 

	LCD_WR_REG(0xcbd0);//cbd1[7:0] : enmode H-byte of sig16 (pwrof_0, pwrof_1, norm, pwron_4 )    
	LCD_Write_DATA(0x00); 
	LCD_WR_REG(0xcbd1);//cbd2[7:0] : enmode H-byte of sig17 (pwrof_0, pwrof_1, norm, pwron_4 )
	LCD_Write_DATA(0x00); 
	LCD_WR_REG(0xcbd2);//cbd3[7:0] : enmode H-byte of sig18 (pwrof_0, pwrof_1, norm, pwron_4 )
	LCD_Write_DATA(0x00); 
	LCD_WR_REG(0xcbd3);//cbd4[7:0] : enmode H-byte of sig19 (pwrof_0, pwrof_1, norm, pwron_4 )
	LCD_Write_DATA(0x00); 
	LCD_WR_REG(0xcbd4);//cbd5[7:0] : enmode H-byte of sig20 (pwrof_0, pwrof_1, norm, pwron_4 )
	LCD_Write_DATA(0x00); 
	LCD_WR_REG(0xcbd5);//cbd6[7:0] : enmode H-byte of sig21 (pwrof_0, pwrof_1, norm, pwron_4 )
	LCD_Write_DATA(0x00); 
	LCD_WR_REG(0xcbd6);//cbd7[7:0] : enmode H-byte of sig22 (pwrof_0, pwrof_1, norm, pwron_4 )
	LCD_Write_DATA(0x04); 
	LCD_WR_REG(0xcbd7);//cbd8[7:0] : enmode H-byte of sig23 (pwrof_0, pwrof_1, norm, pwron_4 )
	LCD_Write_DATA(0x04); 
	LCD_WR_REG(0xcbd8);//cbd9[7:0] : enmode H-byte of sig24 (pwrof_0, pwrof_1, norm, pwron_4 )
	LCD_Write_DATA(0x04); 
	LCD_WR_REG(0xcbd9);//cbda[7:0] : enmode H-byte of sig25 (pwrof_0, pwrof_1, norm, pwron_4 )
	LCD_Write_DATA(0x04); 
	LCD_WR_REG(0xcbda);//cbdb[7:0] : enmode H-byte of sig26 (pwrof_0, pwrof_1, norm, pwron_4 )
	LCD_Write_DATA(0x04); 
	LCD_WR_REG(0xcbdb);//cbdc[7:0] : enmode H-byte of sig27 (pwrof_0, pwrof_1, norm, pwron_4 )
	LCD_Write_DATA(0x00); 
	LCD_WR_REG(0xcbdc);//cbdd[7:0] : enmode H-byte of sig28 (pwrof_0, pwrof_1, norm, pwron_4 )
	LCD_Write_DATA(0x00); 
	LCD_WR_REG(0xcbdd);//cbde[7:0] : enmode H-byte of sig29 (pwrof_0, pwrof_1, norm, pwron_4 )
	LCD_Write_DATA(0x00); 
	LCD_WR_REG(0xcbde);//cbdf[7:0] : enmode H-byte of sig30 (pwrof_0, pwrof_1, norm, pwron_4 )
	LCD_Write_DATA(0x00); 

	LCD_WR_REG(0xcbe0);//cbe1[7:0] : enmode H-byte of sig31 (pwrof_0, pwrof_1, norm, pwron_4 ) 
	LCD_Write_DATA(0x00); 
	LCD_WR_REG(0xcbe1);//cbe2[7:0] : enmode H-byte of sig32 (pwrof_0, pwrof_1, norm, pwron_4 )
	LCD_Write_DATA(0x00); 
	LCD_WR_REG(0xcbe2);//cbe3[7:0] : enmode H-byte of sig33 (pwrof_0, pwrof_1, norm, pwron_4 )
	LCD_Write_DATA(0x00); 
	LCD_WR_REG(0xcbe3);//cbe4[7:0] : enmode H-byte of sig34 (pwrof_0, pwrof_1, norm, pwron_4 )
	LCD_Write_DATA(0x00); 
	LCD_WR_REG(0xcbe4);//cbe5[7:0] : enmode H-byte of sig35 (pwrof_0, pwrof_1, norm, pwron_4 )
	LCD_Write_DATA(0x00); 
	LCD_WR_REG(0xcbe5);//cbe6[7:0] : enmode H-byte of sig36 (pwrof_0, pwrof_1, norm, pwron_4 )
	LCD_Write_DATA(0x00); 
	LCD_WR_REG(0xcbe6);//cbe7[7:0] : enmode H-byte of sig37 (pwrof_0, pwrof_1, norm, pwron_4 )
	LCD_Write_DATA(0x00); 
	LCD_WR_REG(0xcbe7);//cbe8[7:0] : enmode H-byte of sig38 (pwrof_0, pwrof_1, norm, pwron_4 )
	LCD_Write_DATA(0x00); 
	LCD_WR_REG(0xcbe8);//cbe9[7:0] : enmode H-byte of sig39 (pwrof_0, pwrof_1, norm, pwron_4 )
	LCD_Write_DATA(0x00); 
	LCD_WR_REG(0xcbe9);//cbea[7:0] : enmode H-byte of sig40 (pwrof_0, pwrof_1, norm, pwron_4 )
	LCD_Write_DATA(0x00);

	// cc8x   
	LCD_WR_REG(0xcc80);//cc81[7:0] : reg setting for signal01 selection with u2d mode   
	LCD_Write_DATA(0x00); 
	LCD_WR_REG(0xcc81);//cc82[7:0] : reg setting for signal02 selection with u2d mode 
	LCD_Write_DATA(0x26); 
	LCD_WR_REG(0xcc82);//cc83[7:0] : reg setting for signal03 selection with u2d mode 
	LCD_Write_DATA(0x09); 
	LCD_WR_REG(0xcc83);//cc84[7:0] : reg setting for signal04 selection with u2d mode 
	LCD_Write_DATA(0x0B); 
	LCD_WR_REG(0xcc84);//cc85[7:0] : reg setting for signal05 selection with u2d mode 
	LCD_Write_DATA(0x01); 
	LCD_WR_REG(0xcc85);//cc86[7:0] : reg setting for signal06 selection with u2d mode 
	LCD_Write_DATA(0x25); 
	LCD_WR_REG(0xcc86);//cc87[7:0] : reg setting for signal07 selection with u2d mode 
	LCD_Write_DATA(0x00); 
	LCD_WR_REG(0xcc87);//cc88[7:0] : reg setting for signal08 selection with u2d mode 
	LCD_Write_DATA(0x00); 
	LCD_WR_REG(0xcc88);//cc89[7:0] : reg setting for signal09 selection with u2d mode 
	LCD_Write_DATA(0x00); 
	LCD_WR_REG(0xcc89);//cc8a[7:0] : reg setting for signal10 selection with u2d mode 
	LCD_Write_DATA(0x00);  

	// cc9x   
	LCD_WR_REG(0xcc90);//cc91[7:0] : reg setting for signal11 selection with u2d mode   
	LCD_Write_DATA(0x00); 
	LCD_WR_REG(0xcc91);//cc92[7:0] : reg setting for signal12 selection with u2d mode
	LCD_Write_DATA(0x00); 
	LCD_WR_REG(0xcc92);//cc93[7:0] : reg setting for signal13 selection with u2d mode 
	LCD_Write_DATA(0x00); 
	LCD_WR_REG(0xcc93);//cc94[7:0] : reg setting for signal14 selection with u2d mode 
	LCD_Write_DATA(0x00); 
	LCD_WR_REG(0xcc94);//cc95[7:0] : reg setting for signal15 selection with u2d mode 
	LCD_Write_DATA(0x00); 
	LCD_WR_REG(0xcc95);//cc96[7:0] : reg setting for signal16 selection with u2d mode 
	LCD_Write_DATA(0x00); 
	LCD_WR_REG(0xcc96);//cc97[7:0] : reg setting for signal17 selection with u2d mode 
	LCD_Write_DATA(0x00); 
	LCD_WR_REG(0xcc97);//cc98[7:0] : reg setting for signal18 selection with u2d mode 
	LCD_Write_DATA(0x00); 
	LCD_WR_REG(0xcc98);//cc99[7:0] : reg setting for signal19 selection with u2d mode 
	LCD_Write_DATA(0x00); 
	LCD_WR_REG(0xcc99);//cc9a[7:0] : reg setting for signal20 selection with u2d mode 
	LCD_Write_DATA(0x00); 
	LCD_WR_REG(0xcc9a);//cc9b[7:0] : reg setting for signal21 selection with u2d mode 
	LCD_Write_DATA(0x00); 
	LCD_WR_REG(0xcc9b);//cc9c[7:0] : reg setting for signal22 selection with u2d mode 
	LCD_Write_DATA(0x26); 
	LCD_WR_REG(0xcc9c);//cc9d[7:0] : reg setting for signal23 selection with u2d mode 
	LCD_Write_DATA(0x0A); 
	LCD_WR_REG(0xcc9d);//cc9e[7:0] : reg setting for signal24 selection with u2d mode 
	LCD_Write_DATA(0x0C); 
	LCD_WR_REG(0xcc9e);//cc9f[7:0] : reg setting for signal25 selection with u2d mode 
	LCD_Write_DATA(0x02);  
	// ccax   
	LCD_WR_REG(0xcca0);//cca1[7:0] : reg setting for signal26 selection with u2d mode   
	LCD_Write_DATA(0x25); 
	LCD_WR_REG(0xcca1);//cca2[7:0] : reg setting for signal27 selection with u2d mode
	LCD_Write_DATA(0x00); 
	LCD_WR_REG(0xcca2);//cca3[7:0] : reg setting for signal28 selection with u2d mode 
	LCD_Write_DATA(0x00); 
	LCD_WR_REG(0xcca3);//cca4[7:0] : reg setting for signal29 selection with u2d mode 
	LCD_Write_DATA(0x00); 
	LCD_WR_REG(0xcca4);//cca5[7:0] : reg setting for signal20 selection with u2d mode 
	LCD_Write_DATA(0x00); 
	LCD_WR_REG(0xcca5);//cca6[7:0] : reg setting for signal31 selection with u2d mode 
	LCD_Write_DATA(0x00); 
	LCD_WR_REG(0xcca6);//cca7[7:0] : reg setting for signal32 selection with u2d mode 
	LCD_Write_DATA(0x00); 
	LCD_WR_REG(0xcca7);//cca8[7:0] : reg setting for signal33 selection with u2d mode 
	LCD_Write_DATA(0x00); 
	LCD_WR_REG(0xcca8);//cca9[7:0] : reg setting for signal34 selection with u2d mode 
	LCD_Write_DATA(0x00); 
	LCD_WR_REG(0xcca9);//ccaa[7:0] : reg setting for signal35 selection with u2d mode 
	LCD_Write_DATA(0x00); 

  LCD_WR_REG(0x3A00);//ccaa[7:0] : reg setting for signal35 selection with u2d mode 
	LCD_Write_DATA(0x55);//0x55
		
	LCD_WR_REG(0x1100);
	delay(100);
	LCD_WR_REG(0x2900);
	delay(50);
	LCD_WR_REG(0x2C00); 
//  LCD_direction(USE_HORIZONTAL);  //Установите ориентацию ЖК-дисплея
//	LCD_LED=1;					// включкеие подсветки	 
//	LCD_Clear(WHITE);//清全屏白色

	break;
