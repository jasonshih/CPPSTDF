#ifndef _MIR_HPP_
#define _MIR_HPP_

#include <utility>

#include "DataTypes.hpp"
#include "Record.hpp"


class MIR : public Record
{
  public:
    ~MIR() {}
    MIR();
    void clear() {}

  private:
};

MIR::MIR() : Record(Record::MIR_TYPE)
{
    add("SETUP_T", new U4());    // Date and time of job setup
    add("START_T", new U4());    // Date and time first part tested
    add("STAT_NUM", new U1());   // Tester station number
    add("MODE_COD", new C1());   // Test mode code (e.g. prod, dev)
    add("RTST_COD", new C1());   // Lot retest code
    add("PROT_COD", new C1());   // Data protection code
    add("BURN_TIM", new U2());   // Burn-in time (in minutes)
    add("CMOD_COD", new C1());   // Command mode code
    add("LOT_ID", new Cn());     // Lot ID (customer specified)
    add("PART_TYP", new Cn());   // Part type (or Porduct ID)
    add("NODE_NAM", new Cn());   // Name of node which generated data
    add("TSTR_TYP", new Cn());   // Tester type
    add("JOB_NAM", new Cn());    // Job name (test program name)
    add("JOB_REV", new Cn());    // Job (test program) revision number
    add("SBLOT_ID", new Cn());   // Sublot ID
    add("OPER_NAM", new Cn());   // Operator name (at setup time)
    add("EXEC_TYP", new Cn());   // Tester exec software type
    add("EXEC_VER", new Cn());   // Tester exec software version number
    add("TEST_COD", new Cn());   // Test phase or step code
    add("TST_TEMP", new Cn());   // Test temperature
    add("USER_TXT", new Cn());   // Generic user text
    add("AUX_FILE", new Cn());   // Name of auxiliary data file
    add("PKG_TYP", new Cn());    // Package type
    add("FAMLY_ID", new Cn());   // Product family ID
    add("DATE_COD", new Cn());   // Date code
    add("FACIL_ID", new Cn());   // Test facility ID
    add("FLOOR_ID", new Cn());   // Test floor ID
    add("PROC_ID", new Cn());    // Fabrication Process ID
    add("OPER_FRQ", new Cn());   // Operation frequency or step
    add("SPEC_NAM", new Cn());   // Test specification name
    add("SPEC_VER", new Cn());   // Test specification version number
    add("FLOW_ID", new Cn());    // Test flow ID
    add("SETUP_ID", new Cn());   // Test setup ID
    add("DSGN_REV", new Cn());   // Device design revision
    add("ENG_ID", new Cn());     // Engineering lot ID
    add("ROM_COD", new Cn());    // ROM Code ID
    add("SERL_NUM", new Cn());   // Tester serial number
    add("SUPR_NAM", new Cn());   // Supervisor name or ID

    calculate();
}

#endif
