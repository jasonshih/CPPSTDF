#ifndef _STDF_RECORD_HPP_
#define _STDF_RECORD_HPP_

#include "DataTypes.hpp"
#include "Record.hpp"

////////////////////////////// FILE //////////////////////////////

class FAR : public Record
{
  public:
    ~FAR() {}
    FAR() : Record(Record::FAR_TYPE)
    {
      add("CPU_TYPE", boost::shared_ptr<U1>(new U1()));
      add("STDF_VER", boost::shared_ptr<U1>(new U1(4u)));

      setCputype();
    }
    FAR(const FAR& far) : Record(Record::FAR_TYPE)
    {
      add("CPU_TYPE", boost::shared_ptr<U1>(new U1(far.getCputype())));
      add("STDF_VER", boost::shared_ptr<U1>(new U1(far.getStdfver())));

      setCputype();
    }
    void clear() {(*this)["STDF_VER"] = U1(4u);}
    void setStdfver(char ver) {(*this)["STDF_VER"] = U1(ver);}

    const U1& getStdfver()const {return dynamic_cast<U1&>((*this)["STDF_VER"]);}
    const U1& getCputype()const {return dynamic_cast<U1&>((*this)["CPU_TYPE"]);}

  private:
    void setCputype()
    {
#ifdef __hppa
      (*this)["CPU_TYPE"] = U1(1);  // CPU type that wrote file
#elif defined(__i386__) || defined(__ia64__) || defined(__x86_64__)
      (*this)["CPU_TYPE"] = U1(2);  // STDF version number
#else
#error "CPU type unknown."
#endif
    }

};


class ATR : public Record
{
  public:
    ~ATR() {}
    ATR() : Record(Record::ATR_TYPE)
    {
      add("MOD_TIM", boost::shared_ptr<U4>(new U4()));
      add("CMD_LINE", boost::shared_ptr<Cn>(new Cn()));
    }
    ATR(const ATR& atr) : Record(Record::ATR_TYPE)
    {
      add("MOD_TIM", boost::shared_ptr<U4>(new U4(atr.getModtim())));
      add("CMD_LINE", boost::shared_ptr<Cn>(new Cn(atr.getCmdline())));
    }
    void clear() {Record::clear();}
    void setModtim(unsigned int timestamp) {(*this)["MOD_TIM"] = U4(timestamp);}
    void setCmdline(const std::basic_string<char>& cmd) {(*this)["CMD_LINE"] = Cn(cmd);}

    const U4& getModtim()const {return dynamic_cast<U4&>((*this)["MOD_TIM"]);}// Date and time of STDF file modification
    const Cn& getCmdline()const {return dynamic_cast<Cn&>((*this)["CMD_LINE"]);}// Command line of program
};


class VUR : public Record
{
  public:
    ~VUR() {}
    VUR() : Record(Record::VUR_TYPE)
    {
      add("UPD_CNT", boost::shared_ptr<U1>(new U1(1)));
      add("UPD_NAM", boost::shared_ptr<JxTYPE<Cn> >(new JxTYPE<Cn>(dynamic_cast<U1&>((*this)["UPD_CNT"]).getValue())));
      dynamic_cast<JxTYPE<Cn> &>((*this)["UPD_NAM"])[0] = Cn("V4-2007,Scan:2007.1");
    }
    VUR(const VUR& vur) : Record(Record::VUR_TYPE)
    {
      add("UPD_CNT", boost::shared_ptr<U1>(new U1(vur.getUptcnt())));
      add("UPD_NAM", boost::shared_ptr<JxTYPE<Cn> >(new JxTYPE<Cn>(vur.getUptnam())));
    }
    void clear() {Record::clear();}
    void setUpdcnt(unsigned char uptcnt)
    {
      if(dynamic_cast<U1&>((*this)["UPD_CNT"]).getValue()!=uptcnt)
      {
        (*this)["UPD_CNT"] = U1(uptcnt);
        
        boost::shared_ptr<JxTYPE<Cn> > UPD_NAM = boost::shared_ptr<JxTYPE<Cn> >(new JxTYPE<Cn>(uptcnt));
        replace_element("UPD_NAM", UPD_NAM);
      }
    }
    void setUpdnam(unsigned char upts, const std::basic_string<char>& uptnam)
    {assert(upts < dynamic_cast<U1&>((*this)["UPD_CNT"]).getValue());dynamic_cast<JxTYPE<Cn> &>((*this)["UPD_NAM"])[upts] = Cn(uptnam);}

   const  U1&   getUptcnt()const {return dynamic_cast<U1&>((*this)["UPD_CNT"]);}
   const  JxTYPE<Cn>&   getUptnam()const {return dynamic_cast<JxTYPE<Cn> &>((*this)["UPD_NAM"]);}

   void write(std::ofstream& outfile)
   {
     if(0 == (dynamic_cast<U1&>((*this)["UPD_CNT"]).getValue())) delete_element("UPD_NAM");

     Record::write(outfile);
   }

#if !OLD_STDF_VERSION 
   void read(std::ifstream& infile)
   {
     U2 REC_LEN;
     REC_LEN.read(infile);
     U1 REC_TYP;
     REC_TYP.read(infile);
     U1 REC_SUB;
     REC_SUB.read(infile);

     (*this)["UPD_CNT"].read(infile);
     if(0 == dynamic_cast<U1&>((*this)["UPD_CNT"]).getValue())
       delete_element("UPD_NAM");
     else
       (*this)["UPD_NAM"].read(infile, dynamic_cast<U1&>((*this)["UPD_CNT"]).getValue());
   }
#else
   void read(std::ifstream& infile)
   {
     U2 REC_LEN;
     REC_LEN.read(infile);
     U1 REC_TYP;
     REC_TYP.read(infile);
     U1 REC_SUB;
     REC_SUB.read(infile);

     (*this)["UPD_CNT"].read(infile);
     if(REC_LEN.getValue() == dynamic_cast<U1&>((*this)["UPD_CNT"]).getValue()+1)
     {
       infile.seekg(-int(sizeof(char)),std::ios::cur);
       delete_element("UPD_CNT");
       (*this)["UPD_NAM"].read(infile, 1);

       return; 
     }
     (*this)["UPD_NAM"].read(infile, dynamic_cast<U1&>((*this)["UPD_CNT"]).getValue());
   }
#endif
 
};


////////////////////////////// LOT //////////////////////////////

class MIR : public Record
{
  public:
    ~MIR() {}
    MIR() : Record(Record::MIR_TYPE)
    {
      add("SETUP_T",  boost::shared_ptr<U4>(new U4()));   // Date and time of job setup--
      add("START_T",  boost::shared_ptr<U4>(new U4()));   // Date and time first part tested--
      add("STAT_NUM", boost::shared_ptr<U1>(new U1()));   // Tester station number
      add("MODE_COD", boost::shared_ptr<C1>(new C1()));   // Test mode code (e.g. prod, dev)--
      add("RTST_COD", boost::shared_ptr<C1>(new C1()));   // Lot retest code
      add("PROT_COD", boost::shared_ptr<C1>(new C1()));   // Data protection code
      add("BURN_TIM", boost::shared_ptr<U2>(new U2(65535u)));   // Burn-in time (in minutes)
      add("CMOD_COD", boost::shared_ptr<C1>(new C1()));   // Command mode code
      add("LOT_ID",   boost::shared_ptr<Cn>(new Cn()));   // Lot ID (customer specified)
      add("PART_TYP", boost::shared_ptr<Cn>(new Cn()));   // Part type (or Porduct ID)
      add("NODE_NAM", boost::shared_ptr<Cn>(new Cn()));   // Name of node which generated data
      add("TSTR_TYP", boost::shared_ptr<Cn>(new Cn()));   // Tester type
      add("JOB_NAM",  boost::shared_ptr<Cn>(new Cn()));   // Job name (test program name)
      add("JOB_REV",  boost::shared_ptr<Cn>(new Cn()));   // Job (test program) revision number
      add("SBLOT_ID", boost::shared_ptr<Cn>(new Cn()));   // Sublot ID
      add("OPER_NAM", boost::shared_ptr<Cn>(new Cn()));   // Operator name (at setup time)--
      add("EXEC_TYP", boost::shared_ptr<Cn>(new Cn()));   // Tester exec software type
      add("EXEC_VER", boost::shared_ptr<Cn>(new Cn()));   // Tester exec software version number
      add("TEST_COD", boost::shared_ptr<Cn>(new Cn()));   // Test phase or step code
      add("TST_TEMP", boost::shared_ptr<Cn>(new Cn()));   // Test temperature
      add("USER_TXT", boost::shared_ptr<Cn>(new Cn()));   // Generic user text
      add("AUX_FILE", boost::shared_ptr<Cn>(new Cn()));   // Name of auxiliary data file
      add("PKG_TYP",  boost::shared_ptr<Cn>(new Cn()));   // Package type
      add("FAMLY_ID", boost::shared_ptr<Cn>(new Cn()));   // Product family ID
      add("DATE_COD", boost::shared_ptr<Cn>(new Cn()));   // Date code
      add("FACIL_ID", boost::shared_ptr<Cn>(new Cn()));   // Test facility ID
      add("FLOOR_ID", boost::shared_ptr<Cn>(new Cn()));   // Test floor ID
      add("PROC_ID",  boost::shared_ptr<Cn>(new Cn()));   // Fabrication Process ID
      add("OPER_FRQ", boost::shared_ptr<Cn>(new Cn()));   // Operation frequency or step
      add("SPEC_NAM", boost::shared_ptr<Cn>(new Cn()));   // Test specification name
      add("SPEC_VER", boost::shared_ptr<Cn>(new Cn()));   // Test specification version number
      add("FLOW_ID",  boost::shared_ptr<Cn>(new Cn()));   // Test flow ID
      add("SETUP_ID", boost::shared_ptr<Cn>(new Cn()));   // Test setup ID
      add("DSGN_REV", boost::shared_ptr<Cn>(new Cn()));   // Device design revision
      add("ENG_ID",   boost::shared_ptr<Cn>(new Cn()));   // Engineering lot ID
      add("ROM_COD",  boost::shared_ptr<Cn>(new Cn()));   // ROM Code ID
      add("SERL_NUM", boost::shared_ptr<Cn>(new Cn()));   // Tester serial number
      add("SUPR_NAM", boost::shared_ptr<Cn>(new Cn()));   // Supervisor name or ID
    }
    MIR(const MIR& mir) : Record(Record::MIR_TYPE)
    {
      add("SETUP_T",  boost::shared_ptr<U4>(new U4(mir.getSetupt() )));   // Date and time of job setup--
      add("START_T",  boost::shared_ptr<U4>(new U4(mir.getStartt() )));   // Date and time first part tested--
      add("STAT_NUM", boost::shared_ptr<U1>(new U1(mir.getStatnum())));   // Tester station number
      add("MODE_COD", boost::shared_ptr<C1>(new C1(mir.getModecod())));   // Test mode code (e.g. prod, dev)--
      add("RTST_COD", boost::shared_ptr<C1>(new C1(mir.getRtstcod())));   // Lot retest code
      add("PROT_COD", boost::shared_ptr<C1>(new C1(mir.getProtcod())));   // Data protection code
      add("BURN_TIM", boost::shared_ptr<U2>(new U2(mir.getBurntim())));   // Burn-in time (in minutes)
      add("CMOD_COD", boost::shared_ptr<C1>(new C1(mir.getCmodcod())));   // Command mode code
      add("LOT_ID",   boost::shared_ptr<Cn>(new Cn(mir.getLotid()  )));   // Lot ID (customer specified)
      add("PART_TYP", boost::shared_ptr<Cn>(new Cn(mir.getParttyp())));   // Part type (or Porduct ID)
      add("NODE_NAM", boost::shared_ptr<Cn>(new Cn(mir.getNodenam())));   // Name of node which generated data
      add("TSTR_TYP", boost::shared_ptr<Cn>(new Cn(mir.getTstrtyp())));   // Tester type
      add("JOB_NAM",  boost::shared_ptr<Cn>(new Cn(mir.getJobnam() )));   // Job name (test program name)
      add("JOB_REV",  boost::shared_ptr<Cn>(new Cn(mir.getJobrev() )));   // Job (test program) revision number
      add("SBLOT_ID", boost::shared_ptr<Cn>(new Cn(mir.getSblotid())));   // Sublot ID
      add("OPER_NAM", boost::shared_ptr<Cn>(new Cn(mir.getOpernam())));   // Operator name (at setup time)--
      add("EXEC_TYP", boost::shared_ptr<Cn>(new Cn(mir.getExectyp())));   // Tester exec software type
      add("EXEC_VER", boost::shared_ptr<Cn>(new Cn(mir.getExecver())));   // Tester exec software version number
      add("TEST_COD", boost::shared_ptr<Cn>(new Cn(mir.getTestcod())));   // Test phase or step code
      add("TST_TEMP", boost::shared_ptr<Cn>(new Cn(mir.getTsttemp())));   // Test temperature
      add("USER_TXT", boost::shared_ptr<Cn>(new Cn(mir.getUsertxt())));   // Generic user text
      add("AUX_FILE", boost::shared_ptr<Cn>(new Cn(mir.getAuxfile())));   // Name of auxiliary data file
      add("PKG_TYP",  boost::shared_ptr<Cn>(new Cn(mir.getPkgtyp() )));   // Package type
      add("FAMLY_ID", boost::shared_ptr<Cn>(new Cn(mir.getFamlyid())));   // Product family ID
      add("DATE_COD", boost::shared_ptr<Cn>(new Cn(mir.getDatecod())));   // Date code
      add("FACIL_ID", boost::shared_ptr<Cn>(new Cn(mir.getFacilid())));   // Test facility ID
      add("FLOOR_ID", boost::shared_ptr<Cn>(new Cn(mir.getFloorid())));   // Test floor ID
      add("PROC_ID",  boost::shared_ptr<Cn>(new Cn(mir.getProcid() )));   // Fabrication Process ID
      add("OPER_FRQ", boost::shared_ptr<Cn>(new Cn(mir.getOperfrq())));   // Operation frequency or step
      add("SPEC_NAM", boost::shared_ptr<Cn>(new Cn(mir.getSpecnam())));   // Test specification name
      add("SPEC_VER", boost::shared_ptr<Cn>(new Cn(mir.getSpecver())));   // Test specification version number
      add("FLOW_ID",  boost::shared_ptr<Cn>(new Cn(mir.getFlowid() )));   // Test flow ID
      add("SETUP_ID", boost::shared_ptr<Cn>(new Cn(mir.getSetupid())));   // Test setup ID
      add("DSGN_REV", boost::shared_ptr<Cn>(new Cn(mir.getDsgnrev())));   // Device design revision
      add("ENG_ID",   boost::shared_ptr<Cn>(new Cn(mir.getEngid()  )));   // Engineering lot ID
      add("ROM_COD",  boost::shared_ptr<Cn>(new Cn(mir.getRomcod() )));   // ROM Code ID
      add("SERL_NUM", boost::shared_ptr<Cn>(new Cn(mir.getSerlnum())));   // Tester serial number
      add("SUPR_NAM", boost::shared_ptr<Cn>(new Cn(mir.getSuprnam())));   // Supervisor name or ID
    }
    void clear() {Record::clear(); setModecod(); setRtstcod(); setProtcod(); setBurntim(); setCmodcod();}
    void setSetupt(unsigned int setupt)           {(*this)["SETUP_T"]  = U4(setupt );}
    void setStartt(unsigned int startt)           {(*this)["START_T"]  = U4(startt );}
    void setStatnum(unsigned char statnum)        {(*this)["STAT_NUM"] = U1(statnum);}
    void setModecod(char modecod=' ')             {(*this)["MODE_COD"] = C1(modecod);}
    void setRtstcod(char rtstcod=' ')             {(*this)["RTST_COD"] = C1(rtstcod);}
    void setProtcod(char protcod=' ')             {(*this)["PROT_COD"] = C1(protcod);}
    void setBurntim(unsigned short burntim=65535u){(*this)["BURN_TIM"] = U2(burntim);}
    void setCmodcod(char cmodcod=' ')             {(*this)["CMOD_COD"] = C1(cmodcod);}
    void setLotid(const std::basic_string<char>& lotid)    {(*this)["LOT_ID"]   = Cn(lotid  );}
    void setParttyp(const std::basic_string<char>& parttyp){(*this)["PART_TYP"] = Cn(parttyp);}
    void setNodenam(const std::basic_string<char>& nodenam){(*this)["NODE_NAM"] = Cn(nodenam);}
    void setTstrtyp(const std::basic_string<char>& tstrtyp){(*this)["TSTR_TYP"] = Cn(tstrtyp);}
    void setJobnam(const std::basic_string<char>& jobnam)  {(*this)["JOB_NAM"]  = Cn(jobnam );}
    void setJobrev(const std::basic_string<char>& jobrev)  {(*this)["JOB_REV"]  = Cn(jobrev );}
    void setSblotid(const std::basic_string<char>& sblotid){(*this)["SBLOT_ID"] = Cn(sblotid);}
    void setOpernam(const std::basic_string<char>& opernam){(*this)["OPER_NAM"] = Cn(opernam);}
    void setExectyp(const std::basic_string<char>& exectyp){(*this)["EXEC_TYP"] = Cn(exectyp);}
    void setExecver(const std::basic_string<char>& execver){(*this)["EXEC_VER"] = Cn(execver);}
    void setTestcod(const std::basic_string<char>& testcod){(*this)["TEST_COD"] = Cn(testcod);}
    void setTsttemp(const std::basic_string<char>& tsttemp){(*this)["TST_TEMP"] = Cn(tsttemp);}
    void setUsertxt(const std::basic_string<char>& usertxt){(*this)["USER_TXT"] = Cn(usertxt);}
    void setAuxfile(const std::basic_string<char>& auxfile){(*this)["AUX_FILE"] = Cn(auxfile);}
    void setPkgtyp(const std::basic_string<char>& pkgtyp)  {(*this)["PKG_TYP"]  = Cn(pkgtyp );}
    void setFamlyid(const std::basic_string<char>& famlyid){(*this)["FAMLY_ID"] = Cn(famlyid);}
    void setDatecod(const std::basic_string<char>& datecod){(*this)["DATE_COD"] = Cn(datecod);}
    void setFacilid(const std::basic_string<char>& facilid){(*this)["FACIL_ID"] = Cn(facilid);}
    void setFloorid(const std::basic_string<char>& floorid){(*this)["FLOOR_ID"] = Cn(floorid);}
    void setProcid(const std::basic_string<char>& procid)  {(*this)["PROC_ID"]  = Cn(procid );}
    void setOperfrq(const std::basic_string<char>& operfrq){(*this)["OPER_FRQ"] = Cn(operfrq);}
    void setSpecnam(const std::basic_string<char>& specnam){(*this)["SPEC_NAM"] = Cn(specnam);}
    void setSpecver(const std::basic_string<char>& specver){(*this)["SPEC_VER"] = Cn(specver);}
    void setFlowid(const std::basic_string<char>& flowid)  {(*this)["FLOW_ID"]  = Cn(flowid );}
    void setSetupid(const std::basic_string<char>& setupid){(*this)["SETUP_ID"] = Cn(setupid);}
    void setDsgnrev(const std::basic_string<char>& dsgnrev){(*this)["DSGN_REV"] = Cn(dsgnrev);}
    void setEngid(const std::basic_string<char>& engid)    {(*this)["ENG_ID"]   = Cn(engid  );}
    void setRomcod(const std::basic_string<char>& romcod)  {(*this)["ROM_COD"]  = Cn(romcod );}
    void setSerlnum(const std::basic_string<char>& serlnum){(*this)["SERL_NUM"] = Cn(serlnum);}
    void setSuprnam(const std::basic_string<char>& suprnam){(*this)["SUPR_NAM"] = Cn(suprnam);}

    const U4& getSetupt() const{return dynamic_cast<U4&>((*this)["SETUP_T"]);}
    const U4& getStartt() const{return dynamic_cast<U4&>((*this)["START_T"]);}
    const U1& getStatnum()const{return dynamic_cast<U1&>((*this)["STAT_NUM"]);}
    const C1& getModecod()const{return dynamic_cast<C1&>((*this)["MODE_COD"]);}
    const C1& getRtstcod()const{return dynamic_cast<C1&>((*this)["RTST_COD"]);}
    const C1& getProtcod()const{return dynamic_cast<C1&>((*this)["PROT_COD"]);}
    const U2& getBurntim()const{return dynamic_cast<U2&>((*this)["BURN_TIM"]);}
    const C1& getCmodcod()const{return dynamic_cast<C1&>((*this)["CMOD_COD"]);}
    const Cn& getLotid()  const{return dynamic_cast<Cn&>((*this)["LOT_ID"]);}
    const Cn& getParttyp()const{return dynamic_cast<Cn&>((*this)["PART_TYP"]);}
    const Cn& getNodenam()const{return dynamic_cast<Cn&>((*this)["NODE_NAM"]);}
    const Cn& getTstrtyp()const{return dynamic_cast<Cn&>((*this)["TSTR_TYP"]);}
    const Cn& getJobnam() const{return dynamic_cast<Cn&>((*this)["JOB_NAM"]);}
    const Cn& getJobrev() const{return dynamic_cast<Cn&>((*this)["JOB_REV"]);}
    const Cn& getSblotid()const{return dynamic_cast<Cn&>((*this)["SBLOT_ID"]);}
    const Cn& getOpernam()const{return dynamic_cast<Cn&>((*this)["OPER_NAM"]);}
    const Cn& getExectyp()const{return dynamic_cast<Cn&>((*this)["EXEC_TYP"]);}
    const Cn& getExecver()const{return dynamic_cast<Cn&>((*this)["EXEC_VER"]);}
    const Cn& getTestcod()const{return dynamic_cast<Cn&>((*this)["TEST_COD"]);}
    const Cn& getTsttemp()const{return dynamic_cast<Cn&>((*this)["TST_TEMP"]);}
    const Cn& getUsertxt()const{return dynamic_cast<Cn&>((*this)["USER_TXT"]);}
    const Cn& getAuxfile()const{return dynamic_cast<Cn&>((*this)["AUX_FILE"]);}
    const Cn& getPkgtyp() const{return dynamic_cast<Cn&>((*this)["PKG_TYP"]);}
    const Cn& getFamlyid()const{return dynamic_cast<Cn&>((*this)["FAMLY_ID"]);}
    const Cn& getDatecod()const{return dynamic_cast<Cn&>((*this)["DATE_COD"]);}
    const Cn& getFacilid()const{return dynamic_cast<Cn&>((*this)["FACIL_ID"]);}
    const Cn& getFloorid()const{return dynamic_cast<Cn&>((*this)["FLOOR_ID"]);}
    const Cn& getProcid() const{return dynamic_cast<Cn&>((*this)["PROC_ID"]);}
    const Cn& getOperfrq()const{return dynamic_cast<Cn&>((*this)["OPER_FRQ"]);}
    const Cn& getSpecnam()const{return dynamic_cast<Cn&>((*this)["SPEC_NAM"]);}
    const Cn& getSpecver()const{return dynamic_cast<Cn&>((*this)["SPEC_VER"]);}
    const Cn& getFlowid() const{return dynamic_cast<Cn&>((*this)["FLOW_ID"]);}
    const Cn& getSetupid()const{return dynamic_cast<Cn&>((*this)["SETUP_ID"]);}
    const Cn& getDsgnrev()const{return dynamic_cast<Cn&>((*this)["DSGN_REV"]);}
    const Cn& getEngid()  const{return dynamic_cast<Cn&>((*this)["ENG_ID"]);}
    const Cn& getRomcod() const{return dynamic_cast<Cn&>((*this)["ROM_COD"]);}
    const Cn& getSerlnum()const{return dynamic_cast<Cn&>((*this)["SERL_NUM"]);}
    const Cn& getSuprnam()const{return dynamic_cast<Cn&>((*this)["SUPR_NAM"]);}

};


class MRR : public Record
{
  public:
    ~MRR() {}
    MRR() : Record(Record::MRR_TYPE)
    {
      add("FINISH_T", boost::shared_ptr<U4>(new U4()));
      add("DISP_COD", boost::shared_ptr<C1>(new C1()));
      add("USR_DESC", boost::shared_ptr<Cn>(new Cn()));
      add("EXC_DESC", boost::shared_ptr<Cn>(new Cn()));
    }
    MRR(const MRR& mrr) : Record(Record::MRR_TYPE)
    {
      add("FINISH_T", boost::shared_ptr<U4>(new U4(mrr.getFinisht())));
      add("DISP_COD", boost::shared_ptr<C1>(new C1(mrr.getDispcod())));
      add("USR_DESC", boost::shared_ptr<Cn>(new Cn(mrr.getUsrdesc())));
      add("EXC_DESC", boost::shared_ptr<Cn>(new Cn(mrr.getExcdesc())));
    }
    void clear() {Record::clear(); setDispcod();}
    void setFinisht(unsigned int finisht)                   {(*this)["FINISH_T"] = U4(finisht);}
    void setDispcod(char dispcod=' ')                       {(*this)["DISP_COD"] = C1(dispcod);}
    void setUsrdesc(const std::basic_string<char>& usrdesc) {(*this)["USR_DESC"] = Cn(usrdesc);}
    void setExcdesc(const std::basic_string<char>& excdesc) {(*this)["EXC_DESC"] = Cn(excdesc);}

    const U4& getFinisht()const {return dynamic_cast<U4&>((*this)["FINISH_T"]);}
    const C1& getDispcod()const {return dynamic_cast<C1&>((*this)["DISP_COD"]);}
    const Cn& getUsrdesc()const {return dynamic_cast<Cn&>((*this)["USR_DESC"]);}
    const Cn& getExcdesc()const {return dynamic_cast<Cn&>((*this)["EXC_DESC"]);}
};


class PCR : public Record
{
  public:
    ~PCR() {}
    PCR() : Record(Record::PCR_TYPE)
    {
      add("HEAD_NUM", boost::shared_ptr<U1>(new U1())           );
      add("SITE_NUM", boost::shared_ptr<U1>(new U1())           );
      add("PART_CNT", boost::shared_ptr<U4>(new U4())           );
      add("RTST_CNT", boost::shared_ptr<U4>(new U4(4294967295u)));
      add("ABRT_CNT", boost::shared_ptr<U4>(new U4(4294967295u)));
      add("GOOD_CNT", boost::shared_ptr<U4>(new U4(4294967295u)));
      add("FUNC_CNT", boost::shared_ptr<U4>(new U4(4294967295u)));
    }
    PCR(const PCR& pcr) : Record(Record::PCR_TYPE)
    {
      add("HEAD_NUM", boost::shared_ptr<U1>(new U1(pcr.getHeadnum())));
      add("SITE_NUM", boost::shared_ptr<U1>(new U1(pcr.getSitenum())));
      add("PART_CNT", boost::shared_ptr<U4>(new U4(pcr.getPartcnt())));
      add("RTST_CNT", boost::shared_ptr<U4>(new U4(pcr.getRtstcnt())));
      add("ABRT_CNT", boost::shared_ptr<U4>(new U4(pcr.getAbrtcnt())));
      add("GOOD_CNT", boost::shared_ptr<U4>(new U4(pcr.getGoodcnt())));
      add("FUNC_CNT", boost::shared_ptr<U4>(new U4(pcr.getFunccnt())));
    }
    void clear() {Record::clear(); setRtstcnt(); setAbrtcnt(); setGoodcnt(); setFunccnt();}
    void setHeadnum(unsigned char headnum)            {(*this)["HEAD_NUM"] = U1(headnum);}
    void setSitenum(unsigned char sitenum)            {(*this)["SITE_NUM"] = U1(sitenum);}
    void setPartcnt(unsigned int partcnt)             {(*this)["PART_CNT"] = U4(partcnt);}
    void setRtstcnt(unsigned int rtstcnt=4294967295u) {(*this)["RTST_CNT"] = U4(rtstcnt);}
    void setAbrtcnt(unsigned int abrtcnt=4294967295u) {(*this)["ABRT_CNT"] = U4(abrtcnt);}
    void setGoodcnt(unsigned int goodcnt=4294967295u) {(*this)["GOOD_CNT"] = U4(goodcnt);}
    void setFunccnt(unsigned int funccnt=4294967295u) {(*this)["FUNC_CNT"] = U4(funccnt);}

