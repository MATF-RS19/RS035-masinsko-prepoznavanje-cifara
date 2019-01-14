#include "neuralnetwork.h"
#include "ui_neuralnetwork.h"
#include<algorithm>
#include "opencv2/opencv.hpp"
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "network.hpp"
#include "data_loader.hpp"
#include "label_loader.hpp"

#include <random>
#include <string>

using namespace cv;

NeuralNetwork::NeuralNetwork(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::NeuralNetwork)
{
    ui->setupUi(this);
}

NeuralNetwork::~NeuralNetwork()
{
    delete ui;
}

void NeuralNetwork::on_pushButton_clicked()
{
    QString imageName = ui->textEdit_5->toPlainText();
    std::string tmp_name = imageName.toUtf8().constData();
    std::vector<double> pixels;
    Mat image = imread(tmp_name, CV_LOAD_IMAGE_GRAYSCALE);
    pixels = data_loader::to_vector(image);
    network net("mreza");
    net.read_state();
    net.feed(pixels);
    int number=net.result();

    QString valueAsStr = QString::number(number);
    ui->textEdit->setText(valueAsStr);

}

void NeuralNetwork::on_pushButton_2_clicked()
{
    network net("mreza", {784, 15, 11}, 3.0);
    std::vector< std::vector<double> > v_images;
    std::vector<size_t> labels;
    data_loader data("../mnist_data/mnist_images");
    data.read_all(v_images);
    label_loader label("../mnist_data/mnist_labels");
    label.read_all(labels);

    std::default_random_engine generator;
    std::uniform_int_distribution<int> distribution(0,49999);

    for(size_t i=0; i<v_images.size()/20000; ++i){
        for(size_t j=0; j<10000; ++j){
            int rand_img = distribution(generator);
            net.feed(v_images[rand_img]);
            net.propagate(labels[rand_img]);

            net.feed(data_loader::random_noise(784));
            net.propagate(10);
        }
        net.descend();

    }

    net.reset_statistics();
    net.write_state();
    data.close();
    label.close();

}

void NeuralNetwork::on_pushButton_3_clicked()
{
    network net("mreza");
    net.read_state();
    std::vector<std::vector<double>> c_images;
    std::vector<size_t> c_labels;
    data_loader data;
    data.open("../mnist_data/check_images");
    label_loader label;
    label.open("../mnist_data/check_labels");
    data.read_all(c_images);
    label.read_all(c_labels);
    for(size_t i=0; i<c_images.size(); i++){
        net.feed(c_images[i]);
        net.track(c_labels[i]);
    }
    double stat=net.statistics();
    ui->textEdit_2->setPlainText("Statistika:");
    QString valueAsString = QString :: number(stat);
    ui->textEdit_3->setText(valueAsString);
    data.close();
    label.close();

}

void NeuralNetwork::on_pushButton_4_clicked()
{
    QString pathname = ui->textEdit_4->toPlainText();
    std::string path = pathname.toUtf8().constData();
    network net("mreza");
    net.read_state();
    net.write_state(path);
}
