#include <Arduino.h>
#include <sstream>
#include "bluetooth.h"

#include "proximity.h"
#include "line.h"
#ifdef ENABLE_GYRO
#include "gyroscope.h"
#endif
#include "motorDriver.h"
#include "fsm/fsm.h"

void printMenu();
void printProximity();
void printLine();

String command = "";
int choice = -1;

unsigned long referenceTime;

namespace testChoices
{
    const int PROXIMITY_SENSORS = 1;
    const int LINE_SENSORS = 2;
    const int GYRO = 3;
    const int MOTOR_FORWARD = 4;
    const int MOTOR_BACKWARD = 5;
    const int FSM = 6;
    const int MOTORS_TURN_LEFT = 7;
    const int MOTORS_TURN_RIGHT = 8;
}

void setup()
{
    bluetooth::setup();
    proximity::setup();
    line::setup();
#ifdef ENABLE_GYRO
    gyroscope::setup();
#endif
    motors::setup();

    fsm::priorState = NULL;
    fsm::state = fsm::idle;

    delay(3000);
    printMenu();
}

void loop()
{
    Dabble.processInput();
    if (Terminal.available() != 0)
    {
        command = Terminal.readString();

        choice = command.toInt();
        command = "";

        switch (choice)
        {
        case testChoices::PROXIMITY_SENSORS:
            Terminal.println("Enviar 0 para detener.");
            referenceTime = millis();
            while (true)
            {
                if (millis() % referenceTime > 500)
                {
                    proximity::readStates();
                    printProximity();
                }

                Dabble.processInput();
                if (Terminal.available() != 0)
                {
                    command = Terminal.readString();
                    choice = command.toInt();

                    if (choice == 0)
                    {
                        command = "";
                        choice = -1;
                        printMenu();
                        break;
                    }
                }
            }
            break;
        case testChoices::LINE_SENSORS:
            Terminal.println("Enviar 0 para detener.");
            referenceTime = millis();
            while (true)
            {
                if (millis() % referenceTime > 500)
                {
                    line::readValues();
                    printLine();
                }

                Dabble.processInput();
                if (Terminal.available() != 0)
                {
                    command = Terminal.readString();
                    choice = command.toInt();

                    if (choice == 0)
                    {
                        command = "";
                        choice = -1;
                        printMenu();
                        break;
                    }
                }
            }
            break;
        case testChoices::GYRO:
            Terminal.println("Enviar 0 para detener.");
            float angleZ;
            referenceTime = millis();
            while (true)
            {
#ifdef ENABLE_GYRO
                using namespace gyroscope;
                mpu.updateAngleZ();
                angleZ = mpu.getAngleZ();
                if (millis() % referenceTime > 500)
                {
                    Terminal.println(angleZ);
                }
#endif

                Dabble.processInput();
                if (Terminal.available() != 0)
                {
                    command = Terminal.readString();
                    choice = command.toInt();

                    if (choice == 0)
                    {
                        command = "";
                        choice = -1;
                        printMenu();
                        break;
                    }
                }
            }
            break;
        case testChoices::MOTOR_FORWARD:
            Terminal.println("Enviar 0 para detener.");
            motors::goForward(2);

            while (true)
            {
                Dabble.processInput();
                if (Terminal.available() != 0)
                {
                    command = Terminal.readString();
                    choice = command.toInt();

                    if (choice == 0)
                    {
                        motors::brake();
                        command = "";
                        choice = -1;
                        printMenu();
                        break;
                    }
                }
            }
            break;
        case testChoices::MOTOR_BACKWARD:
            Terminal.println("Enviar 0 para detener.");
            motors::goBack(2);

            while (true)
            {
                Dabble.processInput();
                if (Terminal.available() != 0)
                {
                    command = Terminal.readString();
                    choice = command.toInt();

                    if (choice == 0)
                    {
                        motors::brake();
                        command = "";
                        choice = -1;
                        printMenu();
                        break;
                    }
                }
            }
            break;
        case testChoices::FSM:
            Terminal.println("Enviar 0 para detener.");
            fsm::state = fsm::normalSearch;

            while (true)
            {
                fsm::state();

                Dabble.processInput();
                if (Terminal.available() != 0)
                {
                    command = Terminal.readString();
                    choice = command.toInt();

                    if (choice == 0)
                    {
                        motors::brake();
                        command = "";
                        choice = -1;
                        printMenu();
                        break;
                    }
                }
            }
            break;
        case testChoices::MOTORS_TURN_LEFT:
            Terminal.println("Enviar 0 para detener.");
            motors::turnLeft(2);

            while (true)
            {
                Dabble.processInput();
                if (Terminal.available() != 0)
                {
                    command = Terminal.readString();
                    choice = command.toInt();

                    if (choice == 0)
                    {
                        motors::brake();
                        command = "";
                        choice = -1;
                        printMenu();
                        break;
                    }
                }
            }
            break;
        case testChoices::MOTORS_TURN_RIGHT:
            Terminal.println("Enviar 0 para detener.");
            motors::turnRight(2);

            while (true)
            {
                Dabble.processInput();
                if (Terminal.available() != 0)
                {
                    command = Terminal.readString();
                    choice = command.toInt();

                    if (choice == 0)
                    {
                        motors::brake();
                        command = "";
                        choice = -1;
                        printMenu();
                        break;
                    }
                }
            }
            break;
        default:
            Terminal.println("Comando no válido");
            printMenu();
            break;
        }
    }
}

void printMenu()
{
    std::ostringstream menuText;
    menuText << "=== Probar: ===\n";
    menuText << "\t1. Sensores de proximidad\n";
    menuText << "\t2. Sensores de linea\n";
    menuText << "\t3. MPU\n";
    menuText << "\t4. Motores (adelante)\n";
    menuText << "\t5. Motores (reversa)\n";
    menuText << "\t6. FSM\n";
    menuText << "\t7. Motores (giro izq)\n";
    menuText << "\t8. Motores (giro der)";
    Terminal.println(menuText.str().data());
}

void printProximity()
{
    std::ostringstream aux;
    aux << "-----------\n";
    aux << proximity::frontLeft.state;
    aux << " ";
    aux << proximity::frontCenter.state;
    aux << " ";
    aux << proximity::frontRight.state;
    aux << "\n";

    aux << proximity::left.state;
    aux << "   ";
    aux << proximity::right.state;
    aux << "\n";

    aux << "  ";
    aux << proximity::back.state;
    aux << "\n-----------";

    Terminal.println(aux.str().data());
}

void printLine()
{
    std::ostringstream aux;
    aux << "-----------\n";
    aux << line::frontLeft.value;
    aux << "\t";
    aux << line::frontRight.value;
    aux << "\n";
    aux << line::backLeft.value;
    aux << "\t";
    aux << line::backRight.value;
    aux << "\n-----------";

    Terminal.println(aux.str().data());
}