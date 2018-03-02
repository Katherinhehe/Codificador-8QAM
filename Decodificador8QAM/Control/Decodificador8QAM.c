#include <16F887.h>         // Modify for your chip

#DEVICE ADC = 10

#fuses NOMCLR //Se configura master clear
#fuses NOWDT  //Se indican los fuses activos/inactivos. Y el indicativo de alta velocidad

#use delay(clock=20M)

//#include <lcd.c>
//Se ubican los registros de configuracion de puertos

#Byte TRISA = 0x85 
#Byte PORTA = 0x05
#Byte TRISB = 0x86
#Byte PORTB = 0x06

//#fuses XT,NOMCLR,NOWDT,PUT,NOLVP...

//en XT le dice al pic que lleva un oscilador conectado <4mhz
//el NOMCLR le dice al pic que deshabilita el pin masterclear, desactiva el reset externo por el pic MCLR
//el NOWDT le dice al pic que deshabilita el Watchdog timer "perro guardian"
//el PUT habilita el Power Up Timer, tiempo de espera para estabilizacion de alimentacion
//el NOLVP deshabilita un pin asignado para la programacion de bajo voltaje... low voltage programing

#DEFINE S PIN_A0
//#DEFINE I PIN_AN5
//#DEFINE Q PIN_AN6

float vI,vQ;
int p,cuenta;

#int_EXT
void control(){
   
      set_adc_channel(5);
      vI=read_adc();
      vI=(vI/1024)*5;
      //lcd_gotoxy(1,1);
      //printf(lcd_putc,"Voltaje = %.2f V", vI);
      set_adc_channel(6);
      vQ=read_adc();
      vQ=(vQ/1024)*5;
      //lcd_gotoxy(1,2);
      //printf(lcd_putc,"Voltaje = %.2f V", vQ);
      if(1.875<vI<=3.125){ //i=2.5V  [000,010]
        if(3.125<vQ<=4.375){ //q=3.75  [000]
            p=0;
        }if(0.625<vQ<=1.875){  //q=1.25    [010]
            p=2;
        }
      }if(0.625<vI<=1.875 && 1.875<vQ<=3.125){   //i=1.25   [001]
         p=1;
      }if(3.125<vI<=4.375 && 1.875<vQ<=3.125){    //i=3.75  [011]
         p=3;
      }if(4.375<vQ<=5){   //i=5   [100,111]
         if(4.375<vQ<=5){  //q=5 [100]
            p=4;
         }
         if(0<=vQ<=0.625){    //q=0  [111]
            p=7;
         }
      }if(0<=vI<=0.625){   //
         if(4.375<vQ<=5){
            p=5;
         }
         if(0<=vQ<=0.625){
            p=6;
         }
      }
      if(cuenta=3){
         cuenta=0;
      }
      switch (cuenta){
         case 0:
            if(p==0 || p==1 || p==2 || p==3){
               output_low(S);
            }else{ 
               output_high(S);
            }
            break;
         case 1:
             if(p==0 || p==1 || p==4 || p==5){
               output_low(S);
            }else{ 
               output_high(S);
            }break;
         case 2:
            if(p==0 || p==2 || p==4 || p==6){
               output_low(S);
            }else{ 
               output_high(S);
            }break;      
      }cuenta++;
      
}

void main(void) {
vI=0;
vQ=0;
p=0;
cuenta=0;
//Entradas y salidas
enable_interrupts(int_ext);      //activar interrupcion externa
ext_int_edge(H_TO_L);         //configuracion:interrupcion cuando se�al esta en flanco de subida
enable_interrupts(GLOBAL); 

//lcd_init();
setup_adc_ports(5,6);
setup_adc(ADC_CLOCK_DIV_32);

TRISA = 0b00000000; //1 = ENTRADA, 0 = SALIDA
//enable_interrupts(GLOBAL);      //todas las interrupciones desactivadas
output_low(S);

    while(true) {           // Produces a 1khz square wave on pin B0
         
      }
}
