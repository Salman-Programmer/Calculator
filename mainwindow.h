#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QGridLayout>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onDigitButtonClicked();
    void onOperatorButtonClicked();
    void onEqualButtonClicked();
    void onClearButtonClicked();

private:
    QLineEdit *display;
    QGridLayout *buttonLayout;

    QString currentInput;
    QString operatorSymbol;
    double storedValue;
    bool waitingForOperand;

};
#endif // MAINWINDOW_H
