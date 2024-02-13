//byte Tt0, Tt1, Tt2, Tt3, Tt4, Tt5;
//byte Ot0, Ot1, Ot2, Ot3, Ot4, Ot5;

byte Tb0, Tb1, Tb2, Tb3, Tb4, Tb5;
byte Ob0, Ob1, Ob2, Ob3, Ob4, Ob5;
              
bool Gvard_If() {              
   // Tt5=Tt4; Tt4=Tt3; Tt3=Tt2; Tt2=Tt1; Tt1=Tt0;
   // Tt0 = Input1;
   // Ot5=Ot4; Ot4=Ot3; Ot3=Ot2; Ot2=Ot1; Ot1=Ot0;
   // Ot0 = Output1;
    if (Input2 < 50) return (false);  // если температура низа меньше 50 гр защита не работает
    Tb5=Tb4; Tb4=Tb3; Tb3=Tb2; Tb2=Tb1; Tb1=Tb0; 
    Tb0 = Input2;
    Ob5=Ob4; Ob4=Ob3; Ob3=Ob2; Ob2=Ob1; Ob1=Ob0;
    Ob0 = Output2;
    if (Tb5>=Tb4 && Tb4>=Tb3 && Tb3>=Tb2 && Tb2>=Tb1 && Tb1>=Tb0 &&
         Ob5<=Ob4 && Ob4<=Ob3 && Ob3<=Ob2 && Ob2<=Ob1 && Ob1<=Ob0 && Ob0==bottomMaxPwr) {
       return (true); 
       }
     return (false); 
}