    const U1& getHeadnum()const {return dynamic_cast<U1&>((*this)["HEAD_NUM"]);}
    const U1& getSitenum()const {return dynamic_cast<U1&>((*this)["SITE_NUM"]);}
    const U4& getPartcnt()const {return dynamic_cast<U4&>((*this)["PART_CNT"]);}
    const U4& getRtstcnt()const {return dynamic_cast<U4&>((*this)["RTST_CNT"]);}
    const U4& getAbrtcnt()const {return dynamic_cast<U4&>((*this)["ABRT_CNT"]);}
    const U4& getGoodcnt()const {return dynamic_cast<U4&>((*this)["GOOD_CNT"]);}
    const U4& getFunccnt()const {return dynamic_cast<U4&>((*this)["FUNC_CNT"]);}

};


class HBR : public Record
{
  public:
    ~HBR() {}
    HBR() : Record(Record::HBR_TYPE)
    {
      add("HEAD_NUM", boost::shared_ptr<U1>(new U1()));
      add("SITE_NUM", boost::shared_ptr<U1>(new U1()));
      add("HBIN_NUM", boost::shared_ptr<U2>(new U2()));
      add("HBIN_CNT", boost::shared_ptr<U4>(new U4()));
      add("HBIN_PF",  boost::shared_ptr<C1>(new C1()));
      add("HBIN_NAM", boost::shared_ptr<Cn>(new Cn()));
    }
    HBR(const HBR& hbr) : Record(Record::HBR_TYPE)
    {
      add("HEAD_NUM", boost::shared_ptr<U1>(new U1(hbr.getHeadnum())));
      add("SITE_NUM", boost::shared_ptr<U1>(new U1(hbr.getSitenum())));
      add("HBIN_NUM", boost::shared_ptr<U2>(new U2(hbr.getHbinnum())));
      add("HBIN_CNT", boost::shared_ptr<U4>(new U4(hbr.getHbincnt())));
      add("HBIN_PF",  boost::shared_ptr<C1>(new C1(hbr.getHbinpf ())));
      add("HBIN_NAM", boost::shared_ptr<Cn>(new Cn(hbr.getHbinnam())));
    }

    void clear() {Record::clear(); setHbinpf();}
    void setHeadnum(unsigned char headnum)                  {(*this)["HEAD_NUM"] = U1(headnum);}
    void setSitenum(unsigned char sitenum)                  {(*this)["SITE_NUM"] = U1(sitenum);}
    void setHbinnum(unsigned short hbinnum)                 {(*this)["HBIN_NUM"] = U2(hbinnum);}
    void setHbincnt(unsigned int hbincnt)                   {(*this)["HBIN_CNT"] = U4(hbincnt);}
    void setHbinpf(char hbinpf=' ')                         {(*this)["HBIN_PF"]  = C1(hbinpf );}
    void setHbinnam(const std::basic_string<char>& hbinnam) {(*this)["HBIN_NAM"] = Cn(hbinnam);}

    const U1& getHeadnum()const {return dynamic_cast<U1&>((*this)["HEAD_NUM"]);}
    const U1& getSitenum()const {return dynamic_cast<U1&>((*this)["SITE_NUM"]);}
    const U2& getHbinnum()const {return dynamic_cast<U2&>((*this)["HBIN_NUM"]);}
    const U4& getHbincnt()const {return dynamic_cast<U4&>((*this)["HBIN_CNT"]);}
    const C1& getHbinpf ()const {return dynamic_cast<C1&>((*this)["HBIN_PF"]) ;}
    const Cn& getHbinnam()const {return dynamic_cast<Cn&>((*this)["HBIN_NAM"]);}

};


class SBR : public Record
{
  public:
    ~SBR() {}
    SBR() : Record(Record::SBR_TYPE)
    {
      add("HEAD_NUM", boost::shared_ptr<U1>(new U1()));
      add("SITE_NUM", boost::shared_ptr<U1>(new U1()));
      add("SBIN_NUM", boost::shared_ptr<U2>(new U2()));
      add("SBIN_CNT", boost::shared_ptr<U4>(new U4()));
      add("SBIN_PF",  boost::shared_ptr<C1>(new C1()));
      add("SBIN_NAM", boost::shared_ptr<Cn>(new Cn()));
    }
    SBR(const SBR& sbr) : Record(Record::SBR_TYPE)
    {
      add("HEAD_NUM", boost::shared_ptr<U1>(new U1(sbr.getHeadnum())));
      add("SITE_NUM", boost::shared_ptr<U1>(new U1(sbr.getSitenum())));
      add("SBIN_NUM", boost::shared_ptr<U2>(new U2(sbr.getSbinnum())));
      add("SBIN_CNT", boost::shared_ptr<U4>(new U4(sbr.getSbincnt())));
      add("SBIN_PF",  boost::shared_ptr<C1>(new C1(sbr.getSbinpf ())));
      add("SBIN_NAM", boost::shared_ptr<Cn>(new Cn(sbr.getSbinnam())));
    }
    void clear() {Record::clear(); setSbinpf();}
    void setHeadnum(unsigned char headnum)                  {(*this)["HEAD_NUM"] = U1(headnum);}
    void setSitenum(unsigned char sitenum)                  {(*this)["SITE_NUM"] = U1(sitenum);}
    void setSbinnum(unsigned short sbinnum)                 {(*this)["SBIN_NUM"] = U2(sbinnum);}
    void setSbincnt(unsigned int sbincnt)                   {(*this)["SBIN_CNT"] = U4(sbincnt);}
    void setSbinpf(unsigned char sbinpf=' ')                {(*this)["SBIN_PF"]  = C1(sbinpf );}
    void setSbinnam(const std::basic_string<char>& sbinnam) {(*this)["SBIN_NAM"] = Cn(sbinnam);}

    const U1& getHeadnum()const {return dynamic_cast<U1&>((*this)["HEAD_NUM"]);}
    const U1& getSitenum()const {return dynamic_cast<U1&>((*this)["SITE_NUM"]);}
    const U2& getSbinnum()const {return dynamic_cast<U2&>((*this)["SBIN_NUM"]);}
    const U4& getSbincnt()const {return dynamic_cast<U4&>((*this)["SBIN_CNT"]);}
    const C1& getSbinpf ()const {return dynamic_cast<C1&>((*this)["SBIN_PF"]) ;}
    const Cn& getSbinnam()const {return dynamic_cast<Cn&>((*this)["SBIN_NAM"]);}

};


class PMR : public Record
{
  public:
    ~PMR() {}
    PMR() : Record(Record::PMR_TYPE)
    {
      add("PMR_INDX", boost::shared_ptr<U2>(new U2())  );
      add("CHAN_TYP", boost::shared_ptr<U2>(new U2())  );
      add("CHAN_NAM", boost::shared_ptr<Cn>(new Cn())  );
      add("PHY_NAM",  boost::shared_ptr<Cn>(new Cn())  );
      add("LOG_NAM",  boost::shared_ptr<Cn>(new Cn())  );
      add("HEAD_NUM", boost::shared_ptr<U1>(new U1(1u)));
      add("SITE_NUM", boost::shared_ptr<U1>(new U1(1u)));
    }
    PMR(const PMR& pmr) : Record(Record::PMR_TYPE)
    {
      add("PMR_INDX", boost::shared_ptr<U2>(new U2(pmr.getPmrindx()))  );
      add("CHAN_TYP", boost::shared_ptr<U2>(new U2(pmr.getChantyp()))  );
      add("CHAN_NAM", boost::shared_ptr<Cn>(new Cn(pmr.getChannam()))  );
      add("PHY_NAM",  boost::shared_ptr<Cn>(new Cn(pmr.getPhynam ()))  );
      add("LOG_NAM",  boost::shared_ptr<Cn>(new Cn(pmr.getLognam ()))  );
      add("HEAD_NUM", boost::shared_ptr<U1>(new U1(pmr.getHeadnum())));
      add("SITE_NUM", boost::shared_ptr<U1>(new U1(pmr.getSitenum())));
    }
    void clear() {Record::clear(); setChantyp(); setHeadnum(); setSitenum();}
    void setPmrindx(unsigned short pmrindx)                 {(*this)["PMR_INDX"] = U2(pmrindx);}
    void setChantyp(unsigned short chantyp=0u)              {(*this)["CHAN_TYP"] = U2(chantyp);}
    void setChannam(const std::basic_string<char>& channam) {(*this)["CHAN_NAM"] = Cn(channam);}
    void setPhynam(const std::basic_string<char>& phynam)   {(*this)["PHY_NAM"]  = Cn(phynam );}
    void setLognam(const std::basic_string<char>& lognam)   {(*this)["LOG_NAM"]  = Cn(lognam );}
    void setHeadnum(unsigned char headnum=1u)               {(*this)["HEAD_NUM"] = U1(headnum);}
    void setSitenum(unsigned char sitenum=1u)               {(*this)["SITE_NUM"] = U1(sitenum);}

    const U2& getPmrindx()const {return dynamic_cast<U2&>((*this)["PMR_INDX"]);}
    const U2& getChantyp()const {return dynamic_cast<U2&>((*this)["CHAN_TYP"]);}
    const Cn& getChannam()const {return dynamic_cast<Cn&>((*this)["CHAN_NAM"]);}
    const Cn& getPhynam ()const {return dynamic_cast<Cn&>((*this)["PHY_NAM"]);}
    const Cn& getLognam ()const {return dynamic_cast<Cn&>((*this)["LOG_NAM"]);}
    const U1& getHeadnum()const {return dynamic_cast<U1&>((*this)["HEAD_NUM"]);}
    const U1& getSitenum()const {return dynamic_cast<U1&>((*this)["SITE_NUM"]);}

};


class PGR : public Record
{
  public:
    ~PGR() {}
    PGR() : Record(Record::PGR_TYPE)
    {
      add("GRP_INDX",boost::shared_ptr<U2>(new U2()));
      add("GRP_NAM", boost::shared_ptr<Cn>(new Cn()));
      add("INDX_CNT", boost::shared_ptr<U2>(new U2()));
      add("PMR_INDX", boost::shared_ptr<JxTYPE<U2> >(new JxTYPE<U2>())); 
    }
    PGR(const PGR& pgr) : Record(Record::PGR_TYPE)
    {
      add("GRP_INDX",boost::shared_ptr<U2>(new U2(pgr.getGrpindx())));
      add("GRP_NAM",boost::shared_ptr<Cn>(new Cn(pgr.getGrpnam())));
      add("INDX_CNT",boost::shared_ptr<U2>(new U2(pgr.getIndxcnt())));
      add("PMR_INDX", boost::shared_ptr<JxTYPE<U2> >(new JxTYPE<U2>(pgr.getPmrindx()))); 
    }
    void clear() {Record::clear();} 
    void setGrpindx(unsigned short grpindx) {(*this)["GRP_INDX"] = U2(grpindx);}
    void setGrpnam(const std::basic_string<char>& grpnam) {(*this)["GRP_NAM"] = Cn(grpnam);}
    void setIndxcnt(unsigned short indxcnt)
    {
      if(dynamic_cast<U2&>((*this)["INDX_CNT"]).getValue() != indxcnt)
      {
        (*this)["INDX_CNT"] = U2(indxcnt);

        replace_element("PMR_INDX", boost::shared_ptr<JxTYPE<U2> >(new JxTYPE<U2>(indxcnt)));
      }
    }
    void setPmrindx(unsigned short indxcnt, unsigned short pmrindx)
    {assert(indxcnt<dynamic_cast<U2&>((*this)["INDX_CNT"]).getValue()); (dynamic_cast<JxTYPE<U2> &>((*this)["PMR_INDX"]))[indxcnt] = pmrindx;}

    const U2& getGrpindx() const {return dynamic_cast<U2&>((*this)["GRP_INDX"]);}
    const Cn& getGrpnam()const {return dynamic_cast<Cn&>((*this)["GRP_NAM"]);}
    const U2& getIndxcnt()const {return dynamic_cast<U2&>((*this)["PMR_INDX"]);}
    const JxTYPE<U2>& getPmrindx()const {return dynamic_cast<JxTYPE<U2> &>((*this)["PMR_INDX"]);}

    void read(std::ifstream& infile)
    {
      U2 REC_LEN;
      REC_LEN.read(infile);
      U1 REC_TYP;
      REC_TYP.read(infile);
      U1 REC_SUB;
      REC_SUB.read(infile);

      (*this)["GRP_INDX"].read(infile);
      (*this)["GRP_NAM"].read(infile);
      (*this)["INDX_CNT"].read(infile);
      (*this)["PMR_INDX"].read(infile, dynamic_cast<U2&>((*this)["INDX_CNT"]).getValue());
    }
};


class PLR : public Record
{
  public:
    ~PLR() {}
    PLR() : Record(Record::PLR_TYPE)
    {
      add("GRP_CNT",  boost::shared_ptr<U2>(new U2()));
      add("GRP_INDX", boost::shared_ptr<JxTYPE<U2> >(new JxTYPE<U2>()));
      add("GRP_MODE", boost::shared_ptr<JxTYPE<U2> >(new JxTYPE<U2>()));
      add("GRP_RADX", boost::shared_ptr<JxTYPE<U1> >(new JxTYPE<U1>()));
      add("PGM_CHAR", boost::shared_ptr<JxTYPE<Cn> >(new JxTYPE<Cn>()));
      add("RTN_CHAR", boost::shared_ptr<JxTYPE<Cn> >(new JxTYPE<Cn>()));
      add("PGM_CHAL", boost::shared_ptr<JxTYPE<Cn> >(new JxTYPE<Cn>()));
      add("RTN_CHAL", boost::shared_ptr<JxTYPE<Cn> >(new JxTYPE<Cn>()));
    }
    PLR(const PLR& plr) : Record(Record::PLR_TYPE)
    {
      add("GRP_CNT",  boost::shared_ptr<U2>(new U2(plr.getGrpcnt())));
      add("GRP_INDX", boost::shared_ptr<JxTYPE<U2> >(new  JxTYPE<U2>(plr.getGrpindx())));
      add("GRP_MODE", boost::shared_ptr<JxTYPE<U2> >(new  JxTYPE<U2>(plr.getGrpmode())));
      add("GRP_RADX", boost::shared_ptr<JxTYPE<U1> >(new  JxTYPE<U1>(plr.getGrpradx())));
      add("PGM_CHAR", boost::shared_ptr<JxTYPE<Cn> >(new  JxTYPE<Cn>(plr.getPgmchar())));
      add("RTN_CHAR", boost::shared_ptr<JxTYPE<Cn> >(new  JxTYPE<Cn>(plr.getRtnchar())));
      add("PGM_CHAL", boost::shared_ptr<JxTYPE<Cn> >(new  JxTYPE<Cn>(plr.getPgmchal())));
      add("RTN_CHAL", boost::shared_ptr<JxTYPE<Cn> >(new  JxTYPE<Cn>(plr.getRtnchal())));
    }
    void clear(){Record::clear();}
    void setGrpcnt(unsigned short grpcnt)
    {
      if(dynamic_cast<U2&>((*this)["GRP_CNT"]).getValue() != grpcnt)
      {
        dynamic_cast<U2&>((*this)["GRP_CNT"]) = U2(grpcnt);

        boost::shared_ptr<JxTYPE<U2> > GRP_INDX = boost::shared_ptr<JxTYPE<U2> >(new JxTYPE<U2>(grpcnt));
        replace_element("GRP_INDX", GRP_INDX);

        boost::shared_ptr<JxTYPE<U2> > GRP_MODE = boost::shared_ptr<JxTYPE<U2> >(new JxTYPE<U2>(grpcnt));
        replace_element("GRP_MODE", GRP_MODE);

        boost::shared_ptr<JxTYPE<U1> > GRP_RADX = boost::shared_ptr<JxTYPE<U1> >(new JxTYPE<U1>(grpcnt));
        replace_element("GRP_RADX", GRP_RADX);

        boost::shared_ptr<JxTYPE<Cn> > PGM_CHAR = boost::shared_ptr<JxTYPE<Cn> >(new JxTYPE<Cn>(grpcnt));
        replace_element("PGM_CHAR", PGM_CHAR);

        boost::shared_ptr<JxTYPE<Cn> > RTN_CHAR = boost::shared_ptr<JxTYPE<Cn> >(new JxTYPE<Cn>(grpcnt));
        replace_element("RTN_CHAR", RTN_CHAR);

        boost::shared_ptr<JxTYPE<Cn> > PGM_CHAL = boost::shared_ptr<JxTYPE<Cn> >(new JxTYPE<Cn>(grpcnt));
        replace_element("PGM_CHAL", PGM_CHAL);

        boost::shared_ptr<JxTYPE<Cn> > RTN_CHAL = boost::shared_ptr<JxTYPE<Cn> >(new JxTYPE<Cn>(grpcnt));
        replace_element("RTN_CHAL", RTN_CHAL);
      }
    }
    void setGrpindx(unsigned short pins,unsigned short grpindx)
    {assert(pins < dynamic_cast<U2&>((*this)["GRP_CNT"]).getValue());(dynamic_cast<JxTYPE<U2> &>((*this)["GRP_INDX"]))[pins] = grpindx;}
    void setGrpmode(unsigned short pins,unsigned short grpmode)
    {assert(pins < dynamic_cast<U2&>((*this)["GRP_CNT"]).getValue());(dynamic_cast<JxTYPE<U2> &>((*this)["GRP_MODE"]))[pins] = grpmode;}
    void setGrpradx(unsigned short pins,unsigned char grpradx)
    {assert(pins < dynamic_cast<U2&>((*this)["GRP_CNT"]).getValue()); (dynamic_cast<JxTYPE<U1> &>((*this)["GRP_RADX"]))[pins] = grpradx;}
    void setPgmchar(unsigned short pins,const std::basic_string<char>& pgmchar)
    {assert(pins < dynamic_cast<U2&>((*this)["GRP_CNT"]).getValue()); (dynamic_cast<JxTYPE<Cn> &>((*this)["PGM_CHAR"]))[pins] = pgmchar;}
    void setRtnchar(unsigned short pins,const std::basic_string<char>& rtnchar)
    {assert(pins < dynamic_cast<U2&>((*this)["GRP_CNT"]).getValue()); (dynamic_cast<JxTYPE<Cn> &>((*this)["RTN_CHAR"]))[pins] = rtnchar;}
    void setPgmchal(unsigned short pins,const std::basic_string<char>& pgmchal)
    {assert(pins < dynamic_cast<U2&>((*this)["GRP_CNT"]).getValue()); (dynamic_cast<JxTYPE<Cn> &>((*this)["PGM_CHAL"]))[pins] = pgmchal;}
    void setRtnchal(unsigned short pins,const std::basic_string<char>& rtnchal)
    {assert(pins < dynamic_cast<U2&>((*this)["GRP_CNT"]).getValue()); (dynamic_cast<JxTYPE<Cn> &>((*this)["RTN_CHAL"]))[pins] = rtnchal;}

    const U2& getGrpcnt()         const {return dynamic_cast<U2&>((*this)["GRP_CNT"]);}
    const JxTYPE<U2>& getGrpindx()const {return dynamic_cast<JxTYPE<U2> &>((*this)["GRP_INDX"]);} 
    const JxTYPE<U2>& getGrpmode()const {return dynamic_cast<JxTYPE<U2> &>((*this)["GRP_MODE"]);} 
    const JxTYPE<U1>& getGrpradx()const {return dynamic_cast<JxTYPE<U1> &>((*this)["GRP_RADX"]);} 
    const JxTYPE<Cn>& getPgmchar()const {return dynamic_cast<JxTYPE<Cn> &>((*this)["PGM_CHAR"]);}
    const JxTYPE<Cn>& getRtnchar()const {return dynamic_cast<JxTYPE<Cn> &>((*this)["RTN_CHAR"]);} 
    const JxTYPE<Cn>& getPgmchal()const {return dynamic_cast<JxTYPE<Cn> &>((*this)["PGM_CHAL"]);} 
    const JxTYPE<Cn>& getRtnchal()const {return dynamic_cast<JxTYPE<Cn> &>((*this)["RTN_CHAL"]);} 

    void read(std::ifstream& infile)
    {
      U2 REC_LEN;
      REC_LEN.read(infile);
      U1 REC_TYP;
      REC_TYP.read(infile);
      U1 REC_SUB;
      REC_SUB.read(infile);

      (*this)["GRP_CNT"].read(infile);
      (*this)["GRP_INDX"].read(infile, dynamic_cast<U2&>((*this)["GRP_CNT"]).getValue());
      (*this)["GRP_MODE"].read(infile, dynamic_cast<U2&>((*this)["GRP_CNT"]).getValue());
      (*this)["GRP_RADX"].read(infile, dynamic_cast<U2&>((*this)["GRP_CNT"]).getValue());
      (*this)["PGM_CHAR"].read(infile, dynamic_cast<U2&>((*this)["GRP_CNT"]).getValue());
      (*this)["RTN_CHAR"].read(infile, dynamic_cast<U2&>((*this)["GRP_CNT"]).getValue());
      (*this)["PGM_CHAL"].read(infile, dynamic_cast<U2&>((*this)["GRP_CNT"]).getValue());
      (*this)["RTN_CHAL"].read(infile, dynamic_cast<U2&>((*this)["GRP_CNT"]).getValue());
    }
};


class RDR : public Record
{
  public:
    ~RDR() {}
    RDR() : Record(Record::RDR_TYPE)
    {
      add("NUM_BINS",boost::shared_ptr<U2>(new U2()));
      add("RTST_BIN",boost::shared_ptr<JxTYPE<U2> >(new JxTYPE<U2>()));
    }
    RDR(const RDR& rdr) : Record(Record::RDR_TYPE)
    {
      add("NUM_BINS",boost::shared_ptr<U2>(new U2(rdr.getNumbins())));
      add("RTST_BIN",boost::shared_ptr<JxTYPE<U2> >(new JxTYPE<U2>(rdr.getRtstbin())));
    }
    void clear(){Record::clear();}
    void setNumbins(unsigned short numbins)
    {
      if(dynamic_cast<U2&>((*this)["NUM_BINS"]).getValue() != numbins)
      {
        set("NUM_BINS", U2(numbins));

        boost::shared_ptr<JxTYPE<U2> > RTST_BIN = boost::shared_ptr<JxTYPE<U2> >(new JxTYPE<U2>(numbins));
        replace_element("RTST_BIN", RTST_BIN);
      }
    }
    void setRtstbin(unsigned short bins,unsigned short rtstbin)
    {assert(bins < dynamic_cast<U2&>((*this)["NUM_BINS"]).getValue());((dynamic_cast<JxTYPE<U2> &>((*this)["RTST_BIN"])))[bins] = U2(rtstbin);}

    const U2&         getNumbins()const {return dynamic_cast<U2&>((*this)["NUM_BINS"]);}
    const JxTYPE<U2>& getRtstbin()const {return dynamic_cast<JxTYPE<U2> &>((*this)["RTST_BIN"]);}

    void read(std::ifstream& infile)
    {
      U2 REC_LEN;
      REC_LEN.read(infile);
      U1 REC_TYP;
      REC_TYP.read(infile);
      U1 REC_SUB;
      REC_SUB.read(infile);

      (*this)["NUM_BINS"].read(infile);
      (*this)["RTST_BIN"].read(infile, dynamic_cast<U2&>((*this)["NUM_BINS"]).getValue());
    }

};


class SDR : public Record
{
  public:
    ~SDR() {}
    SDR() : Record(Record::SDR_TYPE)
    {
      add("HEAD_NUM", boost::shared_ptr<U1>(new U1()));
      add("SITE_GRP", boost::shared_ptr<U1>(new U1()));
      add("SITE_CNT", boost::shared_ptr<U1>(new U1()));
      add("SITE_NUM", boost::shared_ptr<JxTYPE<U1> >(new JxTYPE<U1>()));
      add("HAND_TYP", boost::shared_ptr<Cn>(new Cn()));
      add("HAND_ID",  boost::shared_ptr<Cn>(new Cn()));
      add("CARD_TYP", boost::shared_ptr<Cn>(new Cn()));
      add("CARD_ID",  boost::shared_ptr<Cn>(new Cn()));
      add("LOAD_TYP", boost::shared_ptr<Cn>(new Cn()));
      add("LOAD_ID",  boost::shared_ptr<Cn>(new Cn()));
      add("DIB_TYP",  boost::shared_ptr<Cn>(new Cn()));
      add("DIB_ID",   boost::shared_ptr<Cn>(new Cn()));
      add("CABL_TYP", boost::shared_ptr<Cn>(new Cn()));
      add("CABL_ID",  boost::shared_ptr<Cn>(new Cn()));
      add("CONT_TYP", boost::shared_ptr<Cn>(new Cn()));
      add("CONT_ID",  boost::shared_ptr<Cn>(new Cn()));
      add("LASR_TYP", boost::shared_ptr<Cn>(new Cn()));
      add("LASR_ID",  boost::shared_ptr<Cn>(new Cn()));
      add("EXTR_TYP", boost::shared_ptr<Cn>(new Cn()));
      add("EXTR_ID",  boost::shared_ptr<Cn>(new Cn()));
    }
    SDR(const SDR& sdr) : Record(Record::SDR_TYPE)
    {
      add("HEAD_NUM", boost::shared_ptr<U1>(new U1(sdr.getHeadnum())));
      add("SITE_GRP", boost::shared_ptr<U1>(new U1(sdr.getSitegrp())));
      add("SITE_CNT", boost::shared_ptr<U1>(new U1(sdr.getSitecnt())));
      add("SITE_NUM", boost::shared_ptr<JxTYPE<U1> >(new JxTYPE<U1>(sdr.getSitenum())));
      add("HAND_TYP", boost::shared_ptr<Cn>(new Cn(sdr.getHandtyp())));
      add("HAND_ID",  boost::shared_ptr<Cn>(new Cn(sdr.getHandid ())));
      add("CARD_TYP", boost::shared_ptr<Cn>(new Cn(sdr.getCardtyp())));
      add("CARD_ID",  boost::shared_ptr<Cn>(new Cn(sdr.getCardid ())));
      add("LOAD_TYP", boost::shared_ptr<Cn>(new Cn(sdr.getLoadtyp())));
      add("LOAD_ID",  boost::shared_ptr<Cn>(new Cn(sdr.getLoadid ())));
      add("DIB_TYP",  boost::shared_ptr<Cn>(new Cn(sdr.getDibtyp ())));
      add("DIB_ID",   boost::shared_ptr<Cn>(new Cn(sdr.getDibid  ())));
      add("CABL_TYP", boost::shared_ptr<Cn>(new Cn(sdr.getCabltyp())));
      add("CABL_ID",  boost::shared_ptr<Cn>(new Cn(sdr.getCablid ())));
      add("CONT_TYP", boost::shared_ptr<Cn>(new Cn(sdr.getConttyp())));
      add("CONT_ID",  boost::shared_ptr<Cn>(new Cn(sdr.getContid ())));
      add("LASR_TYP", boost::shared_ptr<Cn>(new Cn(sdr.getLasrtyp())));
      add("LASR_ID",  boost::shared_ptr<Cn>(new Cn(sdr.getLasrid ())));
      add("EXTR_TYP", boost::shared_ptr<Cn>(new Cn(sdr.getExtrtyp())));
      add("EXTR_ID",  boost::shared_ptr<Cn>(new Cn(sdr.getExtrid ())));
    }
    void clear() {Record::clear();}
    void setHeadnum(unsigned char headnum){(*this)["HEAD_NUM"] = U1(headnum);} 
    void setSitegrp(unsigned char sitegrp){(*this)["SITE_GRP"] = U1(sitegrp);} 
    void setSitecnt(unsigned char sitecnt)
    {
      if( dynamic_cast<U1&>((*this)["SITE_CNT"]).getValue() != sitecnt)
      {
        (*this)["SITE_CNT"] = U1(sitecnt);

        boost::shared_ptr<JxTYPE<U1> > SITE_NUM = boost::shared_ptr<JxTYPE<U1> >(new JxTYPE<U1>(sitecnt));
        replace_element("SITE_NUM", SITE_NUM);
      }
    } 
    void setSitenum(unsigned char sites,unsigned char sitenum)
    {assert(sites<dynamic_cast<U1&>((*this)["SITE_CNT"]).getValue()); dynamic_cast<JxTYPE<U1> &>((*this)["SITE_NUM"])[sites] = U1(sitenum);} 
    void setHandtyp(const std::basic_string<char>& handtyp){(*this)["HAND_TYP"] = Cn(handtyp);} 
    void setHandid(const std::basic_string<char>& handid)  {(*this)["HAND_ID"] = Cn(handid );} 
    void setCardtyp(const std::basic_string<char>& cardtyp){(*this)["CARD_TYP"] = Cn(cardtyp);} 
    void setCardid(const std::basic_string<char>& cardid)  {(*this)["CARD_ID"] = Cn(cardid );} 
    void setLoadtyp(const std::basic_string<char>& loadtyp){(*this)["LOAD_TYP"] = Cn(loadtyp);} 
    void setLoadid(const std::basic_string<char>& loadid)  {(*this)["LOAD_ID"] = Cn(loadid );} 
    void setDibtyp(const std::basic_string<char>& dibtyp)  {(*this)["DIB_TYP"] = Cn(dibtyp );} 
    void setDibid(const std::basic_string<char>& dibid)    {(*this)["DIB_ID"] = Cn(dibid  );} 
    void setCabltyp(const std::basic_string<char>& cabltyp){(*this)["CABL_TYP"] = Cn(cabltyp);} 
    void setCablid(const std::basic_string<char>& cablid)  {(*this)["CABL_ID"] = Cn(cablid );} 
    void setConttyp(const std::basic_string<char>& conttyp){(*this)["CONT_TYP"] = Cn(conttyp);} 
    void setContid(const std::basic_string<char>& contid)  {(*this)["CONT_ID"] = Cn(contid );} 
    void setLasrtyp(const std::basic_string<char>& lasrtyp){(*this)["LASR_TYP"] = Cn(lasrtyp);} 
    void setLasrid(const std::basic_string<char>& lasrid)  {(*this)["LASR_ID"] = Cn(lasrid );} 
    void setExtrtyp(const std::basic_string<char>& extrtyp){(*this)["EXTR_TYP"] = Cn(extrtyp);} 
    void setExtrid(const std::basic_string<char>& extrid)  {(*this)["EXTR_ID"] = Cn(extrid );} 

