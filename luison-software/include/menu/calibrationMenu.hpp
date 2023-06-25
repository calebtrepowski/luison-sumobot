#ifndef _calibration_menu_hpp_
#define _calibration_menu_hpp_

#include <sstream>
#include "calibrationField.h"

class CalibrationMenu
{
public:
    CalibrationMenu();
    ~CalibrationMenu();

    void addField(const char *label, int *value);
    const char *getFields();
    void updateField(int fieldPosition, int newValue);
    int getFieldCount();

private:
    static const int MAX_OPTIONS = 10;
    std::ostringstream calibrationTextStream;
    std::string calibrationText;
    CalibrationField fields[MAX_OPTIONS];
    int fieldCount;
};

#include "calibrationMenu.cpp"

#endif