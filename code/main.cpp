#include <QApplication>
#include "neuralnetwork.h"

int main(int argc, char** argv){



     QApplication a(argc, argv);
     NeuralNetwork w;
     w.show();

    
    return a.exec();
}
