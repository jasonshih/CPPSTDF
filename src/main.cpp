#include "STDF.hpp"
#include <iostream>
#include <time.h>
using std::string;
using std::vector;
using std::ofstream;

static bool DISPLAY_RAW_DATA = false;
#define FORMATTER_VERSION    "1.0.00"
#define FORMATTER_PATCH_VER  ""
static std::string  iofile;

static void Usage (char *progname);
static int  ReadSTDFFile (std::string &filename);
static int  ProcessArgs (int argc, char *argv[]);

static void WriteFileResult(const string type,bool result=true)
{
  if(result)
    std::cout<<std::setfill(' ')<<std::setw(55)<<" "<<type<<": "<<"write successful!"<<std::endl;
  else
    std::cout<<std::setfill(' ')<<std::setw(55)<<" "<<"[ERROR: Sorry, This type"<<" ("<<type<<") "<<"does not exist!]"<<std::endl;
}

static void WriteRecord(ofstream &outfile,Record &R)
{
  R.write(outfile);
}

static void Writefile(ofstream &outfile,const string type)
{
  string str("FAR|ATR|VUR|MIR|MRR|PCR|HBR|SBR|PMR|PGR|PLR|RDR|SDR|PSR|NMR|CNR|SSR|CDR|WIR|WRR|WCR|PIR|PRR|TSR|PTR|MPR|FTR|STR|BPS|EPS|GDR|DTR");
  if(type.size()==3)
  {
    switch((int)str.find(type))
    {
      case 0:   {FAR W;WriteRecord(outfile,W);} WriteFileResult(type,1); break;
      case 4:   {ATR W;WriteRecord(outfile,W);} WriteFileResult(type,1); break;
      case 8:   {VUR W;WriteRecord(outfile,W);} WriteFileResult(type,1); break;

      case 12:  {MIR W;WriteRecord(outfile,W);} WriteFileResult(type,1); break;
      case 16:  {MRR W;WriteRecord(outfile,W);} WriteFileResult(type,1); break;
      case 20:  {PCR W;WriteRecord(outfile,W);} WriteFileResult(type,1); break;
      case 24:  {HBR W;WriteRecord(outfile,W);} WriteFileResult(type,1); break;
      case 28:  {SBR W;WriteRecord(outfile,W);} WriteFileResult(type,1); break;
      case 32:  {PMR W;WriteRecord(outfile,W);} WriteFileResult(type,1); break;
      case 36:  {PGR W;WriteRecord(outfile,W);} WriteFileResult(type,1); break;
      case 40:  {PLR W;WriteRecord(outfile,W);} WriteFileResult(type,1); break;
      case 44:  {RDR W;WriteRecord(outfile,W);} WriteFileResult(type,1); break;
      case 48:  {SDR W;WriteRecord(outfile,W);} WriteFileResult(type,1); break;
      case 52:  {PSR W;WriteRecord(outfile,W);} WriteFileResult(type,1); break;
      case 56:  {NMR W;WriteRecord(outfile,W);} WriteFileResult(type,1); break;
      case 60:  {CNR W;WriteRecord(outfile,W);} WriteFileResult(type,1); break;
      case 64:  {SSR W;WriteRecord(outfile,W);} WriteFileResult(type,1); break;
      case 68:  {CDR W;WriteRecord(outfile,W);} WriteFileResult(type,1); break;

      case 72:  {WIR W;WriteRecord(outfile,W);} WriteFileResult(type,1); break;
      case 76:  {WRR W;WriteRecord(outfile,W);} WriteFileResult(type,1); break;
      case 80:  {WCR W;WriteRecord(outfile,W);} WriteFileResult(type,1); break;

      case 84:  {PIR W;WriteRecord(outfile,W);} WriteFileResult(type,1); break;
      case 88:  {PRR W;WriteRecord(outfile,W);} WriteFileResult(type,1); break;

      case 92:  {TSR W;WriteRecord(outfile,W);} WriteFileResult(type,1); break;

      case 96:  {PTR W;WriteRecord(outfile,W);} WriteFileResult(type,1); break;
      case 100: {MPR W;WriteRecord(outfile,W);} WriteFileResult(type,1); break;//
      case 104: {FTR W;WriteRecord(outfile,W);} WriteFileResult(type,1); break;
      case 108: {STR W;WriteRecord(outfile,W);} WriteFileResult(type,1); break;

      case 112: {BPS W;WriteRecord(outfile,W);} WriteFileResult(type,1); break;
      case 116: {EPS W;WriteRecord(outfile,W);} WriteFileResult(type,1); break;//

      case 120: {GDR W;WriteRecord(outfile,W);} WriteFileResult(type,1); break;
      case 124: {DTR W;WriteRecord(outfile,W);} WriteFileResult(type,1); break;    
      default : WriteFileResult(type,0); break;

    }
  }
  else 
    WriteFileResult(type,0);
}

