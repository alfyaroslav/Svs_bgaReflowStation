 
    //----------------------------|         |         |         |< максимальная длинна заголовка профиля
    const char ProfN0[] PROGMEM = "СНЯТИЕ ЧИПА БЕССВИНЕЦ";       // 1 - заголовок профиля 30 символов
    const char ProfN1[] PROGMEM = "СНЯТИЕ ЧИПА СВИНЕЦ";          // 2 - заголовок профиля 30 символов
    const char ProfN2[] PROGMEM = "УСТАНОВКА ЧИПА БЕССВИНЕЦ";    // 3 - заголовок профиля 30 символов
    const char ProfN3[] PROGMEM = "УСТАНОВКА ЧИПА СВИНЕЦ";       // 4 - заголовок профиля 30 символов
    const char ProfN4[] PROGMEM = "НИЖНИЙ ПОДОГРЕВ";             // 5 - заголовок профиля 30 символов
    const char ProfN5[] PROGMEM = "СНЯТИЕ ЧИПА БЕССВИНЕЦ 6";     // 6 - заголовок профиля 30 символов
    const char ProfN6[] PROGMEM = "СНЯТИЕ ЧИПА БЕССВИНЕЦ 7";     // 7 - заголовок профиля 30 символов
    const char ProfN7[] PROGMEM = "СНЯТИЕ ЧИПА БЕССВИНЕЦ 8";     // 8 - заголовок профиля 30 символов
    const char ProfN8[] PROGMEM = "СНЯТИЕ ЧИПА БЕССВИНЕЦ 9";     // 9 - заголовок профиля 30 символов     
    const char ProfN9[] PROGMEM = "СНЯТИЕ ЧИПА СВИНЕЦ 10";       //10 - заголовок профиля 30 символов  
    const char* const AdrProfN[10] PROGMEM ={ ProfN0, ProfN1, ProfN2, ProfN3, ProfN4,  // адреса констант-заголовков  
                                    ProfN5, ProfN6, ProfN7, ProfN8, ProfN9}; 
    
// ---------Константы настройки профиля--------
    const char str_0[] PROGMEM = "НИЖНИЙ";
    const char str_1[] PROGMEM = "ВЕРХ";
    const char str_2[] PROGMEM = "ПИД";
    const char str_3[] PROGMEM = "ОБЩИЕ";
    const char* const myStr2[4] PROGMEM = {str_0, str_1, str_2, str_3}; // адреса констант-заголовков меню
    const char stp_1[] PROGMEM = "РАЗМЕР НИЗА";
    const char stp_2[] PROGMEM = "СК-ТЬ НАГРЕВА";
    const char stp_3[] PROGMEM = "ТЕМПЕРАТУРА";
    const char stp_4[] PROGMEM = "ВРЕМЯ ЗАДЕРЖКИ";
    const char stp_5[] PROGMEM = "МОЩНОСТЬ МИН";
    const char stp_6[] PROGMEM = "МОЩНОСТЬ МАХ";
    const char stp_7[] PROGMEM = "ШАГ ПРОФИЛЯ  < >";
    const char stp_8[] PROGMEM = "СК-ТЬ НАГРЕВА";
    const char stp_9[] PROGMEM = "ВРЕМЯ ПЕРЕХОДА";
    const char stp_10[] PROGMEM = "ВЕРХ ПРОПОРЦИОНАЛ";
    const char stp_11[] PROGMEM = "    ИНТЕГРАЛ";
    const char stp_12[] PROGMEM = "    ДИФФЕРЕНЦИАЛ";
    const char stp_13[] PROGMEM = "НИЗ ПРОПОРЦИОНАЛ";
    const char stp_14[] PROGMEM = "ЗАЩИТА НИЗ        ";
    const char stp_15[] PROGMEM = "Т` СТАРТА ВЕРХА";
    const char stp_16[] PROGMEM = "МОЩНОСТЬ ВЕРХА";
    const char stp_17[] PROGMEM = "ЗАГРУЗКА ПРОФИЛЯ";
    const char stp_18[] PROGMEM = "Т` СТАРТА ПРОФИЛЯ";
    const char stp_19[] PROGMEM = "МОЩНОСТЬ НИЗА";
    const char* const myStr3[4][6] PROGMEM = {              // адреса констант-надписей меню
      { stp_1, stp_2, stp_3, stp_4, stp_5, stp_6 },
      { stp_7, stp_8, stp_3, stp_9, stp_5, stp_6 },
      { stp_10, stp_11, stp_12, stp_13, stp_11, stp_12 },
      { stp_14, stp_17, stp_15, stp_16, stp_18, stp_19 }
    };
// ---------Константы сообщений--------
    const char text_0[] PROGMEM = " ВЕРХ";
    const char text_1[] PROGMEM = "НИЗ ";
    const char text_2[] PROGMEM = "ОК ";
    const char text_3[] PROGMEM = "ВСЕХ   ";
    const char text_4[] PROGMEM = "ИЗ       ";
    const char text_5[] PROGMEM = " НИЗ   1     2     3     4 ";
    const char text_6[] PROGMEM = " ПРЕДВАРИТЕЛЬНЫЙ НАГРЕВ НИЗА  ";
    const char text_7[] PROGMEM = " НИЖНИЙ НАГРЕВАТЕЛЬ ВКЛЮЧЕН   ";
    const char text_8[] PROGMEM = " ПРЕДВАРИТЕЛЬНЫЙ НАГРЕВ ВЕРХА    ";
    const char text_9[] PROGMEM = " ВЕРХНИЙ НАГРЕВАТЕЛЬ ВКЛЮЧЕН   ";
    const char text_10[] PROGMEM = " АВАРИЯ! СТОП ПРОФИЛЯ     ";
    const char text_11[] PROGMEM = "         СТОП ПРОФИЛЯ           ";
    const char text_12[] PROGMEM = "ПАЯЛЬНАЯ СТАНЦИЯ BGA";

            
    const char* const myText[13] PROGMEM = {text_0, text_1, text_2, text_3, text_4,     // адреса констант-сообщений 
                                    text_5, text_6, text_7, text_8, text_9,
                                    text_10, text_11, text_12};

//        