    const U1&         getHeadnum()const {return dynamic_cast<U1&>((*this)["HEAD_NUM"]);} 
    const U1&         getSitegrp()const {return dynamic_cast<U1&>((*this)["SITE_GRP"]);} 
    const U1&         getSitecnt()const {return dynamic_cast<U1&>((*this)["SITE_CNT"]);}
    const JxTYPE<U1>& getSitenum()const {return dynamic_cast<JxTYPE<U1>&>((*this)["SITE_NUM"]);}
    const Cn&         getHandtyp()const {return dynamic_cast<Cn&>((*this)["HAND_TYP"]);} 
    const Cn&         getHandid ()const {return dynamic_cast<Cn&>((*this)["HAND_ID"]);} 
    const Cn&         getCardtyp()const {return dynamic_cast<Cn&>((*this)["CARD_TYP"]);} 
    const Cn&         getCardid ()const {return dynamic_cast<Cn&>((*this)["CARD_ID"]);} 
    const Cn&         getLoadtyp()const {return dynamic_cast<Cn&>((*this)["LOAD_TYP"]);} 
    const Cn&         getLoadid ()const {return dynamic_cast<Cn&>((*this)["LOAD_ID"]);} 
    const Cn&         getDibtyp ()const {return dynamic_cast<Cn&>((*this)["DIB_TYP"]);} 
    const Cn&         getDibid  ()const {return dynamic_cast<Cn&>((*this)["DIB_ID"]);} 
    const Cn&         getCabltyp()const {return dynamic_cast<Cn&>((*this)["CABL_TYP"]);} 
    const Cn&         getCablid ()const {return dynamic_cast<Cn&>((*this)["CABL_ID"]);} 
    const Cn&         getConttyp()const {return dynamic_cast<Cn&>((*this)["CONT_TYP"]);} 
    const Cn&         getContid ()const {return dynamic_cast<Cn&>((*this)["CONT_ID"]);} 
    const Cn&         getLasrtyp()const {return dynamic_cast<Cn&>((*this)["LASR_TYP"]);} 
    const Cn&         getLasrid ()const {return dynamic_cast<Cn&>((*this)["LASR_ID"]);} 
    const Cn&         getExtrtyp()const {return dynamic_cast<Cn&>((*this)["EXTR_TYP"]);} 
    const Cn&         getExtrid ()const {return dynamic_cast<Cn&>((*this)["EXTR_ID"]);} 

    void read(std::ifstream& infile)
    {
      U2 REC_LEN;
      REC_LEN.read(infile);
      U1 REC_TYP;
      REC_TYP.read(infile);
      U1 REC_SUB;
      REC_SUB.read(infile);

      (*this)["HEAD_NUM"].read(infile);
      (*this)["SITE_GRP"].read(infile);
      (*this)["SITE_CNT"].read(infile);
      (*this)["SITE_NUM"].read(infile, dynamic_cast<U1&>((*this)["SITE_CNT"]).getValue());
      (*this)["HAND_TYP"].read(infile);
      (*this)["HAND_ID"].read(infile);
      (*this)["CARD_TYP"].read(infile);
      (*this)["CARD_ID"].read(infile);
      (*this)["LOAD_TYP"].read(infile);
      (*this)["LOAD_ID"].read(infile);
      (*this)["DIB_TYP"].read(infile);
      (*this)["DIB_ID"].read(infile);
      (*this)["CABL_TYP"].read(infile);
      (*this)["CABL_ID"].read(infile);
      (*this)["CONT_TYP"].read(infile);
      (*this)["CONT_ID"].read(infile);
      (*this)["LASR_TYP"].read(infile);
      (*this)["LASR_ID"].read(infile);
      (*this)["EXTR_TYP"].read(infile);
      (*this)["EXTR_ID"].read(infile);
      
   }
};


class PSR : public Record
{
  public:
    ~PSR() {}
    PSR() : Record(Record::PSR_TYPE)
    {
      add("CONT_FLG", boost::shared_ptr<B1>(new B1()));
      add("PSR_INDX", boost::shared_ptr<U2>(new U2()));
      add("PSR_NAM",  boost::shared_ptr<Cn>(new Cn()));
      add("OPT_FLG",  boost::shared_ptr<B1>(new B1("00000000")));
      add("TOTP_CNT", boost::shared_ptr<U2>(new U2()));
      add("LOCP_CNT", boost::shared_ptr<U2>(new U2()));
      add("PAT_BGN",  boost::shared_ptr<JxTYPE<U8> >(new JxTYPE<U8>()));
      add("PAT_END",  boost::shared_ptr<JxTYPE<U8> >(new JxTYPE<U8>()));
      add("PAT_FILE", boost::shared_ptr<JxTYPE<Cn> >(new JxTYPE<Cn>()));
      add("PAT_LBL",  boost::shared_ptr<JxTYPE<Cn> >(new JxTYPE<Cn>()));
      add("FILE_UID", boost::shared_ptr<JxTYPE<Cn> >(new JxTYPE<Cn>()));
      add("ATPG_DSC", boost::shared_ptr<JxTYPE<Cn> >(new JxTYPE<Cn>()));
      add("SRC_ID",   boost::shared_ptr<JxTYPE<Cn> >(new JxTYPE<Cn>()));
    }
    PSR(const PSR& psr) : Record(Record::PSR_TYPE)
    {
      add("CONT_FLG", boost::shared_ptr<B1>(new B1(psr.getContflg())));
      add("PSR_INDX", boost::shared_ptr<U2>(new U2(psr.getPsrindx())));
      add("PSR_NAM",  boost::shared_ptr<Cn>(new Cn(psr.getPsrnam ())));
      add("OPT_FLG",  boost::shared_ptr<B1>(new B1(psr.getOptflg ())));
      add("TOTP_CNT", boost::shared_ptr<U2>(new U2(psr.getTotpcnt())));
      add("LOCP_CNT", boost::shared_ptr<U2>(new U2(psr.getLocpcnt())));
      add("PAT_BGN",  boost::shared_ptr<JxTYPE<U8> >(new JxTYPE<U8>(psr.getPatbgn() )));
      add("PAT_END",  boost::shared_ptr<JxTYPE<U8> >(new JxTYPE<U8>(psr.getPatend() )));
      add("PAT_FILE", boost::shared_ptr<JxTYPE<Cn> >(new JxTYPE<Cn>(psr.getPatfile())));
      add("PAT_LBL",  boost::shared_ptr<JxTYPE<Cn> >(new JxTYPE<Cn>(psr.getPatlbl() )));
      add("FILE_UID", boost::shared_ptr<JxTYPE<Cn> >(new JxTYPE<Cn>(psr.getFileuid())));
      add("ATPG_DSC", boost::shared_ptr<JxTYPE<Cn> >(new JxTYPE<Cn>(psr.getAtpgdsc())));
      add("SRC_ID",   boost::shared_ptr<JxTYPE<Cn> >(new JxTYPE<Cn>(psr.getSrcid() )));
    }
    void clear() {Record::clear();}
    void setContflg(const std::basic_string<char>& contflg)          {(*this)["CONT_FLG"] = B1(contflg);}
    void setPsrindx(unsigned short psrindx)                          {(*this)["PSR_INDX"] = U2(psrindx);}
    void setPsrnam(const std::basic_string<char>& psrnam)            {(*this)["PSR_NAM"]  = Cn(psrnam);}
    void setOptflg(const std::basic_string<char>& optflg="00000000") {(*this)["OPT_FLG"]  = B1(optflg);}
    void setTotpcnt(unsigned short totpcnt)                          {(*this)["TOTP_CNT"] = U2(totpcnt);}
    void setLocpcnt(unsigned short locpcnt)                                                 
    {
      if(locpcnt != dynamic_cast<U2&>((*this)["LOCP_CNT"]).getValue())
      {
        (*this)["LOCP_CNT"] = U2(locpcnt);

        boost::shared_ptr<JxTYPE<U8> > PAT_BGN = boost::shared_ptr<JxTYPE<U8> >(new JxTYPE<U8>(locpcnt));
        replace_element("PAT_BGN", PAT_BGN);

        boost::shared_ptr<JxTYPE<U8> > PAT_END = boost::shared_ptr<JxTYPE<U8> >(new JxTYPE<U8>(locpcnt));
        replace_element("PAT_END", PAT_END);

        boost::shared_ptr<JxTYPE<Cn> > PAT_FILE = boost::shared_ptr<JxTYPE<Cn> >(new JxTYPE<Cn>(locpcnt));
        replace_element("PAT_FILE", PAT_FILE);

        boost::shared_ptr<JxTYPE<Cn> > PAT_LBL = boost::shared_ptr<JxTYPE<Cn> >(new JxTYPE<Cn>(locpcnt));
        replace_element("PAT_LBL", PAT_LBL);

        boost::shared_ptr<JxTYPE<Cn> > FILE_UID = boost::shared_ptr<JxTYPE<Cn> >(new JxTYPE<Cn>(locpcnt));
        replace_element("FILE_UID", FILE_UID);

        boost::shared_ptr<JxTYPE<Cn> > ATPG_DSC = boost::shared_ptr<JxTYPE<Cn> >(new JxTYPE<Cn>(locpcnt));
        replace_element("ATPG_DSC", ATPG_DSC);

        boost::shared_ptr<JxTYPE<Cn> > SRC_ID = boost::shared_ptr<JxTYPE<Cn> >(new JxTYPE<Cn>(locpcnt));
        replace_element("SRC_ID", SRC_ID);
      }
    }
    void setPatbgn(unsigned short sets,unsigned long long patbgn) 
    {assert(sets<dynamic_cast<U2&>((*this)["LOCP_CNT"]).getValue()); dynamic_cast<JxTYPE<U8> &>((*this)["PAT_BGN"])[sets] = U8(patbgn);}
    void setPatend(unsigned short sets,unsigned long long patend)                                                           
    {assert(sets<dynamic_cast<U2&>((*this)["LOCP_CNT"]).getValue()); dynamic_cast<JxTYPE<U8> &>((*this)["PAT_END"])[sets] = U8(patend);}
    void setPatfile(unsigned short sets,const std::basic_string<char>& patfile)                                             
    {assert(sets<dynamic_cast<U2&>((*this)["LOCP_CNT"]).getValue()); dynamic_cast<JxTYPE<Cn>&>((*this)["PAT_FILE"])[sets] = Cn(patfile);}
    void setPatlbl(unsigned short sets,const std::basic_string<char>& patlbl)                                               
    {assert(sets<dynamic_cast<U2&>((*this)["LOCP_CNT"]).getValue()); dynamic_cast<JxTYPE<Cn> &>((*this)["PAT_LBL"])[sets] = Cn(patlbl);}
    void setFileuid(unsigned short sets,const std::basic_string<char>& fileuid)                                             
    {assert(sets<dynamic_cast<U2&>((*this)["LOCP_CNT"]).getValue()); dynamic_cast<JxTYPE<Cn> &>((*this)["FILE_UID"])[sets]= Cn(fileuid);}
    void setAtpgdsc(unsigned short sets,const std::basic_string<char>& atpgdsc)                                             
    {assert(sets<dynamic_cast<U2&>((*this)["LOCP_CNT"]).getValue()); dynamic_cast<JxTYPE<Cn> &>((*this)["ATPG_DSC"])[sets]= Cn(atpgdsc);}
    void setSrcid(unsigned short sets,const std::basic_string<char>& srcid)                                                 
    {assert(sets<dynamic_cast<U2&>((*this)["LOCP_CNT"]).getValue()); dynamic_cast<JxTYPE<Cn> &>((*this)["SRC_ID"])[sets]  = Cn(srcid);}

    const B1& getContflg()const {return dynamic_cast<B1&>((*this)["CONT_FLG"]);}
    const U2& getPsrindx()const {return dynamic_cast<U2&>((*this)["PSR_INDX"]);}
    const Cn& getPsrnam ()const {return dynamic_cast<Cn&>((*this)["PSR_NAM"]);}
    const B1& getOptflg ()const {return dynamic_cast<B1&>((*this)["OPT_FLG"]);}
    const U2& getTotpcnt()const {return dynamic_cast<U2&>((*this)["TOTP_CNT"]);}
    const U2& getLocpcnt()const {return dynamic_cast<U2&>((*this)["LOCP_CNT"]);}
    const JxTYPE<U8>& getPatbgn() const {return dynamic_cast<JxTYPE<U8> &>((*this)["PAT_BGN"]);}
    const JxTYPE<U8>& getPatend() const {return dynamic_cast<JxTYPE<U8> &>((*this)["PAT_END"]);}
    const JxTYPE<Cn>& getPatfile()const {return dynamic_cast<JxTYPE<Cn> &>((*this)["PAT_FILE"]);}
    const JxTYPE<Cn>& getPatlbl() const {return dynamic_cast<JxTYPE<Cn> &>((*this)["PAT_LBL"]);}
    const JxTYPE<Cn>& getFileuid()const {return dynamic_cast<JxTYPE<Cn> &>((*this)["FILE_UID"]);}
    const JxTYPE<Cn>& getAtpgdsc()const {return dynamic_cast<JxTYPE<Cn> &>((*this)["ATPG_DSC"]);}
    const JxTYPE<Cn>& getSrcid()  const {return dynamic_cast<JxTYPE<Cn> &>((*this)["SRC_ID"]);}

    void write(std::ofstream& outfile)
    {
      if((dynamic_cast<B1&>((*this)["OPT_FLG"])[0])) delete_element("PAT_LBL");
      if((dynamic_cast<B1&>((*this)["OPT_FLG"])[1])) delete_element("FILE_UID");
      if((dynamic_cast<B1&>((*this)["OPT_FLG"])[2])) delete_element("ATPG_DSC");
      if((dynamic_cast<B1&>((*this)["OPT_FLG"])[3])) delete_element("SRC_ID");

      Record::write(outfile);
    }
 
    void read(std::ifstream& infile)
    {
      U2 REC_LEN;
      REC_LEN.read(infile);
      U1 REC_TYP;
      REC_TYP.read(infile);
      U1 REC_SUB;
      REC_SUB.read(infile);

     (*this)["CONT_FLG"].read(infile);
     (*this)["PSR_INDX"].read(infile);
     (*this)["PSR_NAM"].read(infile);
     (*this)["OPT_FLG"].read(infile);
     (*this)["TOTP_CNT"].read(infile);
     (*this)["LOCP_CNT"].read(infile);
     (*this)["PAT_BGN"].read(infile, dynamic_cast<U2&>((*this)["LOCP_CNT"]).getValue());
     (*this)["PAT_END"].read(infile, dynamic_cast<U2&>((*this)["LOCP_CNT"]).getValue());
     (*this)["PAT_FILE"].read(infile,dynamic_cast<U2&>((*this)["LOCP_CNT"]).getValue());
#if  !OLD_STDF_VERSION 
     if(!(dynamic_cast<B1&>((*this)["OPT_FLG"])[0]))(*this)["PAT_LBL"].read(infile, dynamic_cast<U2&>((*this)["LOCP_CNT"]).getValue()); else delete_element("PAT_LBL");
     if(!(dynamic_cast<B1&>((*this)["OPT_FLG"])[1]))(*this)["FILE_UID"].read(infile, dynamic_cast<U2&>((*this)["LOCP_CNT"]).getValue());else delete_element("FILE_UID");
     if(!(dynamic_cast<B1&>((*this)["OPT_FLG"])[2]))(*this)["ATPG_DSC"].read(infile, dynamic_cast<U2&>((*this)["LOCP_CNT"]).getValue());else delete_element("ATPG_DSC");
     if(!(dynamic_cast<B1&>((*this)["OPT_FLG"])[3]))(*this)["SRC_ID"].read(infile,  dynamic_cast<U2&>((*this)["LOCP_CNT"]).getValue()); else delete_element("SRC_ID");
#else
     if(!(dynamic_cast<B1&>((*this)["OPT_FLG"])[0]))(*this)["PAT_LBL"].read(infile, dynamic_cast<U2&>((*this)["LOCP_CNT"]).getValue()); 
     if(!(dynamic_cast<B1&>((*this)["OPT_FLG"])[1]))(*this)["FILE_UID"].read(infile, dynamic_cast<U2&>((*this)["LOCP_CNT"]).getValue());
     if(!(dynamic_cast<B1&>((*this)["OPT_FLG"])[2]))(*this)["ATPG_DSC"].read(infile, dynamic_cast<U2&>((*this)["LOCP_CNT"]).getValue());
     if(!(dynamic_cast<B1&>((*this)["OPT_FLG"])[3]))(*this)["SRC_ID"].read(infile,  dynamic_cast<U2&>((*this)["LOCP_CNT"]).getValue()); 
#endif
    }

};


class NMR : public Record
{
  public:
    ~NMR() {}
    NMR() : Record(Record::NMR_TYPE)
    {
      add("CONT_FLG", boost::shared_ptr<B1>(new B1()));
      add("NMR_INDX", boost::shared_ptr<U2>(new U2()));
      add("TOTM_CNT", boost::shared_ptr<U2>(new U2()));
      add("LOCM_CNT", boost::shared_ptr<U2>(new U2()));
      add("PMR_INDX", boost::shared_ptr<JxTYPE<U2> >(new JxTYPE<U2>()));
      add("ATPG_NAM", boost::shared_ptr<JxTYPE<Cn> >(new JxTYPE<Cn>()));
    }
    NMR(const NMR& nmr) : Record(Record::NMR_TYPE)
    {
      add("CONT_FLG", boost::shared_ptr<B1>(new B1(nmr.getContflg())));
      add("NMR_INDX", boost::shared_ptr<U2>(new U2(nmr.getNmrindx())));
      add("TOTM_CNT", boost::shared_ptr<U2>(new U2(nmr.getTotmcnt())));
      add("LOCM_CNT", boost::shared_ptr<U2>(new U2(nmr.getLocmcnt())));
      add("PMR_INDX", boost::shared_ptr<JxTYPE<U2> >(new JxTYPE<U2>(nmr.getPmrindx())));
      add("ATPG_NAM", boost::shared_ptr<JxTYPE<Cn> >(new JxTYPE<Cn>(nmr.getAtpgnam())));
    }                                                               
    void clear() {Record::clear();}
    void setContflg(const std::basic_string<char>& contflg) {(*this)["CONT_FLG"] = B1(contflg);}
    void setNmrindx(unsigned short nmrindx) {((*this)["NMR_INDX"]) = U2(nmrindx);}
    void setTotmcnt(unsigned short totmcnt) {((*this)["TOTM_CNT"]) = U2(totmcnt);}
    void setLocmcnt(unsigned short locmcnt)
    {
      if(dynamic_cast<U2&>((*this)["LOCM_CNT"]).getValue() != locmcnt)
      {
        (*this)["LOCM_CNT"] = U2(locmcnt);

        boost::shared_ptr<JxTYPE<U2> > PMR_INDX = boost::shared_ptr<JxTYPE<U2> >(new JxTYPE<U2>(locmcnt));
        replace_element("PMR_INDX", PMR_INDX);

        boost::shared_ptr<JxTYPE<Cn> > ATPG_NAM = boost::shared_ptr<JxTYPE<Cn> >(new JxTYPE<Cn>(locmcnt));
        replace_element("ATPG_NAM", ATPG_NAM);
      }
    }
    void setPmrindx(unsigned short pmrs,unsigned short pmrindx)
    {assert(pmrs < dynamic_cast<U2&>((*this)["LOCM_CNT"]).getValue());               dynamic_cast<JxTYPE<U2> &>((*this)["PMR_INDX"])[pmrs] = U2(pmrindx);}
    void setAtpgnam(unsigned short pmrs,const std::basic_string<char>& atpgnam)
    {assert(pmrs<dynamic_cast<U2&>((*this)["LOCM_CNT"]).getValue()); dynamic_cast<JxTYPE<Cn> &>((*this)["ATPG_NAM"])[pmrs] = Cn(atpgnam);}

    const B1&         getContflg()const {return dynamic_cast<B1&>(((*this)["CONT_FLG"]));}
    const U2&         getNmrindx()const {return dynamic_cast<U2&>(((*this)["NMR_INDX"]));}
    const U2&         getTotmcnt()const {return dynamic_cast<U2&>(((*this)["TOTM_CNT"]));}
    const U2&         getLocmcnt()const {return dynamic_cast<U2&>(((*this)["LOCM_CNT"]));}
    const JxTYPE<U2>& getPmrindx()const {return dynamic_cast<JxTYPE<U2> &>(((*this)["PMR_INDX"]));}
    const JxTYPE<Cn>& getAtpgnam()const {return dynamic_cast<JxTYPE<Cn> &>(((*this)["ATPG_NAM"]));}

    void read(std::ifstream& infile)
    {
      U2 REC_LEN;
      REC_LEN.read(infile);
      U1 REC_TYP;
      REC_TYP.read(infile);
      U1 REC_SUB;
      REC_SUB.read(infile);

      (*this)["CONT_FLG"].read(infile);
      (*this)["NMR_INDX"].read(infile);
      (*this)["TOTM_CNT"].read(infile);
      (*this)["LOCM_CNT"].read(infile);
      (*this)["PMR_INDX"].read(infile, dynamic_cast<U2&>((*this)["LOCM_CNT"]).getValue());
      (*this)["ATPG_NAM"].read(infile, dynamic_cast<U2&>((*this)["LOCM_CNT"]).getValue());
    }
};


class CNR : public Record
{
  public:
    ~CNR() {}
    CNR() : Record(Record::CNR_TYPE)
    {
      add("CHN_NUM",  boost::shared_ptr<U2>(new U2()));
      add("BIT_POS",  boost::shared_ptr<U4>(new U4()));
      add("CELL_NAM", boost::shared_ptr<Sn>(new Sn()));
    }
    CNR(const CNR& cnr) : Record(Record::CNR_TYPE)
    {
      add("CHN_NUM",  boost::shared_ptr<U2>(new U2(cnr.getChnnum() )));
      add("BIT_POS",  boost::shared_ptr<U4>(new U4(cnr.getBitpos() )));
      add("CELL_NAM", boost::shared_ptr<Sn>(new Sn(cnr.getCellnam())));
    }
    void clear() {Record::clear();}
    void setChnnum(unsigned short chnnum)                   {(*this)["CHN_NUM"]  = U2(chnnum);}
    void setBitpos(unsigned int bitpos)                     {(*this)["BIT_POS"]  = U4(bitpos);}
    void setCellnam(const std::basic_string<char>& cellnam) {(*this)["CELL_NAM"] = Sn(cellnam);}

    const U2& getChnnum() const {return dynamic_cast<U2&>((*this)["CHN_NUM"]);}
    const U4& getBitpos() const {return dynamic_cast<U4&>((*this)["BIT_POS"]);}
    const Sn& getCellnam()const {return dynamic_cast<Sn&>((*this)["CELL_NAM"]);}

};


class SSR : public Record
{
  public:
    ~SSR() {}
    SSR() : Record(Record::SSR_TYPE)
    {
      add("SSR_NAM", boost::shared_ptr<Cn>(new Cn())                  );
      add("CHN_CNT", boost::shared_ptr<U2>(new U2())                  );
      add("CHN_LIST",boost::shared_ptr<JxTYPE<U2> >(new JxTYPE<U2>() ));
    }
    SSR(const SSR& ssr) : Record(Record::SSR_TYPE)
    {
      add("SSR_NAM", boost::shared_ptr<Cn>(new Cn(ssr.getSsrnam()))                  );
      add("CHN_CNT", boost::shared_ptr<U2>(new U2(ssr.getChncnt()))                  );
      add("CHN_LIST",boost::shared_ptr<JxTYPE<U2> >(new JxTYPE<U2>(ssr.getChnlist()) ));
    }
    void clear(){Record::clear();}
    void setSsrnam(const std::basic_string<char>& ssrnam){(*this)["SSR_NAM"] = Cn(ssrnam);}
    void setChncnt(unsigned short chncnt)
    {
      if(dynamic_cast<U2&>((*this)["CHN_CNT"]).getValue() != chncnt)
      {
        (*this)["CHN_CNT"] = U2(chncnt);

        boost::shared_ptr<JxTYPE<U2> > CHN_LIST = boost::shared_ptr<JxTYPE<U2> >(new JxTYPE<U2>(chncnt));
        replace_element("CHN_LIST", CHN_LIST);
      }
    }
    void setChnlist(unsigned short chains,unsigned short chnlist)
    {assert(chains < dynamic_cast<U2&>((*this)["CHN_CNT"])); dynamic_cast<JxTYPE<U2> &>((*this)["CHN_LIST"])[chains] = U2(chnlist);}

    const Cn&        getSsrnam() const {return dynamic_cast<Cn&>((*this)["SSR_NAM"]);}
    const U2&        getChncnt() const {return dynamic_cast<U2&>((*this)["CHN_CNT"]);}
    const JxTYPE<U2>& getChnlist()const {return dynamic_cast<JxTYPE<U2> &>((*this)["CHN_LIST"]);}

    void read(std::ifstream& infile)
    {
      U2 REC_LEN;
      REC_LEN.read(infile);
      U1 REC_TYP;
      REC_TYP.read(infile);
      U1 REC_SUB;
      REC_SUB.read(infile);

      (*this)["SSR_NAM"].read(infile);
      (*this)["CHN_CNT"].read(infile);
      (*this)["CHN_LIST"].read(infile, dynamic_cast<U2&>((*this)["CHN_CNT"]).getValue());
    }

};


