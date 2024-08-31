#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , display(new QLineEdit(this)),
    buttonLayout(new QGridLayout),
    storedValue(0),
    waitingForOperand(false)
{
    // Setup the display
    display->setReadOnly(true);
    display->setAlignment(Qt::AlignRight);
    display->setMaxLength(15);

    // Create a central widget to hold the layout
    QWidget *centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    // Set up the digit buttons
    QStringList digitButtons{"7", "8", "9", "4", "5", "6", "1", "2", "3", "0"};

    int pos = 0;
    for (const QString &digit : digitButtons) {
        QPushButton *button = new QPushButton(digit, this);
        connect(button, &QPushButton::clicked, this, &MainWindow::onDigitButtonClicked);
        buttonLayout->addWidget(button, pos / 3, pos % 3);
        pos++;
    }

    // Set up operator buttons
    QStringList operators{"+", "-", "*", "/"};
    for (const QString &op : operators) {
        QPushButton *button = new QPushButton(op, this);
        connect(button, &QPushButton::clicked, this, &MainWindow::onOperatorButtonClicked);
        buttonLayout->addWidget(button, pos / 3, pos % 3);
        pos++;
    }

    // Set up equals and clear buttons
    QPushButton *equalsButton = new QPushButton("=", this);
    QPushButton *clearButton = new QPushButton("C", this);

    connect(equalsButton, &QPushButton::clicked, this, &MainWindow::onEqualButtonClicked);
    connect(clearButton, &QPushButton::clicked, this, &MainWindow::onClearButtonClicked);

    buttonLayout->addWidget(equalsButton, pos / 3, pos % 3);
    pos++;
    buttonLayout->addWidget(clearButton, pos / 3, pos % 3);

    // Set up the main layout
    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(display);
    mainLayout->addLayout(buttonLayout);

    centralWidget->setLayout(mainLayout);
}

MainWindow::~MainWindow()
{   
}
void MainWindow::onDigitButtonClicked() {
    QPushButton *button = qobject_cast<QPushButton*>(sender());
    QString digitValue = button->text();

    if (waitingForOperand) {
        display->clear();
        waitingForOperand = false;
    }

    currentInput += digitValue;
    display->setText(currentInput);
}

void MainWindow::onOperatorButtonClicked() {
    QPushButton *button = qobject_cast<QPushButton*>(sender());
    operatorSymbol = button->text();

    storedValue = display->text().toDouble();
    currentInput.clear();
    waitingForOperand = true;
}

void MainWindow::onEqualButtonClicked() {
    double result = storedValue;

    if (!currentInput.isEmpty()) {
        double operand = currentInput.toDouble();

        if (operatorSymbol == "+") {
            result += operand;
        } else if (operatorSymbol == "-") {
            result -= operand;
        } else if (operatorSymbol == "*") {
            result *= operand;
        } else if (operatorSymbol == "/") {
            if (operand != 0.0) {
                result /= operand;
            } else {
                display->setText("Error");
                return;
            }
        }
    }

    display->setText(QString::number(result));
    currentInput.clear();
    storedValue = result;
    waitingForOperand = true;
}

void MainWindow::onClearButtonClicked() {
    storedValue = 0;
    currentInput.clear();
    display->clear();
    waitingForOperand = false;
}
