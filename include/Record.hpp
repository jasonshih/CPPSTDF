#ifndef _HEADER_HPP_
#define _HEADER_HPP_

#include "DataTypes.hpp"
#include <boost/noncopyable.hpp>

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

class Record: public boost::noncopyable
{
  friend std::basic_ostream<char>& operator<<(std::basic_ostream<char>& os, Record& record) 
  {
    std::vector<std::basic_string<char> > strings;
    record.to_string1(strings);
    for(size_t i = 0; i < strings.size(); i++)
    {
      os << strings[i]; 
    }

    return os;
  }

  private:
    typedef std::vector<std::pair<std::basic_string<char>, DataType::DataTypeSharedPtr> > Container;

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
    Record(){}
    virtual ~Record(){}
    explicit Record(Record::RecordType type)
      : REC_LEN(new U2(0))
      , REC_TYP(new U1(0))
      , REC_SUB(new U1(0))
    {
      switch(type)
      {
        case FAR_TYPE:  *REC_SUB = STDF_FAR_SUB; *REC_TYP = STDF_FILE_DATA; mData.reserve(5);  break;
        case ATR_TYPE:  *REC_SUB = STDF_ATR_SUB; *REC_TYP = STDF_FILE_DATA; mData.reserve(5);  break;
        case VUR_TYPE:  *REC_SUB = STDF_VUR_SUB; *REC_TYP = STDF_FILE_DATA; mData.reserve(5);  break;

        case MIR_TYPE:  *REC_SUB = STDF_MIR_SUB; *REC_TYP = STDF_LOT_DATA; mData.reserve(41);  break;
        case MRR_TYPE:  *REC_SUB = STDF_MRR_SUB; *REC_TYP = STDF_LOT_DATA; mData.reserve(7);  break;
        case PCR_TYPE:  *REC_SUB = STDF_PCR_SUB; *REC_TYP = STDF_LOT_DATA; mData.reserve(10);  break;
        case HBR_TYPE:  *REC_SUB = STDF_HBR_SUB; *REC_TYP = STDF_LOT_DATA; mData.reserve(9);  break;
        case SBR_TYPE:  *REC_SUB = STDF_SBR_SUB; *REC_TYP = STDF_LOT_DATA; mData.reserve(9);  break;
        case PMR_TYPE:  *REC_SUB = STDF_PMR_SUB; *REC_TYP = STDF_LOT_DATA; mData.reserve(10);  break;
        case PGR_TYPE:  *REC_SUB = STDF_PGR_SUB; *REC_TYP = STDF_LOT_DATA; mData.reserve(7);  break;
        case PLR_TYPE:  *REC_SUB = STDF_PLR_SUB; *REC_TYP = STDF_LOT_DATA; mData.reserve(11);  break;
        case RDR_TYPE:  *REC_SUB = STDF_RDR_SUB; *REC_TYP = STDF_LOT_DATA; mData.reserve(5);  break;
        case SDR_TYPE:  *REC_SUB = STDF_SDR_SUB; *REC_TYP = STDF_LOT_DATA; mData.reserve(23);  break;
        case PSR_TYPE:  *REC_SUB = STDF_PSR_SUB; *REC_TYP = STDF_LOT_DATA; mData.reserve(16);  break;
        case NMR_TYPE:  *REC_SUB = STDF_NMR_SUB; *REC_TYP = STDF_LOT_DATA; mData.reserve(8);  break;
        case CNR_TYPE:  *REC_SUB = STDF_CNR_SUB; *REC_TYP = STDF_LOT_DATA; mData.reserve(6);  break;
        case SSR_TYPE:  *REC_SUB = STDF_SSR_SUB; *REC_TYP = STDF_LOT_DATA; mData.reserve(6);  break;
        case CDR_TYPE:  *REC_SUB = STDF_CDR_SUB; *REC_TYP = STDF_LOT_DATA; mData.reserve(16);  break;

        case WIR_TYPE:  *REC_SUB = STDF_WIR_SUB; *REC_TYP = STDF_WAFER_DATA; mData.reserve(7);  break;
        case WRR_TYPE:  *REC_SUB = STDF_WRR_SUB; *REC_TYP = STDF_WAFER_DATA; mData.reserve(17);  break;
        case WCR_TYPE:  *REC_SUB = STDF_WCR_SUB; *REC_TYP = STDF_WAFER_DATA; mData.reserve(12);  break;

        case PIR_TYPE:  *REC_SUB = STDF_PIR_SUB; *REC_TYP = STDF_PART_DATA; mData.reserve(5);  break;
        case PRR_TYPE:  *REC_SUB = STDF_PRR_SUB; *REC_TYP = STDF_PART_DATA; mData.reserve(15);  break;

        case TSR_TYPE:  *REC_SUB = STDF_TSR_SUB; *REC_TYP = STDF_TEST_DATA; mData.reserve(19);  break;

        case PTR_TYPE:  *REC_SUB = STDF_PTR_SUB; *REC_TYP = STDF_EXECUTION_DATA; mData.reserve(23);  break;
        case MPR_TYPE:  *REC_SUB = STDF_MPR_SUB; *REC_TYP = STDF_EXECUTION_DATA; mData.reserve(30);  break;
        case FTR_TYPE:  *REC_SUB = STDF_FTR_SUB; *REC_TYP = STDF_EXECUTION_DATA; mData.reserve(31);  break;
        case STR_TYPE:  *REC_SUB = STDF_STR_SUB; *REC_TYP = STDF_EXECUTION_DATA; mData.reserve(62);  break;

        case BPS_TYPE:  *REC_SUB = STDF_BPS_SUB; *REC_TYP = STDF_SEGMENT_DATA; mData.reserve(4);  break;
        case EPS_TYPE:  *REC_SUB = STDF_EPS_SUB; *REC_TYP = STDF_SEGMENT_DATA; mData.reserve(3);  break;

        case GDR_TYPE:  *REC_SUB = STDF_GDR_SUB; *REC_TYP = STDF_GENERIC_DATA; mData.reserve(5);  break;
        case DTR_TYPE:  *REC_SUB = STDF_DTR_SUB; *REC_TYP = STDF_GENERIC_DATA; mData.reserve(4);  break;
      }
      add("REC_LEN", REC_LEN);
      add("REC_TYP", REC_TYP);
      add("REC_SUB", REC_SUB);
    }

