
    //----------------------------|         |         |         |< maximum profile's header lenght
    const char ProfN0[] PROGMEM = "REMOVE CHIP LEADFREE";        // 1 - profile header 30 symbols
    const char ProfN1[] PROGMEM = "REMOVE CHIP LEAD+";           // 2 - profile header 30 symbols
    const char ProfN2[] PROGMEM = "INSTALL CHIP LEADFREE";       // 3 - profile header 30 symbols
    const char ProfN3[] PROGMEM = "INSTALL CHIP LEAD+";          // 4 -profile header 30 symbols
    const char ProfN4[] PROGMEM = "ONLY BOTTOM";                 // 5 - profile header 30 symbols
    const char ProfN5[] PROGMEM = "REMOVE CHIP LEADFREE 6";      // 6 - profile header 30 symbols
    const char ProfN6[] PROGMEM = "REMOVE CHIP LEADFREE 7";      // 7 - profile header 30 symbols
    const char ProfN7[] PROGMEM = "REMOVE CHIP LEADFREE 8";      // 8 - profile header 30 symbols
    const char ProfN8[] PROGMEM = "REMOVE CHIP LEADFREE 9";      // 9 - profile header 30 symbols    
    const char ProfN9[] PROGMEM = "REMOVE CHIP LEAD+ 10";        //10 - profile header 30 symbols
    const char* const AdrProfN[10] PROGMEM ={ ProfN0, ProfN1, ProfN2, ProfN3, ProfN4,  // constant-headers addresses  
                                    ProfN5, ProfN6, ProfN7, ProfN8, ProfN9}; 
// ---------Profile settings constants--------
    const char str_0[] PROGMEM = "BOTTOM";
    const char str_1[] PROGMEM = "TOP";
    const char str_2[] PROGMEM = "PID";
    const char str_3[] PROGMEM = "COMMON";
    const char* const myStr2[4] PROGMEM = {str_0, str_1, str_2, str_3}; // menu's  constant-headers addresses 
    const char stp_1[] PROGMEM = "BOTTOM SIZE";
    const char stp_2[] PROGMEM = "HEATING SPEED";
    const char stp_3[] PROGMEM = "TEMPERATURE";
    const char stp_4[] PROGMEM = "TIME DELAY";
    const char stp_5[] PROGMEM = "POWER MIN";
    const char stp_6[] PROGMEM = "POWER МАХ";
    const char stp_7[] PROGMEM = "PROFILE STEP  < >";
    const char stp_8[] PROGMEM = "HEATING SPEED";				// Hеating speed
    const char stp_9[] PROGMEM = "TRANSITION TIME";
    const char stp_10[] PROGMEM = "TOP PROPORTIONAL";
    const char stp_11[] PROGMEM = "    INTEGRA";
    const char stp_12[] PROGMEM = "    DIFF";
    const char stp_13[] PROGMEM = "BOTT PROPORTIONAL";
    const char stp_14[] PROGMEM = "PROTECT BOTTOM";
    const char stp_15[] PROGMEM = "TOP'S START `";
    const char stp_16[] PROGMEM = "TOP'S POWER"; 
    const char stp_17[] PROGMEM = "PROFILE LOADING";
    const char stp_18[] PROGMEM = "PROFILE'S START `";
    const char stp_19[] PROGMEM = "BOTTOM'S POWER";
    const char* const myStr3[4][6] PROGMEM = {              // menu's constant-notes addresses
      { stp_1, stp_2, stp_3, stp_4, stp_5, stp_6 },
      { stp_7, stp_8, stp_3, stp_9, stp_5, stp_6 },
      { stp_10, stp_11, stp_12, stp_13, stp_11, stp_12 },
      { stp_14, stp_17, stp_15, stp_16, stp_18, stp_19 }
    };
// ---------Messages constants--------
    const char text_0[] PROGMEM = " TOP";
    const char text_1[] PROGMEM = "BOTTOM";
    const char text_2[] PROGMEM = "OK";
    const char text_3[] PROGMEM = "ALL     ";
    const char text_4[] PROGMEM = "FROM    ";
    const char text_5[] PROGMEM = "BOTTOM 1     2     3     4";
    const char text_6[] PROGMEM = " PRELIMINARY BOTTOM HEATING   ";
    const char text_7[] PROGMEM = " BOTTOM HEATER ON    ";
    const char text_8[] PROGMEM = " PRELIMINARY TOP HEATING  ";
    const char text_9[] PROGMEM = " TOP HEATER ON   ";
    const char text_10[] PROGMEM = " ERROR! PROFILE STOPPED     ";    // 
    const char text_11[] PROGMEM = "         PROFILE STOPPED           ";
    const char text_12[] PROGMEM = "BGA REWORK STATION";
            
    const char* const myText[13] PROGMEM = {text_0, text_1, text_2, text_3, text_4,     // constant-messages addresses 
                                    text_5, text_6, text_7, text_8, text_9,
                                    text_10, text_11, text_12};

//        
