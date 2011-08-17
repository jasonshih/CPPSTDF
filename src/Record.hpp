#ifndef _HEADER_HPP_
#define _HEADER_HPP_

#include "vector"

#include "DataTypes.hpp"

using std::vector;

class Record
{
  public:
    enum Type
    {
      STDF_FILE_TYPE       =  0u,    // Information about the STDF File
      STDF_LOT_TYPE        =  1u,    // Data collected on a per lot basis
      STDF_WAFER_TYPE      =  2u,    // Data collected per wafer
      STDF_PART_TYPE       =  5u,    // Data collected on a per part basis
      STDF_TEST_TYPE       = 10u,    // Data collected per test in the test program
      STDF_EXECUTION_TYPE  = 15u,    // Data collected per test execution
      STDF_SEGMENT_TYPE    = 20u,    // Data collected per program segment
      STDF_GENERIC_TYPE    = 50u,    // Generic Data
      STDF_IMAGE_TYPE      = 180u,   // Reserved Types
      STDF_IG900_TYPE      = 181u,   // Reserved Types
    };

    enum SubType
    {
      STDF_FAR_SUB_TYPE    = 10u,    // File Attributes Record (FAR)
      STDF_ATR_SUB_TYPE    = 20u,    // Audit Trail Record (ATR)
      STDF_VUR_SUB_TYPE    = 30u,    // Version Update Record (VUR)

      STDF_MIR_SUB_TYPE    = 10u,    // Master Information Record (MIR)
      STDF_MRR_SUB_TYPE    = 20u,    // Master Results Record (MRR)
      STDF_PCR_SUB_TYPE    = 30u,    // PartCount Record (PCR)
      STDF_HBR_SUB_TYPE    = 40u,    // Hardware Bin Record (HBR)
      STDF_SBR_SUB_TYPE    = 50u,    // Software Bin Record (SBR)
      STDF_PMR_SUB_TYPE    = 60u,    // Pin Map Record (PMR)
      STDF_PGR_SUB_TYPE    = 62u,    // Pin Group Record (PGR)
      STDF_PLR_SUB_TYPE    = 63u,    // Pin List Record (PLR)
      STDF_RDR_SUB_TYPE    = 70u,    // Retest Data Record (RDR)
      STDF_SDR_SUB_TYPE    = 80u,    // Site Description Record (SDR)
      STDF_PSR_SUB_TYPE    = 90u,    // Pattern Sequence Record (PSR)
      STDF_NMR_SUB_TYPE    = 91u,    // Name Map Record (NMR)
      STDF_CNR_SUB_TYPE    = 92u,    // Cell Name Record (CNR)
      STDF_SSR_SUB_TYPE    = 93u,    // Scan Structure Record (SSR)
      STDF_CDR_SUB_TYPE    = 94u,    // Chain Description Record (CDR)

      STDF_WIR_SUB_TYPE    = 10u,    // Wafer Information Record (WIR)
      STDF_WRR_SUB_TYPE    = 20u,    // Wafer Results Record (WRR)
      STDF_WCR_SUB_TYPE    = 30u,    // Wafer Configuration Record (WCR)

      STDF_PIR_SUB_TYPE    = 10u,    // Part Information Record (PIR)
      STDF_PRR_SUB_TYPE    = 20u,    // Part Results Record (PRR)

      STDF_TSR_SUB_TYPE    = 30u,    // Test Synopsis Record (TSR)

      STDF_PTR_SUB_TYPE    = 10u,    // Parametric Test Record (PTR)
      STDF_MPR_SUB_TYPE    = 15u,    // Multiple-Result Parametric Record (MPR)
      STDF_FTR_SUB_TYPE    = 20u,    // Functional Test Record (FTR)
      STDF_STR_SUB_TYPE    = 30u,    // Scan Test Record (STR)

      STDF_BPS_SUB_TYPE    = 10u,    // Begin Program Segment Record (BPS)
      STDF_EPS_SUB_TYPE    = 20u,    // END Program Segment Record (EPS)

      STDF_GDR_SUB_TYPE    = 10u,    // Generic Data Record (GDR)
      STDF_DTR_SUB_TYPE    = 30u,    // Datalog Text Record (DTR)
    };

  public:
    virtual ~Record() {}
    Record() {}
    virtual void clear() = 0;
    virtual void write(ofstream& outfile);
    virtual void read(ifstream& infile);
    virtual size_t storage();
    virtual void to_string(vector<string>& val) const;
    void setRecordType(Record::SubType type);

  private:
    Record(const Record& rhs);
    Record& operator=(const Record& rhs);

  protected:
    U2 REC_LEN;
    U1 REC_TYP;
    U1 REC_SUB;

};

void Record::setRecordType(Record::SubType type)
{
  REC_SUB = type;
  switch(type)
  {
    case STDF_FAR_SUB_TYPE:
    case STDF_ATR_SUB_TYPE:
    case STDF_VUR_SUB_TYPE:
      REC_TYP = STDF_FILE_TYPE;
      break;
/*
    case STDF_MIR_SUB_TYPE:
    case STDF_MRR_SUB_TYPE:
    case STDF_PCR_SUB_TYPE:
    case STDF_HBR_SUB_TYPE:
    case STDF_SBR_SUB_TYPE:
    case STDF_PMR_SUB_TYPE:
    case STDF_PGR_SUB_TYPE:
    case STDF_PLR_SUB_TYPE:
    case STDF_RDR_SUB_TYPE:
    case STDF_SDR_SUB_TYPE:
    case STDF_PSR_SUB_TYPE:
    case STDF_NMR_SUB_TYPE:
    case STDF_CNR_SUB_TYPE:
    case STDF_SSR_SUB_TYPE:
    case STDF_CDR_SUB_TYPE:
      REC_TYP = STDF_LOT_TYPE;
      break;
    case STDF_WIR_SUB_TYPE:
    case STDF_WRR_SUB_TYPE:
    case STDF_WCR_SUB_TYPE:
      REC_TYP = STDF_WAFER_TYPE;
      break;
    case STDF_PIR_SUB_TYPE:
    case STDF_PRR_SUB_TYPE:
      REC_TYP = STDF_PART_TYPE;
      break;
    case STDF_TSR_SUB_TYPE:
      REC_TYP = STDF_TEST_TYPE;
      break;
    case STDF_PTR_SUB_TYPE:
    case STDF_MPR_SUB_TYPE:
    case STDF_FTR_SUB_TYPE:
    case STDF_STR_SUB_TYPE:
      REC_TYP = STDF_EXECUTION_TYPE;
      break;
    case STDF_BPS_SUB_TYPE:
    case STDF_EPS_SUB_TYPE:
      REC_TYP = STDF_SEGMENT_TYPE;
      break;
    case STDF_GDR_SUB_TYPE:
    case STDF_DTR_SUB_TYPE:
      REC_TYP = STDF_GENERIC_TYPE;
      break;
*/
  }
}

void Record::write(ofstream& outfile)
{
  REC_LEN.write(outfile);
  REC_TYP.write(outfile);
  REC_SUB.write(outfile);
}

void Record::read(ifstream& infile)
{
  REC_LEN.read(infile);
  REC_TYP.read(infile);
  REC_SUB.read(infile);
}

size_t Record::storage()
{
  return REC_LEN.storage()+REC_TYP.storage()+REC_SUB.storage();
}

void Record::to_string(vector<string>& val) const
{
  val.push_back(REC_LEN.to_string());
  val.push_back(REC_TYP.to_string());
  val.push_back(REC_SUB.to_string());
}

#endif
