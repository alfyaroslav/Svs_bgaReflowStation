#ifdef SetEncoder 
Cl_do_btn_long Btn_ok(BTN_OK);
// Введены два новых параметра, которые могут принимать два значения 0 или 1
#define Rotate 1  // направление вращения
#define I_Type 1  // тип энкодера
// если энкодер ведет себя неправильно - смените тип энкодера
// 
RotaryEncoder encoder(Enc_Clk, Enc_DT, Rotate, I_Type);   // пины подключения энкодера
#endif

static byte LastPos = 2;
byte K_Pos;
int NewPos, Pos_Mem;