#ifndef NEURALNETWORK_H
#define NEURALNETWORK_H

#include <QMainWindow>

namespace Ui {
class NeuralNetwork;
}

class NeuralNetwork : public QMainWindow
{
    Q_OBJECT

public:
    explicit NeuralNetwork(QWidget *parent = nullptr);
    ~NeuralNetwork();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

private:
    Ui::NeuralNetwork *ui;
};

#endif // NEURALNETWORK_H
