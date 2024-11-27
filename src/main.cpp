#include <iostream>
#include <cstdint>
#include <serial/serial.h>
#include <controller/controller.hpp>

#define COMMUNICATION_PORT "/dev/tty29"
#define Controlador TheController::Instance()

int Command;

int main() {
    serial::Serial serialComm(COMMUNICATION_PORT, 9600, serial::Timeout::simpleTimeout(1000));

    std::cout << "Iniciando" << std::endl;

    Controlador->setSerial(serialComm);
    
    while(true)
    {   
        std::cout << "Pressione 1 para calibrar" << std::endl;
        std::cout << "Pressione 2 para medir" << std::endl;
        std::cout << "Pressione 3 para sair" << std::endl;
        std::cout << "Comando: ";

        std::cin >> Command;

        std::cout << std::endl << std::endl;

        switch (Command) {
            case 1:
                Controlador->FazMedida("calibracao.txt");
                break;
            case 2:
                Controlador->FazMedida("medida.txt");
                break;
            case 3:
                std::cout << "Saindo..." << std::endl;
                break;
            default:
                std::cout << "Comando inválido\n\n" << std::endl;
        }

        if(Command == 3)
        {
            break;
        }
    }
    

    serialComm.close();
    return 0;
}
