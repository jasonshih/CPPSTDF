#include "STDF.hpp"

STDF::~STDF()
{
  if(NULL != infile){(*infile).close(); delete infile;}
  if(NULL != outfile){(*outfile).close(); delete outfile;}
}

STDF::STDF(const std::string& filename, STDF::STDFType type):filename(filename)
{
  switch(type)
  {
    case WRITE:     outfile = new std::ofstream(filename.c_str(), std::ofstream::binary); infile = NULL;                    assert(NULL!=outfile); break;
    case READ:      infile  = new std::ifstream(filename.c_str(), std::ifstream::binary); outfile = NULL;                   assert(NULL!=infile); break;
    case APPEND:    outfile = new std::ofstream(filename.c_str(), std::ofstream::binary|std::ofstream::app); infile = NULL; assert(NULL!=outfile); break;
    case MODIFY:    infile  = new std::ifstream(filename.c_str(), std::ifstream::binary); outfile = NULL;                   assert(NULL!=infile); break;
    case READ_ONLY: infile  = new std::ifstream(filename.c_str(), std::ifstream::binary); outfile = NULL;                   assert(NULL!=infile); break;
  }
}

void STDF::clear()
{
  for(Container::size_type i=0;i < mData.size();i++)
  {
    mData[i].second->clear();
  }
}

void STDF::close()
{
  if(NULL != infile){(*infile).close(); delete infile; infile = NULL;}
  if(NULL != outfile){(*outfile).close(); delete outfile; outfile = NULL;}
}

void STDF::write()
{
  if(NULL!=infile)
  {
    (*infile).close();
    delete infile;
    infile = NULL;
  }
  if(NULL==outfile)
  {
    outfile = new std::ofstream(filename.c_str(), std::ofstream::binary);
    assert(NULL!=outfile);
  }
  for(Container::const_iterator it = mData.begin();it!=mData.end();it++)
  { 
    (it->second)->write(*outfile);
  }
}

size_t STDF::storage()const
{
  size_t iret=0;
  for(size_t i=0;i<mData.size();i++)
  {
    iret+=mData[i].second->storage();
  }
  return iret;
}

void STDF::read(STDF::STDFType type)
{
  if(outfile != NULL)
  {
    (*outfile).close();
    delete outfile;
    outfile=NULL;
  }
  if(infile == NULL)
  {
    infile = new std::ifstream(filename.c_str(), std::ifstream::binary); 
    assert(NULL!=infile);
  }

  std::pair<std::basic_string<char>, RecordSharedPtr> data;
  size_t len = 0;
  unsigned short REC_LEN = 0;
  char REC_TYP = 0;
  char REC_SUB = 0;
  (*infile).seekg(0,std::ios::end);
  size_t size = (*infile).tellg();
  (*infile).seekg(0,std::ios::beg);

  while(len<size)
  {
    (*infile).read((char*)&REC_LEN,sizeof(short));
    (*infile).read((char*)&REC_TYP,sizeof(char));
    (*infile).read((char*)&REC_SUB,sizeof(char));
    (*infile).seekg(-int(sizeof(int)),std::ios::cur);
    len += REC_LEN+4;

    data = StdfRecordFactory::Create(REC_TYP,REC_SUB);

    if(NULL != data.second)
    {
      data.second->read(*infile);

      if(READ_ONLY == type)
        std::cout << data.first << *data.second;
      else 
        mData.push_back(data);
    }
    else
    {
      break;
    }
  }
}

void STDF::print_record(std::ostream &os)const
{
  std::stringstream ss;
  std::vector<std::basic_string<char> > str;
  for(size_t i=0;i<mData.size();i++)
  {
    str.push_back(mData[i].first);
    mData[i].second->to_string1(str);
  }
  for(size_t i=0;i<str.size();i++)
  {
    ss<<str[i]; 
  }
  
  os << ss.str();
  os.flush();
}

std::basic_string<char> STDF::to_string()const
{
  std::stringstream ss;
  std::vector<std::basic_string<char> > str;
  for(size_t i=0;i<mData.size();i++)
  {
    str.push_back(mData[i].first);
    mData[i].second->to_string(str);
  }
  for(size_t i=0;i<str.size();i++)
  {
    ss<<str[i]<<","; 
  }
  std::basic_string<char> iret=ss.str();
  if(!iret.empty()) iret=iret.substr(0,iret.size());

  return iret;
}

STDF::Container::iterator STDF::find(const std::basic_string<char>& name,size_t order)
{
  STDF::Container::iterator it = mData.begin();
  size_t icount=0;
  for(;it!=mData.end(); it++)
  {
    if(it->first==name && icount == order)
      break;
    if(it->first==name)
      ++icount;
  }
  return it;
}
