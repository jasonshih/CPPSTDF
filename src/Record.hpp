#ifndef _HEADER_HPP_
#define _HEADER_HPP_

#include "DataTypes.hpp"

/********
 * STDF Record Type and Sub-type Codes
 ********/
#define  STDF_FILE_DATA         ( 0)    // Information about the STDF File
  #define  STDF_FAR_SUB         (10)    // File Attributes Record (FAR)
  #define  STDF_ATR_SUB         (20)    // Audit Trail Record (ATR)
  #define  STDF_VUR_SUB         (30)    // Version Update Record (VUR)

#define  STDF_LOT_DATA          ( 1)    // Data collected on a per lot basis
  #define  STDF_MIR_SUB         (10)    // Master Information Record (MIR)
  #define  STDF_MRR_SUB         (20)    // Master Results Record (MRR)
  #define  STDF_PCR_SUB         (30)    // PartCount Record (PCR)
  #define  STDF_HBR_SUB         (40)    // Hardware Bin Record (HBR)
  #define  STDF_SBR_SUB         (50)    // Software Bin Record (SBR)
  #define  STDF_PMR_SUB         (60)    // Pin Map Record (PMR)
  #define  STDF_PGR_SUB         (62)    // Pin Group Record (PGR)
  #define  STDF_PLR_SUB         (63)    // Pin List Record (PLR)
  #define  STDF_RDR_SUB         (70)    // Retest Data Record (RDR)
  #define  STDF_SDR_SUB         (80)    // Site Description Record (SDR)
  #define  STDF_PSR_SUB         (90)    // Pattern Sequence Record (PSR)
  #define  STDF_NMR_SUB         (91)    // Name Map Record (NMR)
  #define  STDF_CNR_SUB         (92)    // Cell Name Record (CNR)
  #define  STDF_SSR_SUB         (93)    // Scan Structure Record (SSR)
  #define  STDF_CDR_SUB         (94)    // Chain Description Record (CDR)

#define  STDF_WAFER_DATA        ( 2)    // Data collected on a per wafer basis
  #define  STDF_WIR_SUB         (10)    // Wafer Information Record (WIR)
  #define  STDF_WRR_SUB         (20)    // Wafer Results Record (WRR)
  #define  STDF_WCR_SUB         (30)    // Wafer Configuration Record (WCR)

#define  STDF_PART_DATA         ( 5)    // Data collected on a per part basis
  #define  STDF_PIR_SUB         (10)    // Part Information Record (PIR)
  #define  STDF_PRR_SUB         (20)    // Part Results Record (PRR)

#define  STDF_TEST_DATA         (10)    // Data collected per test in the test program
   #define STDF_TSR_SUB         (30)    // Test Synopsis Record (TSR)

#define  STDF_EXECUTION_DATA    (15)    // Data collected per test execution
  #define  STDF_PTR_SUB         (10)    // Parametric Test Record (PTR)
  #define  STDF_MPR_SUB         (15)    // Multiple-Result Parametric Record (MPR)
  #define  STDF_FTR_SUB         (20)    // Functional Test Record (FTR)
  #define  STDF_STR_SUB         (30)    // Scan Test Record (STR)

#define  STDF_SEGMENT_DATA      (20)    // Data collected per program segment
  #define  STDF_BPS_SUB         (10)    // Begin Program Segment Record (BPS)
  #define  STDF_EPS_SUB         (20)    // END Program Segment Record (EPS)

#define  STDF_GENERIC_DATA      (50)    // Generic Data
  #define  STDF_GDR_SUB         (10)    // Generic Data Record (GDR)
  #define  STDF_DTR_SUB         (30)    // Datalog Text Record (DTR)

class Record
{
  public:
    enum RecordType
    {
      FAR_TYPE, ATR_TYPE, VUR_TYPE,

      MIR_TYPE, MRR_TYPE, PCR_TYPE, HBR_TYPE, SBR_TYPE, PMR_TYPE, PGR_TYPE, PLR_TYPE,
      RDR_TYPE, SDR_TYPE, PSR_TYPE, NMR_TYPE, CNR_TYPE, SSR_TYPE, CDR_TYPE,

      WIR_TYPE, WRR_TYPE, WCR_TYPE,

      PIR_TYPE, PRR_TYPE,

      TSR_TYPE,

      PTR_TYPE, MPR_TYPE, FTR_TYPE, STR_TYPE,

      BPS_TYPE, EPS_TYPE,

      GDR_TYPE, DTR_TYPE
    };

  public:
    virtual ~Record()
    {
      for(Container::iterator it = mData.begin(); it != mData.end(); it++) delete (it->second);
    }

    Record(Record::RecordType type);
    virtual void clear() = 0;

    void write(ofstream& outfile)
    {
      for(Container::const_iterator it = mData.begin(); it != mData.end(); it++) (it->second)->write(outfile);
    }

    void read(ifstream& infile)
    {
      for(Container::const_iterator it = mData.begin(); it != mData.end(); it++) (it->second)->read(infile, 0);
    }

    size_t storage()
    {
      return (*REC_LEN).getValue();
    }

    void to_string(vector<string>& val) const
    {
      for(Container::const_iterator it = mData.begin(); it != mData.end(); it++) val.push_back((it->second)->to_string());
    }

