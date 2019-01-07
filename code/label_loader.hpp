#ifndef __LABEL_LOADER__
#define __LABEL_LOADER__ 1

#include <string>
#include <vector>
#include <fstream>

class label_loader{
public:
    label_loader();
    label_loader(const std::string& pathname);
    void open(const std::string& pathname);
    bool is_open() const;
    void close();
    size_t image_counter() const;
    size_t image_number() const;
    void read_all(std::vector<size_t>& labels);
    void read(size_t& label);
    void next();
    void reset_iterator();
    
private:
    std::ifstream m_fin;
    size_t m_image_number;
    unsigned char m_offset;
    size_t m_image_counter;
    
    void load();
    size_t generate_label();
    
    static int reverse(int i);
};

#endif
