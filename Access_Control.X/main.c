#pragma config FOSC = XT        // Oscillator Selection bits (XT oscillator)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config BOREN = OFF      // Brown-out Reset Enable bit (BOR disabled)
#pragma config LVP = OFF        // Low-Voltage (Single-Supply) In-Circuit Serial Programming Enable bit (RB3 is digital I/O, HV on MCLR must be used for programming)
#pragma config CPD = OFF        // Data EEPROM Memory Code Protection bit (Data EEPROM code protection off)
#pragma config WRT = OFF        // Flash Program Memory Write Enable bits (Write protection off; all program memory may be written to by EECON control)
#pragma config CP = OFF         // Flash Program Memory Code Protection bit (Code protection off)

#define _XTAL_FREQ 4e6
#define RED RC0
#define GREEN RC1
#define BUZZER RC2

#include <xc.h>
#include <string.h>
#include "Serial.h"
#include "LiquidCrystal.h"

void accessGranted() {
    BUZZER = 1;
    __delay_ms(20);
    BUZZER = 0;
    GREEN = 1;
    RED = 0;
    command(0xC0);
    LCD_Print("Granted!");
}

void accessDenied() {
    command(0xC0);
    LCD_Print("Denied..");
    BUZZER = 1;
    RED = 1;
    __delay_ms(500);
    BUZZER = 0;
    GREEN = 0;
}


int main() {
    char UID[] = "hello";
    char UID_In[20];
    serialInit();
    LCD_Init();
    
    while(1) {
        command(0x80);
        LCD_Print("Show Tag:");
        serialRead(UID_In);
        
        if(!strcmp(UID, UID_In)) {
            accessGranted();
        }
        else {
            accessDenied();
        }
        __delay_ms(1000);
        command(0x01);
        RED = 0;
        GREEN = 0;
    }
}