#include "calibrationMenu.hpp"
#include <DabbleESP32.h>

CalibrationMenu::CalibrationMenu() : fieldCount(0), calibrationTextStream("") {}

CalibrationMenu::~CalibrationMenu() {}

void CalibrationMenu::addField(const char *label, int *value)
{
    if (fieldCount < MAX_OPTIONS)
    {
        CalibrationField field;
        field = {
            .label = label,
            .value = value};

        fields[fieldCount++] = field;
        calibrationTextStream << fieldCount << ". " << label << ": " << *value << '\n';
        calibrationText = calibrationTextStream.str();
    }
}

const char *CalibrationMenu::getFields()
{
    return calibrationText.data();
}

void CalibrationMenu::updateField(int fieldPosition, int newValue)
{
    *fields[fieldPosition].value = newValue;
    calibrationTextStream.str("");
    calibrationTextStream.clear();
    for (int i = 0; i < fieldCount; i++)
    {
        calibrationTextStream << i + 1 << ". " << fields[i].label << ": " << *fields[i].value << '\n';
    }
    calibrationText = calibrationTextStream.str();
}

int CalibrationMenu::getFieldCount() { return fieldCount; }