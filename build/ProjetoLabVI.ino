#include <Stepper.h> //include the function library, standard Arduino library
#define STEPS 32 // 64 steps per rev

Stepper motor(STEPS, 5, 3, 4, 2); //create the stepper0  <<< Order here is important

byte sensorPin = A0;
byte qtdMedidas = 100;

char comando;
unsigned short qtdPassosDados = 0;
unsigned short passos;

void resetMotor()
{
    motor.step(-qtdPassosDados);
    qtdPassosDados = 0;
}

void giraMotor(int steps)
{   
    resetMotor();
    motor.step(steps);
    qtdPassosDados += steps;
    Serial.println(1); // Código 1 significa que o motor terminou a rotação
}

void medeFotodiodo()
{
    int cumSensorValue = 0;

    for(int i = 0; i < qtdMedidas; i++)
    {
        cumSensorValue += analogRead(sensorPin);
    }

    Serial.println(cumSensorValue/qtdMedidas); //Manda a média pela porta serial
}

void Controlador()
{   
    if(Serial.available() > 0)
    {
        comando = Serial.read();

        if(comando == "0")
        {
            resetMotor();
        }
        else if(comando == "1")
        {
            passos = Serial.parseInt();
            giraMotor(passos);
            Serial.read(); // Retira o caractere n
        }
        else if(comando == "2")
        {
            medeFotodiodo();
        }
        else
        {
            Serial.println("x");
        }
    }
}

void setup()
{
  motor.setSpeed(900);
  Serial.begin(9600);
}

void loop()
{
  Controlador();
}