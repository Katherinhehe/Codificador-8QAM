#include <16F887.h>         // Modify for your chip

#use delay(internal=8mhz)   // Modify for your clock and freq
                            //   for example: internal=8mhz
//#fuses XT,NOMCLR,NOWDT,PUT,NOLVP...

//en XT le dice al pic que lleva un oscilador conectado <4mhz
//el NOMCLR le dice al pic que deshabilita el pin masterclear, desactiva el reset externo por el pic MCLR
//el NOWDT le dice al pic que deshabilita el Watchdog timer "perro guardian"
//el PUT habilita el Power Up Timer, tiempo de espera para estabilizacion de alimentacion
//el NOLVP deshabilita un pin asignado para la programacion de bajo voltaje... low voltage programing

void main(void) {
    while(TRUE) {           // Produces a 1khz square wave on pin B0
        output_high(PIN_B0);
        delay_us(500);
        output_low(PIN_B0);
        delay_us(500);
    }
}
