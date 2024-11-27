#ifndef CONTROLLER
#define CONTROLLER

#include <serial/serial.h>

enum class State {
    Ligado,
    Reiniciar,
    Desligado
};

class Controller{

    private:
        Controller(){}
        serial::Serial* serialPort;
        int nCompsOnda = 3;
        double compsOnda[3] = {10, 20, 30};
        
    public:
        std::string fileName;
        static State state;
        std::string messageState;
        static Controller* pController;
        static Controller* Instance(); 
        void changeState();
        void setSerial( serial::Serial& serialComm );
        bool Interruptor();
        void SerialReader();

        int wlToSteps(double wv);
        void FazMedida( std::string );
};

typedef Controller TheController;



#endif