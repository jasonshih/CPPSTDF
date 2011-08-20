#ifndef _ATR_HPP_
#define _ATR_HPP_

#include "DataTypes.hpp"
#include "Record.hpp"

class ATR : public Record
{
  public:
    ~ATR() {}
    ATR();
    void clear() {(*MOD_TIM).clear(); (*CMD_LINE).clear(); calculate();}
    void setModtime(unsigned int timestamp) {*MOD_TIM = timestamp;}
    void setCmdline(const string& cmd) {*CMD_LINE = cmd; calculate();}

  private:
    U4* MOD_TIM;    // Date and time of STDF file modification
    Cn* CMD_LINE;   // Command line of program
};

ATR::ATR() : Record(Record::ATR_TYPE)
{
  MOD_TIM = new U4(0u);
  mData.push_back(std::make_pair("MOD_TIM", MOD_TIM));
  CMD_LINE = new Cn();
  mData.push_back(std::make_pair("CMD_LINE", CMD_LINE));

  calculate();
}

#endif
