#ifndef _STDF_HPP_
#define _STDF_HPP_

#include <iostream>
#include "Record.hpp"
#include "StdfRecordFactory.hpp"

class STDF: boost::noncopyable
{
  public:
    friend class TestSTDF;
    friend std::basic_ostream<char>& operator<<(std::basic_ostream<char>& os, const STDF& stdf) {stdf.print_record(os); return os;}
    typedef std::vector<std::pair<std::basic_string<char>, RecordSharedPtr > > Container;

    enum STDFType{WRITE, READ, APPEND, MODIFY, READ_ONLY};

    ~STDF();
    STDF(const std::string& filename, STDF::STDFType type = WRITE);
    void write();
    void read(STDF::STDFType type = WRITE);
    void read_only(){read(READ_ONLY);}
    void print_record(std::ostream &os = std::cout) const;
    void clear();
    void close();

    std::basic_string<char> to_string() const;
    size_t storage() const;
    Container::iterator find(const std::basic_string<char>& name,size_t order=0);

    template<typename T> void changeValue(const std::basic_string<char>& recordname, const std::basic_string<char>& datetypename, const T& dateValue, size_t order=0);
    template<typename T> STDF& addRecord(const T& record);
    template<typename T> STDF& operator <<(const T& record);

  private:
    Container mData;
    std::ofstream *outfile;
    std::ifstream *infile;
    std::string filename;
};

template<typename T> STDF& STDF::addRecord(const T& record)
{
  T* data = new T(record); 
  data->write(*outfile);
  delete data;
  return *this;
}

template<typename T> STDF& STDF::operator <<(const T& record)
{
  T* data = new T(record);
  data->write(*outfile);
  delete data;
  return *this;
}

template<typename T> void STDF::changeValue(const std::basic_string<char>& recordname, const std::basic_string<char>& datetypename, const T& dateValue, size_t order)
{
  Container::iterator target = find(recordname,order);
  (*(target->second))[datetypename]=dateValue;
  //this->write();
}
#endif // _STDF_HPP_
