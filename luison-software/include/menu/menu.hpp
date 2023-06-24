#ifndef _menu_hpp_
#define _menu_hpp_

#include <sstream>
#include "menuOption.hpp"

class Menu
{
public:
    Menu();
    ~Menu();

    /**
     * @brief Adds an option to the menu with its related actions.
     *
     * The setupAction function will be executed once at the beginning.
     * The action function will be executed in an infinite loop until receive
     * the command to stop. The cleanup function will be executed once at the end.
     *
     * @param text The text to be displayed for the option in the menu.
     * @param setupAction The initial actions to be executed. If not needed,
     * pass `nullptr`.
     * @param action The actions to be executed. If not needed, pass `nullptr`.
     * This function will already be called inside an infinite loop.
     * @param cleanupAction The final actions to be executed. If not needed,
     * pass `nullptr`.
     *
     *
     * Examples:
     * menu.addOption("Option 1", action1, nullptr, nullptr);
     * The `action1` function will be executed once and then the main menu will
     * show up again.
     *
     * menu.addOption("Option 2", nullptr, action2, action2cleanup).
     * The `action2` function will be executed until get an `0` as input.
     * The `action2cleanup` will be executed after the loop ends, then the main
     * menu will show up again.
     */
    void addOption(const char *text, void (*setupAction)(),
                   void (*action)(), void (*cleanupAction)());

    /** Call this method inside the program main loop */
    void run();

private:
    static const int MAX_OPTIONS = 10;
    std::ostringstream menuTextStream;
    MenuOption options[MAX_OPTIONS];
    int optionCount;

    virtual void executeAction(int option);

protected:
    std::string menuText;

    virtual void displayMenu() = 0;
    virtual void showMessage(const char *message) = 0;
    virtual bool inputAvailable() = 0;
    virtual int readInput() = 0;
};

#include "menu.cpp"

#endif