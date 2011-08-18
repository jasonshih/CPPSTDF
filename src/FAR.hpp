#ifndef _FAR_HPP_
#define _FAR_HPP_

#include "DataTypes.hpp"
#include "Record.hpp"

class FAR : public Record
{
  public:
    ~FAR() {}
    FAR();
    void clear() {STDF_VER = 4u;}
    void write(ofstream& outfile);
    void read(ifstream& infile);
    size_t storage() {return REC_LEN.getValue();}
    void to_string(vector<string>& val) const;
    void setVersion(char ver) {STDF_VER = ver;}

  private:
    void setCpuType()
    {
      #ifdef __hppa
        CPU_TYPE = 1;
      #elif defined(__i386__) || defined(__ia64__) || defined(__x86_64__)
        CPU_TYPE = 2;
      #else
        #error "CPU type unknown."
      #endif
    }
    void calculate()
    {
      REC_LEN = this->Record::storage()+CPU_TYPE.storage()+STDF_VER.storage();
    }

  private:
    U1 CPU_TYPE;
    U1 STDF_VER;
};

FAR::FAR() : Record(Record::FAR_TYPE), STDF_VER(4u)
{
  setCpuType();
  calculate();
}

void FAR::write(ofstream& outfile)
{
  this->Record::write(outfile);
  CPU_TYPE.write(outfile);
  STDF_VER.write(outfile);
}

void FAR::read(ifstream& infile)
{
  this->Record::read(infile);
  CPU_TYPE.read(infile);
  STDF_VER.read(infile);
}

void FAR::to_string(vector<string>& val) const
{
  this->Record::to_string(val);
  val.push_back(CPU_TYPE.to_string());
  val.push_back(STDF_VER.to_string());
}

#endif
