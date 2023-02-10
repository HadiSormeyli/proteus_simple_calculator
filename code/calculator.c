#include <mega32.h>
#include <alcd.h>
#include <delay.h>
#include <stdlib.h>
#include <math.h>
#include <stdio.h>

long int first_operand;
long int second_operand; 
char operator;

int check_button(void){

    PORTD.4=0;
    PORTD.5=0;
    PORTD.6=0;           
    PORTD.7=0;
    delay_ms(500);      
    
    while(1){  
    
        PORTD.4=1;
        if(PIND.0==1)return 7;
        if(PIND.1==1)return 4;
        if(PIND.2==1)return 1; 
        if(PIND.3==1)return 10;//on/c   
        PORTD.4=0;
         
        PORTD.5=1;
        if(PIND.0==1)return 8;
        if(PIND.1==1)return 5;
        if(PIND.2==1)return 2;
        if(PIND.3==1)return 0;   
        PORTD.5=0;       
         
        PORTD.6=1;
        if(PIND.0==1)return 9;
        if(PIND.1==1)return 6;
        if(PIND.2==1)return 3;
        if(PIND.3==1)return 11;   
        PORTD.6=0;       
                   
        PORTD.7=1;
        if(PIND.0==1)return 12;
        if(PIND.1==1)return 13;
        if(PIND.2==1)return 14;
        if(PIND.3==1)return 15;  
        PORTD.7=0;       
    }
}


 void show_input(int button){
      char c ='';
       if(button<=9 && button >=0) {
            c=button+'0';      
            
            if(operator == '0') { 
                first_operand = first_operand * 10 + button;
            }else {
                second_operand = second_operand * 10 + button;
            }
       } else if(operator == '0'){             
            if(button ==12)
                c='/';
           else if(button ==13)
                c='*';   
           else if(button ==14)
                c='-';
           else if(button ==15)
                c='+';      
           
           operator = c;
       }                          
       
       if(c != '')
            lcd_putchar(c);
 }   
 
 long  int  calculate_result(){
    switch(operator) {
        case '+':
            return first_operand+second_operand;
        case '-':
            return first_operand-second_operand;  
        case '*':
            return first_operand*second_operand;
        case '/':
            return first_operand/second_operand;
    }
 }
 
 
// #define Max_Digits 10
void show_result_on_lcd(){
       long int result = calculate_result(); 
       
       char str[256];
       
       sprintf(str, "%d", result);
       
       lcd_puts(str);
}


void reset() {  
    lcd_clear();  
    first_operand=0;
    second_operand=0;
    operator='0';     
}
 

void main(void){

    DDRD=0xf0;
    PORTD=0x00;

    //intit lcd
    lcd_init(16);
    reset();


    while (1){
        int button=0;          

        while(button != 11){      
            button=check_button();
            
            if(button != 10 && button !=11){                           
                show_input(button);     
            } else if(button == 10){
                reset();                           
                continue;     
            }                                        
        }              
        lcd_putchar('=');
        show_result_on_lcd();
          
        check_button();
        reset(); 
    }
}
