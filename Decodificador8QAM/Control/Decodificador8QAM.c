#include <16F887.h>         // Modify for your chip
//#include <lcd.c>

#DEVICE ADC = 10
#fuses HS,NOWDT,NOMCLR,NOPROTECT,NOLVP

#use delay(clock=20M)




//Se ubican los registros de configuracion de puertos

#Byte TRISA = 0x85 
#Byte PORTA = 0x05
#Byte ANSEL = 0x188
#Byte ANSELH = 0x189

#Byte TRISB = 0x86
#Byte PORTB = 0x06


#DEFINE I PIN_A0
#DEFINE Q PIN_A1
#DEFINE S PIN_B1

//#fuses XT,NOMCLR,NOWDT,PUT,NOLVP...

//en XT le dice al pic que lleva un oscilador conectado <4mhz
//el NOMCLR le dice al pic que deshabilita el pin masterclear, desactiva el reset externo por el pic MCLR
//el NOWDT le dice al pic que deshabilita el Watchdog timer "perro guardian"
//el PUT habilita el Power Up Timer, tiempo de espera para estabilizacion de alimentacion
//el NOLVP deshabilita un pin asignado para la programacion de bajo voltaje... low voltage programing




int16 vI=0,vQ=0;
int p=0;
int cuenta=0;

#int_EXT
void control(){   
      set_adc_channel(0);
      delay_us(30);
      vI=read_adc();
      set_adc_channel(1);
      delay_us(30);
      vQ=read_adc();
      
//!      if((0<=vI)&&(vI<512)){
//!      p=1;
//!      }else{
//!      p=0;
//!      }
//!      
      if((384<vI)&&(vI<=640)){ //i=2.5V  [000,010]
        if((640<vQ)&&(vQ<=896)){ //q=3.75  [000]
            p=0;
        }if((128<vQ)&&(vQ<=384)){  //q=1.25    [010]
            p=2;
        }
      }if((128<vI)&&(vI<=384) && (384<vQ)&&(vQ<=640)){   //i=1.25   [001]
         p=1;
      }if((640<vI)&&(vI<=896) && (384<vQ)&&(vQ<=640)){    //i=3.75  [011]
         p=3;
      }if((896<vI)&&(vI<=1023)){   //i=5   [100,111]
         if((896<vQ)&&(vQ<=1023)){  //q=5 [100]
            p=4;
         }
         if((0<=vQ)&&(vQ<=128)){    //q=0  [111]
            p=7;
         }
      }if((0<=vI)&&(vI<=128)){   //
         if(896<vQ<=1024){
            p=5;
         }
         if((0<=vQ)&&(vQ<=128)){
            p=6;
         }
      }
//!
      if(cuenta==3){
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
p=1;
cuenta=0;
//Entradas y salidas
enable_interrupts(int_ext);      //activar interrupcion externa
ext_int_edge(H_TO_L);         //configuracion:interrupcion cuando se�al esta en flanco de subida
enable_interrupts(GLOBAL); 

TRISA = 0b00000011; //1 = ENTRADA, 0 = SALIDA
ANSEL = 0b00000011;//PUERTO A
ANSELH= 0b00000000;//Puerto E
TRISB = 0b00000001; //1 = ENTRADA, 0 = SALIDA


setup_adc_ports(sAN0|sAN1,VSS_VDD);
setup_adc(ADC_CLOCK_INTERNAL);           // Built-in A/D setup function
//setup_adc(ADC_CLOCK_DIV_32);

output_low(S);
output_low(Q);
output_low(I);


    while(true) {           // Produces a 1khz square wave on pin B0
         
      }
}