static void Createmenu()
{
  std::cout<<std::setfill(' ')<<std::setw(30)<<" "<<"|--------------------------------------------------------------|"<<std::endl
           <<std::setfill(' ')<<std::setw(30)<<" "<<"||--------------------support record type:--------------------||"<<std::endl 
           <<std::setfill(' ')<<std::setw(30)<<" "<<"|| FAR   ATR   VUR   MIR   MRR   PCR   HBR   SBR   PMR   PGR  ||"<<std::endl
           <<std::setfill(' ')<<std::setw(30)<<" "<<"|| PLR   RDR   SDR   PSR   NMR   CNR   SSR   CDR   WIR   WRR  ||"<<std::endl
           <<std::setfill(' ')<<std::setw(30)<<" "<<"|| WCR   PIR   PRR   TSR   PTR   MPR   FTR   STR   BPS   EPS  ||"<<std::endl 
           <<std::setfill(' ')<<std::setw(30)<<" "<<"|| GDR   DTR                                                  ||"<<std::endl 
           <<std::setfill(' ')<<std::setw(30)<<" "<<"||------------------------------------------------------------||"<<std::endl
           <<std::setfill(' ')<<std::setw(30)<<" "<<"|--------------------------------------------------------------|"<<std::endl;
}

static void  Cmdline(string &type)
{
  size_t found = type.find_first_of(' ');
  while(found<type.size())
  {
    type.erase(found,1);
    found=type.find_first_of(' ',found++);
  }
}

static void  WriteFile(ofstream &outfile,const string type)
{
  string str;
  for(size_t i=0;i<type.size();i=i+3)
  {
    str=type.substr(i,3);
    Writefile(outfile,str);
  }
}

static void  Inputcmd(string &type)
{
  std::cout<<"==>Please input RecordType:";
  getline(std::cin,type);
}

static void Closefile(ofstream& outfile)
{
  outfile.close();
}

static void Messagebox(const string& str)
{
  std::cout<<str<<std::endl;
}


static int ProcessArgs (int argc, char *argv[])
{
  if( (2 == argc) && (argv[1][0] != '-') )
  {
    iofile = argv[1];
    DISPLAY_RAW_DATA = true;
    return 0;
  }
  else if( (3 == argc) && (strcmp(argv[1], "-r") == 0) && (argv[2][0] != '-') )
  {
    iofile = argv[2];
    DISPLAY_RAW_DATA = true;
    return 0;
  }
  else if( (3 == argc) && (strcmp(argv[1], "-w") == 0) && (argv[2][0] != '-') )
  {
    iofile = argv[2];
    DISPLAY_RAW_DATA = false;
    return 0;
  }
  else
  {
    Usage(argv[0]);
    return 1;
  }
}

static void Usage (char *progname)
{
  std::cout << std::endl
    << " Release Version : " << FORMATTER_VERSION << FORMATTER_PATCH_VER << " " << __DATE__ << " " << " " << __TIME__ << std::endl
    << " Usage: " << progname << " <STDF_file>" << std::endl
    << "        " << progname << " [-r] <STDF_file>" << std::endl
    << "        " << progname << " [-w] <STDF_file>" << std::endl
    << "        " << progname << " [-h]" << std::endl << std::endl
    << "   <STDF_file>         - Read from STDF(tm) file" << std::endl
    << "   -r  <STDF_file>     - Read from STDF(tm) file" << std::endl
    << "   -w  <STDF_file>     - Write into STDF(tm) file" << std::endl
    << "   -h                  - This help message" << std::endl << std::endl;
}

static int ReadSTDFFile (std::string &filename)
{
  STDF      stdf(filename.c_str(),STDF::READ);

  std::cout << "Data from file '" << iofile << "'" << std::endl;
  stdf.read_only();
  fputs("End of file. Done!\n\n", stdout);
  return 1;
}

int main(int argc, char *argv[])
{
  char ch;
  string type;
  bool Tryagain = true;

  if (ProcessArgs(argc, argv))
  {
      return (1);
  }

  if(DISPLAY_RAW_DATA)
  {
      std::cout << "Starting " << argv[0] << ":" << std::endl << std::endl
          << "   STDF is a trademark of Teradyne, Inc." << std::endl << std::endl;
      return ((1 != ReadSTDFFile(iofile)) ? 0 : 1);
  }else
  {
      ofstream outfile(iofile.c_str(), ofstream::binary);

      while(Tryagain)
      {
          Createmenu();
          Inputcmd(type);
          Cmdline(type);
          WriteFile(outfile,type);
          Messagebox("Would you like try again?(Y/N)");
          std::cin>>ch;
          if(ch != 'y' && ch != 'Y')
          { 
              Tryagain = false;
              Closefile(outfile);
          }
          std::cin.ignore();
      }

      return 0;
  }
}