class CDR : public Record
{
  public:
    ~CDR() {}
    CDR() : Record(Record::CDR_TYPE)
    {
      add("CONT_FLG",boost::shared_ptr<B1>        (new B1()));
      add("CDR_INDX",boost::shared_ptr<U2>        (new U2()));
      add("CHN_NAM", boost::shared_ptr<Cn>        (new Cn()));
      add("CHN_LEN", boost::shared_ptr<U4>        (new U4()));
      add("SIN_PIN", boost::shared_ptr<U2>        (new U2()));
      add("SOUT_PIN",boost::shared_ptr<U2>        (new U2()));
      add("MSTR_CNT",boost::shared_ptr<U1>        (new U1()));
      add("M_CLKS",  boost::shared_ptr<JxTYPE<U2> >(new JxTYPE<U2>()));
      add("SLAV_CNT",boost::shared_ptr<U1>( new U1()));
      add("S_CLKS",  boost::shared_ptr<JxTYPE<U2> >(new JxTYPE<U2>()));
      add("INV_VAL", boost::shared_ptr<U1>(new U1(255u)));
      add("LST_CNT", boost::shared_ptr<U2>(new U2()));
      add("CELL_LST",boost::shared_ptr<JxTYPE<Sn> >(new JxTYPE<Sn>()));
    }
    CDR(const CDR& cdr) : Record(Record::CDR_TYPE)
    {
      add("CONT_FLG",boost::shared_ptr<B1>        (new B1(cdr.getContflg())));
      add("CDR_INDX",boost::shared_ptr<U2>        (new U2(cdr.getCdrindx())));
      add("CHN_NAM", boost::shared_ptr<Cn>        (new Cn(cdr.getChnnam() )));
      add("CHN_LEN", boost::shared_ptr<U4>        (new U4(cdr.getChnlen() )));
      add("SIN_PIN", boost::shared_ptr<U2>        (new U2(cdr.getSinpin() )));
      add("SOUT_PIN",boost::shared_ptr<U2>        (new U2(cdr.getSoutpin())));
      add("MSTR_CNT",boost::shared_ptr<U1>        (new U1(cdr.getMstrcnt())));
      add("M_CLKS",  boost::shared_ptr<JxTYPE<U2> >(new JxTYPE<U2>(cdr.getMclks())));
      add("SLAV_CNT",boost::shared_ptr<U1>(new U1(cdr.getSlavcnt())));
      add("S_CLKS",  boost::shared_ptr<JxTYPE<U2> >(new JxTYPE<U2>(cdr.getSclks())));
      add("INV_VAL", boost::shared_ptr<U1>(new U1(cdr.getinvval())));
      add("LST_CNT", boost::shared_ptr<U2>(new U2(cdr.getLstcnt())));
      add("CELL_LST",boost::shared_ptr<JxTYPE<Sn> >(new JxTYPE<Sn>(cdr.getCelllst())));
    }
    void clear() {Record::clear(); setInvval();}
    void setContflg(const std::basic_string<char>& contflg) {(*this)["CONT_FLG"] = B1(contflg);}
    void setCdrindx(unsigned short cdrindx) {(*this)["CDR_INDX"] = U2(cdrindx);}
    void setChnnam(const std::basic_string<char>& chnnam) {(*this)["CHN_NAM"] = Cn(chnnam);}
    void setChnlen(unsigned int chnlen) {(*this)["CHN_LEN"] = U4(chnlen);}
    void setSinpin(unsigned short sinpin) {(*this)["SIN_PIN"] = U2(sinpin);}
    void setSoutpin(unsigned short soutpin) {(*this)["SOUT_PIN"] = U2(soutpin);}
    void setMstrcnt(unsigned char mstrcnt)
    {
      if(dynamic_cast<U1&>((*this)["MSTR_CNT"]).getValue() != mstrcnt)
      {
        (*this)["MSTR_CNT"] = U1(mstrcnt);
        
        boost::shared_ptr<JxTYPE<U2> > M_CLKS = boost::shared_ptr<JxTYPE<U2> >(new JxTYPE<U2>(mstrcnt));
        replace_element("M_CLKS", M_CLKS);
      }
    }
    void setMclks(unsigned char mcps,unsigned short mclks) {assert(mcps < dynamic_cast<U1&>((*this)["MSTR_CNT"]).getValue()); dynamic_cast<JxTYPE<U2> &>((*this)["M_CLKS"])[mcps] = U2(mclks);}
    void setSlavcnt(unsigned char slavcnt)
    {
      if(dynamic_cast<U1&>((*this)["SLAV_CNT"]).getValue() != slavcnt)
      {
        (*this)["SLAV_CNT"] = U1(slavcnt);
        
        boost::shared_ptr<JxTYPE<U2> > S_CLKS = boost::shared_ptr<JxTYPE<U2> >(new JxTYPE<U2>(slavcnt));
        replace_element("S_CLKS", S_CLKS);
    	}	
    }
    void setSclks(unsigned char scps,unsigned short lstcnt) {assert(scps < dynamic_cast<U1&>((*this)["SLAV_CNT"]).getValue()); dynamic_cast<JxTYPE<U2> &>((*this)["S_CLKS"])[scps] = lstcnt;}
    void setInvval(unsigned char invval = 255u) {dynamic_cast<U1&>((*this)["INV_VAL"]) = U1(invval);}
    void setLstcnt(unsigned short lstcnt)
    {
      if(dynamic_cast<U2&>((*this)["LST_CNT"]).getValue() != lstcnt)
      {
        (*this)["LST_CNT"] = U2(lstcnt);
     
        boost::shared_ptr<JxTYPE<Sn> > CELL_LST = boost::shared_ptr<JxTYPE<Sn> >(new JxTYPE<Sn>(lstcnt));
        replace_element("CELL_LST", CELL_LST);
      }
    }
    void setCelllst(unsigned short scl,const std::basic_string<char>& celllst) {assert(scl < dynamic_cast<U2&>((*this)["LST_CNT"]).getValue()); dynamic_cast<JxTYPE<Sn> &>((*this)["CELL_LST"])[scl] = Sn(celllst);}

    const B1&         getContflg() const {return dynamic_cast<B1&>((*this)["CONT_FLG"]);}
    const U2&         getCdrindx() const {return dynamic_cast<U2&>((*this)["CDR_INDX"]);}
    const Cn&         getChnnam()  const {return dynamic_cast<Cn&>((*this)["CHN_NAM"]);}
    const U4&         getChnlen()  const {return dynamic_cast<U4&>((*this)["CHN_LEN"]);}
    const U2&         getSinpin()  const {return dynamic_cast<U2&>((*this)["SIN_PIN"]);}
    const U2&         getSoutpin() const {return dynamic_cast<U2&>((*this)["SOUT_PIN"]);}
    const U1&         getMstrcnt() const {return dynamic_cast<U1&>((*this)["MSTR_CNT"]);} 
    const JxTYPE<U2>& getMclks()   const {return dynamic_cast<JxTYPE<U2> &>((*this)["M_CLKS"]);}
    const U1&         getSlavcnt() const {return dynamic_cast<U1&>((*this)["SLAV_CNT"]);}
    const JxTYPE<U2>& getSclks()   const {return dynamic_cast<JxTYPE<U2> &>((*this)["S_CLKS"]);}
    const U1&         getinvval()  const {return dynamic_cast<U1&>((*this)["INV_VAL"]);}
    const U2&         getLstcnt()  const {return dynamic_cast<U2&>((*this)["LST_CNT"]);}
    const JxTYPE<Sn>& getCelllst() const {return dynamic_cast<JxTYPE<Sn> &>((*this)["CELL_LST"]);}
 
    void read(std::ifstream& infile)
    {
      U2 REC_LEN;
      REC_LEN.read(infile);
      U1 REC_TYP;
      REC_TYP.read(infile);
      U1 REC_SUB;
      REC_SUB.read(infile);

      (*this)["CONT_FLG"].read(infile);
      (*this)["CDR_INDX"].read(infile);
      (*this)["CHN_NAM"].read(infile);
      (*this)["CHN_LEN"].read(infile);
      (*this)["SIN_PIN"].read(infile);
      (*this)["SOUT_PIN"].read(infile);
      (*this)["MSTR_CNT"].read(infile);
      (*this)["M_CLKS"].read(infile, dynamic_cast<U1&>((*this)["MSTR_CNT"]).getValue());
      (*this)["SLAV_CNT"].read(infile);
      (*this)["S_CLKS"].read(infile, dynamic_cast<U1&>((*this)["SLAV_CNT"]).getValue());
      (*this)["INV_VAL"].read(infile);
      (*this)["LST_CNT"].read(infile);
      (*this)["CELL_LST"].read(infile, dynamic_cast<U2&>((*this)["LST_CNT"]).getValue());
    }

};


////////////////////////////// WAFER //////////////////////////////

class WIR : public Record
{
  public:
    ~WIR() {}
    WIR() : Record(Record::WIR_TYPE)
    {
      add("HEAD_NUM", boost::shared_ptr<U1>(new U1()    ));
      add("SITE_GRP", boost::shared_ptr<U1>(new U1(255u)));
      add("START_T",  boost::shared_ptr<U4>(new U4()    ));
      add("WAFER_ID", boost::shared_ptr<Cn>(new Cn()    ));
    }
    WIR(const WIR& wir) : Record(Record::WIR_TYPE)
    {
      add("HEAD_NUM", boost::shared_ptr<U1>(new U1(wir.getHeadnum())));
      add("SITE_GRP", boost::shared_ptr<U1>(new U1(wir.getSitegrp())));
      add("START_T",  boost::shared_ptr<U4>(new U4(wir.getStart  ())));
      add("WAFER_ID", boost::shared_ptr<Cn>(new Cn(wir.getWaferid())));
    }
    void clear() {Record::clear(); setSitegrp();}

    void setHeadnum(unsigned char headnum)                  {(*this)["HEAD_NUM"] = U1(headnum);}
    void setSitegrp(unsigned char sitegrp=255u)             {(*this)["SITE_GRP"] = U1(sitegrp);}
    void setStart(unsigned int start)                       {(*this)["START_T"]  = U4(start  );}
    void setWaferid(const std::basic_string<char>& waferid) {(*this)["WAFER_ID"] = Cn(waferid);}

    const U1& getHeadnum()const {return dynamic_cast<U1&>((*this)["HEAD_NUM"]);}
    const U1& getSitegrp()const {return dynamic_cast<U1&>((*this)["SITE_GRP"]);}
    const U4& getStart  ()const {return dynamic_cast<U4&>((*this)["START_T"]) ;}
    const Cn& getWaferid()const {return dynamic_cast<Cn&>((*this)["WAFER_ID"]);}

};


class WRR : public Record
{
  public:
    ~WRR() {};
    WRR() : Record(Record::WRR_TYPE)
    {
      add("HEAD_NUM", boost::shared_ptr<U1>(new U1()));
      add("SITE_GRP", boost::shared_ptr<U1>(new U1(255u)) );
      add("FINISH_T", boost::shared_ptr<U4>(new U4()));
      add("PART_CNT", boost::shared_ptr<U4>(new U4()));
      add("RTST_CNT", boost::shared_ptr<U4>(new U4(4294967295u)));
      add("ABRT_CNT", boost::shared_ptr<U4>(new U4(4294967295u)));
      add("GOOD_CNT", boost::shared_ptr<U4>(new U4(4294967295u)));
      add("FUNC_CNT", boost::shared_ptr<U4>(new U4(4294967295u)));
      add("WAFER_ID", boost::shared_ptr<Cn>(new Cn()));
      add("FABWF_ID", boost::shared_ptr<Cn>(new Cn()));
      add("FRAME_ID", boost::shared_ptr<Cn>(new Cn()));
      add("MASK_ID",  boost::shared_ptr<Cn>(new Cn()));
      add("USR_DESC", boost::shared_ptr<Cn>(new Cn()));
      add("EXC_DESC", boost::shared_ptr<Cn>(new Cn()));
    }
    WRR(const WRR& wrr) : Record(Record::WRR_TYPE)
    {
      add("HEAD_NUM", boost::shared_ptr<U1>(new U1(wrr.getHeadnum())));
      add("SITE_GRP", boost::shared_ptr<U1>(new U1(wrr.getSitegrp())));
      add("FINISH_T", boost::shared_ptr<U4>(new U4(wrr.getFinisht())));
      add("PART_CNT", boost::shared_ptr<U4>(new U4(wrr.getPartcnt())));
      add("RTST_CNT", boost::shared_ptr<U4>(new U4(wrr.getAbrtcnt())));
      add("ABRT_CNT", boost::shared_ptr<U4>(new U4(wrr.getRtstcnt())));
      add("GOOD_CNT", boost::shared_ptr<U4>(new U4(wrr.getGoodcnt())));
      add("FUNC_CNT", boost::shared_ptr<U4>(new U4(wrr.getFunccnt())));
      add("WAFER_ID", boost::shared_ptr<Cn>(new Cn(wrr.getWaferid())));
      add("FABWF_ID", boost::shared_ptr<Cn>(new Cn(wrr.getFabwfid())));
      add("FRAME_ID", boost::shared_ptr<Cn>(new Cn(wrr.getFrameid())));
      add("MASK_ID",  boost::shared_ptr<Cn>(new Cn(wrr.getMaskid ())));
      add("USR_DESC", boost::shared_ptr<Cn>(new Cn(wrr.getUsrdesc())));
      add("EXC_DESC", boost::shared_ptr<Cn>(new Cn(wrr.getExcdesc())));
    }
    void clear() {Record::clear(); setSitegrp(); setRtstcnt(); setAbrtcnt(); setGoodcnt(); setFunccnt();}
    void setHeadnum(unsigned char headnum)                  {(*this)["HEAD_NUM"] = U1(headnum);}
    void setSitegrp(unsigned char sitegrp=255u)             {(*this)["SITE_GRP"] = U1(sitegrp);}
    void setFinisht(unsigned int finisht)                   {(*this)["FINISH_T"] = U4(finisht);}
    void setPartcnt(unsigned int partcnt)                   {(*this)["PART_CNT"] = U4(partcnt);}
    void setAbrtcnt(unsigned int abrtcnt=4294967295u)       {(*this)["ABRT_CNT"] = U4(abrtcnt);}
    void setRtstcnt(unsigned int rtstcnt=4294967295u)       {(*this)["RTST_CNT"] = U4(rtstcnt);}
    void setGoodcnt(unsigned int goodcnt=4294967295u)       {(*this)["GOOD_CNT"] = U4(goodcnt);}
    void setFunccnt(unsigned int funccnt=4294967295u)       {(*this)["FUNC_CNT"] = U4(funccnt);}
    void setWaferid(const std::basic_string<char>& waferid) {(*this)["WAFER_ID"] = Cn(waferid);}
    void setFabwfid(const std::basic_string<char>& fabwfid) {(*this)["FABWF_ID"] = Cn(fabwfid);}
    void setFrameid(const std::basic_string<char>& frameid) {(*this)["FRAME_ID"] = Cn(frameid);}
    void setMaskid(const std::basic_string<char>& maskid)   {(*this)["MASK_ID"]  = Cn(maskid );}
    void setUsrdesc(const std::basic_string<char>& usrdesc) {(*this)["USR_DESC"] = Cn(usrdesc);}
    void setExcdesc(const std::basic_string<char>& excdesc) {(*this)["EXC_DESC"] = Cn(excdesc);}

    const U1& getHeadnum()const {return dynamic_cast<U1&>((*this)["HEAD_NUM"]);}
    const U1& getSitegrp()const {return dynamic_cast<U1&>((*this)["SITE_GRP"]);}
    const U4& getFinisht()const {return dynamic_cast<U4&>((*this)["FINISH_T"]);}
    const U4& getPartcnt()const {return dynamic_cast<U4&>((*this)["PART_CNT"]);}
    const U4& getAbrtcnt()const {return dynamic_cast<U4&>((*this)["ABRT_CNT"]);}
    const U4& getRtstcnt()const {return dynamic_cast<U4&>((*this)["RTST_CNT"]);}
    const U4& getGoodcnt()const {return dynamic_cast<U4&>((*this)["GOOD_CNT"]);}
    const U4& getFunccnt()const {return dynamic_cast<U4&>((*this)["FUNC_CNT"]);}
    const Cn& getWaferid()const {return dynamic_cast<Cn&>((*this)["WAFER_ID"]);}
    const Cn& getFabwfid()const {return dynamic_cast<Cn&>((*this)["FABWF_ID"]);}
    const Cn& getFrameid()const {return dynamic_cast<Cn&>((*this)["FRAME_ID"]);}
    const Cn& getMaskid ()const {return dynamic_cast<Cn&>((*this)["MASK_ID"] );}
    const Cn& getUsrdesc()const {return dynamic_cast<Cn&>((*this)["USR_DESC"]);}
    const Cn& getExcdesc()const {return dynamic_cast<Cn&>((*this)["EXC_DESC"]);}

};


class WCR : public Record
{
  public:
    ~WCR() {}
    WCR() : Record(Record::WCR_TYPE)
    {
      add("WAFR_SIZ", boost::shared_ptr<R4>(new R4()));
      add("DIE_HT",   boost::shared_ptr<R4>(new R4()));
      add("DIE_WID",  boost::shared_ptr<R4>(new R4()));
      add("WF_UNITS", boost::shared_ptr<U1>(new U1()));
      add("WF_FLAT",  boost::shared_ptr<C1>(new C1()));
      add("CENTER_X", boost::shared_ptr<I2>(new I2(-32768)));
      add("CENTER_Y", boost::shared_ptr<I2>(new I2(-32768)));
      add("POS_X",    boost::shared_ptr<C1>(new C1()));
      add("POS_Y",    boost::shared_ptr<C1>(new C1()));
    }
    WCR(const WCR& wcr) : Record(Record::WCR_TYPE)
    {
      add("WAFR_SIZ", boost::shared_ptr<R4>(new R4(wcr.getWafrsiz())));
      add("DIE_HT",   boost::shared_ptr<R4>(new R4(wcr.getDieht  ())));
      add("DIE_WID",  boost::shared_ptr<R4>(new R4(wcr.getDiewid ())));
      add("WF_UNITS", boost::shared_ptr<U1>(new U1(wcr.getWfunits())));
      add("WF_FLAT",  boost::shared_ptr<C1>(new C1(wcr.getWfflat ())));
      add("CENTER_X", boost::shared_ptr<I2>(new I2(wcr.getCenterx())));
      add("CENTER_Y", boost::shared_ptr<I2>(new I2(wcr.getCentery())));
      add("POS_X",    boost::shared_ptr<C1>(new C1(wcr.getPosx   ())));
      add("POS_Y",    boost::shared_ptr<C1>(new C1(wcr.getPosy   ())));
    }
    void clear() {Record::clear(); setCenterx(); setCentery();}
    void setWafrsiz(float wafrsiz)          {(*this)["WAFR_SIZ"]  = R4(wafrsiz);}
    void setDieht(float dieht)              {(*this)["DIE_HT"]   = R4(dieht  );}
    void setDiewid(float diewid)            {(*this)["DIE_WID"]  = R4(diewid );}
    void setWfunits(unsigned char wfunits)  {(*this)["WF_UNITS"] = U1(wfunits);}
    void setWfflat(unsigned char wfflat)    {(*this)["WF_FLAT"]  = C1(wfflat );}
    void setCenterx(short centerx=-32768)   {(*this)["CENTER_X"] = I2(centerx);}
    void setCentery(short centery=-32768)   {(*this)["CENTER_Y"] = I2(centery);}
    void setPosx(unsigned char posx)        {(*this)["POS_X"]    = C1(posx   );}
    void setPosy(unsigned char posy)        {(*this)["POS_Y"]    = C1(posy   );}

    const R4& getWafrsiz()const {return dynamic_cast<R4&>((*this)["WAFR_SIZ"]);}
    const R4& getDieht  ()const {return dynamic_cast<R4&>((*this)["DIE_HT"])  ;}
    const R4& getDiewid ()const {return dynamic_cast<R4&>((*this)["DIE_WID"]) ;}
    const U1& getWfunits()const {return dynamic_cast<U1&>((*this)["WF_UNITS"]);}
    const C1& getWfflat ()const {return dynamic_cast<C1&>((*this)["WF_FLAT"]) ;}
    const I2& getCenterx()const {return dynamic_cast<I2&>((*this)["CENTER_X"]);}
    const I2& getCentery()const {return dynamic_cast<I2&>((*this)["CENTER_Y"]);}
    const C1& getPosx   ()const {return dynamic_cast<C1&>((*this)["POS_X"])   ;}
    const C1& getPosy   ()const {return dynamic_cast<C1&>((*this)["POS_Y"])   ;}

};


////////////////////////////// PART //////////////////////////////

class PIR : public Record
{
  public:
    ~PIR() {}
    PIR() : Record(Record::PIR_TYPE)
    {
      add("HEAD_NUM", boost::shared_ptr<U1>(new U1()));
      add("SITE_NUM", boost::shared_ptr<U1>(new U1()));
    }
    PIR(const PIR& pir) : Record(Record::PIR_TYPE)
    {
      add("HEAD_NUM", boost::shared_ptr<U1>(new U1(pir.getHeadnum())));
      add("SITE_NUM", boost::shared_ptr<U1>(new U1(pir.getSitenum())));
    }
    void clear() {Record::clear();}
    void setHeadnum(unsigned char headnum) {(*this)["HEAD_NUM"] =U1(headnum);}
    void setSitenum(unsigned char sitenum) {(*this)["SITE_NUM"] =U1(sitenum);}

    const U1& getHeadnum()const {return dynamic_cast<U1&>((*this)["HEAD_NUM"]);}
    const U1& getSitenum()const {return dynamic_cast<U1&>((*this)["SITE_NUM"]);}

    void read(std::ifstream& infile)
    {
      U2 REC_LEN;
      REC_LEN.read(infile);
      U1 REC_TYP;
      REC_TYP.read(infile);
      U1 REC_SUB;
      REC_SUB.read(infile);


      (*this)["HEAD_NUM"].read(infile);
      (*this)["SITE_NUM"].read(infile);
    }
};


class PRR : public Record
{
  public:
    ~PRR() {}
    PRR() : Record(Record::PRR_TYPE)
    {
      add("HEAD_NUM", boost::shared_ptr<U1>(new U1()));
      add("SITE_NUM", boost::shared_ptr<U1>(new U1()));
      add("PART_FLG", boost::shared_ptr<B1>(new B1("00001000")));
      add("NUM_TEST", boost::shared_ptr<U2>(new U2()));
      add("HARD_BIN", boost::shared_ptr<U2>(new U2()));
      add("SOFT_BIN", boost::shared_ptr<U2>(new U2(65535)));
      add("X_COORD",  boost::shared_ptr<I2>(new I2(-32768)));
      add("Y_COORD",  boost::shared_ptr<I2>(new I2(-32768)));
      add("TEST_T",   boost::shared_ptr<U4>(new U4()));
      add("PART_ID",  boost::shared_ptr<Cn>(new Cn()));
      add("PART_TXT", boost::shared_ptr<Cn>(new Cn()));
      add("PART_FIX", boost::shared_ptr<Bn>(new Bn()));
    }
    PRR(const PRR& prr) : Record(Record::PRR_TYPE)
    {
      add("HEAD_NUM",  boost::shared_ptr<U1>(new U1(prr.getHeadnum())));
      add("SITE_NUM",  boost::shared_ptr<U1>(new U1(prr.getSitenum())));
      add("PART_FLG",  boost::shared_ptr<B1>(new B1(prr.getPartflg())));
      add("NUM_TEST",  boost::shared_ptr<U2>(new U2(prr.getNumtest())));
      add("HARD_BIN",  boost::shared_ptr<U2>(new U2(prr.getHardbin())));
      add("SOFT_BIN",  boost::shared_ptr<U2>(new U2(prr.getSoftbin())));
      add("X_COORD",   boost::shared_ptr<I2>(new I2(prr.getXcoord() )));
      add("Y_COORD",   boost::shared_ptr<I2>(new I2(prr.getYcoord() )));
      add("TEST_T",    boost::shared_ptr<U4>(new U4(prr.getTestt()  )));
      add("PART_ID",   boost::shared_ptr<Cn>(new Cn(prr.getPartid() )));
      add("PART_TXT",  boost::shared_ptr<Cn>(new Cn(prr.getParttxt())));
      add("PART_FIX",  boost::shared_ptr<Bn>(new Bn(prr.getPartfix())));
    }
    void clear() {Record::clear(); setPartflg(); setSoftbin(); setXcoord(); setYcoord();}
    void setHeadnum(unsigned char headnum)                                {(*this)["HEAD_NUM"] = U1(headnum);}
    void setSitenum(unsigned char sitenum)                                {(*this)["SITE_NUM"] = U1(sitenum);}
    void setPartflg(const std::basic_string<char>& partflg = "00001000")  {(*this)["PART_FLG"] = B1(partflg);}
    void setNumtest(unsigned short numtest)                               {(*this)["NUM_TEST"] = U2(numtest);}
    void setHardbin(unsigned short hardbin)                               {(*this)["HARD_BIN"] = U2(hardbin);}
    void setSoftbin(unsigned short softbin=65535u)                        {(*this)["SOFT_BIN"] = U2(softbin);}
    void setXcoord(short xcoord=-32768)                                   {(*this)["X_COORD"]  = I2(xcoord );}
    void setYcoord(short ycoord=-32768)                                   {(*this)["Y_COORD"]  = I2(ycoord );}
    void setTestt(unsigned int testt=0u)                                  {(*this)["TEST_T"]   = U4(testt  );}
    void setPartid(const std::basic_string<char>& partid)                 {(*this)["PART_ID"]  = Cn(partid );}
    void setParttxt(const std::basic_string<char>&  parttxt)              {(*this)["PART_TXT"] = Cn(parttxt);}
    void setPartfix(const std::basic_string<char>&  partfix)              {(*this)["PART_FIX"] = Bn(partfix);}

    const U1&  getHeadnum()const {return dynamic_cast<U1&>((*this)["HEAD_NUM"]);} 
    const U1&  getSitenum()const {return dynamic_cast<U1&>((*this)["SITE_NUM"]);} 
    const B1&  getPartflg()const {return dynamic_cast<B1&>((*this)["PART_FLG"]);} 
    const U2&  getNumtest()const {return dynamic_cast<U2&>((*this)["NUM_TEST"]);} 
    const U2&  getHardbin()const {return dynamic_cast<U2&>((*this)["HARD_BIN"]);} 
    const U2&  getSoftbin()const {return dynamic_cast<U2&>((*this)["SOFT_BIN"]);} 
    const I2&  getXcoord() const {return dynamic_cast<I2&>((*this)["X_COORD"]);} 
    const I2&  getYcoord() const {return dynamic_cast<I2&>((*this)["Y_COORD"]);} 
    const U4&  getTestt()  const {return dynamic_cast<U4&>((*this)["TEST_T"]);} 
    const Cn&  getPartid() const {return dynamic_cast<Cn&>((*this)["PART_ID"]);} 
    const Cn&  getParttxt()const {return dynamic_cast<Cn&>((*this)["PART_TXT"]);} 
    const Bn&  getPartfix()const {return dynamic_cast<Bn&>((*this)["PART_FIX"]);} 

};


////////////////////////////// TEST //////////////////////////////

