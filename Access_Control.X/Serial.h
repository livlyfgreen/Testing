void serialInit() {
    TRISC = 1 << 7;
    PORTC = 0x00;
    TXSTA = 0x24;
    RCSTA = 0x90;
    SPBRG = 25;
}

void serialRead(char *str) {
    int i;
    for(i = 0; ; i++) {
        while(!RCIF);
        str[i] = RCREG;
        if(str[i] == '\r' || str[i] == '\n') {
            str[i] = '\0'; //or try str[i+1] = '\0;
            break;
        }
    }
}