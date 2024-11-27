#include <iostream>
#include <fstream>
#include "controller.hpp"
#include <string.h>
#include <chrono>
#include <atomic>

State Controller::state = State::Desligado;

Controller* Controller::pController = 0;

Controller* Controller::Instance(){

    if(pController == 0){
        pController = new Controller();
    }  

    return pController;
}

void Controller::changeState(){

    if( Controller::state == State::Desligado ){
        Controller::state = State::Ligado;
        Controller::messageState = "1";
    }
    else if (Controller::state == State::Ligado){
        Controller::state = State::Reiniciar;
        Controller::messageState = "2";
    }
    else{
        Controller::state = State::Desligado;
        Controller::messageState = "0";
    }
} 

void Controller::setSerial( serial::Serial& serialComm ){
    this->serialPort = &serialComm;
}

bool Controller::Interruptor(){

    //TODO: Adicionar um jeito de "handle" as respostas do arduino pra ter certeza que rodou
    if( state == State::Desligado ){

        std::cout << "Desligando......" << std::endl;
        Controller::serialPort->write(Controller::messageState);
        
        while(true){
            if(Controller::serialPort->available()){
                std::string response = Controller::serialPort->readline();
                if(response == "1"){
                    return true;
                } 
                else{
                    return false;
                }
            }
        }
        
    }
    else if( state == State::Ligado ){

        std::cout << "Ligandooo......" << std::endl;
        Controller::serialPort->write(Controller::messageState);

        while(true){
            if(Controller::serialPort->available()){
                std::string response = Controller::serialPort->readline();
                if(response == "1"){
                    return true;
                } 
                else{
                    return false;
                }
            }
        }
    }
    else if( state == State::Reiniciar ){

        std::cout << "Reiniciandooo......" << std::endl;
        Controller::serialPort->write(Controller::messageState);

        while(true){
            if(Controller::serialPort->available()){
                std::string response = Controller::serialPort->readline();
                if(response == "1"){
                    return true;
                } 
                else{
                    return false;
                }
            }
        }
    }
    return false;
}

void Controller::SerialReader(){

    if(Controller::state == State::Ligado){
        fileName = "calibracao.txt";
    }
    else{
        fileName = "medidas.txt";
    }

    std::ofstream outFile(Controller::fileName);

    if (!outFile) {
        std::cerr << "Error creating the file!" << std::endl;
    }

    while(true){
        if(Controller::serialPort->available()){
            
            std::string line = Controller::serialPort->readline();
            
            if(line == "Terminou"){
                break;
            }
            else{
                outFile << line << std::endl;
            }
        }
    }

    outFile.close();
}

int Controller::wlToSteps( double wv )
{
    return (int)wv;
}

void Controller::FazMedida( std::string filename )
{   
    std::ofstream outFile(filename);
    int terminouAcao = 0;

    if (!outFile) {
        std::cerr << "Error creating the file!" << std::endl;
    }

    this->serialPort->write("0"); //Reseta o angulo da grade de difração
    
    for(int i = 0; i < this->nCompsOnda; i++)
    {   
        terminouAcao = 0;
        this->serialPort->write("1"); //Diz para a arduino girar o motor
        this->serialPort->write( std::to_string( wlToSteps( compsOnda[i] ) ) + "n" ); //Gira a devida quantidade de vezes
        
        while( !(this->serialPort->available() && terminouAcao != 0 ) )
        {
            if( this->serialPort->available() )
            {
                if(this->serialPort->readline() == "1")
                {
                    terminouAcao = 1;
                }
            }
        }

        this->serialPort->write("2");//Diz para a arduino medir com o fotodiodo

        std::string medida = "";

        while(this->serialPort->available())
        {
            medida = this->serialPort->readline();
        }

        outFile << medida << std::endl;

    }

    outFile.close();
}