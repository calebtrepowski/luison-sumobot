#include "menu.hpp"

Menu::Menu() : optionCount(0), menuTextStream("") {}

Menu::~Menu() {}

void Menu::addOption(const char *text, void (*setupAction)(), void (*action)(), void (*cleanupAction)())
{
    if (optionCount < MAX_OPTIONS)
    {
        MenuOption option;
        option = {
            .text = text,
            .setupAction = setupAction,
            .action = action,
            .cleanupAction = cleanupAction};

        options[optionCount++] = option;
        menuTextStream << optionCount << ". " << text << '\n';
        menuText = menuTextStream.str();
    }
}

void Menu::run()
{
    displayMenu();

    while (true)
    {
        if (inputAvailable())
        {
            int option = readInput();

            if (option >= 1 && option <= optionCount)
            {
                executeAction(option);
                break;
            }
            else
            {
                showMessage("Opción inválida.");
                displayMenu();
            }
        }
    }
}

void Menu::executeAction(int option)
{
    if (options[option - 1].setupAction != nullptr)
    {
        options[option - 1].setupAction();
    }
    if (options[option - 1].action != nullptr)
    {
        while (true)
        {
            options[option - 1].action();

            if (inputAvailable())
            {
                int option = readInput();
                if (option == 0)
                {
                    break;
                }
                else
                {
                    showMessage("Opción inválida. Enviar 0 para detener");
                }
            }
        }
    }
    if (options[option - 1].cleanupAction != nullptr)
    {
        options[option - 1].cleanupAction();
    }
    run();
}