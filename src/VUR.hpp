#ifndef _VUR_HPP_
#define _VUR_HPP_

#include "DataTypes.hpp"
#include "Record.hpp"

class VUR : public Record
{
  public:
    ~VUR() {}
    VUR();
    void clear() {}

  private:
    U1*            UPT_CNT;   // Count(k) of version update entries
    KxTYPE<Cn, 2>* UPT_NAM;   // Array of Update Version Name
};

VUR::VUR() : Record(Record::VUR_TYPE)
{
  UPT_CNT = new U1(2u);
  add("UPT_CNT", UPT_CNT);
  UPT_NAM = new KxTYPE<Cn, 2>;
  (*UPT_NAM)[0] = "V4-2007";
  (*UPT_NAM)[1] = "Scan:2007.1";
  add("UPT_NAM", UPT_NAM);

  calculate();
}

#endif
