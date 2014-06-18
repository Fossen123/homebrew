#include <iostream>
#include <QCoreApplication>
#include <QScriptEngine>
#include <QScriptValue>
#include <QString>

///--- The object needs to be MOC'd to be called by the script
#include "ScriptedClass.h"

int main(int argc, char *argv[]){
    QCoreApplication a(argc, argv);
    
    /// Class we'll query at runtime
    ScriptedClass object;
    
    /// Start the engine and link QObject to the application
    QScriptEngine engine;
    QScriptValue value = engine.newQObject(&object);
    engine.globalObject().setProperty("object", value);
    
    //--- Scripts
    QString script1("print('HELLO HELLO HELLO');");
    QString script2("object.method();");
    QString& script = script2;
    
    // do static check so far of code:
    if (!engine.canEvaluate(script)){
        std::cout << "[QScript ERROR] static check failed" << std::endl; 
        // QMessageBox::critical(0, "Error", "canEvaluate returned false!");
    }
    
    // evaluate the script 
    QScriptValue result = engine.evaluate(script);
    if (result.isError()){
        int line_number = result.property("lineNumber").toInt32();
        std::string error = result.toString().toStdString();
        std::cout << "[QScript ERROR]" << line_number << ": " << error << std::endl;
    }   
    
    
    return a.exec();
}
