#include <16F887.h>         // Modify for your chip


#fuses MCLR //Se configura master clear
#fuses NOWDT  //Se indican los fuses activos/inactivos. Y el indicativo de alta velocidad
#fuses INTRC_IO

#use delay(clock=4M)

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

int cuenta=1,p=1;
unsigned int arreglo[24]={0,0,0,0,0,1,0,1,0,0,1,1,1,0,0,1,0,1,1,1,0,1,1,1};
unsigned int aux[3]={0,0,0};
//!
#int_EXT
void control(){

if(cuenta==24){
   cuenta=0;
}
   
if(p==3){

   if(aux[1]==1){
      output_high(PIN_A2);
   }else{
      output_low(PIN_A2);
   }
   if(aux[2]==1){
      output_high(PIN_A3);
   }else{
      output_low(PIN_A3);
   }
   if(aux[3]==1){
      output_high(PIN_A4);
   }else{
      output_low(PIN_A4);
   }

   p=0;
}

if(arreglo[cuenta]==1){
   output_high(PIN_A1);
}else{
   output_low(PIN_A1);
}

aux[p]=arreglo[cuenta];
p++;
cuenta++;


}



void main(void) {
//reloj interno


//Entradas y salidas
TRISA = 0b00000000; //1 = ENTRADA, 0 = SALIDA
//TRISB = 0b00000001; //1 = ENTRADA, 0 = SALIDA

enable_interrupts(int_ext);      //activar interrupcion externa
ext_int_edge(H_TO_L);         //configuracion:interrupcion cuando se�al esta en flanco de subida
enable_interrupts(GLOBAL);      //todas las interrupciones desactivadas
p=0;
cuenta=0;
    while(true) {           // Produces a 1khz square wave on pin B0
    }
}
