#include "label_loader.hpp"

label_loader::label_loader():m_offset(4*sizeof(int)){}

label_loader::label_loader(const std::string& pathname):m_fin(pathname, std::ios::binary), m_offset(4*sizeof(int)), m_image_counter(0){
    load();
}

void label_loader::open(const std::string& pathname){
    m_fin.open(pathname, std::ios::binary);
    m_image_counter=0;
    load();
}

bool label_loader::is_open() const{
    return m_fin.is_open();
}

void label_loader::close(){
    m_fin.close();
}

size_t label_loader::image_counter() const{
    return m_image_counter;
}

size_t label_loader::image_number() const{
    return m_image_number;
}

void label_loader::read_all(std::vector<size_t>& labels){
    labels.clear();
    labels.reserve(m_image_number);
    for(size_t i=0; i<m_image_number; ++i)
        labels.push_back(generate_label());
    m_fin.seekg(m_offset);
}

void label_loader::read(size_t& label){
    if(m_image_counter==m_image_number)
        return;
    m_fin.seekg(m_image_counter*sizeof(unsigned char)+m_offset);
    label=generate_label();
    m_fin.seekg(m_offset);      
}

void label_loader::next(){
    ++m_image_counter;
}
    
void label_loader::reset_iterator(){
    m_image_counter=0;
}

void label_loader::load(){
    int tmp;
    m_fin.read((char*) &tmp, sizeof(int));
    m_fin.read((char*) &tmp, sizeof(int));
    m_image_number=reverse(tmp);
    m_fin.read((char*) &tmp, sizeof(int));
    m_fin.read((char*) &tmp, sizeof(int));
}

size_t label_loader::generate_label(){
    unsigned char tmp;
    m_fin.read((char*) &tmp, sizeof(unsigned char));
    return tmp;
}

int label_loader::reverse(int i){
    unsigned char ch0, ch1, ch2, ch3;
    ch0=i & 255;
    ch1=(i>>8) & 255;
    ch2=(i>>16) & 255;
    ch3=(i>>24) & 255;
    return (int(ch0)<<24)+(int(ch1)<<16)+(int(ch2)<<8)+ch3;
}
