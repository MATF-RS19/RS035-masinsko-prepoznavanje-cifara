#ifndef __MNIST_LOADER__
#define __MNIST_LOADER__ 1

#include "opencv2/core/core.hpp"

#include <string>
#include <vector>
#include <fstream>
#include <tuple>

class mnist_loader{
public:
    mnist_loader();
    mnist_loader(const std::string& pathname);
    void open(const std::string& pathname);
    bool is_open() const;
    void close();
    size_t image_counter() const;
    size_t image_number() const;
    void read_mnist(std::vector<std::vector<double> >& dst);
    void read_mnist(std::vector<cv::Mat>& dst);
    void iterate_mnist(std::vector<double>& dst);
    void iterate_mnist(cv::Mat& dst);
    void reset_iterator();
    std::tuple<size_t, size_t, size_t> format() const;
    
    static cv::Mat rotate(const cv::Mat& src, double angle);
    static std::vector<double> random_noise(size_t size);
private:
    std::ifstream m_fin;
    size_t m_image_number, m_row_counter, m_col_counter;
    unsigned char m_offset;
    size_t m_image_counter, m_image_size;
    
    static void load(std::ifstream& fin, size_t& image_counter, size_t& n_rows, size_t& n_cols);
    static int reverse(int i);
};

#endif
