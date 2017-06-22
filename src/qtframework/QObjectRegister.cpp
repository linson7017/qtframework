#include "QObjectRegister.h"
#include "Utils/QObjectFactory.h"
#include <QtWidgets>

void QObjectRegister::RegisterWidgets()
{
    REGISTER_CLASS("QPushButton",QPushButton);
    REGISTER_CLASS("QLabel", QLabel);
    REGISTER_CLASS("QLineEdit", QLineEdit);
    REGISTER_CLASS("QComboBox", QComboBox);
    REGISTER_CLASS("QTextEdit", QTextEdit);
    REGISTER_CLASS("QWidget", QWidget);
    REGISTER_CLASS("QSlider", QSlider);
    REGISTER_CLASS("QSplitter", QSplitter);
    REGISTER_CLASS("QProgressBar", QProgressBar);
    REGISTER_CLASS("QCheckBox", QCheckBox);
    REGISTER_CLASS("QRadioButton", QRadioButton);
    REGISTER_CLASS("QStackedWidget", QStackedWidget);
}
