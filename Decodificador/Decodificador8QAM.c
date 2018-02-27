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

//#DEFINE I PIN_AN5
//#DEFINE Q PIN_AN6

float adc,vI,vQ;

#int_EXT
void control(){
   
      set_adc_channel(5);
      adc=read_adc();
      vI=(adc/1024)*5;
      //lcd_gotoxy(1,1);
      //printf(lcd_putc,"Voltaje = %.2f V", vI);
      set_adc_channel(6);
      adc=read_adc();
      vQ=(adc/1024)*5;
      //lcd_gotoxy(1,2);
      //printf(lcd_putc,"Voltaje = %.2f V", vQ);
      
}

void main(void) {

//Entradas y salidas
enable_interrupts(int_ext);      //activar interrupcion externa
ext_int_edge(H_TO_L);         //configuracion:interrupcion cuando se�al esta en flanco de subida
enable_interrupts(GLOBAL); 

//lcd_init();
setup_adc_ports(5,6);
setup_adc(ADC_CLOCK_DIV_32);
set_adc_channel(5);

//TRISB = 0b00000000; //1 = ENTRADA, 0 = SALIDA
//enable_interrupts(GLOBAL);      //todas las interrupciones desactivadas


    while(true) {           // Produces a 1khz square wave on pin B0

      }
}
