// -------------------------------------
void Set_Pin_6675() {  //define pin modes
  pinMode(thermoCS_T, OUTPUT);  //digitalWrite(thermoCS_T, HIGH);
  pinMode(thermoCS_B, OUTPUT);  //digitalWrite(thermoCS_B, HIGH);
  pinMode(thermoDO, INPUT);
  pinMode(thermoCLK, OUTPUT);   //digitalWrite(thermoCLK, LOW);
}
double ReadCelsius(int CLK, int iCS, int DO) {
  int d = 0;
  digitalWrite(iCS, LOW);  //delay(100); 
  asm volatile (" nop"  "\n\t" );
  for (int8_t i=15; i >= 0; i--) {
    digitalWrite(CLK, HIGH);    //delay(1);
    asm volatile ( " nop"  "\n\t" );//    d = (d << 1) | digitalRead(iDO);  
    if ( digitalRead(DO))   d |= (1 << i);
    digitalWrite(CLK, LOW);
    asm volatile ( " nop"  "\n\t" );    //delay(1);
    }
  digitalWrite(iCS, HIGH);
  if (d & 0x4) return(-100);     //return -100;
    else  return ((d >> 3) * 0.25);
}
