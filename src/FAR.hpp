#ifndef _FAR_HPP_
#define _FAR_HPP_

#include "DataTypes.hpp"
#include "Record.hpp"

class FAR : public Record
{
  public:
    ~FAR() {}
    FAR();
    void clear() {*STDF_VER = 4u;}
    void setVersion(char ver) {*STDF_VER = ver;}

  private:
    void setCpuType()
    {
      #ifdef __hppa
        *CPU_TYPE = 1;
      #elif defined(__i386__) || defined(__ia64__) || defined(__x86_64__)
        *CPU_TYPE = 2;
      #else
        #error "CPU type unknown."
      #endif
    }

  private:
    U1* CPU_TYPE;   // CPU type that wrote file
    U1* STDF_VER;   // STDF version number
};

FAR::FAR() : Record(Record::FAR_TYPE)
{
  CPU_TYPE = new U1(0u);
  add("CPU_TYPE", CPU_TYPE);
  STDF_VER = new U1(4u);
  add("STDF_VER", STDF_VER);

  setCpuType();
  calculate();
}

#endif
