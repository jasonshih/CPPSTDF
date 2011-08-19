#ifndef _MIR_HPP_
#define _MIR_HPP_

#include <utility>

#include "DataTypes.hpp"
#include "Record.hpp"


class MIR : public Record
{
  public:
    ~MIR() {for(Container::iterator it = mData.begin(); it != mData.end(); it++) delete (it->second);}
    MIR();
    void clear() {}
    void write(ofstream& outfile);
    void read(ifstream& infile);
    size_t storage() {return REC_LEN.getValue();}
    void to_string(vector<string>& val) const;

  private:
    typedef vector< std::pair<string, DataType*> > Container;

    void calculate()
    {
      REC_LEN = this->Record::storage();
      for(Container::const_iterator it = mData.begin(); it != mData.end(); it++) REC_LEN += (it->second)->storage();
    }

  private:
    Container       mData;
};

MIR::MIR() : Record(Record::MIR_TYPE)
{
    mData.push_back(std::make_pair("SETUP_T", new U4()));    // Date and time of job setup
    mData.push_back(std::make_pair("START_T", new U4()));    // Date and time first part tested
    mData.push_back(std::make_pair("STAT_NUM", new U1()));   // Tester station number
    mData.push_back(std::make_pair("MODE_COD", new C1()));   // Test mode code (e.g. prod, dev)
    mData.push_back(std::make_pair("RTST_COD", new C1()));   // Lot retest code
    mData.push_back(std::make_pair("PROT_COD", new C1()));   // Data protection code
    mData.push_back(std::make_pair("BURN_TIM", new U2()));   // Burn-in time (in minutes)
    mData.push_back(std::make_pair("CMOD_COD", new C1()));   // Command mode code
    mData.push_back(std::make_pair("LOT_ID", new Cn()));     // Lot ID (customer specified)
    mData.push_back(std::make_pair("PART_TYP", new Cn()));   // Part type (or Porduct ID)
    mData.push_back(std::make_pair("NODE_NAM", new Cn()));   // Name of node which generated data
    mData.push_back(std::make_pair("TSTR_TYP", new Cn()));   // Tester type
    mData.push_back(std::make_pair("JOB_NAM", new Cn()));    // Job name (test program name)
    mData.push_back(std::make_pair("JOB_REV", new Cn()));    // Job (test program) revision number
    mData.push_back(std::make_pair("SBLOT_ID", new Cn()));   // Sublot ID
    mData.push_back(std::make_pair("OPER_NAM", new Cn()));   // Operator name (at setup time)
    mData.push_back(std::make_pair("EXEC_TYP", new Cn()));   // Tester exec software type
    mData.push_back(std::make_pair("EXEC_VER", new Cn()));   // Tester exec software version number
    mData.push_back(std::make_pair("TEST_COD", new Cn()));   // Test phase or step code
    mData.push_back(std::make_pair("TST_TEMP", new Cn()));   // Test temperature
    mData.push_back(std::make_pair("USER_TXT", new Cn()));   // Generic user text
    mData.push_back(std::make_pair("AUX_FILE", new Cn()));   // Name of auxiliary data file
    mData.push_back(std::make_pair("PKG_TYP", new Cn()));    // Package type
    mData.push_back(std::make_pair("FAMLY_ID", new Cn()));   // Product family ID
    mData.push_back(std::make_pair("DATE_COD", new Cn()));   // Date code
    mData.push_back(std::make_pair("FACIL_ID", new Cn()));   // Test facility ID
    mData.push_back(std::make_pair("FLOOR_ID", new Cn()));   // Test floor ID
    mData.push_back(std::make_pair("PROC_ID", new Cn()));    // Fabrication Process ID
    mData.push_back(std::make_pair("OPER_FRQ", new Cn()));   // Operation frequency or step
    mData.push_back(std::make_pair("SPEC_NAM", new Cn()));   // Test specification name
    mData.push_back(std::make_pair("SPEC_VER", new Cn()));   // Test specification version number
    mData.push_back(std::make_pair("FLOW_ID", new Cn()));    // Test flow ID
    mData.push_back(std::make_pair("SETUP_ID", new Cn()));   // Test setup ID
    mData.push_back(std::make_pair("DSGN_REV", new Cn()));   // Device design revision
    mData.push_back(std::make_pair("ENG_ID", new Cn()));     // Engineering lot ID
    mData.push_back(std::make_pair("ROM_COD", new Cn()));    // ROM Code ID
    mData.push_back(std::make_pair("SERL_NUM", new Cn()));   // Tester serial number
    mData.push_back(std::make_pair("SUPR_NAM", new Cn()));   // Supervisor name or ID

    calculate();
}

void MIR::write(ofstream& outfile)
{
  this->Record::write(outfile);
  for(Container::const_iterator it = mData.begin(); it != mData.end(); it++) (it->second)->write(outfile);
}

void MIR::read(ifstream& infile)
{
  this->Record::read(infile);
  for(Container::const_iterator it = mData.begin(); it != mData.end(); it++) (it->second)->read(infile, 0);
}

void MIR::to_string(vector<string>& val) const
{
  this->Record::to_string(val);
  for(Container::const_iterator it = mData.begin(); it != mData.end(); it++) val.push_back((it->second)->to_string());
}

#endif
