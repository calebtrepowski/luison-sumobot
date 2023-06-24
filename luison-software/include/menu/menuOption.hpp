#ifndef _menu_option_hpp_
#define _menu_option_hpp_

struct MenuOption
{
    const char *text;
    void (*setupAction)();
    void (*action)();
    void (*cleanupAction)();
};

#endif