class TSR : public Record
{
  public:
    ~TSR() {}
    TSR() : Record(Record::TSR_TYPE)
    {
      add("HEAD_NUM", boost::shared_ptr<U1>(new U1()));
      add("SITE_NUM", boost::shared_ptr<U1>(new U1()));
      add("TEST_TYP", boost::shared_ptr<C1>(new C1()));
      add("TEST_NUM", boost::shared_ptr<U4>(new U4()));
      add("EXEC_CNT", boost::shared_ptr<U4>(new U4(4294967295u)));
      add("FAIL_CNT", boost::shared_ptr<U4>(new U4(4294967295u)));
      add("ALRM_CNT", boost::shared_ptr<U4>(new U4(4294967295u)));
      add("TEST_NAM", boost::shared_ptr<Cn>(new Cn()));
      add("SEQ_NAME", boost::shared_ptr<Cn>(new Cn()));
      add("TEST_LBL", boost::shared_ptr<Cn>(new Cn()));
      add("OPT_FLAG", boost::shared_ptr<B1>(new B1("11111111")));
      add("TEST_TIM", boost::shared_ptr<R4>(new R4()));
      add("TEST_MIN", boost::shared_ptr<R4>(new R4()));
      add("TEST_MAX", boost::shared_ptr<R4>(new R4()));
      add("TST_SUMS", boost::shared_ptr<R4>(new R4()));
      add("TST_SQRS", boost::shared_ptr<R4>(new R4()));
    }
    TSR(const TSR& tsr) : Record(Record::TSR_TYPE)
    {
      //add("HEAD_NUM", boost::shared_ptr<U1>(new U1(tsr.getHeadnum())));
      add("HEAD_NUM", boost::shared_ptr<U1>(new U1(tsr.get<U1>("HEAD_NUM"))));
      add("SITE_NUM", boost::shared_ptr<U1>(new U1(tsr.getSitenum())));
      add("TEST_TYP", boost::shared_ptr<C1>(new C1(tsr.getTesttyp())));
      add("TEST_NUM", boost::shared_ptr<U4>(new U4(tsr.getTestnum())));
      add("EXEC_CNT", boost::shared_ptr<U4>(new U4(tsr.getExeccnt())));
      add("FAIL_CNT", boost::shared_ptr<U4>(new U4(tsr.getFailcnt())));
      add("ALRM_CNT", boost::shared_ptr<U4>(new U4(tsr.getAlrmcnt())));
      add("TEST_NAM", boost::shared_ptr<Cn>(new Cn(tsr.getTestnam())));
      add("SEQ_NAME", boost::shared_ptr<Cn>(new Cn(tsr.getSeqname())));
      add("TEST_LBL", boost::shared_ptr<Cn>(new Cn(tsr.getTestlbl())));
      add("OPT_FLAG", boost::shared_ptr<B1>(new B1(tsr.getOptflag())));
      add("TEST_TIM", boost::shared_ptr<R4>(new R4(tsr.getTesttim())));
      add("TEST_MIN", boost::shared_ptr<R4>(new R4(tsr.getTestmin())));
      add("TEST_MAX", boost::shared_ptr<R4>(new R4(tsr.getTestmax())));
      add("TST_SUMS", boost::shared_ptr<R4>(new R4(tsr.getTstsums())));
      add("TST_SQRS", boost::shared_ptr<R4>(new R4(tsr.getTstsqrs())));
    }
    void clear() {Record::clear(); setExeccnt(); setFailcnt(); setAlrmcnt(); setOptflag();}
    void setHeadnum(unsigned char headnum) {(*this)["HEAD_NUM"]  = U1(headnum); }
    void setSitenum(unsigned char sitenum) {(*this)["SITE_NUM"]  = U1(sitenum); }
    void setTesttyp(unsigned char testtyp) {(*this)["TEST_TYP"]  = C1(testtyp); }
    void setTestnum(unsigned int testnum)  {(*this)["TEST_NUM"]  = U4(testnum); }
    void setExeccnt(unsigned int execcnt=4294967295u) {(*this)["EXEC_CNT"] = U4(execcnt); }
    void setFailcnt(unsigned int failcnt=4294967295u) {(*this)["FAIL_CNT"] = U4(failcnt); }
    void setAlrmcnt(unsigned int alrmcnt=4294967295u) {(*this)["ALRM_CNT"] = U4(alrmcnt); }
    void setTestnam(const std::basic_string<char>& testnam) {(*this)["TEST_NAM"] = Cn(testnam);}
    void setSeqname(const std::basic_string<char>& seqname) {(*this)["SEQ_NAME"] = Cn(seqname);}
    void setTestlbl(const std::basic_string<char>& testlbl) {(*this)["TEST_LBL"] = Cn(testlbl);}
    void setOptflag(const std::basic_string<char>& optflag="11111111") {(*this)["OPT_FLAG"] = B1(optflag);}
    void setTesttim(float testtim) {(*this)["TEST_TIM"] = R4(testtim); }
    void setTestmin(float testmin) {(*this)["TEST_MIN"] = R4(testmin); }
    void setTestmax(float testmax) {(*this)["TEST_MAX"] = R4(testmax); }
    void setTstsums(float tstsums) {(*this)["TST_SUMS"] = R4(tstsums); }
    void setTstsqrs(float tstsqrs) {(*this)["TST_SQRS"] = R4(tstsqrs); }

    const U1&    getHeadnum()const {return dynamic_cast<U1&>((*this)["HEAD_NUM"]);}
    const U1&    getSitenum()const {return dynamic_cast<U1&>((*this)["SITE_NUM"]);}
    const C1&    getTesttyp()const {return dynamic_cast<C1&>((*this)["TEST_TYP"]);}
    const U4&    getTestnum()const {return dynamic_cast<U4&>((*this)["TEST_NUM"]);}
    const U4&    getExeccnt()const {return dynamic_cast<U4&>((*this)["EXEC_CNT"]);}
    const U4&    getFailcnt()const {return dynamic_cast<U4&>((*this)["FAIL_CNT"]);}
    const U4&    getAlrmcnt()const {return dynamic_cast<U4&>((*this)["ALRM_CNT"]);}
    const Cn&    getTestnam()const {return dynamic_cast<Cn&>((*this)["TEST_NAM"]);}
    const Cn&    getSeqname()const {return dynamic_cast<Cn&>((*this)["SEQ_NAME"]);}
    const Cn&    getTestlbl()const {return dynamic_cast<Cn&>((*this)["TEST_LBL"]);}
    const B1&    getOptflag()const {return dynamic_cast<B1&>((*this)["OPT_FLAG"]);}
    const R4&    getTesttim()const {return dynamic_cast<R4&>((*this)["TEST_TIM"]);}
    const R4&    getTestmin()const {return dynamic_cast<R4&>((*this)["TEST_MIN"]);}
    const R4&    getTestmax()const {return dynamic_cast<R4&>((*this)["TEST_MAX"]);}
    const R4&    getTstsums()const {return dynamic_cast<R4&>((*this)["TST_SUMS"]);}
    const R4&    getTstsqrs()const {return dynamic_cast<R4&>((*this)["TST_SQRS"]);}

};


////////////////////////////// EXECUTION //////////////////////////////

class PTR : public Record
{
  public:
    ~PTR() {}
    PTR() : Record(Record::PTR_TYPE)
    {
      add("TEST_NUM", boost::shared_ptr<U4>(new U4()));
      add("HEAD_NUM", boost::shared_ptr<U1>(new U1()));
      add("SITE_NUM", boost::shared_ptr<U1>(new U1()));
      add("TEST_FLG", boost::shared_ptr<B1>(new B1()));
      add("PARM_FLG", boost::shared_ptr<B1>(new B1("11000000")));
      add("RESULT",   boost::shared_ptr<R4>(new R4()));
      add("TEST_TXT", boost::shared_ptr<Cn>(new Cn()));
      add("ALARM_ID", boost::shared_ptr<Cn>(new Cn()));
      add("OPT_FLAG", boost::shared_ptr<B1>(new B1("00001110")));
      add("RES_SCAL", boost::shared_ptr<I1>(new I1()));
      add("LLM_SCAL", boost::shared_ptr<I1>(new I1()));
      add("HLM_SCAL", boost::shared_ptr<I1>(new I1()));
      add("LO_LIMIT", boost::shared_ptr<R4>(new R4()));
      add("HI_LIMIT", boost::shared_ptr<R4>(new R4()));
      add("UNITS",    boost::shared_ptr<Cn>(new Cn()));
      add("C_RESFMT", boost::shared_ptr<Cn>(new Cn()));
      add("C_LLMFMT", boost::shared_ptr<Cn>(new Cn()));
      add("C_HLMFMT", boost::shared_ptr<Cn>(new Cn()));
      add("LO_SPEC",  boost::shared_ptr<R4>(new R4()));
      add("HI_SPEC",  boost::shared_ptr<R4>(new R4()));
    }
    PTR(const PTR& ptr) : Record(Record::PTR_TYPE)
    {
      add("TEST_NUM", boost::shared_ptr<U4>(new U4(ptr.getTestnum())));
      add("HEAD_NUM", boost::shared_ptr<U1>(new U1(ptr.getHeadnum())));
      add("SITE_NUM", boost::shared_ptr<U1>(new U1(ptr.getSitenum())));
      add("TEST_FLG", boost::shared_ptr<B1>(new B1(ptr.getTestflg())));
      add("PARM_FLG", boost::shared_ptr<B1>(new B1(ptr.getParmflg())));
      add("RESULT",   boost::shared_ptr<R4>(new R4(ptr.getResult() )));
      add("TEST_TXT", boost::shared_ptr<Cn>(new Cn(ptr.getTesttxt())));
      add("ALARM_ID", boost::shared_ptr<Cn>(new Cn(ptr.getAlarmid())));
      add("OPT_FLAG", boost::shared_ptr<B1>(new B1(ptr.getOptflag())));
      add("RES_SCAL", boost::shared_ptr<I1>(new I1(ptr.getResscal())));
      add("LLM_SCAL", boost::shared_ptr<I1>(new I1(ptr.getLlmscal())));
      add("HLM_SCAL", boost::shared_ptr<I1>(new I1(ptr.getHlmscal())));
      add("LO_LIMIT", boost::shared_ptr<R4>(new R4(ptr.getLolimit())));
      add("HI_LIMIT", boost::shared_ptr<R4>(new R4(ptr.getHilimit())));
      add("UNITS",    boost::shared_ptr<Cn>(new Cn(ptr.getUnits()  )));
      add("C_RESFMT", boost::shared_ptr<Cn>(new Cn(ptr.getCresfmt())));
      add("C_LLMFMT", boost::shared_ptr<Cn>(new Cn(ptr.getCllmfmt())));
      add("C_HLMFMT", boost::shared_ptr<Cn>(new Cn(ptr.getChlmfmt())));
      add("LO_SPEC",  boost::shared_ptr<R4>(new R4(ptr.getLospec() )));
      add("HI_SPEC",  boost::shared_ptr<R4>(new R4(ptr.getHispec() )));
    }
    void clear() {Record::clear();setParmflg();setOptflag();}
    void setTestnum(unsigned int testnum)                              {(*this)["TEST_NUM"] = U4(testnum);}
    void setHeadnum(unsigned char headnum)                             {(*this)["HEAD_NUM"] = U1(headnum);}
    void setSitenum(unsigned char sitenum)                             {(*this)["SITE_NUM"] = U1(sitenum);}
    void setTestflg(const std::basic_string<char>& testflg)            {(*this)["TEST_FLG"] = B1(testflg);}
    void setParmflg(const std::basic_string<char>& parmflg="11000000") {(*this)["PARM_FLG"] = B1(parmflg);}
    void setResult(float  result)                                      {(*this)["RESULT"]   = R4(result );}
    void setTesttxt(const std::basic_string<char>& testtxt)            {(*this)["TEST_TXT"] = Cn(testtxt);}
    void setAlarmid(const std::basic_string<char>& alarmid)            {(*this)["ALARM_ID"] = Cn(alarmid);}
    void setOptflag(const std::basic_string<char>& optflag="00001110") {(*this)["OPT_FLAG"] = B1(optflag);}
    void setResscal(char resscal)                                      {(*this)["RES_SCAL"] = I1(resscal);}
    void setLlmscal(char llmscal)                                      {(*this)["LLM_SCAL"] = I1(llmscal);}
    void setHlmscal(char hlmscal)                                      {(*this)["HLM_SCAL"] = I1(hlmscal);}
    void setLolimit(float lolimit)                                     {(*this)["LO_LIMIT"] = R4(lolimit);}
    void setHilimit(float hilimit)                                     {(*this)["HI_LIMIT"] = R4(hilimit);}
    void setUnits(const std::basic_string<char>& units)                {(*this)["UNITS"]    = Cn(units  );}
    void setCresfmt(const std::basic_string<char>& cresfmt)            {(*this)["C_RESFMT"] = Cn(cresfmt);}
    void setCllmfmt(const std::basic_string<char>& cllmfmt)            {(*this)["C_LLMFMT"] = Cn(cllmfmt);}
    void setChlmfmt(const std::basic_string<char>& chlmfmt)            {(*this)["C_HLMFMT"] = Cn(chlmfmt);}
    void setLospec(float lospec)                                       {(*this)["LO_SPEC"]  = R4(lospec );}
    void setHispec(float hispec)                                       {(*this)["HI_SPEC"]  = R4(hispec );}

    const  U4&  getTestnum()const {return dynamic_cast<U4&>((*this)["TEST_NUM"]);}
    const  U1&  getHeadnum()const {return dynamic_cast<U1&>((*this)["HEAD_NUM"]);}
    const  U1&  getSitenum()const {return dynamic_cast<U1&>((*this)["SITE_NUM"]);}
    const  B1&  getTestflg()const {return dynamic_cast<B1&>((*this)["TEST_FLG"]);}
    const  B1&  getParmflg()const {return dynamic_cast<B1&>((*this)["PARM_FLG"]);}
    const  R4&  getResult() const {return dynamic_cast<R4&>((*this)["RESULT"]);}
    const  Cn&  getTesttxt()const {return dynamic_cast<Cn&>((*this)["TEST_TXT"]);}
    const  Cn&  getAlarmid()const {return dynamic_cast<Cn&>((*this)["ALARM_ID"]);}
    const  B1&  getOptflag()const {return dynamic_cast<B1&>((*this)["OPT_FLAG"]);}
    const  I1&  getResscal()const {return dynamic_cast<I1&>((*this)["RES_SCAL"]);}
    const  I1&  getLlmscal()const {return dynamic_cast<I1&>((*this)["LLM_SCAL"]);}
    const  I1&  getHlmscal()const {return dynamic_cast<I1&>((*this)["HLM_SCAL"]);}
    const  R4&  getLolimit()const {return dynamic_cast<R4&>((*this)["LO_LIMIT"]);}
    const  R4&  getHilimit()const {return dynamic_cast<R4&>((*this)["HI_LIMIT"]);}
    const  Cn&  getUnits()  const {return dynamic_cast<Cn&>((*this)["UNITS"]);}
    const  Cn&  getCresfmt()const {return dynamic_cast<Cn&>((*this)["C_RESFMT"]);}
    const  Cn&  getCllmfmt()const {return dynamic_cast<Cn&>((*this)["C_LLMFMT"]);}
    const  Cn&  getChlmfmt()const {return dynamic_cast<Cn&>((*this)["C_HLMFMT"]);}
    const  R4&  getLospec() const {return dynamic_cast<R4&>((*this)["LO_SPEC"]);}
    const  R4&  getHispec() const {return dynamic_cast<R4&>((*this)["HI_SPEC"]);}

    void read(std::ifstream& infile)
    {
      U2 REC_LEN;
      REC_LEN.read(infile);
      U1 REC_TYP;
      REC_TYP.read(infile);
      U1 REC_SUB;
      REC_SUB.read(infile);

      size_t rz = REC_LEN.getValue();
      (*this)["TEST_NUM"].read(infile);
      (*this)["HEAD_NUM"].read(infile);
      (*this)["SITE_NUM"].read(infile);
      (*this)["TEST_FLG"].read(infile);
      (*this)["PARM_FLG"].read(infile);
      (*this)["RESULT"]  .read(infile);
      (*this)["TEST_TXT"].read(infile);
      (*this)["ALARM_ID"].read(infile);
      size_t az = 12 + (*this)["ALARM_ID"].storage() +(*this)["TEST_TXT"].storage(); 
      if(rz == az)
      {
        delete_element("OPT_FLAG");
        delete_element("RES_SCAL");
        delete_element("LLM_SCAL");
        delete_element("HLM_SCAL");
        delete_element("LO_LIMIT");
        delete_element("HI_LIMIT");
        delete_element("UNITS");
        delete_element("C_RESFMT");
        delete_element("C_LLMFMT");
        delete_element("C_HLMFMT");
        delete_element("LO_SPEC");
        delete_element("HI_SPEC");
        return;
      }
      (*this)["OPT_FLAG"].read(infile);
      (*this)["RES_SCAL"].read(infile);
      (*this)["LLM_SCAL"].read(infile);
      (*this)["HLM_SCAL"].read(infile);
      (*this)["LO_LIMIT"].read(infile);
      (*this)["HI_LIMIT"].read(infile);
      (*this)["UNITS"]   .read(infile);
      (*this)["C_RESFMT"].read(infile);
      (*this)["C_LLMFMT"].read(infile);
      (*this)["C_HLMFMT"].read(infile);
      (*this)["LO_SPEC"] .read(infile);
      (*this)["HI_SPEC"] .read(infile);
#if OLD_STDF_VERSION
      delete_element("RES_SCAL");
      delete_element("LLM_SCAL");
      delete_element("HLM_SCAL");
      delete_element("C_RESFMT");
      delete_element("C_LLMFMT");
      delete_element("C_HLMFMT");
#endif
    }

};


class MPR : public Record
{
  public:
    ~MPR() {}
    MPR() : Record(Record::MPR_TYPE)
    {
      add("TEST_NUM", boost::shared_ptr<U4>         (new U4())        );
      add("HEAD_NUM", boost::shared_ptr<U1>         (new U1())        );
      add("SITE_NUM", boost::shared_ptr<U1>         (new U1())        );
      add("TEST_FLG", boost::shared_ptr<B1>         (new B1())        );
      add("PARM_FLG", boost::shared_ptr<B1>         (new B1())        );
      add("RTN_ICNT", boost::shared_ptr<U2>         (new U2())        );
      add("RSLT_CNT", boost::shared_ptr<U2>         (new U2())        );
      add("RTN_STAT", boost::shared_ptr<JxN1>       (new JxN1())      );
      add("RTN_RSLT", boost::shared_ptr<JxTYPE<R4> >(new JxTYPE<R4>()));
      add("TEST_TXT", boost::shared_ptr<Cn>         (new Cn())        );
      add("ALARM_ID", boost::shared_ptr<Cn>         (new Cn())        );
      add("OPT_FLAG", boost::shared_ptr<B1>         (new B1())        );
      add("RES_SCAL", boost::shared_ptr<I1>         (new I1())        );
      add("LLM_SCAL", boost::shared_ptr<I1>         (new I1())        );
      add("HLM_SCAL", boost::shared_ptr<I1>         (new I1())        );
      add("LO_LIMIT", boost::shared_ptr<R4>         (new R4())        );
      add("HI_LIMIT", boost::shared_ptr<R4>         (new R4())        );
      add("START_IN", boost::shared_ptr<R4>         (new R4())        );
      add("INCR_IN",  boost::shared_ptr<R4>         (new R4())        );
      add("RTN_INDX", boost::shared_ptr<JxTYPE<U2> >(new JxTYPE<U2>()));
      add("UNITS",    boost::shared_ptr<Cn>         (new Cn())        );
      add("UNITS_IN", boost::shared_ptr<Cn>         (new Cn())        );
      add("C_RESFMT", boost::shared_ptr<Cn>         (new Cn())        );
      add("C_LLMFMT", boost::shared_ptr<Cn>         (new Cn())        );
      add("C_HLMFMT", boost::shared_ptr<Cn>         (new Cn())        );
      add("LO_SPEC",  boost::shared_ptr<R4>         (new R4())        );
      add("HI_SPEC",  boost::shared_ptr<R4>         (new R4())        );
    }
    MPR(const MPR& mpr) : Record(Record::MPR_TYPE)
    {
      add("TEST_NUM", boost::shared_ptr<U4>         (new U4(mpr.getTestnum())));
      add("HEAD_NUM", boost::shared_ptr<U1>         (new U1(mpr.getHeadnum())));
      add("SITE_NUM", boost::shared_ptr<U1>         (new U1(mpr.getSitenum())));
      add("TEST_FLG", boost::shared_ptr<B1>         (new B1(mpr.getTestflg())));
      add("PARM_FLG", boost::shared_ptr<B1>         (new B1(mpr.getParmflg())));
      add("RTN_ICNT", boost::shared_ptr<U2>         (new U2(mpr.getRtnicnt())));
      add("RSLT_CNT", boost::shared_ptr<U2>         (new U2(mpr.getRsltcnt())));
      add("RTN_STAT", boost::shared_ptr<JxN1>       (new JxN1(mpr.getRtnstat())));
      add("RTN_RSLT", boost::shared_ptr<JxTYPE<R4> >(new JxTYPE<R4>(mpr.getRtnrslt())));
      add("TEST_TXT", boost::shared_ptr<Cn>         (new Cn(mpr.getTesttxt()))        );
      add("ALARM_ID", boost::shared_ptr<Cn>         (new Cn(mpr.getAlarmid()))        );
      add("OPT_FLAG", boost::shared_ptr<B1>         (new B1(mpr.getOptflag()))        );
      add("RES_SCAL", boost::shared_ptr<I1>         (new I1(mpr.getResscal()))        );
      add("LLM_SCAL", boost::shared_ptr<I1>         (new I1(mpr.getLlmscal()))        );
      add("HLM_SCAL", boost::shared_ptr<I1>         (new I1(mpr.getHlmscal()))        );
      add("LO_LIMIT", boost::shared_ptr<R4>         (new R4(mpr.getLolimit()))        );
      add("HI_LIMIT", boost::shared_ptr<R4>         (new R4(mpr.getHilimit()))        );
      add("START_IN", boost::shared_ptr<R4>         (new R4(mpr.getStartin()))        );
      add("INCR_IN",  boost::shared_ptr<R4>         (new R4(mpr.getIncrin() ))        );
      add("RTN_INDX", boost::shared_ptr<JxTYPE<U2> >(new JxTYPE<U2>(mpr.getRtnindx())));
      add("UNITS",    boost::shared_ptr<Cn>         (new Cn(mpr.getUnits()  ))        );
      add("UNITS_IN", boost::shared_ptr<Cn>         (new Cn(mpr.getUnitsin()))        );
      add("C_RESFMT", boost::shared_ptr<Cn>         (new Cn(mpr.getCresfmt()))        );
      add("C_LLMFMT", boost::shared_ptr<Cn>         (new Cn(mpr.getCllmfmt()))        );
      add("C_HLMFMT", boost::shared_ptr<Cn>         (new Cn(mpr.getChlmfmt()))        );
      add("LO_SPEC",  boost::shared_ptr<R4>         (new R4(mpr.getLospec() ))        );
      add("HI_SPEC",  boost::shared_ptr<R4>         (new R4(mpr.getHispec() ))        );
    }
    void clear() {Record::clear();}
    void setTestnum(unsigned int testnum)                   {set("TEST_NUM", U4(testnum));}
    void setHeadnum(unsigned char headnum)                  {set("HEAD_NUM", U1(headnum));}
    void setSitenum(unsigned char sitenum)                  {set("SITE_NUM", U1(sitenum));}
    void setTestflg(const std::basic_string<char>& testflg) {set("TEST_FLG", B1(testflg));}
    void setParmflg(const std::basic_string<char>& parmflg) {set("PARM_FLG", B1(parmflg));}
    void setRtnicnt(unsigned short rtnicnt)                                    
    {                                                                          
      if(dynamic_cast<U2&>((*this)["RTN_ICNT"]).getValue() != rtnicnt)
      {
        (*this)["RTN_ICNT"] = U2(rtnicnt);
        
        boost::shared_ptr<JxN1> RTN_STAT = boost::shared_ptr<JxN1>(new JxN1(rtnicnt));
        replace_element("RTN_STAT", RTN_STAT);
        
        boost::shared_ptr<JxTYPE<U2> > RTN_INDX = boost::shared_ptr<JxTYPE<U2> >(new JxTYPE<U2>(rtnicnt));
        replace_element("RTN_INDX", RTN_INDX);
      }
    }
    void setRsltcnt(unsigned short rsltcnt)
    {
      if(dynamic_cast<U2&>((*this)["RSLT_CNT"]).getValue() != rsltcnt)
      {
        set("RSLT_CNT", U2(rsltcnt));

        boost::shared_ptr<JxTYPE<R4> > RTN_RSLT = boost::shared_ptr<JxTYPE<R4> >(new JxTYPE<R4>(rsltcnt));
        replace_element("RTN_RSLT", RTN_RSLT);
      }
    }
    void setRtnstat(unsigned short rtn,uint8_t rtnstat)
    {assert(rtn < dynamic_cast<U2&>((*this)["RTN_ICNT"]).getValue());(dynamic_cast<JxN1&>((*this)["RTN_STAT"])[rtn] = rtnstat);}
    void setRtnrslt(unsigned short rtn,float result)
    {assert(rtn < dynamic_cast<U2&>((*this)["RSLT_CNT"]).getValue());(dynamic_cast<JxTYPE<R4> &>((*this)["RTN_RSLT"])[rtn] = R4(result));}
    void setTesttxt(const std::basic_string<char>& testtxt)                                              {set("TEST_TXT", Cn(testtxt));}
    void setAlarmid(const std::basic_string<char>& alarmid)                                              {set("ALARM_ID", Cn(alarmid));}
    void setOptflag(const std::basic_string<char>& optflag)                                              {set("OPT_FLAG", B1(optflag));}
    void setResscal(char resscal)                                                                        {set("RES_SCAL", I1(resscal));}
    void setLlmscal(char llmscal)                                                                        {set("LLM_SCAL", I1(llmscal));}
    void setHlmscal(char hlmscal)                                                                        {set("HLM_SCAL", I1(hlmscal));}
    void setLolimit(float lolimit)                                                                       {set("LO_LIMIT", R4(lolimit));}
    void setHilimit(float hilimit)                                                                       {set("HI_LIMIT", R4(hilimit));}
    void setStartin(float startIn)                                                                       {set("START_IN", R4(startIn));}
    void setIncrin(float incrIn)                                                                         {set("INCR_IN" , R4(incrIn));}
    void setRtnindx(unsigned short rtn,unsigned short pmrIndx)
    {assert(rtn < dynamic_cast<U2&>((*this)["RTN_ICNT"]).getValue());      (dynamic_cast<JxTYPE<U2> &>((*this)["RTN_INDX"])[rtn] = U2(pmrIndx));}
    void setUnits(const std::basic_string<char>& units)                                                  {set("UNITS" ,   Cn(units  ));}
    void setUnitsin(const std::basic_string<char>& unitsIn)                                              {set("UNITS_IN", Cn(unitsIn));}
    void setCresfmt(const std::basic_string<char>& cresfmt)                                              {set("C_RESFMT", Cn(cresfmt));}
    void setCllmfmt(const std::basic_string<char>& cllmfmt)                                              {set("C_LLMFMT", Cn(cllmfmt));}
    void setChlmfmt(const std::basic_string<char>& chlmfmt)                                              {set("C_HLMFMT", Cn(chlmfmt));}
    void setLospec(float lospec)                                                                         {set("LO_SPEC" , R4(lospec ));}
    void setHispec(float hispec)                                                                         {set("HI_SPEC" , R4(hispec ));}

    const  U4&          getTestnum() const {return dynamic_cast<U4&         >((*this)["TEST_NUM"]);}
    const  U1&          getHeadnum() const {return dynamic_cast<U1&         >((*this)["HEAD_NUM"]);}
    const  U1&          getSitenum() const {return dynamic_cast<U1&         >((*this)["SITE_NUM"]);}
    const  B1&          getTestflg() const {return dynamic_cast<B1&         >((*this)["TEST_FLG"]);}
    const  B1&          getParmflg() const {return dynamic_cast<B1&         >((*this)["PARM_FLG"]);}
    const  U2&          getRtnicnt() const {return dynamic_cast<U2&         >((*this)["RTN_ICNT"]);}
    const  U2&          getRsltcnt() const {return dynamic_cast<U2&         >((*this)["RSLT_CNT"]);}
    const  JxN1&        getRtnstat() const {return dynamic_cast<JxN1&       >((*this)["RTN_STAT"]);}
    const  JxTYPE<R4>&  getRtnrslt() const {return dynamic_cast<JxTYPE<R4> &>((*this)["RTN_RSLT"]);}
    const  Cn&          getTesttxt() const {return dynamic_cast<Cn&         >((*this)["TEST_TXT"]);}
    const  Cn&          getAlarmid() const {return dynamic_cast<Cn&         >((*this)["ALARM_ID"]);}
    const  B1&          getOptflag() const {return dynamic_cast<B1&         >((*this)["OPT_FLAG"]);}
    const  I1&          getResscal() const {return dynamic_cast<I1&         >((*this)["RES_SCAL"]);}
    const  I1&          getLlmscal() const {return dynamic_cast<I1&         >((*this)["LLM_SCAL"]);}
    const  I1&          getHlmscal() const {return dynamic_cast<I1&         >((*this)["HLM_SCAL"]);}
    const  R4&          getLolimit() const {return dynamic_cast<R4&         >((*this)["LO_LIMIT"]);}
    const  R4&          getHilimit() const {return dynamic_cast<R4&         >((*this)["HI_LIMIT"]);}
    const  R4&          getStartin() const {return dynamic_cast<R4&         >((*this)["START_IN"]);}
    const  R4&          getIncrin()  const {return dynamic_cast<R4&         >((*this)["INCR_IN"]);} 
    const  JxTYPE<U2>&  getRtnindx() const {return dynamic_cast<JxTYPE<U2> &>((*this)["RTN_INDX"]);}
    const  Cn&          getUnits()   const {return dynamic_cast<Cn&         >((*this)["UNITS"]);}   
    const  Cn&          getUnitsin() const {return dynamic_cast<Cn&         >((*this)["UNITS_IN"]);}
    const  Cn&          getCresfmt() const {return dynamic_cast<Cn&         >((*this)["C_RESFMT"]);}
    const  Cn&          getCllmfmt() const {return dynamic_cast<Cn&         >((*this)["C_LLMFMT"]);}
    const  Cn&          getChlmfmt() const {return dynamic_cast<Cn&         >((*this)["C_HLMFMT"]);}
    const  R4&          getLospec()  const {return dynamic_cast<R4&         >((*this)["LO_SPEC"]);} 
    const  R4&          getHispec()  const {return dynamic_cast<R4&         >((*this)["HI_SPEC"]);} 

