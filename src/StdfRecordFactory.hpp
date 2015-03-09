#ifndef _STDF_STDFRECORDFACTORY_HPP_
#define _STDF_STDFRECORDFACTORY_HPP_

#include "StdfRecord.hpp"

typedef boost::shared_ptr<Record> RecordSharedPtr;

class StdfRecordFactory
{
  public:
    static std::pair<std::basic_string<char>, RecordSharedPtr> Create(char REC_TYP, char REC_SUB)
    {
      std::pair<std::basic_string<char>, RecordSharedPtr> data ;
      switch(REC_TYP)
      {
        case STDF_FILE_DATA:       if(STDF_FAR_SUB == REC_SUB) {data = std::make_pair("FAR", new FAR());}
                                     else if(STDF_ATR_SUB == REC_SUB) {data = std::make_pair("ATR", new ATR());}
                                     else if(STDF_VUR_SUB == REC_SUB) {data = std::make_pair("VUR", new VUR());}
                                     break;

        case STDF_LOT_DATA:        if(STDF_MIR_SUB == REC_SUB) {data = std::make_pair("MIR", new MIR());}
                                     else if(STDF_MRR_SUB == REC_SUB) {data = std::make_pair("MRR", new MRR());}
                                     else if(STDF_PCR_SUB == REC_SUB) {data = std::make_pair("PCR", new PCR());}
                                     else if(STDF_HBR_SUB == REC_SUB) {data = std::make_pair("HBR", new HBR());}
                                     else if(STDF_SBR_SUB == REC_SUB) {data = std::make_pair("SBR", new SBR());}
                                     else if(STDF_PMR_SUB == REC_SUB) {data = std::make_pair("PMR", new PMR());}
                                     else if(STDF_PGR_SUB == REC_SUB) {data = std::make_pair("PGR", new PGR());}
                                     else if(STDF_PLR_SUB == REC_SUB) {data = std::make_pair("PLR", new PLR());}
                                     else if(STDF_RDR_SUB == REC_SUB) {data = std::make_pair("RDR", new RDR());}
                                     else if(STDF_SDR_SUB == REC_SUB) {data = std::make_pair("SDR", new SDR());}
                                     else if(STDF_PSR_SUB == REC_SUB) {data = std::make_pair("PSR", new PSR());}
                                     else if(STDF_NMR_SUB == REC_SUB) {data = std::make_pair("NMR", new NMR());}
                                     else if(STDF_CNR_SUB == REC_SUB) {data = std::make_pair("CNR", new CNR());}
                                     else if(STDF_SSR_SUB == REC_SUB) {data = std::make_pair("SSR", new SSR());}
                                     else if(STDF_CDR_SUB == REC_SUB) {data = std::make_pair("CDR", new CDR());}
                                     break;

        case STDF_WAFER_DATA:      if(STDF_WIR_SUB == REC_SUB) {data = std::make_pair("WIR", new WIR());}
                                     else if(STDF_WRR_SUB == REC_SUB) {data = std::make_pair("WRR", new WRR());}
                                     else if(STDF_WCR_SUB == REC_SUB) {data = std::make_pair("WCR", new WCR());}
                                     break;

        case STDF_PART_DATA:       if(STDF_PIR_SUB == REC_SUB) {data = std::make_pair("PIR", new PIR());}
                                     else if(STDF_PRR_SUB == REC_SUB) {data = std::make_pair("PRR", new PRR());}
                                     break;

        case STDF_TEST_DATA:       if(STDF_TSR_SUB == REC_SUB) {data = std::make_pair("TSR", new TSR());}
                                     break;

        case STDF_EXECUTION_DATA:  if(STDF_PTR_SUB == REC_SUB) {data = std::make_pair("PTR", new PTR());}
                                     else if(STDF_MPR_SUB == REC_SUB) {data = std::make_pair("MPR", new MPR());}
                                     else if(STDF_FTR_SUB == REC_SUB) {data = std::make_pair("FTR", new FTR());}
                                     else if(STDF_STR_SUB == REC_SUB) {data = std::make_pair("STR", new STR());}
                                     break;

        case STDF_SEGMENT_DATA:    if(STDF_BPS_SUB == REC_SUB) {data = std::make_pair("BPS", new BPS());}
                                     else if(STDF_EPS_SUB == REC_SUB) {data = std::make_pair("EPS", new EPS());}
                                     break;

        case STDF_GENERIC_DATA:    if(STDF_GDR_SUB == REC_SUB) {data = std::make_pair("GDR", new GDR());}
                                     else if(STDF_DTR_SUB == REC_SUB) {data = std::make_pair("DTR", new DTR());}
                                     break;
      }
      return data;
    }
};

#endif
