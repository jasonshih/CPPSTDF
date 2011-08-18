#ifndef _ATR_HPP_
#define _ATR_HPP_

#include "DataTypes.hpp"
#include "Record.hpp"

class ATR : public Record
{
  public:
    ~ATR() {}
    ATR() : Record(Record::ATR_TYPE) {calculate();}
    void clear() {MOD_TIM.clear(); CMD_LINE.clear(); calculate();}
    void write(ofstream& outfile);
    void read(ifstream& infile);
    size_t storage() {return REC_LEN.getValue();}
    void to_string(vector<string>& val) const;
    void setModtime(unsigned int timestamp) {MOD_TIM = timestamp;}
    void setCmdline(const string& cmd) {CMD_LINE = cmd; calculate();}

  private:
    inline void calculate()
    {
      REC_LEN = this->Record::storage()+MOD_TIM.storage()+CMD_LINE.storage();
    }

  private:
    U4 MOD_TIM;
    Cn CMD_LINE;
};

void ATR::write(ofstream& outfile)
{
  this->Record::write(outfile);
  MOD_TIM.write(outfile);
  CMD_LINE.write(outfile);
}

void ATR::read(ifstream& infile)
{
  this->Record::read(infile);
  MOD_TIM.read(infile);
  CMD_LINE.read(infile);
}

void ATR::to_string(vector<string>& val) const
{
  this->Record::to_string(val);
  val.push_back(MOD_TIM.to_string());
  val.push_back(CMD_LINE.to_string());
}

#endif
