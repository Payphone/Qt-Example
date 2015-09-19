#include <QtGui>
#include <string>
#include <iostream>
#include <tinyxml2.h>
#include "application.h"

using namespace std;
using namespace tinyxml2;
Application::Application() {
    setWindowTitle("Title");
    resize(600, 400);

    submitButton = new QPushButton("&Submit");
    ipInputLabel = new QLabel();
    ipInputLabel->setText("IP Range:");
    ipInput = new QLineEdit();

    output = new QTextEdit();
    output->setReadOnly(true);
    output->setAlignment(Qt::AlignBottom);

    connect(ipInput, SIGNAL(returnPressed()), this, SLOT(nmap()));
    connect(submitButton, SIGNAL(clicked()), this, SLOT(nmap()));

    layout = new QHBoxLayout();
    layout->addWidget(ipInputLabel);
    layout->addWidget(ipInput);
    layout->addWidget(submitButton);

    layoutMaster = new QVBoxLayout();
    layoutMaster->addLayout(layout);
    
    layoutMaster->addWidget(output);

    setLayout(layoutMaster);

}

void Application::nmap() {
    output->setPlainText("Running scan...");
    qApp->processEvents();

    nmapProgram = new QProcess;
    inputText = ipInput->text();
    nmapProgram->start("exampleProgram", QStringList() << inputText << "example-arguments"); 
    connect(nmapProgram, SIGNAL(finished(int)), this, SLOT(readXml()));
}

void Application::readXml() {
    XMLDocument doc;
    doc.LoadFile("nmap.xml"); 

    XMLElement* root = doc.FirstChildElement("nmaprun");
    if(root == nullptr) {
        output->setPlainText("");
        return;
    }
    XMLElement* host = root->FirstChildElement("host");
    if(host == nullptr) {
        output->setPlainText("Please enter a valid IP range");
        return;
    }
    else
        output->setPlainText("");

    while(host != nullptr) {
        outputString = ""; 
        outputString += host->FirstChildElement("address")->Attribute("addr"); 
        outputString += "";
        output->append(outputString);

        XMLElement* port = host->FirstChildElement("ports")->FirstChildElement("port");
        while(port != nullptr) {
            outputString = "    "; 
            outputString += port->Attribute("portid");
            outputString += "  "; 
            outputString += port->FirstChildElement("service")->Attribute("name");
            outputString += + "";
            output->append(outputString);

            port = port->NextSiblingElement("port");
        }
        outputString = "";
        output->append(outputString);
        host = host->NextSiblingElement("host");
    }
    
    qApp->processEvents();
}
