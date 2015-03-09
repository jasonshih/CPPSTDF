#include <cxxtest/TestSuite.h>

#include "DataTypes.hpp"

class TestCf : public CxxTest::TestSuite 
{
  private:
    typedef Cf<0> Cf0;
    typedef Cf<1> Cf1;
    typedef Cf<5> Cf5;
    typedef Cf<5000> Cf5000;

  public:
    void setUp()
    {
    }
    void tearDown()
    {
    }

    void testConstructor1()
    {
      Cf1 stdfStr;
      TS_ASSERT_EQUALS(stdfStr.mData, "");
      TS_ASSERT_EQUALS(stdfStr.to_string(), " ");
      TS_ASSERT_EQUALS(stdfStr.storage(), 1u);
    }

    void testConstructor2()
    {
      Cf1 stdfStr = "";
      TS_ASSERT_EQUALS(stdfStr.mData, "");
      TS_ASSERT_EQUALS(stdfStr.to_string(), " ");
      TS_ASSERT_EQUALS(stdfStr.storage(), 1u);
      stdfStr += "";
      TS_ASSERT_EQUALS(stdfStr.mData, "");
      TS_ASSERT_EQUALS(stdfStr.to_string(), " ");
      TS_ASSERT_EQUALS(stdfStr.storage(), 1u);
      stdfStr = "";
      TS_ASSERT_EQUALS(stdfStr.mData, "");
      TS_ASSERT_EQUALS(stdfStr.to_string(), " ");
      TS_ASSERT_EQUALS(stdfStr.storage(), 1u);
    }

    void testConstructor3()
    {
      Cf5 stdfStr = "AA";
      TS_ASSERT_EQUALS(stdfStr.mData, "AA");
      TS_ASSERT_EQUALS(stdfStr.to_string(), "AA   ");
      TS_ASSERT_EQUALS(stdfStr.storage(), 5u);
      stdfStr += "BB";
      TS_ASSERT_EQUALS(stdfStr.mData, "AABB");
      TS_ASSERT_EQUALS(stdfStr.to_string(), "AABB ");
      TS_ASSERT_EQUALS(stdfStr.storage(), 5u);
      stdfStr = "CC";
      TS_ASSERT(stdfStr.mData == "CC");
      TS_ASSERT_EQUALS(stdfStr.to_string(), "CC   ");
      TS_ASSERT_EQUALS(stdfStr.storage(), 5u);
      stdfStr += "BBAA";
      TS_ASSERT_EQUALS(stdfStr.mData, "CCBBAA");
      TS_ASSERT_EQUALS(stdfStr.to_string(), "CCBBA");
      TS_ASSERT_EQUALS(stdfStr.storage(), 5u);
    }

    void testCopyConstructor1()
    {
      Cf5 stdfStr = "AA";
      TS_ASSERT_EQUALS(stdfStr.mData, "AA");
      TS_ASSERT_EQUALS(stdfStr.to_string(), "AA   ");
      TS_ASSERT_EQUALS(stdfStr.storage(), 5u);
      Cf5 stdfStrC(stdfStr);
      stdfStr = "CC";
      TS_ASSERT_EQUALS(stdfStr.mData, "CC");
      TS_ASSERT_EQUALS(stdfStrC.mData, "AA");
      TS_ASSERT_EQUALS(stdfStr.to_string(), "CC   ");
      TS_ASSERT_EQUALS(stdfStrC.to_string(), "AA   ");
      TS_ASSERT_EQUALS(stdfStr.storage(), 5u);
      TS_ASSERT_EQUALS(stdfStrC.storage(), 5u);
    }

    void testAssigner1()
    {
      Cf5 stdfStr = "AA";
      TS_ASSERT_EQUALS(stdfStr.mData, "AA");
      TS_ASSERT_EQUALS(stdfStr.to_string(), "AA   ");
      TS_ASSERT_EQUALS(stdfStr.storage(), 5u);
      Cf5 stdfStrC;
      stdfStrC = stdfStr;
      stdfStr = "CC";
      TS_ASSERT_EQUALS(stdfStr.mData, "CC");
      TS_ASSERT_EQUALS(stdfStrC.mData, "AA");
      TS_ASSERT_EQUALS(stdfStr.to_string(), "CC   ");
      TS_ASSERT_EQUALS(stdfStrC.to_string(), "AA   ");
      TS_ASSERT_EQUALS(stdfStr.storage(), 5u);
      TS_ASSERT_EQUALS(stdfStrC.storage(), 5u);
    }

