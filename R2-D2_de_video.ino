#include "ibus.h"
#include <Servo.h>

//Taxa de atualização da comunicação em milisegundos(Não mexer)
#define UPDATE_INTERVAL 10 

//Numero de entradas digitais,que são o numero de botões liga/desliga a serem usados no controle
#define DIGITAL_INPUTS_COUNT 4 


//Portas digitais onde serão conectados os fios dos botões feitos
byte digitalPins[] = { 3, 4, 5, 6};

#define BAUD_RATE 115200 


//Os tipos de entradas pro controle são somados 
#define NUM_CHANNELS ( (DIGITAL_INPUTS_COUNT) )

//E aqui esse valor informa quantos canais vão receber os dados dos botões e analógicos por voce controlados
IBus ibus(NUM_CHANNELS);

Servo myservo;  // create servo object to control a servo
// twelve servo objects can be created on most boards

int pos = 0;// variable to store the servo position

int estado_pausa_atual=0;
int estado_frente_atual=0;
int estado_tras_atual=0;


int estado_pausa_antes=0;
int estado_frente_antes=0;
int estado_tras_antes=0;
void setup() {
   myservo.attach(9);
   // attaches the servo on pin 9 to the servo object
   
   //control buttons
  pinMode(3, INPUT_PULLUP);//tecla tab
 pinMode(4, INPUT_PULLUP);// tecla backspace
 pinMode(5, INPUT_PULLUP);// tecla seta direita
 pinMode(6, INPUT_PULLUP);// tecla seta esquerda

 for (pos = 0; pos <= 180; pos += 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15ms for the servo to reach the position
  }
    for (pos = 180; pos >= 0; pos -= 1) { // goes from 180 degrees to 0 degrees
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15ms for the servo to reach the position
  }

Serial.begin(BAUD_RATE);

}

void loop() 
{

estado_pausa_atual = digitalRead(4);
estado_frente_atual = digitalRead(5);
estado_tras_atual = digitalRead(6);

if(estado_pausa_atual!= estado_pausa_antes)
{
 gira_inicio();
  
}

else if(estado_frente_atual!= estado_frente_antes) 
{
  gira_frente();
}


else if(estado_tras_atual!= estado_tras_antes) 
{
  gira_tras();
}

estado_pausa_antes=estado_pausa_atual;
estado_frente_antes=estado_frente_atual;
estado_tras_antes=estado_tras_atual;

int i = 0;
unsigned long time = millis();

   
       ibus.begin();
  
//Aqui os estados dos botões  são lidos e enviados para a comunicação serial
 
     for(i=0; i < DIGITAL_INPUTS_COUNT; i++)
    ibus.write(digitalRead(digitalPins[i]) == HIGH ? 1023 : 0);
 
     ibus.end();

}

void gira_inicio()
{
 pos=0;
 myservo.write(pos);      
}

void gira_frente()
{
  
  pos=pos+10;
  myservo.write(pos);      

}

void gira_tras()
{
  pos=pos-10;
  myservo.write(pos);      

}