    void read(std::ifstream& infile)
    {
      U2 REC_LEN;
      REC_LEN.read(infile);
      U1 REC_TYP;
      REC_TYP.read(infile);
      U1 REC_SUB;
      REC_SUB.read(infile);
      
      (*this)["TEST_NUM"].read(infile);
      (*this)["HEAD_NUM"].read(infile);
      (*this)["SITE_NUM"].read(infile);
      (*this)["TEST_FLG"].read(infile);
      (*this)["PARM_FLG"].read(infile);
      (*this)["RTN_ICNT"].read(infile);
      (*this)["RSLT_CNT"].read(infile);
      (*this)["RTN_STAT"].read(infile, dynamic_cast<U2&>((*this)["RTN_ICNT"]).getValue());
      (*this)["RTN_RSLT"].read(infile, dynamic_cast<U2&>((*this)["RSLT_CNT"]).getValue());
      (*this)["TEST_TXT"].read(infile);
      (*this)["ALARM_ID"].read(infile);
      size_t rz = 12 + ((dynamic_cast<U2&>((*this)["RTN_ICNT"]).getValue())?(((dynamic_cast<U2&>((*this)["RTN_ICNT"]).getValue()-1) >> 1) + 1):0)//just for 9/2=5, 10/2=5 and 0/2=0;
                     + (dynamic_cast<U2&>((*this)["RSLT_CNT"]).getValue() * 4 )
                     + (*this)["TEST_TXT"].storage()+(*this)["ALARM_ID"].storage();
      if(REC_LEN.getValue() == rz )
      {
        delete_element("OPT_FLAG");
        delete_element("RES_SCAL");
        delete_element("LLM_SCAL");
        delete_element("HLM_SCAL");
        delete_element("LO_LIMIT");
        delete_element("HI_LIMIT");
        delete_element("START_IN");
        delete_element("INCR_IN" );
        delete_element("RTN_INDX");
        delete_element("UNITS"   );
        delete_element("UNITS_IN");
        delete_element("C_RESFMT");
        delete_element("C_LLMFMT");
        delete_element("C_HLMFMT");
        delete_element("LO_SPEC" );
        delete_element("HI_SPEC" );
        return;
      }
      (*this)["OPT_FLAG"].read(infile);
      (*this)["RES_SCAL"].read(infile);
      (*this)["LLM_SCAL"].read(infile);
      (*this)["HLM_SCAL"].read(infile);
      (*this)["LO_LIMIT"].read(infile);
      (*this)["HI_LIMIT"].read(infile);
      (*this)["START_IN"].read(infile);
      (*this)["INCR_IN" ].read(infile);
      (*this)["RTN_INDX"].read(infile, dynamic_cast<U2&>((*this)["RTN_ICNT"]).getValue()); 
      (*this)["UNITS"   ].read(infile);
      (*this)["UNITS_IN"].read(infile);
      (*this)["C_RESFMT"].read(infile);
      (*this)["C_LLMFMT"].read(infile);
      (*this)["C_HLMFMT"].read(infile);
      (*this)["LO_SPEC" ].read(infile);
      (*this)["HI_SPEC" ].read(infile);//TODO : display style
#if OLD_STDF_VERSION
      delete_element("RES_SCAL");
      delete_element("LLM_SCAL");
      delete_element("HLM_SCAL");
 
      delete_element("C_RESFMT");
      delete_element("C_LLMFMT");
      delete_element("C_HLMFMT");
 #endif
    }

};


class FTR : public Record
{
  public:
    ~FTR() {}
    FTR() : Record(Record::FTR_TYPE)
    {
      add("TEST_NUM", boost::shared_ptr<U4>         (new U4())               );
      add("HEAD_NUM", boost::shared_ptr<U1>         (new U1())               );
      add("SITE_NUM", boost::shared_ptr<U1>         (new U1())               );
      add("TEST_FLG", boost::shared_ptr<B1>         (new B1())               );
      add("OPT_FLAG", boost::shared_ptr<B1>         (new B1())               );
      add("CYCL_CNT", boost::shared_ptr<U4>         (new U4())               );
      add("REL_VADR", boost::shared_ptr<U4>         (new U4())               );
      add("REPT_CNT", boost::shared_ptr<U4>         (new U4())               );
      add("NUM_FAIL", boost::shared_ptr<U4>         (new U4())               );
      add("XFAIL_AD", boost::shared_ptr<I4>         (new I4())               );
      add("YFAIL_AD", boost::shared_ptr<I4>         (new I4())               );
      add("VECT_OFF", boost::shared_ptr<I2>         (new I2())               );
      add("RTN_ICNT", boost::shared_ptr<U2>         (new U2())               );
      add("PGM_ICNT", boost::shared_ptr<U2>         (new U2())               );
      add("RTN_INDX", boost::shared_ptr<JxTYPE<U2> >(new JxTYPE<U2>())       );
      add("RTN_STAT", boost::shared_ptr<JxN1>       (new JxN1())             );
      add("PGM_INDX", boost::shared_ptr<JxTYPE<U2> >(new JxTYPE<U2>())       );
      add("PGM_STAT", boost::shared_ptr<JxN1>       (new JxN1())             );
      add("FAIL_PIN", boost::shared_ptr<Dn>         (new Dn())               );
      add("VECT_NAM", boost::shared_ptr<Cn>         (new Cn())               );
      add("TIME_SET", boost::shared_ptr<Cn>         (new Cn())               );
      add("OP_CODE",  boost::shared_ptr<Cn>         (new Cn())               );
      add("TEST_TXT", boost::shared_ptr<Cn>         (new Cn())               );
      add("ALARM_ID", boost::shared_ptr<Cn>         (new Cn())               );
      add("PROG_TXT", boost::shared_ptr<Cn>         (new Cn())               );
      add("RSLT_TXT", boost::shared_ptr<Cn>         (new Cn())               );
      add("PATG_NUM", boost::shared_ptr<U1>         (new U1(255u))           );
      add("SPIN_MAP", boost::shared_ptr<Dn>         (new Dn())               );
    }
    FTR(const FTR& ftr) : Record(Record::FTR_TYPE)
    {
      add("TEST_NUM", boost::shared_ptr<U4>         (new U4        (ftr.getTestnum())));
      add("HEAD_NUM", boost::shared_ptr<U1>         (new U1        (ftr.getHeadnum())));
      add("SITE_NUM", boost::shared_ptr<U1>         (new U1        (ftr.getSitenum())));
      add("TEST_FLG", boost::shared_ptr<B1>         (new B1        (ftr.getTestflg())));
      add("OPT_FLAG", boost::shared_ptr<B1>         (new B1        (ftr.getOptflag())));
      add("CYCL_CNT", boost::shared_ptr<U4>         (new U4        (ftr.getCyclcnt())));
      add("REL_VADR", boost::shared_ptr<U4>         (new U4        (ftr.getRelvadr())));
      add("REPT_CNT", boost::shared_ptr<U4>         (new U4        (ftr.getReptcnt())));
      add("NUM_FAIL", boost::shared_ptr<U4>         (new U4        (ftr.getNumfail())));
      add("XFAIL_AD", boost::shared_ptr<I4>         (new I4        (ftr.getXfailad())));
      add("YFAIL_AD", boost::shared_ptr<I4>         (new I4        (ftr.getYfailad())));
      add("VECT_OFF", boost::shared_ptr<I2>         (new I2        (ftr.getVectoff())));
      add("RTN_ICNT", boost::shared_ptr<U2>         (new U2        (ftr.getRtnicnt())));
      add("PGM_ICNT", boost::shared_ptr<U2>         (new U2        (ftr.getPgmicnt())));
      add("RTN_INDX", boost::shared_ptr<JxTYPE<U2> >(new JxTYPE<U2>(ftr.getRtnindx())));
      add("RTN_STAT", boost::shared_ptr<JxN1>       (new JxN1      (ftr.getRtnstat())));
      add("PGM_INDX", boost::shared_ptr<JxTYPE<U2> >(new JxTYPE<U2>(ftr.getPgmindx())));
      add("PGM_STAT", boost::shared_ptr<JxN1>       (new JxN1      (ftr.getPgmstat())));
      add("FAIL_PIN", boost::shared_ptr<Dn>         (new Dn        (ftr.getFailpin())));
      add("VECT_NAM", boost::shared_ptr<Cn>         (new Cn        (ftr.getVectnam())));
      add("TIME_SET", boost::shared_ptr<Cn>         (new Cn        (ftr.getTimeset())));
      add("OP_CODE",  boost::shared_ptr<Cn>         (new Cn        (ftr.getOpcode() )));
      add("TEST_TXT", boost::shared_ptr<Cn>         (new Cn        (ftr.getTesttxt())));
      add("ALARM_ID", boost::shared_ptr<Cn>         (new Cn        (ftr.getAlarmid())));
      add("PROG_TXT", boost::shared_ptr<Cn>         (new Cn        (ftr.getProgtxt())));
      add("RSLT_TXT", boost::shared_ptr<Cn>         (new Cn        (ftr.getRslttxt())));
      add("PATG_NUM", boost::shared_ptr<U1>         (new U1        (ftr.getPatgnum())));
      add("SPIN_MAP", boost::shared_ptr<Dn>         (new Dn        (ftr.getSpinmap())));
    }
    void clear() {Record::clear(); setPatgnum();}
    void setTestnum(unsigned int testnum)                   {set("TEST_NUM", U4(testnum));} 
    void setHeadnum(unsigned char headnum)                  {set("HEAD_NUM", U1(headnum));}
    void setSitenum(unsigned char sitenum)                  {set("SITE_NUM", U1(sitenum));}
    void setTestflg(const std::basic_string<char>& testflg) {set("TEST_FLG", B1(testflg));}
    void setOptflag(const std::basic_string<char>& optflag) {set("OPT_FLAG", B1(optflag));}
    void setCyclcnt(unsigned int cyclcnt)                   {set("CYCL_CNT", U4(cyclcnt));}
    void setRelvadr(unsigned int relvadr)                   {set("REL_VADR", U4(relvadr));}
    void setReptcnt(unsigned int reptcnt)                   {set("REPT_CNT", U4(reptcnt));}
    void setNumfail(unsigned int numfail)                   {set("NUM_FAIL", U4(numfail));}
    void setXfailad(int xfailad)                            {set("XFAIL_AD", I4(xfailad));}
    void setYfailad(int yfailad)                            {set("YFAIL_AD", I4(yfailad));}
    void setVectoff(short vectoff)                          {set("VECT_OFF", I2(vectoff));}
    void setRtnicnt(unsigned short rtnicnt)
    {
      if(dynamic_cast<U2&>((*this)["RTN_ICNT"]).getValue() != rtnicnt)
      {
          set("RTN_ICNT", U2(rtnicnt));
          replace_element("RTN_INDX", boost::shared_ptr<JxTYPE<U2> >(new JxTYPE<U2>(rtnicnt)));

          replace_element("RTN_STAT", boost::shared_ptr<JxN1>(new JxN1(rtnicnt)));
      }
    }
    void setPgmicnt(unsigned short pgmicnt)
    {
      if(dynamic_cast<U2&>((*this)["PGM_ICNT"]).getValue() != pgmicnt)
      {
          set("PGM_ICNT", U2(pgmicnt));
          replace_element("PGM_INDX", boost::shared_ptr<JxTYPE<U2> >(new JxTYPE<U2>(pgmicnt)));

          replace_element("PGM_STAT", boost::shared_ptr<JxN1>(new JxN1(pgmicnt)));
      }
    }
    void setRtnindx(unsigned short rtn,unsigned short rtnindx)
    {assert(rtn<dynamic_cast<U2&>((*this)["RTN_ICNT"]).getValue());dynamic_cast<JxTYPE<U2> &>((*this)["RTN_INDX"])[rtn] = U2(rtnindx);}
    void setRtnstat(unsigned short rtn,uint8_t rtnstat)
    {assert(rtn<dynamic_cast<U2&>((*this)["RTN_ICNT"]).getValue());dynamic_cast<JxN1&>((*this)["RTN_STAT"])[rtn] = rtnstat;}
    void setPgmindx(unsigned short pgm,unsigned short pgmindx)
    {assert(pgm<dynamic_cast<U2&>((*this)["PGM_ICNT"]).getValue());dynamic_cast<JxTYPE<U2> &>((*this)["PGM_INDX"])[pgm] = U2(pgmindx);}
    void setPgmstat(unsigned short pgm,uint8_t pgmstat)
    {assert(pgm<dynamic_cast<U2&>((*this)["PGM_ICNT"]).getValue());dynamic_cast<JxN1&>((*this)["PGM_STAT"])[pgm] = pgmstat;}
    void setFailpin(const std::basic_string<char>& failpin) {set("FAIL_PIN", Dn(failpin));}
    void setVectnam(const std::basic_string<char>& vectnam) {set("VECT_NAM", Cn(vectnam));}
    void setTimeset(const std::basic_string<char>& timeset) {set("TIME_SET", Cn(timeset));}
    void setOpcode(const std::basic_string<char>& opcode)   {set("OP_CODE",  Cn(opcode ));}
    void setTesttxt(const std::basic_string<char>& testtxt) {set("TEST_TXT", Cn(testtxt));}
    void setAlarmid(const std::basic_string<char>& alarmid) {set("ALARM_ID", Cn(alarmid));}
    void setProgtxt(const std::basic_string<char>& progtxt) {set("PROG_TXT", Cn(progtxt));}
    void setRslttxt(const std::basic_string<char>& rslttxt) {set("RSLT_TXT", Cn(rslttxt));}
    void setPatgnum(uint16_t patgnum=255u)                  {set("PATG_NUM", U1(patgnum));}
    void setSpinmap(const std::basic_string<char>& spinmap) {set("SPIN_MAP", Dn(spinmap));}

    const U4&              getTestnum()const {return dynamic_cast<U4&         >((*this)["TEST_NUM"]);} 
    const U1&              getHeadnum()const {return dynamic_cast<U1&         >((*this)["HEAD_NUM"]);}
    const U1&              getSitenum()const {return dynamic_cast<U1&         >((*this)["SITE_NUM"]);}
    const B1&              getTestflg()const {return dynamic_cast<B1&         >((*this)["TEST_FLG"]);}
    const B1&              getOptflag()const {return dynamic_cast<B1&         >((*this)["OPT_FLAG"]);}
    const U4&              getCyclcnt()const {return dynamic_cast<U4&         >((*this)["CYCL_CNT"]);}
    const U4&              getRelvadr()const {return dynamic_cast<U4&         >((*this)["REL_VADR"]);}
    const U4&              getReptcnt()const {return dynamic_cast<U4&         >((*this)["REPT_CNT"]);}
    const U4&              getNumfail()const {return dynamic_cast<U4&         >((*this)["NUM_FAIL"]);}
    const I4&              getXfailad()const {return dynamic_cast<I4&         >((*this)["XFAIL_AD"]);}
    const I4&              getYfailad()const {return dynamic_cast<I4&         >((*this)["YFAIL_AD"]);}
    const I2&              getVectoff()const {return dynamic_cast<I2&         >((*this)["VECT_OFF"]);}
    const U2&              getRtnicnt()const {return dynamic_cast<U2&         >((*this)["RTN_ICNT"]);}
    const U2&              getPgmicnt()const {return dynamic_cast<U2&         >((*this)["PGM_ICNT"]);}
    const JxTYPE<U2> &     getRtnindx()const {return dynamic_cast<JxTYPE<U2> &>((*this)["RTN_INDX"]);}
    const JxN1&            getRtnstat()const {return dynamic_cast<JxN1&>((*this)["RTN_STAT"]);}
    const JxTYPE<U2> &     getPgmindx()const {return dynamic_cast<JxTYPE<U2> &>((*this)["PGM_INDX"]);}
    const JxN1&            getPgmstat()const {return dynamic_cast<JxN1&       >((*this)["PGM_STAT"]);}
    const Dn&              getFailpin()const {return dynamic_cast<Dn&         >((*this)["FAIL_PIN"]);}
    const Cn&              getVectnam()const {return dynamic_cast<Cn&         >((*this)["VECT_NAM"]);}
    const Cn&              getTimeset()const {return dynamic_cast<Cn&         >((*this)["TIME_SET"]);}
    const Cn&              getOpcode() const {return dynamic_cast<Cn&         >((*this)["OP_CODE"]) ;}
    const Cn&              getTesttxt()const {return dynamic_cast<Cn&         >((*this)["TEST_TXT"]);}
    const Cn&              getAlarmid()const {return dynamic_cast<Cn&         >((*this)["ALARM_ID"]);}
    const Cn&              getProgtxt()const {return dynamic_cast<Cn&         >((*this)["PROG_TXT"]);}
    const Cn&              getRslttxt()const {return dynamic_cast<Cn&         >((*this)["RSLT_TXT"]);}
    const U1&              getPatgnum()const {return dynamic_cast<U1&         >((*this)["PATG_NUM"]);}
    const Dn&              getSpinmap()const {return dynamic_cast<Dn&         >((*this)["SPIN_MAP"]);}

    void read(std::ifstream& infile)
    {
      U2 REC_LEN;
      REC_LEN.read(infile);
      U1 REC_TYP;
      REC_TYP.read(infile);
      U1 REC_SUB;
      REC_SUB.read(infile);

      size_t rz = REC_LEN.getValue();
      (*this)["TEST_NUM"].read(infile);
      (*this)["HEAD_NUM"].read(infile);
      (*this)["SITE_NUM"].read(infile);
      (*this)["TEST_FLG"].read(infile);
      (*this)["OPT_FLAG"].read(infile);
      (*this)["CYCL_CNT"].read(infile);
      (*this)["REL_VADR"].read(infile);
      (*this)["REPT_CNT"].read(infile);
      (*this)["NUM_FAIL"].read(infile);
      (*this)["XFAIL_AD"].read(infile);
      (*this)["YFAIL_AD"].read(infile);
      (*this)["VECT_OFF"].read(infile);
      (*this)["RTN_ICNT"].read(infile);
      (*this)["PGM_ICNT"].read(infile);
      (*this)["RTN_INDX"].read(infile,dynamic_cast<U2&>((*this)["RTN_ICNT"]).getValue());
      (*this)["RTN_STAT"].read(infile,dynamic_cast<U2&>((*this)["RTN_ICNT"]).getValue());
      (*this)["PGM_INDX"].read(infile,dynamic_cast<U2&>((*this)["PGM_ICNT"]).getValue());
      (*this)["PGM_STAT"].read(infile,dynamic_cast<U2&>((*this)["PGM_ICNT"]).getValue());
      (*this)["FAIL_PIN"].read(infile);
      (*this)["VECT_NAM"].read(infile);
      (*this)["TIME_SET"].read(infile);
      (*this)["OP_CODE"].read(infile);
      (*this)["TEST_TXT"].read(infile);
      (*this)["ALARM_ID"].read(infile);
      (*this)["PROG_TXT"].read(infile);
      (*this)["RSLT_TXT"].read(infile);

      size_t aa = (dynamic_cast<U2&>((*this)["RTN_ICNT"]).getValue() && dynamic_cast<U2&>((*this)["PGM_ICNT"]).getValue())
                  ?(5*(dynamic_cast<U2&>((*this)["RTN_ICNT"]).getValue() + dynamic_cast<U2&>((*this)["PGM_ICNT"]).getValue())/2) + 1
                  :0;

      size_t az = (38 + aa + (*this)["FAIL_PIN"].storage() + (*this)["VECT_NAM"].storage()+(*this)["TIME_SET"].storage()
                  + (*this)["OP_CODE"].storage()+(*this)["TEST_TXT"].storage()+(*this)["ALARM_ID"].storage()
                  + (*this)["PROG_TXT"].storage()+(*this)["RSLT_TXT"].storage());

      if(rz == az)
      {
#if OLD_STDF_VERSION
        boost::shared_ptr<U1> PATG_NUM = boost::shared_ptr<U1>(new U1(0u));
        replace_element("PATG_NUM", PATG_NUM);
#else
        delete_element("PATG_NUM");
        delete_element("SPIN_MAP");
#endif
        return;
      }
      (*this)["PATG_NUM"].read(infile);
      (*this)["SPIN_MAP"].read(infile);
    }     

};


class STR : public Record
{
  public:
    ~STR() {}
    STR() : Record(Record::STR_TYPE)
    {
      add("CONT_FLG",boost::shared_ptr<B1>              (new B1())                );
      add("TEST_NUM",boost::shared_ptr<U4>              (new U4())                );
      add("HEAD_NUM",boost::shared_ptr<U1>              (new U1())                );
      add("SITE_NUM",boost::shared_ptr<U1>              (new U1())                );
      add("PSR_REF", boost::shared_ptr<U2>              (new U2())                );
      add("TEST_FLG",boost::shared_ptr<B1>              (new B1())                );
      add("LOG_TYP", boost::shared_ptr<Cn>              (new Cn())                );
      add("TEST_TXT",boost::shared_ptr<Cn>              (new Cn())                );
      add("ALARM_ID",boost::shared_ptr<Cn>              (new Cn())                );
      add("PROG_TXT",boost::shared_ptr<Cn>              (new Cn())                );
      add("RSLT_TXT",boost::shared_ptr<Cn>              (new Cn())                );
      add("Z_VAL",   boost::shared_ptr<U1>              (new U1())                );
      add("FMU_FLG", boost::shared_ptr<B1>              (new B1("00000101"))      );
      add("MASK_MAP",boost::shared_ptr<Dn>              (new Dn())                );
      add("FAL_MAP", boost::shared_ptr<Dn>              (new Dn())                );
      add("CYC_CNT", boost::shared_ptr<U8>              (new U8())                );
      add("TOTF_CNT",boost::shared_ptr<U4>              (new U4())                );
      add("TOTL_CNT",boost::shared_ptr<U4>              (new U4())                );
      add("CYC_BASE",boost::shared_ptr<U8>              (new U8())                );
      add("BIT_BASE",boost::shared_ptr<U4>              (new U4())                );
      add("COND_CNT",boost::shared_ptr<U2>              (new U2())                );
      add("LIM_CNT", boost::shared_ptr<U2>              (new U2())                );
      add("CYC_SIZE",boost::shared_ptr<U1>              (new U1())                );
      add("PMR_SIZE",boost::shared_ptr<U1>              (new U1())                );
      add("CHN_SIZE",boost::shared_ptr<U1>              (new U1())                );
      add("PAT_SIZE",boost::shared_ptr<U1>              (new U1())                );
      add("BIT_SIZE",boost::shared_ptr<U1>              (new U1())                );
      add("U1_SIZE", boost::shared_ptr<U1>              (new U1())                );
      add("U2_SIZE", boost::shared_ptr<U1>              (new U1())                );
      add("U3_SIZE", boost::shared_ptr<U1>              (new U1())                );
      add("UTX_SIZE",boost::shared_ptr<U1>              (new U1())                );
      add("CAP_BGN", boost::shared_ptr<U2>              (new U2())                );
      add("LIM_INDX",boost::shared_ptr<JxTYPE<U2> >     (new JxTYPE<U2>())        );
      add("LIM_SPEC",boost::shared_ptr<JxTYPE<U4> >     (new JxTYPE<U4>())        );
      add("COND_LST",boost::shared_ptr<JxTYPE<Cn> >     (new JxTYPE<Cn>())        );
      add("CYCO_CNT",boost::shared_ptr<U2>              (new U2())                );
      add("CYC_OFST",boost::shared_ptr<JxTYPE<Uf<8> > > (new JxTYPE<Uf<8> >())    );
      add("PMR_CNT", boost::shared_ptr<U2>              (new U2())                );
      add("PMR_INDX",boost::shared_ptr<JxTYPE<Uf<2> > > (new JxTYPE<Uf<2> >())    );
      add("CHN_CNT", boost::shared_ptr<U2>              (new U2())                );
      add("CHN_NUM", boost::shared_ptr<JxTYPE<Uf<8> > > (new JxTYPE<Uf<8> >())    );
      add("EXP_CNT", boost::shared_ptr<U2>              (new U2())                );
      add("EXP_DATA",boost::shared_ptr<JxTYPE<U1> >     (new JxTYPE<U1>())        );
      add("CAP_CNT", boost::shared_ptr<U2>              (new U2())                );
      add("CAP_DATA",boost::shared_ptr<JxTYPE<U1> >     (new JxTYPE<U1>())        );
      add("NEW_CNT", boost::shared_ptr<U2>              (new U2())                );
      add("NEW_DATA",boost::shared_ptr<JxTYPE<U1> >     (new JxTYPE<U1>())        );
      add("PAT_CNT", boost::shared_ptr<U2>              (new U2())                );
      add("PAT_NUM", boost::shared_ptr<JxTYPE<Uf<8> > > (new JxTYPE<Uf<8> >())    );
      add("BPOS_CNT",boost::shared_ptr<U2>              (new U2())                );
      add("BIT_POS", boost::shared_ptr<JxTYPE<Uf<8> > > (new JxTYPE<Uf<8> >())    );
      add("USR1_CNT",boost::shared_ptr<U2>              (new U2())                );
      add("USR1",    boost::shared_ptr<JxTYPE<Uf<8> > > (new JxTYPE<Uf<8> >())    );
      add("USR2_CNT",boost::shared_ptr<U2>              (new U2())                );
      add("USR2",    boost::shared_ptr<JxTYPE<Uf<8> > > (new JxTYPE<Uf<8> >())    );
      add("USR3_CNT",boost::shared_ptr<U2>              (new U2())                );
      add("USR3",    boost::shared_ptr<JxTYPE<Uf<8> > > (new JxTYPE<Uf<8> >())    );
      add("TXT_CNT", boost::shared_ptr<U2>              (new U2())                );
      add("USER_TXT",boost::shared_ptr<MxCf>(new MxCf()) );
    }

  private:
      STR(const STR& str):Record(Record::STR_TYPE) {};
      void operator = (const STR& str) {};
 