    void testClone1()
    {
      Cf5 stdfStr = "AA";
      TS_ASSERT_EQUALS(stdfStr.mData, "AA");
      TS_ASSERT_EQUALS(stdfStr.to_string(), "AA   ");
      TS_ASSERT_EQUALS(stdfStr.storage(), 5u);
      DataType::DataTypeSharedPtr stdfStrP = stdfStr.clone();
      stdfStr = "CC";
      TS_ASSERT_EQUALS(stdfStr.to_string(), "CC   ");
      TS_ASSERT_EQUALS(stdfStrP->to_string(), "AA   ");
      TS_ASSERT_EQUALS(stdfStr.storage(), 5u);
      TS_ASSERT_EQUALS(stdfStrP->storage(), 5u);
    }

    void testWriteRead1()
    {
      const char *filename = "TestCf.testWriteRead1.txt";

      Cf0 stdfStrIn;
      std::ofstream outfile(filename, std::ofstream::binary);
      stdfStrIn.write(outfile);
      outfile.close();

      Cf0 stdfStrOut;
      std::ifstream infile(filename, std::ifstream::binary);
      stdfStrOut.read(infile);
      outfile.close();

      TS_ASSERT(stdfStrIn.mData == stdfStrOut.mData);
      TS_ASSERT_EQUALS(stdfStrIn.to_string(), "");
      TS_ASSERT_EQUALS(stdfStrOut.to_string(), "");
      TS_ASSERT_EQUALS(stdfStrIn.storage(), 0u);
      TS_ASSERT_EQUALS(stdfStrOut.storage(), 0u);
    }

    void testWriteRead2()
    {
      const char *filename = "TestCf.testWriteRead2.txt";

      Cf5 stdfStrIn = "123456789";
      std::ofstream outfile(filename, std::ofstream::binary);
      stdfStrIn.write(outfile);
      outfile.close();

      Cf5 stdfStrOut;
      std::ifstream infile(filename, std::ifstream::binary);
      stdfStrOut.read(infile);
      outfile.close();

      TS_ASSERT_EQUALS(stdfStrIn.mData, "123456789");
      TS_ASSERT_EQUALS(stdfStrOut.mData, "12345");
      TS_ASSERT_EQUALS(stdfStrIn.to_string(), "12345");
      TS_ASSERT_EQUALS(stdfStrOut.to_string(), "12345");
      TS_ASSERT_EQUALS(stdfStrIn.storage(), 5u);
      TS_ASSERT_EQUALS(stdfStrOut.storage(), 5u);
    }

    void testWriteRead3()
    {
      const char *filename = "TestCf.testWriteRead3.txt";

      Cf5000 stdfStrIn = "123456789";
      std::ofstream outfile(filename, std::ofstream::binary);
      stdfStrIn.write(outfile);
      outfile.close();

      Cf5000 stdfStrOut;
      std::ifstream infile(filename, std::ifstream::binary);
      stdfStrOut.read(infile);
      outfile.close();

      TS_ASSERT_EQUALS(stdfStrIn.mData, "123456789");
      TS_ASSERT_EQUALS(stdfStrOut.mData, "123456789");
      std::stringstream ss;
      ss << "123456789"; for(size_t i = 0; i < 5000-stdfStrIn.mData.size(); i++) ss << ' ';
      TS_ASSERT_EQUALS(stdfStrIn.to_string(), ss.str());
      TS_ASSERT_EQUALS(stdfStrOut.to_string(), ss.str());
      TS_ASSERT_EQUALS(stdfStrIn.storage(), 5000u);
      TS_ASSERT_EQUALS(stdfStrOut.storage(), 5000u);
    }

};
