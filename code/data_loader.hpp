#ifndef __DATA_LOADER__
#define __DATA_LOADER__ 1

#include "opencv2/core/core.hpp"

#include <string>
#include <vector>
#include <fstream>
#include <tuple>

class data_loader{
public:
    data_loader();
    data_loader(const std::string& pathname);
    void open(const std::string& pathname);
    bool is_open() const;
    void close();
    size_t image_counter() const;
    size_t image_number() const;
    void read_all(std::vector<std::vector<double> >& vectors);
    void read_all(std::vector<cv::Mat>& matrices);
    void read(std::vector<double>& vector);
    void read(cv::Mat& matrix);
    void next();
    void reset_iterator();
    std::tuple<size_t, size_t, size_t> format() const;
    
    static cv::Mat rotate(const cv::Mat& matrix, double angle);
    static cv::Mat to_matrix(const std::vector<double>& vector, size_t rows, size_t cols);
    static std::vector<double> to_vector(const cv::Mat& matrix);
    static std::vector<double> random_noise(size_t size);
    
private:
    std::ifstream m_fin;
    size_t m_image_number, m_row_counter, m_col_counter;
    unsigned char m_offset;
    size_t m_image_counter, m_image_size;
    
    void load();
    std::vector<double> generate_vector();
    cv::Mat generate_matrix();
    
    static int reverse(int i);
};

#endif
