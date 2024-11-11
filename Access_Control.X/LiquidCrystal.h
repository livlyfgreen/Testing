#define RS RB0
#define RW RB1
#define EN RB2

void command(char cmd) {
    PORTB = (cmd & 0xF0);
    RS = 0;
    RW = 0;
    EN = 1;
    __delay_ms(5);
    EN = 0;
    
    PORTB = ((cmd << 4) & 0xF0);
    RS = 0;
    RW = 0;
    EN = 1;
    __delay_ms(5);
    EN = 0;
}

void data(char ch) {
    PORTB = (ch & 0xF0);
    RS = 1;
    RW = 0;
    EN = 1;
    __delay_ms(5);
    EN = 0;
    
    PORTB = ((ch << 4) & 0xF0);
    RS = 1;
    RW = 0;
    EN = 1;
    __delay_ms(5);
    EN = 0;
}

void LCD_Print(char *str) {
    while(*str) {
        data(*str);
        str++;
    }
}

void LCD_Init() {
    TRISB = 0x00;
    PORTB = 0x00;
    command(0x02);
    command(0x28);
    command(0x0C);
    command(0x01);
    command(0x80);
}