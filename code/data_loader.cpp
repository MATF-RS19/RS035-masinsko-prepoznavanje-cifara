#include "data_loader.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"

#include <utility>
#include <random>
#include <algorithm>

data_loader::data_loader():m_offset(4*sizeof(int)){}

data_loader::data_loader(const std::string& pathname):m_fin(pathname, std::ios::binary), m_offset(4*sizeof(int)), m_image_counter(0){
    load();
    m_image_size=m_row_counter*m_col_counter;
}

void data_loader::open(const std::string& pathname){
    m_fin.open(pathname, std::ios::binary);
    m_image_counter=0;
    load();
    m_image_size=m_row_counter*m_col_counter;
}

bool data_loader::is_open() const{
    return m_fin.is_open();
}

void data_loader::close(){
    m_fin.close();
}

size_t data_loader::image_counter() const{
    return m_image_counter;
}

size_t data_loader::image_number() const{
    return m_image_number;
}

void data_loader::read_all(std::vector<std::vector<double> >& vectors){
    vectors.clear();
    vectors.reserve(m_image_number);
    for(size_t i=0; i<m_image_number; ++i)
        vectors.push_back(generate_vector());
    m_fin.seekg(m_offset);
}

void data_loader::read_all(std::vector<cv::Mat>& matrices){
    matrices.clear();
    matrices.reserve(m_image_number);
    for(size_t i=0; i<m_image_number; ++i)
        matrices.push_back(generate_matrix());
    m_fin.seekg(m_offset);
}
    
void data_loader::read(std::vector<double>& vector){
    if(m_image_counter==m_image_number)
        return;
    m_fin.seekg(m_image_counter*sizeof(unsigned char)*m_image_size+m_offset);
    vector=generate_vector();
    m_fin.seekg(m_offset);
}
    
void data_loader::read(cv::Mat& matrix){
    if(m_image_counter==m_image_number)
        return;
    m_fin.seekg(m_image_counter*sizeof(unsigned char)*m_image_size+m_offset);
    matrix=generate_matrix();
    m_fin.seekg(m_offset);   
}

void data_loader::next(){
    ++m_image_counter;
}
    
void data_loader::reset_iterator(){
    m_image_counter=0;
}

std::tuple<size_t, size_t, size_t> data_loader::format() const{
    return std::tuple<size_t, size_t, size_t> (m_image_number, m_row_counter, m_col_counter);
}

cv::Mat data_loader::rotate(const cv::Mat& matrix, double angle){
    cv::Mat result, rotation=cv::getRotationMatrix2D(cv::Point2f(matrix.cols/2., matrix.rows/2.), angle, 1.0);
    cv::warpAffine(matrix, result, rotation, cv::Size(matrix.cols, matrix.rows));
    return result;
}

cv::Mat data_loader::to_matrix(const std::vector<double>& vector, size_t rows, size_t cols){
    cv::Mat result(rows, cols, CV_8UC1);
    memcpy(result.data, vector.data(), vector.size()*sizeof(double));
    return result;
}

std::vector<double> data_loader::to_vector(const cv::Mat& matrix){
    if(matrix.isContinuous())
        return std::vector<double>((double*) matrix.datastart, (double*) matrix.dataend);
    std::vector<double> result;
    result.reserve(matrix.rows*matrix.cols);
    for(int i=0; i<matrix.rows; ++i)
            result.insert(result.end(), matrix.ptr<double>(i), matrix.ptr<double>(i)+matrix.cols);
    return result;
}

std::vector<double> data_loader::random_noise(size_t size){
    std::default_random_engine generator;
    std::uniform_real_distribution<double> distribution(0.0, 1.0);
    std::vector<double> result(size);
    std::generate_n(result.begin(), size, [&generator, &distribution]() mutable {return distribution(generator);});
    return result;
}

void data_loader::load(){
    int tmp;
    m_fin.read((char*) &tmp, sizeof(int));
    m_fin.read((char*) &tmp, sizeof(int));
    m_image_number=reverse(tmp);
    m_fin.read((char*) &tmp, sizeof(int));
    m_row_counter=reverse(tmp);
    m_fin.read((char*) &tmp, sizeof(int));
    m_col_counter=reverse(tmp);
}

std::vector<double> data_loader::generate_vector(){
        std::vector<double> result;
        result.reserve(m_image_size);
        unsigned char tmp;
        for(size_t j=0; j<m_row_counter; ++j)
            for(size_t k=0; k<m_col_counter; ++k){
                m_fin.read((char*) &tmp, sizeof(unsigned char));
                result.push_back(double(tmp));
            }
        return result;
}

cv::Mat data_loader::generate_matrix(){
    cv::Mat result=cv::Mat::zeros(m_row_counter, m_col_counter, CV_8UC1);
    unsigned char tmp;
    for(size_t j=0; j<m_row_counter; ++j)
            for(size_t k=0; k<m_col_counter; ++k){
                m_fin.read((char*) &tmp, sizeof(unsigned char));
                result.at<uchar>(j, k)=int(tmp);
            }
    return result;
}

int data_loader::reverse(int i){
    unsigned char ch0, ch1, ch2, ch3;
    ch0=i & 255;
    ch1=(i>>8) & 255;
    ch2=(i>>16) & 255;
    ch3=(i>>24) & 255;
    return (int(ch0)<<24)+(int(ch1)<<16)+(int(ch2)<<8)+ch3;
}