    virtual void clear()
    {
      Container::iterator begin = mData.begin();
      std::advance(begin, 3);
      std::for_each(begin, mData.end(), boost::bind(DataType::Cleaner(), boost::bind(&Container::value_type::second, _1)));
      //std::for_each(begin, mData.end(), boost::bind(&DataType::clear, boost::bind(&Container::value_type::second, _1))); // not working
    }

    void delete_element(const std::basic_string<char>& name)
    {
      Container::iterator target = find(name);
      assert(mData.end()!=target);
      mData.erase(target);
    }

    void replace_element(const std::basic_string<char>& name, DataType::DataTypeSharedPtr obj)
    {
      Container::iterator target = find(name);
      assert(mData.end()!=target);
      target->second = obj;
    }

    DataType& operator[] (const std::basic_string<char>& name)
    {
       Container::iterator target = find(name);
       assert(target != mData.end());
       return *(target->second);
    }

    DataType& operator[] (const std::basic_string<char>& name) const
    {
       Container::const_iterator target = find(name);
       assert(target != mData.end());
       return *(target->second);
    }

    template<typename Derived> void set(const std::basic_string<char>& name, const Derived& value)
    {
      this->operator[](name) = value;
    }

    template<typename Derived> const Derived& get(const std::basic_string<char>& name) const
    {
      return dynamic_cast<Derived&>(this->operator[](name));
    }

    virtual void write(std::ofstream& outfile)
    {
      calculate();
      std::for_each(mData.begin(), mData.end(), boost::bind(DataType::Writer(outfile), boost::bind(&Container::value_type::second, _1)));
    }

    virtual void read(std::ifstream& infile)
    {
      std::for_each(mData.begin(), mData.end(), boost::bind(DataType::Reader(infile), boost::bind(&Container::value_type::second, _1)));
    }