  public:
    void clear() {Record::clear();setFmuflg();}
    void setContflg(const std::basic_string<char>& contflg) {set("CONT_FLG", B1(contflg));}
    void setTestnum(unsigned int testnum)                   {set("TEST_NUM", U4(testnum ));}
    void setHeadnum(unsigned char headnum)                  {set("HEAD_NUM", U1(headnum ));}
    void setSitenum(unsigned char sitenum)                  {set("SITE_NUM", U1(sitenum ));}
    void setPsrref(unsigned short psrref)                   {set("PSR_REF" , U2(psrref  ));}
    void setTestflg(const std::basic_string<char>& testflg) {set("TEST_FLG", B1(testflg ));}
    void setLogtyp(const std::basic_string<char>& logtyp)   {set("LOG_TYP" , Cn(logtyp  ));}
    void setTesttxt(const std::basic_string<char>& testtxt) {set("TEST_TXT", Cn(testtxt ));}
    void setAlarmid(const std::basic_string<char>& alarmid) {set("ALARM_ID", Cn(alarmid ));}
    void setProgtxt(const std::basic_string<char>& progtxt) {set("PROG_TXT", Cn(progtxt ));}
    void setRslttxt(const std::basic_string<char>& rslttxt) {set("RSLT_TXT", Cn(rslttxt ));}
    void setZval(unsigned char zval)                        {set("Z_VAL"   , U1(zval    ));}
    void setFmuflg(const std::basic_string<char>& fmuflg="00000101")   {set("FMU_FLG" , B1(fmuflg  ));}
    void setMaskmap(const std::basic_string<char>& maskmap) {set("MASK_MAP", Dn(maskmap ));}
    void setFalmap(const std::basic_string<char>& falmap)   {set("FAL_MAP" , Dn(falmap  ));}
    void setCyccnt(unsigned long long cyccnt)               {set("CYC_CNT" , U8(cyccnt  ));}
    void settotfcnt(unsigned int totfcnd)                   {set("TOTF_CNT", U4(totfcnd ));}
    void settotlcnt(unsigned int totlcnd)                   {set("TOTL_CNT", U4(totlcnd ));}
    void setCycbase(unsigned long long cycbase)             {set("CYC_BASE", U8(cycbase ));}
    void setBitbase(unsigned int bitbase)                   {set("BIT_BASE", U4(bitbase ));}
    void setCondcnt(unsigned short condcnt)
    {
      if(dynamic_cast<U2&>((*this)["COND_CNT"]).getValue() != condcnt)
      {
        set("COND_CNT", U2(condcnt));
        boost::shared_ptr<JxTYPE<Cn> > COND_LST = boost::shared_ptr<JxTYPE<Cn> >(new JxTYPE<Cn>(condcnt));
        replace_element("COND_LST", COND_LST);
      }
    }
    void setLimcnt(unsigned short limcnt)
    {
      if(dynamic_cast<U2&>((*this)["LIM_CNT"]).getValue() != limcnt)
      {
        set("LIM_CNT", U2(limcnt));
        boost::shared_ptr<JxTYPE<U2> > LIM_INDX = boost::shared_ptr<JxTYPE<U2> >(new JxTYPE<U2>(limcnt));
        replace_element("LIM_INDX", LIM_INDX);
        	
        boost::shared_ptr<JxTYPE<U4> > LIM_SPEC = boost::shared_ptr<JxTYPE<U4> >(new JxTYPE<U4>(limcnt));
        replace_element("LIM_SPEC", LIM_SPEC);
      }
    }
    void setCycsize(unsigned char cycsize) {assert(1 == cycsize || 2 == cycsize || 4 == cycsize || 8 == cycsize); set("CYC_SIZE", U1(cycsize));}
    void setPmrsize(unsigned char pmrsize) {assert(1 == pmrsize || 2 == pmrsize                                ); set("PMR_SIZE", U1(pmrsize));}
    //note: Old versions CHN_SIZE value default is 8, but does't match standard.
    void setChnsize(unsigned char chnsize) {assert(1 == chnsize || 2 == chnsize || 4 == chnsize                ); set("CHN_SIZE", U1(chnsize));}
    void setPatsize(unsigned char patsize) {assert(1 == patsize || 2 == patsize || 4 == patsize                ); set("PAT_SIZE", U1(patsize));}
    void setBitsize(unsigned char bitsize) {assert(1 == bitsize || 2 == bitsize || 4 == bitsize                ); set("BIT_SIZE", U1(bitsize));}
    void setU1size(unsigned char   u1size) {assert(1 ==  u1size || 2 ==  u1size || 4 ==  u1size || 8 ==  u1size); set("U1_SIZE",  U1(u1size) );}
    void setU2size(unsigned char   u2size) {assert(1 ==  u2size || 2 ==  u2size || 4 ==  u2size || 8 ==  u2size); set("U2_SIZE",  U1(u2size) );}
    void setU3size(unsigned char   u3size) {assert(1 ==  u3size || 2 ==  u3size || 4 ==  u3size || 8 ==  u3size); set("U3_SIZE",  U1(u3size) );}
    void setUtxsize(unsigned char utxsize) {set("UTX_SIZE", U1(utxsize));}
    void setCapbgn(unsigned short capgbn)  {set("CAP_BGN" , U2(capgbn ));}
    void setLimindx(unsigned short i,unsigned short limindx)
    {assert(i < dynamic_cast<U2&>((*this)["LIM_CNT"]).getValue() ); dynamic_cast<JxTYPE<U2> &>((*this)["LIM_INDX"])[i] = U2(limindx);}
    void setLimspec(unsigned short i,unsigned short limspec)
    {assert(i <  dynamic_cast<U2&>((*this)["LIM_CNT"]).getValue() ); dynamic_cast<JxTYPE<U4> &>((*this)["LIM_SPEC"])[i] = U4(limspec);}
    void setCondlst(unsigned short i,const std::basic_string<char>& condlst)
    {assert(i < dynamic_cast<U2&>((*this)["COND_CNT"]).getValue()); (dynamic_cast<JxTYPE<Cn> &>((*this)["COND_LST"]))[i] = condlst;}
    void setCycocnt(unsigned short cycocnt)
    {
      if(dynamic_cast<U2&>((*this)["CYCO_CNT"]).getValue() != cycocnt)
      {
        set("CYCO_CNT",U2(cycocnt));

        switch(dynamic_cast<U1&>((*this)["CYC_SIZE"]).getValue())
        {
            case 1:
                {
                    boost::shared_ptr<JxTYPE<Uf<1> > > CYC_OFST = boost::shared_ptr<JxTYPE<Uf<1> > >(new JxTYPE<Uf<1> >(cycocnt));
                    replace_element("CYC_OFST", CYC_OFST);
                }
                break;
            case 2:
                {
                    boost::shared_ptr<JxTYPE<Uf<2> > > CYC_OFST = boost::shared_ptr<JxTYPE<Uf<2> > >(new JxTYPE<Uf<2> >(cycocnt));
                    replace_element("CYC_OFST", CYC_OFST);
                }
                break;
            case 4:
                {
                    boost::shared_ptr<JxTYPE<Uf<4> > > CYC_OFST = boost::shared_ptr<JxTYPE<Uf<4> > >(new JxTYPE<Uf<4> >(cycocnt));
                    replace_element("CYC_OFST", CYC_OFST);
                }
                break;
            case 8:
                {
                    boost::shared_ptr<JxTYPE<Uf<8> > > CYC_OFST = boost::shared_ptr<JxTYPE<Uf<8> > >(new JxTYPE<Uf<8> >(cycocnt));
                    replace_element("CYC_OFST", CYC_OFST);
                }
                break;
        }

      }
    }
    void setCycofst(unsigned short i,unsigned long long cycofst)
    {
      assert(i < dynamic_cast<U2&>((*this)["CYCO_CNT"]).getValue());
      
      switch(dynamic_cast<U1&>((*this)["CYC_SIZE"]).getValue())
      {
          case 1:
              dynamic_cast<JxTYPE<Uf<1> > &>((*this)["CYC_OFST"])[i] = Uf<1>(cycofst); break;
          case 2:
              dynamic_cast<JxTYPE<Uf<2> > &>((*this)["CYC_OFST"])[i] = Uf<2>(cycofst); break;
          case 4:
              dynamic_cast<JxTYPE<Uf<4> > &>((*this)["CYC_OFST"])[i] = Uf<4>(cycofst); break;
          case 8:
              dynamic_cast<JxTYPE<Uf<8> > &>((*this)["CYC_OFST"])[i] = Uf<8>(cycofst); break;
      }

    }
    void setPmrcnt(unsigned short pmrcnt)
    {
      if(dynamic_cast<U2&>((*this)["PMR_CNT"]).getValue() != pmrcnt)
      {
        set("PMR_CNT", U2(pmrcnt));

        switch(dynamic_cast<U1&>((*this)["PMR_SIZE"]).getValue())
        {
            case 1:
                {
                    boost::shared_ptr<JxTYPE<Uf<1> > > PMR_INDX = boost::shared_ptr<JxTYPE<Uf<1> > >(new JxTYPE<Uf<1> >(pmrcnt));
                    replace_element("PMR_INDX", PMR_INDX);
                }
                break;
            case 2:
                {
                    boost::shared_ptr<JxTYPE<Uf<2> > > PMR_INDX = boost::shared_ptr<JxTYPE<Uf<2> > >(new JxTYPE<Uf<2> >(pmrcnt));
                    replace_element("PMR_INDX", PMR_INDX);
                } 
                break;
        }

      }
    }
    void setPmrindx(unsigned short i,unsigned long long pmrindx)
    {
      assert(i < dynamic_cast<U2&>((*this)["PMR_CNT"]).getValue());
    
      switch(dynamic_cast<U1&>((*this)["PMR_SIZE"]).getValue())
      {
          case 1:
              dynamic_cast<JxTYPE<Uf<1> > &>((*this)["PMR_INDX"])[i] = Uf<1>(pmrindx); break;
          case 2:
              dynamic_cast<JxTYPE<Uf<2> > &>((*this)["PMR_INDX"])[i] = Uf<2>(pmrindx); break;
      }

    }
    void setChncnt(unsigned short chncnt)
    {
        if(dynamic_cast<U2&>((*this)["CHN_CNT"]).getValue() != chncnt)
        {
            set("CHN_CNT", U2(chncnt));

            switch(dynamic_cast<U1&>((*this)["CHN_SIZE"]).getValue())
            {
                case 1:
                    {
                        boost::shared_ptr<JxTYPE<Uf<1> > > CHN_NUM = boost::shared_ptr<JxTYPE<Uf<1> > >(new JxTYPE<Uf<1> >(chncnt));
                        replace_element("CHN_NUM", CHN_NUM);
                    }
                    break;
                case 2:
                    {
                        boost::shared_ptr<JxTYPE<Uf<2> > > CHN_NUM = boost::shared_ptr<JxTYPE<Uf<2> > >(new JxTYPE<Uf<2> >(chncnt));
                        replace_element("CHN_NUM", CHN_NUM);
                    }
                    break;
                case 4:
                    {
                        boost::shared_ptr<JxTYPE<Uf<4> > > CHN_NUM = boost::shared_ptr<JxTYPE<Uf<4> > >(new JxTYPE<Uf<4> >(chncnt));
                        replace_element("CHN_NUM", CHN_NUM);
                    }
                    break;
            }

        }
    }
    void setChnnum(unsigned short i,unsigned long long chnmum)
    {
      assert(i < dynamic_cast<U2&>((*this)["CHN_CNT"]).getValue());

      switch(dynamic_cast<U1&>((*this)["CHN_SIZE"]).getValue())
      {
          case 1:
              dynamic_cast<JxTYPE<Uf<1> > &>((*this)["CHN_NUM"])[i] = Uf<1>(chnmum); break;
          case 2:
              dynamic_cast<JxTYPE<Uf<2> > &>((*this)["CHN_NUM"])[i] = Uf<2>(chnmum); break;
          case 4:
              dynamic_cast<JxTYPE<Uf<4> > &>((*this)["CHN_NUM"])[i] = Uf<4>(chnmum); break;
      }

    }
    void setExpcnt(unsigned short expcnt)
    {
        if(dynamic_cast<U2&>((*this)["EXP_CNT"]).getValue() != expcnt)
        {
            set("EXP_CNT", U2(expcnt));

            boost::shared_ptr<JxTYPE<U1> > EXP_DATA = boost::shared_ptr<JxTYPE<U1> >(new JxTYPE<U1>(expcnt));
            replace_element("EXP_DATA", EXP_DATA);
        }
    }
    void setExpdata(unsigned short i,unsigned char expdata)
    {assert(i < dynamic_cast<U2&>((*this)["EXP_CNT"]).getValue());dynamic_cast<JxTYPE<U1> &>((*this)["EXP_DATA"])[i] = U1(expdata);}
    void setCapcnt(unsigned short capcnt)
    {
        if(dynamic_cast<U2&>((*this)["CAP_CNT"]).getValue() != capcnt)
        {
            set("CAP_CNT", U2(capcnt));

            boost::shared_ptr<JxTYPE<U1> > CAP_DATA = boost::shared_ptr<JxTYPE<U1> >(new JxTYPE<U1>(capcnt));
            replace_element("CAP_DATA", CAP_DATA);
        }
    }
    void setCapdata(unsigned short i,unsigned char capdata)
    {assert(i < dynamic_cast<U2&>((*this)["CAP_CNT"]).getValue()); dynamic_cast<JxTYPE<U1> &>((*this)["CAP_DATA"])[i] = U1(capdata);}
    void setNewcnt(unsigned short newcnt)
    {
        if(dynamic_cast<U2&>((*this)["NEW_CNT"]).getValue() != newcnt)
        {
            set("NEW_CNT", U2(newcnt));

            boost::shared_ptr<JxTYPE<U1> > NEW_DATA = boost::shared_ptr<JxTYPE<U1> >(new JxTYPE<U1>(newcnt));
            replace_element("NEW_DATA", NEW_DATA);
        }
    }
    void setNewdata(unsigned short i,unsigned char newdata)
    {assert(i < dynamic_cast<U2&>((*this)["NEW_CNT"]).getValue()); dynamic_cast<JxTYPE<U1> &>((*this)["NEW_DATA"])[i] = U1(newdata);}
    void setPatcnt(unsigned short patcnt)
    {
        if(dynamic_cast<U2&>((*this)["PAT_CNT"]).getValue() != patcnt)
        {
            set("PAT_CNT", U2(patcnt));

            switch(dynamic_cast<U1&>((*this)["PAT_SIZE"]).getValue())
            {
                case 1:
                    {
                        boost::shared_ptr<JxTYPE<Uf<1> > > PAT_NUM = boost::shared_ptr<JxTYPE<Uf<1> > >(new JxTYPE<Uf<1> >(patcnt));
                        replace_element("PAT_NUM", PAT_NUM);
                    }
                    break;
                case 2:
                    {
                        boost::shared_ptr<JxTYPE<Uf<2> > > PAT_NUM = boost::shared_ptr<JxTYPE<Uf<2> > >(new JxTYPE<Uf<2> >(patcnt));
                        replace_element("PAT_NUM", PAT_NUM);
                    }
                    break;
                case 4:
                    {
                        boost::shared_ptr<JxTYPE<Uf<4> > > PAT_NUM = boost::shared_ptr<JxTYPE<Uf<4> > >(new JxTYPE<Uf<4> >(patcnt));
                        replace_element("PAT_NUM", PAT_NUM);
                    }
                    break;
            }

        }
    }
    void setPatnum(unsigned short i,unsigned long long patdnum)
    {
      assert(i < dynamic_cast<U2&>((*this)["PAT_CNT"]).getValue());

      switch(dynamic_cast<U1&>((*this)["PAT_SIZE"]).getValue())
      {
          case 1:
              dynamic_cast<JxTYPE<Uf<1> > &>((*this)["PAT_NUM"])[i] = Uf<1>(patdnum); break;
          case 2:
              dynamic_cast<JxTYPE<Uf<2> > &>((*this)["PAT_NUM"])[i] = Uf<2>(patdnum); break;
          case 4:
              dynamic_cast<JxTYPE<Uf<4> > &>((*this)["PAT_NUM"])[i] = Uf<4>(patdnum); break;
      }

    }
    void setBposcnt(unsigned short bposcnt)
    {
    	if(dynamic_cast<U2&>((*this)["BPOS_CNT"]).getValue() != bposcnt)
        {
            set("BPOS_CNT", U2(bposcnt));

            switch(dynamic_cast<U1&>((*this)["BIT_SIZE"]).getValue())
            {
                case 1:
                    {
                        boost::shared_ptr<JxTYPE<Uf<1> > > BIT_POS = boost::shared_ptr<JxTYPE<Uf<1> > >(new JxTYPE<Uf<1> >(bposcnt));
                        replace_element("BIT_POS", BIT_POS);
                    }
                    break;
                case 2:
                    {
                        boost::shared_ptr<JxTYPE<Uf<2> > > BIT_POS = boost::shared_ptr<JxTYPE<Uf<2> > >(new JxTYPE<Uf<2> >(bposcnt));
                        replace_element("BIT_POS", BIT_POS);
                    }

                    break;
                case 4:
                    {
                        boost::shared_ptr<JxTYPE<Uf<4> > > BIT_POS = boost::shared_ptr<JxTYPE<Uf<4> > >(new JxTYPE<Uf<4> >(bposcnt));
                        replace_element("BIT_POS", BIT_POS);
                    }
                    break;
            }

        }
    }
    void setBitpos(unsigned short i,unsigned long long bitpos)
    {
       assert(i < dynamic_cast<U2&>((*this)["BPOS_CNT"]).getValue()); 

       switch(dynamic_cast<U1&>((*this)["BIT_SIZE"]).getValue())
       {
           case 1:
               dynamic_cast<JxTYPE<Uf<1> > &>((*this)["BIT_POS"])[i] = Uf<1>(bitpos); break;
           case 2:
               dynamic_cast<JxTYPE<Uf<2> > &>((*this)["BIT_POS"])[i] = Uf<2>(bitpos); break;
           case 4:
               dynamic_cast<JxTYPE<Uf<4> > &>((*this)["BIT_POS"])[i] = Uf<4>(bitpos); break;
       }

    }
    void setUsr1cnt(unsigned short cnt)
    {
        if(dynamic_cast<U2&>((*this)["USR1_CNT"]).getValue() != cnt)
        {
            set("USR1_CNT", U2(cnt));

            switch(dynamic_cast<U1&>((*this)["U1_SIZE"]).getValue())
            {
                case 1:
                    {
                        boost::shared_ptr<JxTYPE<Uf<1> > > USR1 = boost::shared_ptr<JxTYPE<Uf<1> > >(new JxTYPE<Uf<1> >(cnt));
                        replace_element("USR1", USR1);
                    }
                    break;
                case 2:
                    {
                        boost::shared_ptr<JxTYPE<Uf<2> > > USR1 = boost::shared_ptr<JxTYPE<Uf<2> > >(new JxTYPE<Uf<2> >(cnt));
                        replace_element("USR1", USR1);
                    }
                    break;
                case 4:
                    {
                        boost::shared_ptr<JxTYPE<Uf<4> > > USR1 = boost::shared_ptr<JxTYPE<Uf<4> > >(new JxTYPE<Uf<4> >(cnt));
                        replace_element("USR1", USR1);
                    }
                    break;
                case 8:
                    {
                        boost::shared_ptr<JxTYPE<Uf<8> > > USR1 = boost::shared_ptr<JxTYPE<Uf<8> > >(new JxTYPE<Uf<8> >(cnt));
                        replace_element("USR1", USR1);
                    }
                    break;
            }

        }
    }
    void setUsr1(unsigned short i,unsigned long long data)
    {
      assert(i < dynamic_cast<U2&>((*this)["USR1_CNT"]).getValue());

      switch(dynamic_cast<U1&>((*this)["U1_SIZE"]).getValue())
      {
          case 1:
              dynamic_cast<JxTYPE<Uf<1> > &>((*this)["USR1"])[i] = Uf<1>(data); break;
          case 2:
              dynamic_cast<JxTYPE<Uf<2> > &>((*this)["USR1"])[i] = Uf<2>(data); break;
          case 4:
              dynamic_cast<JxTYPE<Uf<4> > &>((*this)["USR1"])[i] = Uf<4>(data); break;
          case 8:
              dynamic_cast<JxTYPE<Uf<8> > &>((*this)["USR1"])[i] = Uf<8>(data); break;
      }

    }
    void setUsr2cnt(unsigned short cnt)
    {
        if(dynamic_cast<U2&>((*this)["USR2_CNT"]).getValue() != cnt)
        {
            set("USR2_CNT", U2(cnt));

            switch(dynamic_cast<U1&>((*this)["U2_SIZE"]).getValue())
            {
                case 1:
                    {
                        boost::shared_ptr<JxTYPE<Uf<1> > > USR2 = boost::shared_ptr<JxTYPE<Uf<1> > >(new JxTYPE<Uf<1> >(cnt));
                        replace_element("USR2", USR2);
                    }
                    break;
                case 2:
                    {
                        boost::shared_ptr<JxTYPE<Uf<2> > > USR2 = boost::shared_ptr<JxTYPE<Uf<2> > >(new JxTYPE<Uf<2> >(cnt));
                        replace_element("USR2", USR2);
                    }
                    break;
                case 4:
                    {
                        boost::shared_ptr<JxTYPE<Uf<4> > > USR2 = boost::shared_ptr<JxTYPE<Uf<4> > >(new JxTYPE<Uf<4> >(cnt));
                        replace_element("USR2", USR2);
                    }
                    break;
                case 8:
                    {
                        boost::shared_ptr<JxTYPE<Uf<8> > > USR2 = boost::shared_ptr<JxTYPE<Uf<8> > >(new JxTYPE<Uf<8> >(cnt));
                        replace_element("USR2", USR2);
                    }
                    break;
            }

        }
    }
    void setUsr2(unsigned short i,unsigned long long data)
    {
        assert(i < dynamic_cast<U2&>((*this)["USR2_CNT"]).getValue());

        switch(dynamic_cast<U1&>((*this)["U2_SIZE"]).getValue())
        {
            case 1:
                dynamic_cast<JxTYPE<Uf<1> > &>((*this)["USR2"])[i] = Uf<1>(data); break;
            case 2:
                dynamic_cast<JxTYPE<Uf<2> > &>((*this)["USR2"])[i] = Uf<2>(data); break;
            case 4:
                dynamic_cast<JxTYPE<Uf<4> > &>((*this)["USR2"])[i] = Uf<4>(data); break;
            case 8:
                dynamic_cast<JxTYPE<Uf<8> > &>((*this)["USR2"])[i] = Uf<8>(data); break;
        }

    }
    void setUsr3cnt(unsigned short cnt)
    {
        if(dynamic_cast<U2&>((*this)["USR3_CNT"]).getValue() != cnt)
        {
            set("USR3_CNT", U2(cnt));

            switch(dynamic_cast<U1&>((*this)["U3_SIZE"]).getValue())
            {
                case 1:
                    {
                        boost::shared_ptr<JxTYPE<Uf<1> > > USR3 = boost::shared_ptr<JxTYPE<Uf<1> > >(new JxTYPE<Uf<1> >(cnt));
                        replace_element("USR3", USR3);
                    }
                    break;
                case 2:
                    {
                        boost::shared_ptr<JxTYPE<Uf<2> > > USR3 = boost::shared_ptr<JxTYPE<Uf<2> > >(new JxTYPE<Uf<2> >(cnt));
                        replace_element("USR3", USR3);
                    }
                    break;
                case 4:
                    {
                        boost::shared_ptr<JxTYPE<Uf<4> > > USR3 = boost::shared_ptr<JxTYPE<Uf<4> > >(new JxTYPE<Uf<4> >(cnt));
                        replace_element("USR3", USR3);
                    }
                    break;
                case 8:
                    {
                        boost::shared_ptr<JxTYPE<Uf<8> > > USR3 = boost::shared_ptr<JxTYPE<Uf<8> > >(new JxTYPE<Uf<8> >(cnt));
                        replace_element("USR3", USR3);
                    }
                    break;
            }

        }
    }
    void setUsr3(unsigned short i,unsigned long long data)
    {
      assert(i < dynamic_cast<U2&>((*this)["USR3_CNT"]).getValue());

      switch(dynamic_cast<U1&>((*this)["U3_SIZE"]).getValue())
      {
          case 1:
              dynamic_cast<JxTYPE<Uf<1> > &>((*this)["USR3"])[i] = Uf<1>(data); break;
          case 2:
              dynamic_cast<JxTYPE<Uf<2> > &>((*this)["USR3"])[i] = Uf<2>(data); break;
          case 4:
              dynamic_cast<JxTYPE<Uf<4> > &>((*this)["USR3"])[i] = Uf<4>(data); break;
          case 8:
              dynamic_cast<JxTYPE<Uf<8> > &>((*this)["USR3"])[i] = Uf<8>(data); break;
      }

    }
    void setTxtcnt(unsigned short cnt)
    {
        if(dynamic_cast<U2&>((*this)["TXT_CNT"]).getValue() != cnt)
        {
            set("TXT_CNT", U2(cnt));

            boost::shared_ptr<MxCf> USER_TXT = boost::shared_ptr<MxCf>(new MxCf(cnt));
            USER_TXT->string_size(dynamic_cast<U1&>((*this)["UTX_SIZE"]).getValue());
            replace_element("USER_TXT", USER_TXT);
        }
    }
    void setUsertxt(unsigned short i,std::basic_string<char> data)
    {
      assert(i < dynamic_cast<U2&>((*this)["TXT_CNT"]).getValue());
      data.resize(dynamic_cast<U1&>((*this)["UTX_SIZE"]).getValue(),' ');
      dynamic_cast<MxCf&>((*this)["USER_TXT"])[i] = data;
    }

    const  B1               &  getContflg()const {return dynamic_cast<B1               &>((*this)["CONT_FLG"]);}
    const  U4               &  getTestnum()const {return dynamic_cast<U4               &>((*this)["TEST_NUM"]);}
    const  U1               &  getHeadnum()const {return dynamic_cast<U1               &>((*this)["HEAD_NUM"]);}
    const  U1               &  getSitenum()const {return dynamic_cast<U1               &>((*this)["SITE_NUM"]);}
    const  U2               &  getPsrref() const {return dynamic_cast<U2               &>((*this)["PSR_REF"]);}
    const  B1               &  getTestflg()const {return dynamic_cast<B1               &>((*this)["TEST_FLG"]);}
    const  Cn               &  getLogtyp() const {return dynamic_cast<Cn               &>((*this)["LOG_TYP"]);}
    const  Cn               &  getTesttxt()const {return dynamic_cast<Cn               &>((*this)["TEST_TXT"]);}
    const  Cn               &  getAlarmid()const {return dynamic_cast<Cn               &>((*this)["ALARM_ID"]);}
    const  Cn               &  getProgtxt()const {return dynamic_cast<Cn               &>((*this)["PROG_TXT"]);}
    const  Cn               &  getRslttxt()const {return dynamic_cast<Cn               &>((*this)["RSLT_TXT"]);}
    const  U1               &  getZval()   const {return dynamic_cast<U1               &>((*this)["Z_VAL"]);}
    const  B1               &  getFmuflg() const {return dynamic_cast<B1               &>((*this)["FMU_FLG"]);}
    const  Dn               &  getMaskmap()const {return dynamic_cast<Dn               &>((*this)["MASK_MAP"]);}
    const  Dn               &  getFalmap() const {return dynamic_cast<Dn               &>((*this)["FAL_MAP"]);}
    const  U8               &  getCyccnt() const {return dynamic_cast<U8               &>((*this)["CYC_CNT"]);}
    const  U4               &  gettotfcnt()const {return dynamic_cast<U4               &>((*this)["TOTF_CNT"]);}
    const  U4               &  gettotlcnt()const {return dynamic_cast<U4               &>((*this)["TOTL_CNT"]);}
    const  U8               &  getCycbase()const {return dynamic_cast<U8               &>((*this)["CYC_BASE"]);}
    const  U4               &  getBitbase()const {return dynamic_cast<U4               &>((*this)["BIT_BASE"]);}
    const  U2               &  getCondcnt()const {return dynamic_cast<U2               &>((*this)["COND_CNT"]);}
    const  U2               &  getLimcnt() const {return dynamic_cast<U2               &>((*this)["LIM_CNT"]);}
    const  U1               &  getCycsize()const {return dynamic_cast<U1               &>((*this)["CYC_SIZE"]);}
    const  U1               &  getPmrsize()const {return dynamic_cast<U1               &>((*this)["PMR_SIZE"]);}
    const  U1               &  getChnsize()const {return dynamic_cast<U1               &>((*this)["CHN_SIZE"]);}
    const  U1               &  getPatsize()const {return dynamic_cast<U1               &>((*this)["PAT_SIZE"]);}
    const  U1               &  getBitsize()const {return dynamic_cast<U1               &>((*this)["BIT_SIZE"]);}
    const  U1               &  getU1size() const {return dynamic_cast<U1               &>((*this)["U1_SIZE"]);}
    const  U1               &  getU2size() const {return dynamic_cast<U1               &>((*this)["U2_SIZE"]);}
    const  U1               &  getU3size() const {return dynamic_cast<U1               &>((*this)["U3_SIZE"]);}
    const  U1               &  getUtxsize()const {return dynamic_cast<U1               &>((*this)["UTX_SIZE"]);}
    const  U2               &  getCapbgn() const {return dynamic_cast<U2               &>((*this)["CAP_BGN"]);}
    const  JxTYPE<U2>       &  getLimindx()const {return dynamic_cast<JxTYPE<U2>       &>((*this)["LIM_INDX"]);}
    const  JxTYPE<U4>       &  getLimspec()const {return dynamic_cast<JxTYPE<U4>       &>((*this)["LIM_SPEC"]);}
    const  JxTYPE<Cn>       &  getCondlst()const {return dynamic_cast<JxTYPE<Cn>       &>((*this)["COND_LST"]);}
    const  U2               &  getCycocnt()const {return dynamic_cast<U2               &>((*this)["CYCO_CNT"]);}
    const  JxTYPE<Uf<8> >   &  getCycofst()const {return dynamic_cast<JxTYPE<Uf<8> >   &>((*this)["CYC_OFST"]);}
    const  U2               &  getPmrcnt() const {return dynamic_cast<U2               &>((*this)["PMR_CNT"]);}
    const  JxTYPE<Uf<2> >   &  getPmrindx()const {return dynamic_cast<JxTYPE<Uf<2> >   &>((*this)["PMR_INDX"]);}
    const  U2               &  getChncnt() const {return dynamic_cast<U2               &>((*this)["CHN_CNT"]);}
    const  JxTYPE<Uf<8> >   &  getChnnum() const {return dynamic_cast<JxTYPE<Uf<8> >   &>((*this)["CHN_NUM"]);}
    const  U2               &  getExpcnt() const {return dynamic_cast<U2               &>((*this)["EXP_CNT"]);}
    const  JxTYPE<U1>       &  getExpdata()const {return dynamic_cast<JxTYPE<U1>       &>((*this)["EXP_DATA"]);}
    const  U2               &  getCapcnt() const {return dynamic_cast<U2               &>((*this)["CAP_CNT"]);}
    const  JxTYPE<U1>       &  getCapdata()const {return dynamic_cast<JxTYPE<U1>       &>((*this)["CAP_DATA"]);}
    const  U2               &  getNewcnt() const {return dynamic_cast<U2               &>((*this)["NEW_CNT"]);}
    const  JxTYPE<U1>       &  getNewdata()const {return dynamic_cast<JxTYPE<U1>       &>((*this)["NEW_DATA"]);}
    const  U2               &  getPatcnt() const {return dynamic_cast<U2               &>((*this)["PAT_CNT"]);}
    const  JxTYPE<Uf<8> >   &  getPatnum() const {return dynamic_cast<JxTYPE<Uf<8> >   &>((*this)["PAT_NUM"]);}
    const  U2               &  getBposcnt()const {return dynamic_cast<U2               &>((*this)["BPOS_CNT"]);}
    const  JxTYPE<Uf<8> >   &  getBitpos() const {return dynamic_cast<JxTYPE<Uf<8> >   &>((*this)["BIT_POS"]);}
    const  U2               &  getUsr1cnt()const {return dynamic_cast<U2               &>((*this)["USR1_CNT"]);}
    const  JxTYPE<Uf<8> >   &  getUsr1()   const {return dynamic_cast<JxTYPE<Uf<8> >   &>((*this)["USR1"]);}
    const  U2               &  getUsr2cnt()const {return dynamic_cast<U2               &>((*this)["USR2_CNT"]);}
    const  JxTYPE<Uf<8> >   &  getUsr2()   const {return dynamic_cast<JxTYPE<Uf<8> >   &>((*this)["USR2"]);}
    const  U2               &  getUsr3cnt()const {return dynamic_cast<U2               &>((*this)["USR3_CNT"]);}
    const  JxTYPE<Uf<8> >   &  getUsr3()   const {return dynamic_cast<JxTYPE<Uf<8> >   &>((*this)["USR3"]);}
    const  U2               &  getTxtcnt() const {return dynamic_cast<U2               &>((*this)["TXT_CNT"]);}
    //const  JxTYPE<Cf<255> > &  getUsertxt()const {return dynamic_cast<JxTYPE<Cf<255> > &>((*this)["USER_TXT"]);}

