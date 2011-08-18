#ifndef _VUR_HPP_
#define _VUR_HPP_

#include "DataTypes.hpp"
#include "Record.hpp"

class VUR : public Record
{
  public:
    ~VUR() {}
    VUR() : Record(Record::VUR_TYPE), UPT_CNT(2u) {UPT_NAM[0] = "V4-2007"; UPT_NAM[1] = "Scan:2007.1"; calculate();}
    void clear() {}
    void write(ofstream& outfile);
    void read(ifstream& infile);
    size_t storage() {return REC_LEN.getValue();}
    void to_string(vector<string>& val) const;

  private:
    inline void calculate()
    {
      REC_LEN = this->Record::storage()+UPT_CNT.storage()+UPT_NAM.storage();
    }

  private:
    U1 UPT_CNT;
    KxTYPE<Cn, 2> UPT_NAM;
};

void VUR::write(ofstream& outfile)
{
  this->Record::write(outfile);
  UPT_CNT.write(outfile);
  UPT_NAM.write(outfile);
}

void VUR::read(ifstream& infile)
{
  this->Record::read(infile);
  UPT_CNT.read(infile);
  UPT_NAM.read(infile);
}

void VUR::to_string(vector<string>& val) const
{
  this->Record::to_string(val);
  val.push_back(UPT_CNT.to_string());
  val.push_back(UPT_NAM.to_string());
}

#endif
