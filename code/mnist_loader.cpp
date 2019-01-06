#include "mnist_loader.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"

#include <utility>
#include <random>
#include <algorithm>

mnist_loader::mnist_loader():m_offset(4*sizeof(int)){}

mnist_loader::mnist_loader(const std::string& pathname):m_fin(pathname, std::ios::binary), m_offset(4*sizeof(int)), m_image_counter(0){
    load(m_fin, m_image_number, m_row_counter, m_col_counter);
    m_image_size=m_row_counter*m_col_counter*sizeof(unsigned char);
}

void mnist_loader::open(const std::string& pathname){
    m_fin.open(pathname, std::ios::binary);
    m_image_counter=0;
    load(m_fin, m_image_number, m_row_counter, m_col_counter);
    m_image_size=m_row_counter*m_col_counter*sizeof(unsigned char);
}

bool mnist_loader::is_open() const{
    return m_fin.is_open();
}

void mnist_loader::close(){
    m_fin.close();
}

size_t mnist_loader::image_counter() const{
    return m_image_counter;
}

size_t mnist_loader::image_number() const{
    return m_image_number;
}

void mnist_loader::read_mnist(std::vector<std::vector<double> >& dst){
    dst.clear();
    dst.reserve(m_image_number);
    unsigned char tmp;
    for(size_t i=0; i<m_image_number; ++i){
        std::vector<double> tmp_v;
        tmp_v.reserve(m_row_counter*m_col_counter);
        for(size_t j=0; j<m_row_counter; ++j)
            for(size_t k=0; k<m_col_counter; ++k){
                m_fin.read((char*) &tmp, sizeof(unsigned char));
                tmp_v.push_back(double(tmp));
            }
        dst.push_back(std::move(tmp_v));
    }
    m_fin.seekg(m_offset);
}
    
void mnist_loader::read_mnist(std::vector<cv::Mat>& dst){
    dst.clear();
    dst.reserve(m_image_number);
    unsigned char tmp;
    for(size_t i=0; i<m_image_number; ++i){
        cv::Mat tmp_m=cv::Mat::zeros(m_row_counter, m_col_counter, CV_8UC1);
        for(size_t j=0; j<m_row_counter; ++j)
            for(size_t k=0; k<m_col_counter; ++k){
                m_fin.read((char*) &tmp, sizeof(unsigned char));
                tmp_m.at<uchar>(j, k)=int(tmp);
            }
        dst.push_back(std::move(tmp_m));
    }
    m_fin.seekg(m_offset);
}
    
void mnist_loader::iterate_mnist(std::vector<double>& dst){
    dst.clear();
    if(m_image_counter==m_image_number)
        return;
    
    dst.reserve(m_row_counter*m_col_counter);
    unsigned char tmp;
    m_fin.seekg(m_image_counter*m_image_size+m_offset);
    for(size_t i=0; i<m_row_counter; ++i)
        for(size_t j=0; j<m_col_counter; ++j){
            m_fin.read((char*) &tmp, sizeof(unsigned char));
            dst.push_back(double(tmp));
        }
    ++m_image_counter;
    m_fin.seekg(m_offset);
}
    
void mnist_loader::iterate_mnist(cv::Mat& dst){
    dst=cv::Mat::zeros(m_row_counter, m_col_counter, CV_8UC1);
    if(m_image_counter==m_image_number)
        return;
    
    unsigned char tmp;
    m_fin.seekg(m_image_counter*m_image_size+m_offset);
    for(size_t i=0; i<m_row_counter; ++i)
        for(size_t j=0; j<m_col_counter; ++j){
            m_fin.read((char*) &tmp, sizeof(unsigned char));
            dst.at<uchar>(i, j)=int(tmp);
        }
    ++m_image_counter;
    m_fin.seekg(m_offset);   
}
    
void mnist_loader::reset_iterator(){
    m_image_counter=0;
}

std::tuple<size_t, size_t, size_t> mnist_loader::format() const{
    return std::tuple<size_t, size_t, size_t> (m_image_number, m_row_counter, m_col_counter);
}

cv::Mat mnist_loader::rotate(const cv::Mat& src, double angle){
    cv::Mat dst, rot=cv::getRotationMatrix2D(cv::Point2f(src.cols/2., src.rows/2.), angle, 1.0);
    cv::warpAffine(src, dst, rot, cv::Size(src.cols, src.rows));
    return dst;
}

std::vector<double> mnist_loader::random_noise(size_t size){
    std::default_random_engine generator;
    std::uniform_real_distribution<double> distribution(0.0, 1.0);
    std::vector<double> result(size);
    std::generate_n(result.begin(), size, [&generator, &distribution]() mutable {return distribution(generator);});
    return result;
}

void mnist_loader::load(std::ifstream& fin, size_t& image_counter, size_t& row_counter, size_t& col_counter){
    int tmp_magic_number, tmp_image_counter, tmp_row_counter, tmp_col_counter;
    fin.read((char*) &tmp_magic_number, sizeof(int));
    fin.read((char*) &tmp_image_counter, sizeof(int));
    image_counter=reverse(image_counter);
    fin.read((char*) &tmp_row_counter, sizeof(int));
    row_counter=reverse(row_counter);
    fin.read((char*) &tmp_col_counter, sizeof(int));
    col_counter=reverse(col_counter);
}

int mnist_loader::reverse(int i){
    unsigned char ch0, ch1, ch2, ch3;
    ch0=i & 255;
    ch1=(i>>8) & 255;
    ch2=(i>>16) & 255;
    ch3=(i>>24) & 255;
    return (int(ch0)<<24)+(int(ch1)<<16)+(int(ch2)<<8)+ch3;
}
