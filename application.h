#ifndef APPLICATION_H 
#define APPLICATION_H
 
#include <QtGui>
#include <tinyxml2.h>

class Application : public QWidget
{
    Q_OBJECT
public:
    Application();
private slots:
    void nmap();
    void readXml();
private:
    QPushButton *submitButton;
    QLabel *ipInputLabel;
    QLineEdit *ipInput;
    QTextEdit *output;
    QHBoxLayout *layout;
    QVBoxLayout *layoutMaster;
    QString inputText;
    QString outputString;
    QProcess *nmapProgram;
};
#endif