    void write(std::ofstream& outfile)
    {
      if(!dynamic_cast<B1&>((*this)["FMU_FLG"])[0] || (dynamic_cast<B1&>((*this)["FMU_FLG"]))[1]) delete_element("MASK_MAP");
      if(!dynamic_cast<B1&>((*this)["FMU_FLG"])[2] || (dynamic_cast<B1&>((*this)["FMU_FLG"]))[3]) delete_element("FAL_MAP");

      Record::write(outfile);
    }

    void read(std::ifstream& infile)
    {
     U2 REC_LEN;
     REC_LEN.read(infile);
     U1 REC_TYP;
     REC_TYP.read(infile);
     U1 REC_SUB;
     REC_SUB.read(infile);

     (*this)["CONT_FLG"].read(infile);
     (*this)["TEST_NUM"].read(infile);
     (*this)["HEAD_NUM"].read(infile);
     (*this)["SITE_NUM"].read(infile);
     (*this)["PSR_REF"].read(infile);
     (*this)["TEST_FLG"].read(infile);
     (*this)["LOG_TYP"].read(infile);
     (*this)["TEST_TXT"].read(infile);
     (*this)["ALARM_ID"].read(infile);
     (*this)["PROG_TXT"].read(infile);
     (*this)["RSLT_TXT"].read(infile);
     (*this)["Z_VAL"].read(infile);
     (*this)["FMU_FLG"].read(infile);
     if(dynamic_cast<B1&>((*this)["FMU_FLG"])[0] && !(dynamic_cast<B1&>((*this)["FMU_FLG"]))[1]) (*this)["MASK_MAP"].read(infile); else delete_element("MASK_MAP");
     if(dynamic_cast<B1&>((*this)["FMU_FLG"])[2] && !(dynamic_cast<B1&>((*this)["FMU_FLG"]))[3]) (*this)["FAL_MAP"].read(infile); else delete_element("FAL_MAP");
     (*this)["CYC_CNT"].read(infile);
     (*this)["TOTF_CNT"].read(infile);
     (*this)["TOTL_CNT"].read(infile);
     (*this)["CYC_BASE"].read(infile);
     (*this)["BIT_BASE"].read(infile);
     (*this)["COND_CNT"].read(infile);
     (*this)["LIM_CNT"].read(infile);
     (*this)["CYC_SIZE"].read(infile);
     (*this)["PMR_SIZE"].read(infile);
     (*this)["CHN_SIZE"].read(infile);
     (*this)["PAT_SIZE"].read(infile);
     (*this)["BIT_SIZE"].read(infile);
     (*this)["U1_SIZE"].read(infile);
     (*this)["U2_SIZE"].read(infile);
     (*this)["U3_SIZE"].read(infile);
     (*this)["UTX_SIZE"].read(infile);
     (*this)["CAP_BGN"].read(infile);
     (*this)["LIM_INDX"].read(infile, dynamic_cast<U2&>((*this)["LIM_CNT"]).getValue());
     (*this)["LIM_SPEC"].read(infile, dynamic_cast<U2&>((*this)["LIM_CNT"]).getValue());
     (*this)["COND_LST"].read(infile, dynamic_cast<U2&>((*this)["COND_CNT"]).getValue());
#if OLD_STDF_VERSION 
     (*this)["CYCO_CNT"].read(infile);
     (*this)["CYC_OFST"].read(infile, dynamic_cast<U2&>((*this)["CYCO_CNT"]).getValue());
     (*this)["PMR_CNT" ].read(infile);
     (*this)["PMR_INDX"].read(infile, dynamic_cast<U2&>((*this)["PMR_CNT"]).getValue());
     (*this)["CHN_CNT" ].read(infile);
     (*this)["CHN_NUM" ].read(infile, dynamic_cast<U2&>((*this)["CHN_CNT"]).getValue());
     (*this)["EXP_CNT" ].read(infile);
     (*this)["EXP_DATA"].read(infile, dynamic_cast<U2&>((*this)["EXP_CNT"]).getValue());
     (*this)["CAP_CNT" ].read(infile);
     (*this)["CAP_DATA"].read(infile, dynamic_cast<U2&>((*this)["CAP_CNT"]).getValue());
     (*this)["NEW_CNT" ].read(infile);
     (*this)["NEW_DATA"].read(infile, dynamic_cast<U2&>((*this)["NEW_CNT"]).getValue());
     (*this)["PAT_CNT" ].read(infile);
     (*this)["PAT_NUM" ].read(infile, dynamic_cast<U2&>((*this)["PAT_CNT"]).getValue());
     (*this)["BPOS_CNT"].read(infile);
     //(*this)["BIT_POS" ].read(infile, dynamic_cast<U2&>((*this)["BPOS_CNT"]).getValue());
     (*this)["USR1_CNT"].read(infile);
     //(*this)["USR1"    ].read(infile, dynamic_cast<U2&>((*this)["USR1_CNT"]).getValue());
     (*this)["USR2_CNT"].read(infile);
     //(*this)["USR2"    ].read(infile, dynamic_cast<U2&>((*this)["USR2_CNT"]).getValue());
     (*this)["USR3_CNT"].read(infile);
     //(*this)["USR3"    ].read(infile, dynamic_cast<U2&>((*this)["USR3_CNT"]).getValue());
     (*this)["TXT_CNT" ].read(infile);
     if(0 != dynamic_cast<U2&>((*this)["TXT_CNT"]).getValue() || 0 != dynamic_cast<U1&>((*this)["UTX_SIZE"]).getValue())
     {
       boost::shared_ptr<MxCf> USER_TXT = boost::shared_ptr<MxCf>(new MxCf(dynamic_cast<U2&>((*this)["TXT_CNT"]).getValue()));
       USER_TXT->string_size(255);
       USER_TXT->read(infile, dynamic_cast<U2&>((*this)["TXT_CNT"]).getValue());
       replace_element("USER_TXT", USER_TXT);
     }
#else
     (*this)["CYCO_CNT"].read(infile);
     uint16_t cycocnt = dynamic_cast<U2&>((*this)["CYCO_CNT"]).getValue(); 
     switch(dynamic_cast<U1&>((*this)["CYC_SIZE"]).getValue())
     {
         case 1:
             {
                 boost::shared_ptr<JxTYPE<Uf<1> > > CYC_OFST = boost::shared_ptr<JxTYPE<Uf<1> > >(new JxTYPE<Uf<1> >(cycocnt));
                 CYC_OFST->read(infile, cycocnt);
                 replace_element("CYC_OFST", CYC_OFST);
             }
             break;
         case 2:
             {
                 boost::shared_ptr<JxTYPE<Uf<2> > > CYC_OFST = boost::shared_ptr<JxTYPE<Uf<2> > >(new JxTYPE<Uf<2> >(cycocnt));
                 CYC_OFST->read(infile, cycocnt);
                 replace_element("CYC_OFST", CYC_OFST);
             }
             break;
         case 4:
             {
                 boost::shared_ptr<JxTYPE<Uf<4> > > CYC_OFST = boost::shared_ptr<JxTYPE<Uf<4> > >(new JxTYPE<Uf<4> >(cycocnt));
                 CYC_OFST->read(infile, cycocnt);
                 replace_element("CYC_OFST", CYC_OFST);
             }
             break;
         case 8:
             {
                 boost::shared_ptr<JxTYPE<Uf<8> > > CYC_OFST = boost::shared_ptr<JxTYPE<Uf<8> > >(new JxTYPE<Uf<8> >(cycocnt));
                 CYC_OFST->read(infile, cycocnt);
                 replace_element("CYC_OFST", CYC_OFST);
             }
             break;
     }

     (*this)["PMR_CNT"].read(infile);

     uint16_t pmrcnt = dynamic_cast<U2&>((*this)["PMR_CNT"]).getValue();
     switch(dynamic_cast<U1&>((*this)["PMR_SIZE"]).getValue())
     {
         case 1:
             {
                 boost::shared_ptr<JxTYPE<Uf<1> > > PMR_INDX= boost::shared_ptr<JxTYPE<Uf<1> > >(new JxTYPE<Uf<1> >(pmrcnt));
                 PMR_INDX->read(infile, pmrcnt);
                 replace_element("PMR_INDX", PMR_INDX);
             }
             break;
         case 2:
             {
                 boost::shared_ptr<JxTYPE<Uf<2> > > PMR_INDX= boost::shared_ptr<JxTYPE<Uf<2> > >(new JxTYPE<Uf<2> >(pmrcnt));
                 PMR_INDX->read(infile, pmrcnt);
                 replace_element("PMR_INDX", PMR_INDX);
             }
             break;
         case 4:
             {
                 boost::shared_ptr<JxTYPE<Uf<4> > > PMR_INDX= boost::shared_ptr<JxTYPE<Uf<4> > >(new JxTYPE<Uf<4> >(pmrcnt));
                 PMR_INDX->read(infile, pmrcnt);
                 replace_element("PMR_INDX", PMR_INDX);
             }
             break;
         case 8:
             {
                 boost::shared_ptr<JxTYPE<Uf<8> > > PMR_INDX= boost::shared_ptr<JxTYPE<Uf<8> > >(new JxTYPE<Uf<8> >(pmrcnt));
                 PMR_INDX->read(infile, pmrcnt);
                 replace_element("PMR_INDX", PMR_INDX);
             }
             break;
     }
 
     (*this)["CHN_CNT"].read(infile);

     uint16_t chncnt = dynamic_cast<U2&>((*this)["CHN_CNT"]).getValue();
     switch(dynamic_cast<U1&>((*this)["CHN_SIZE"]).getValue())
     {
         case 1:
             {
                 boost::shared_ptr<JxTYPE<Uf<1> > > CHN_NUM= boost::shared_ptr<JxTYPE<Uf<1> > >(new JxTYPE<Uf<1> >(chncnt));
                 CHN_NUM->read(infile, chncnt);
                 replace_element("CHN_NUM", CHN_NUM);
             }
             break;
         case 2:
             {
                 boost::shared_ptr<JxTYPE<Uf<2> > > CHN_NUM= boost::shared_ptr<JxTYPE<Uf<2> > >(new JxTYPE<Uf<2> >(chncnt));
                 CHN_NUM->read(infile, chncnt);
                 replace_element("CHN_NUM", CHN_NUM);
             }
             break;
         case 4:
             {
                 boost::shared_ptr<JxTYPE<Uf<4> > > CHN_NUM= boost::shared_ptr<JxTYPE<Uf<4> > >(new JxTYPE<Uf<4> >(chncnt));
                 CHN_NUM->read(infile, chncnt);
                 replace_element("CHN_NUM", CHN_NUM);
             }
             break;
         case 8:
             {
                 boost::shared_ptr<JxTYPE<Uf<8> > > CHN_NUM= boost::shared_ptr<JxTYPE<Uf<8> > >(new JxTYPE<Uf<8> >(chncnt));
                 CHN_NUM->read(infile, chncnt);
                 replace_element("CHN_NUM", CHN_NUM);
             }
             break;
     }

     (*this)["EXP_CNT"].read(infile);
     (*this)["EXP_DATA"].read(infile, dynamic_cast<U2&>((*this)["EXP_CNT"]).getValue());
     (*this)["CAP_CNT"].read(infile);
     (*this)["CAP_DATA"].read(infile, dynamic_cast<U2&>((*this)["CAP_CNT"]).getValue());
     (*this)["NEW_CNT"].read(infile);
     (*this)["NEW_DATA"].read(infile, dynamic_cast<U2&>((*this)["NEW_CNT"]).getValue());
     (*this)["PAT_CNT"].read(infile);

     uint16_t patcnt = dynamic_cast<U2&>((*this)["PAT_CNT"]).getValue();
     switch(dynamic_cast<U1&>((*this)["PAT_SIZE"]).getValue())
     {
         case 1:
             {
                 boost::shared_ptr<JxTYPE<Uf<1> > > PAT_NUM= boost::shared_ptr<JxTYPE<Uf<1> > >(new JxTYPE<Uf<1> >(patcnt));
                 PAT_NUM->read(infile, patcnt);
                 replace_element("PAT_NUM", PAT_NUM);
             }
             break;
         case 2:
             {
                 boost::shared_ptr<JxTYPE<Uf<2> > > PAT_NUM= boost::shared_ptr<JxTYPE<Uf<2> > >(new JxTYPE<Uf<2> >(patcnt));
                 PAT_NUM->read(infile, patcnt);
                 replace_element("PAT_NUM", PAT_NUM);
             }
             break;
         case 4:
             {
                 boost::shared_ptr<JxTYPE<Uf<4> > > PAT_NUM= boost::shared_ptr<JxTYPE<Uf<4> > >(new JxTYPE<Uf<4> >(patcnt));
                 PAT_NUM->read(infile, patcnt);
                 replace_element("PAT_NUM", PAT_NUM);
             }
             break;
         case 8:
             {
                 boost::shared_ptr<JxTYPE<Uf<8> > > PAT_NUM= boost::shared_ptr<JxTYPE<Uf<8> > >(new JxTYPE<Uf<8> >(patcnt));
                 PAT_NUM->read(infile, patcnt);
                 replace_element("PAT_NUM", PAT_NUM);
             }
             break;
     }

     (*this)["BPOS_CNT"].read(infile);

     uint16_t bposcnt = dynamic_cast<U2&>((*this)["BPOS_CNT"]).getValue();
     switch(dynamic_cast<U1&>((*this)["BIT_SIZE"]).getValue())
     {
         case 1:
             {
                 boost::shared_ptr<JxTYPE<Uf<1> > > BIT_POS= boost::shared_ptr<JxTYPE<Uf<1> > >(new JxTYPE<Uf<1> >(bposcnt));
                 BIT_POS->read(infile, bposcnt);
                 replace_element("BIT_POS", BIT_POS);
             }
             break;
         case 2:
             {
                 boost::shared_ptr<JxTYPE<Uf<2> > > BIT_POS= boost::shared_ptr<JxTYPE<Uf<2> > >(new JxTYPE<Uf<2> >(bposcnt));
                 BIT_POS->read(infile, bposcnt);
                 replace_element("BIT_POS", BIT_POS);
             }
             break;
         case 4:
             {
                 boost::shared_ptr<JxTYPE<Uf<4> > > BIT_POS= boost::shared_ptr<JxTYPE<Uf<4> > >(new JxTYPE<Uf<4> >(bposcnt));
                 BIT_POS->read(infile, bposcnt);
                 replace_element("BIT_POS", BIT_POS);
             }
             break;
         case 8:
             {
                 boost::shared_ptr<JxTYPE<Uf<8> > > BIT_POS= boost::shared_ptr<JxTYPE<Uf<8> > >(new JxTYPE<Uf<8> >(bposcnt));
                 BIT_POS->read(infile, bposcnt);
                 replace_element("BIT_POS", BIT_POS);
             }
             break;
     }
 
     (*this)["USR1_CNT"].read(infile);

     uint16_t usr1cnt = dynamic_cast<U2&>((*this)["USR1_CNT"]).getValue();
     switch(dynamic_cast<U1&>((*this)["U1_SIZE"]).getValue())
     {
       case 1:
             {
                 boost::shared_ptr<JxTYPE<Uf<1> > > USR1= boost::shared_ptr<JxTYPE<Uf<1> > >(new JxTYPE<Uf<1> >(usr1cnt));
                 USR1->read(infile, usr1cnt);
                 replace_element("USR1", USR1);
             }
             break;
         case 2:
             {
                 boost::shared_ptr<JxTYPE<Uf<2> > > USR1= boost::shared_ptr<JxTYPE<Uf<2> > >(new JxTYPE<Uf<2> >(usr1cnt));
                 USR1->read(infile, usr1cnt);
                 replace_element("USR1", USR1);
             }
             break;
         case 4:
             {
                 boost::shared_ptr<JxTYPE<Uf<4> > > USR1= boost::shared_ptr<JxTYPE<Uf<4> > >(new JxTYPE<Uf<4> >(usr1cnt));
                 USR1->read(infile, usr1cnt);
                 replace_element("USR1", USR1);
             }
             break;
         case 8:
             {
                 boost::shared_ptr<JxTYPE<Uf<8> > > USR1= boost::shared_ptr<JxTYPE<Uf<8> > >(new JxTYPE<Uf<8> >(usr1cnt));
                 USR1->read(infile, usr1cnt);
                 replace_element("USR1", USR1);
             }
             break;
     }
 
     (*this)["USR2_CNT"].read(infile);

     uint16_t usr2cnt = dynamic_cast<U2&>((*this)["USR2_CNT"]).getValue();
     switch(dynamic_cast<U1&>((*this)["U2_SIZE"]).getValue())
     {
         case 1:
             {
                 boost::shared_ptr<JxTYPE<Uf<1> > > USR2= boost::shared_ptr<JxTYPE<Uf<1> > >(new JxTYPE<Uf<1> >(usr2cnt));
                 USR2->read(infile, usr2cnt);
                 replace_element("USR2", USR2);
             }
             break;
         case 2:
             {
                 boost::shared_ptr<JxTYPE<Uf<2> > > USR2= boost::shared_ptr<JxTYPE<Uf<2> > >(new JxTYPE<Uf<2> >(usr2cnt));
                 USR2->read(infile, usr2cnt);
                 replace_element("USR2", USR2);
             }
             break;
         case 4:
             {
                 boost::shared_ptr<JxTYPE<Uf<4> > > USR2= boost::shared_ptr<JxTYPE<Uf<4> > >(new JxTYPE<Uf<4> >(usr2cnt));
                 USR2->read(infile, usr2cnt);
                 replace_element("USR2", USR2);
             }
             break;
         case 8:
             {
                 boost::shared_ptr<JxTYPE<Uf<8> > > USR2= boost::shared_ptr<JxTYPE<Uf<8> > >(new JxTYPE<Uf<8> >(usr2cnt));
                 USR2->read(infile, usr2cnt);
                 replace_element("USR2", USR2);
             }
             break;
     }
 
     (*this)["USR3_CNT"].read(infile);

     uint16_t usr3cnt = dynamic_cast<U2&>((*this)["USR3_CNT"]).getValue();
     switch(dynamic_cast<U1&>((*this)["U3_SIZE"]).getValue())
     {
         case 1:
             {
                 boost::shared_ptr<JxTYPE<Uf<1> > > USR3= boost::shared_ptr<JxTYPE<Uf<1> > >(new JxTYPE<Uf<1> >(usr3cnt));
                 USR3->read(infile, usr3cnt);
                 replace_element("USR3", USR3);
             }
             break;
         case 2:
             {
                 boost::shared_ptr<JxTYPE<Uf<2> > > USR3= boost::shared_ptr<JxTYPE<Uf<2> > >(new JxTYPE<Uf<2> >(usr3cnt));
                 USR3->read(infile, usr3cnt);
                 replace_element("USR3", USR3);
             }
             break;
         case 4:
             {
                 boost::shared_ptr<JxTYPE<Uf<4> > > USR3= boost::shared_ptr<JxTYPE<Uf<4> > >(new JxTYPE<Uf<4> >(usr3cnt));
                 USR3->read(infile, usr3cnt);
                 replace_element("USR3", USR3);
             }
             break;
         case 8:
             {
                 boost::shared_ptr<JxTYPE<Uf<8> > > USR3= boost::shared_ptr<JxTYPE<Uf<8> > >(new JxTYPE<Uf<8> >(usr3cnt));
                 USR3->read(infile, usr3cnt);
                 replace_element("USR3", USR3);
             }
             break;
     }
     (*this)["TXT_CNT"].read(infile);

     if(0 != dynamic_cast<U2&>((*this)["TXT_CNT"]).getValue() || 0 != dynamic_cast<U1&>((*this)["UTX_SIZE"]).getValue())
     {
       boost::shared_ptr<MxCf> USER_TXT = boost::shared_ptr<MxCf>(new MxCf(dynamic_cast<U2&>((*this)["TXT_CNT"]).getValue()));
       USER_TXT->string_size(dynamic_cast<U1&>((*this)["UTX_SIZE"]).getValue());
       USER_TXT->read(infile, dynamic_cast<U2&>((*this)["TXT_CNT"]).getValue());
       replace_element("USER_TXT", USER_TXT);
     }
#endif
    }
  
  };


////////////////////////////// SEGMENT //////////////////////////////

class BPS : public Record
{
  public:
    ~BPS() {}
    BPS() : Record(Record::BPS_TYPE)
    {
      add("SEQ_NAME", boost::shared_ptr<Cn>(new Cn()));
    }
    BPS(const BPS& bps) : Record(Record::BPS_TYPE)
    {
      add("SEQ_NAME", boost::shared_ptr<Cn>(new Cn(bps.getSeqname())));
    }
    void clear() {Record::clear();}
    void setSeqname(const std::basic_string<char>& seqname) {dynamic_cast<Cn&>((*this)["SEQ_NAME"]) = Cn(seqname);}

    const Cn&  getSeqname()const {return dynamic_cast<Cn&>((*this)["SEQ_NAME"]);}

};


class EPS : public Record
{
  public:
    ~EPS() {}
    EPS() : Record(Record::EPS_TYPE) {}
    EPS(const EPS& bps) : Record(Record::EPS_TYPE) {}
    void clear() {Record::clear();}

  private:
};


////////////////////////////// GENERIC //////////////////////////////

class GDR : public Record
{
  public:
    ~GDR() {}
    GDR() : Record(Record::GDR_TYPE)
    {
      add("FLD_CNT", boost::shared_ptr<U2>(new U2()));
      add("GEN_DATA",boost::shared_ptr<Vn>(new Vn()));
    }
    GDR(const GDR& dtr) : Record(Record::GDR_TYPE)
    {
      add("FLD_CNT", boost::shared_ptr<U2>(new U2(dtr.getFldCnt() )));
      add("GEN_DATA",boost::shared_ptr<Vn>(new Vn(dtr.getGendata())));
    }
    void clear(){Record::clear();}
    void setFldcnt() {dynamic_cast<U2&>((*this)["FLD_CNT"]) = U2(dynamic_cast<Vn&>((*this)["GEN_DATA"]).size());}
    GDR& addU1(const U1& u1) {dynamic_cast<Vn&>((*this)["GEN_DATA"]).addU1(u1); setFldcnt(); return *this;}
    GDR& addU2(const U2& u2) {dynamic_cast<Vn&>((*this)["GEN_DATA"]).addU2(u2); setFldcnt(); return *this;}
    GDR& addU4(const U4& u4) {dynamic_cast<Vn&>((*this)["GEN_DATA"]).addU4(u4); setFldcnt(); return *this;}
    GDR& addI1(const I1& i1) {dynamic_cast<Vn&>((*this)["GEN_DATA"]).addI1(i1); setFldcnt(); return *this;}
    GDR& addI2(const I2& i2) {dynamic_cast<Vn&>((*this)["GEN_DATA"]).addI2(i2); setFldcnt(); return *this;}
    GDR& addI4(const I4& i4) {dynamic_cast<Vn&>((*this)["GEN_DATA"]).addI4(i4); setFldcnt(); return *this;}
    GDR& addR4(const R4& r4) {dynamic_cast<Vn&>((*this)["GEN_DATA"]).addR4(r4); setFldcnt(); return *this;}
    GDR& addR8(const R8& r8) {dynamic_cast<Vn&>((*this)["GEN_DATA"]).addR8(r8); setFldcnt(); return *this;}
    GDR& addCn(const Cn& cn) {dynamic_cast<Vn&>((*this)["GEN_DATA"]).addCn(cn); setFldcnt(); return *this;}
    GDR& addBn(const Bn& bn) {dynamic_cast<Vn&>((*this)["GEN_DATA"]).addBn(bn); setFldcnt(); return *this;}
    GDR& addDn(const Dn& dn) {dynamic_cast<Vn&>((*this)["GEN_DATA"]).addDn(dn); setFldcnt(); return *this;}
    GDR& addN1(const N1& n1) {dynamic_cast<Vn&>((*this)["GEN_DATA"]).addN1(n1); setFldcnt(); return *this;}

    const U2&  getFldCnt() const{return dynamic_cast<U2&>((*this)["FLD_CNT"]);}
    const Vn&  getGendata()const{return dynamic_cast<Vn&>((*this)["GEN_DATA"]);}

    void read(std::ifstream& infile)
    {
      
      U2 REC_LEN;
      REC_LEN.read(infile);
      U1 REC_TYP;
      REC_TYP.read(infile);
      U1 REC_SUB;
      REC_SUB.read(infile);

      (*this)["FLD_CNT"].read(infile);
      (*this)["GEN_DATA"].read(infile, REC_LEN.getValue() - 2);
      //(*this)["GEN_DATA"].read(infile, dynamic_cast<U2&>((*this)["FLD_CNT"]).getValue());
    }
 
};


class DTR : public Record
{
  public:
    ~DTR() {}
    DTR() : Record(Record::DTR_TYPE)
    {
      add("TEXT_DAT",boost::shared_ptr<Cn>(new Cn()));
    }
    DTR(const DTR& dtr) : Record(Record::DTR_TYPE)
    {
      add("TEXT_DAT",boost::shared_ptr<Cn>(new Cn(dtr.getTextdat())));
    }
    void clear(){Record::clear();}
    void setTextdat(const std::basic_string<char>& testdat){dynamic_cast<Cn&>((*this)["TEXT_DAT"]) = Cn(testdat);}

    const Cn&  getTextdat()const {return dynamic_cast<Cn&>((*this)["TEXT_DAT"]);}

};


#endif