  protected:
    void calculate()
    {
      *REC_LEN = 0;
      for(Container::const_iterator it = mData.begin(); it != mData.end(); it++) *REC_LEN += (it->second)->storage();
    }

    Record& add(const string& name, DataType* obj)
    {
      mData.push_back(std::make_pair(name, obj));
      return *this;
    }

  private:
    typedef vector< std::pair<string, DataType*> > Container;

    Record(const Record& rhs);
    Record& operator=(const Record& rhs);

  private:
    Container       mData;

  private:
    U2* REC_LEN;
    U1* REC_TYP;
    U1* REC_SUB;

};

Record::Record(Record::RecordType type)
{
  REC_LEN = new U2(0);
  add("REC_LEN", REC_LEN);
  REC_TYP = new U1(0);
  add("REC_TYP", REC_TYP);
  REC_SUB = new U1(0);
  add("REC_SUB", REC_SUB);

  switch(type)
  {
    case FAR_TYPE:  *REC_SUB = STDF_FAR_SUB; *REC_TYP = STDF_FILE_DATA; break;
    case ATR_TYPE:  *REC_SUB = STDF_ATR_SUB; *REC_TYP = STDF_FILE_DATA; break;
    case VUR_TYPE:  *REC_SUB = STDF_VUR_SUB; *REC_TYP = STDF_FILE_DATA; break;

    case MIR_TYPE:  *REC_SUB = STDF_MIR_SUB; *REC_TYP = STDF_LOT_DATA; break;
    case MRR_TYPE:  *REC_SUB = STDF_MRR_SUB; *REC_TYP = STDF_LOT_DATA; break;
    case PCR_TYPE:  *REC_SUB = STDF_PCR_SUB; *REC_TYP = STDF_LOT_DATA; break;
    case HBR_TYPE:  *REC_SUB = STDF_HBR_SUB; *REC_TYP = STDF_LOT_DATA; break;
    case SBR_TYPE:  *REC_SUB = STDF_SBR_SUB; *REC_TYP = STDF_LOT_DATA; break;
    case PMR_TYPE:  *REC_SUB = STDF_PMR_SUB; *REC_TYP = STDF_LOT_DATA; break;
    case PGR_TYPE:  *REC_SUB = STDF_PGR_SUB; *REC_TYP = STDF_LOT_DATA; break;
    case PLR_TYPE:  *REC_SUB = STDF_PLR_SUB; *REC_TYP = STDF_LOT_DATA; break;
    case RDR_TYPE:  *REC_SUB = STDF_RDR_SUB; *REC_TYP = STDF_LOT_DATA; break;
    case SDR_TYPE:  *REC_SUB = STDF_SDR_SUB; *REC_TYP = STDF_LOT_DATA; break;
    case PSR_TYPE:  *REC_SUB = STDF_PSR_SUB; *REC_TYP = STDF_LOT_DATA; break;
    case NMR_TYPE:  *REC_SUB = STDF_NMR_SUB; *REC_TYP = STDF_LOT_DATA; break;
    case CNR_TYPE:  *REC_SUB = STDF_CNR_SUB; *REC_TYP = STDF_LOT_DATA; break;
    case SSR_TYPE:  *REC_SUB = STDF_SSR_SUB; *REC_TYP = STDF_LOT_DATA; break;
    case CDR_TYPE:  *REC_SUB = STDF_CDR_SUB; *REC_TYP = STDF_LOT_DATA; break;

    case WIR_TYPE:  *REC_SUB = STDF_WIR_SUB; *REC_TYP = STDF_WAFER_DATA; break;
    case WRR_TYPE:  *REC_SUB = STDF_WRR_SUB; *REC_TYP = STDF_WAFER_DATA; break;
    case WCR_TYPE:  *REC_SUB = STDF_WCR_SUB; *REC_TYP = STDF_WAFER_DATA; break;

    case PIR_TYPE:  *REC_SUB = STDF_PIR_SUB; *REC_TYP = STDF_PART_DATA; break;
    case PRR_TYPE:  *REC_SUB = STDF_PRR_SUB; *REC_TYP = STDF_PART_DATA; break;

    case TSR_TYPE:  *REC_SUB = STDF_TSR_SUB; *REC_TYP = STDF_TEST_DATA; break;

    case PTR_TYPE:  *REC_SUB = STDF_PTR_SUB; *REC_TYP = STDF_EXECUTION_DATA; break;
    case MPR_TYPE:  *REC_SUB = STDF_MPR_SUB; *REC_TYP = STDF_EXECUTION_DATA; break;
    case FTR_TYPE:  *REC_SUB = STDF_FTR_SUB; *REC_TYP = STDF_EXECUTION_DATA; break;
    case STR_TYPE:  *REC_SUB = STDF_STR_SUB; *REC_TYP = STDF_EXECUTION_DATA; break;

    case BPS_TYPE:  *REC_SUB = STDF_BPS_SUB; *REC_TYP = STDF_SEGMENT_DATA; break;
    case EPS_TYPE:  *REC_SUB = STDF_EPS_SUB; *REC_TYP = STDF_SEGMENT_DATA; break;

    case GDR_TYPE:  *REC_SUB = STDF_GDR_SUB; *REC_TYP = STDF_GENERIC_DATA; break;
    case DTR_TYPE:  *REC_SUB = STDF_DTR_SUB; *REC_TYP = STDF_GENERIC_DATA; break;
  }
}

#endif