    size_t storage()
    {
      calculate();
      return REC_LEN->getValue();
    }

    void to_string(std::vector<std::basic_string<char> >& val)
    {
      calculate();
      val.reserve(mData.size());
      std::transform(mData.begin(), mData.end(), std::back_inserter(val), boost::bind(DataType::Stringer(), boost::bind(&Container::value_type::second, _1)));
    }

    // for keeping same output with STDFreader
    void to_string1(std::vector<std::basic_string<char> >& val)
    {
      calculate();
      val.reserve(mData.size());
      val.push_back(" Record\n"); 
      for(size_t i=3;i<mData.size();i++)
      {
        val.push_back("  "); 
        val.push_back(mData[i].first); 
        switch(mData[i].first.size())
        {
          case 4: val.push_back(":          ");break;
          case 5: val.push_back(":         ");break;
          case 6: val.push_back(":        ");break;
          case 7: val.push_back(":       ");break;
          case 8: val.push_back(":      ");break;
        }

        if(  !mData[i].first.compare("MOD_TIME")
           ||!mData[i].first.compare("MOD_TIM")
           ||!mData[i].first.compare("START_T")
           ||!mData[i].first.compare("SETUP_T")
           ||!mData[i].first.compare("FINISH_T")
          )
        {
          time_t timeStamp = reinterpret_cast<boost::shared_ptr<U4> &>(mData[i].second)->getValue();
          struct tm tmResult;
          char timestr[129] = {0};
          strftime(timestr, 128, "%d-%b-%Y %X", gmtime_r(&timeStamp, &tmResult));
          std::string mod_time_ts = (timestr[0] == '\0')? "": timestr;
          val.push_back(mData[i].second->to_string());
          val.push_back(" (");
          val.push_back(mod_time_ts);
          val.push_back(")");
        }
#if OLD_STDF_VERSION
        else if(   !mData[i].first.compare("LO_LIMIT")
                || !mData[i].first.compare("HI_LIMIT")
                || !mData[i].first.compare("RESULT")
                || !mData[i].first.compare("TEST_MIN")
                || !mData[i].first.compare("TEST_MAX")
                || !mData[i].first.compare("TEST_TIM")
               )
        {
          std::stringstream ss;
          ss.setf(std::ios::scientific | std::ios::uppercase);
          ss << std::setprecision(12) << std::dec << reinterpret_cast<boost::shared_ptr<R4> &>(mData[i].second)->getValue();
          val.push_back(ss.str());
        }        
#endif
        else val.push_back(mData[i].second->to_string()); 

        val.push_back("\n"); 
      }
    }

    void calculate()
    {
      DataType::StorageCalculator totalStorage;
      std::for_each(mData.begin(), mData.end(), boost::bind(boost::ref(totalStorage), boost::bind(&Container::value_type::second, _1)));
      size_t headerStorage = REC_LEN->storage() + REC_TYP->storage() + REC_SUB->storage();
      assert((totalStorage >= headerStorage) && totalStorage <= (headerStorage + REC_LEN->max()));
      *REC_LEN = U2(totalStorage - headerStorage);
    }

  protected:
    Record& add(const std::basic_string<char>& name, DataType::DataTypeSharedPtr obj)
    {
      mData.push_back(std::make_pair(name, obj));
      return *this;
    }

    Container::iterator find(const std::basic_string<char>& name)
    {
      std::equal_to<const std::basic_string<char> > e;
      return std::find_if(mData.begin(), mData.end(), boost::bind(e, boost::ref(name), boost::bind(&Container::value_type::first, _1)));
    }

    Container::const_iterator find(const std::basic_string<char>& name) const
    {
      std::equal_to<const std::basic_string<char> > e;
      return std::find_if(mData.begin(), mData.end(), boost::bind(e, boost::ref(name), boost::bind(&Container::value_type::first, _1)));
    }

  private:
    boost::shared_ptr<U2> REC_LEN;
    boost::shared_ptr<U1> REC_TYP;
    boost::shared_ptr<U1> REC_SUB;

    Container       mData;
};

#endif
