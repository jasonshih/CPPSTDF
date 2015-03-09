#include <cfloat>
#include <cxxtest/TestSuite.h>

#include "DataTypes.hpp"

class TestJxR4 : public CxxTest::TestSuite 
{
  private:
    bool isEqual(float a, float b, float relError)
    {
      if(fabs(a) < fabs(b)) return ((fabs((a-b))/a) < relError)? true:false;
      else                  return ((fabs((a-b))/b) < relError)? true:false;
    }
    bool isEqual(float a, float b) {return isEqual(a, b, FLT_EPSILON);}

  public:
    void setUp()
    {
    }
    void tearDown()
    {
    }

    void testConstructor0()
    {
      const size_t size = 0;
      JxTYPE<R4> stdfStr;
      TS_ASSERT_EQUALS(stdfStr.size(), size);
      TS_ASSERT_EQUALS(stdfStr.storage(), size);
      TS_ASSERT_EQUALS(stdfStr.to_string(), "");
    }

    void testConstructor1()
    {
      const size_t size = 10;
      JxTYPE<R4> stdfStr(size);
      TS_ASSERT_EQUALS(stdfStr.size(), size);
      TS_ASSERT_EQUALS(stdfStr.storage(), 4*size);
      TS_ASSERT_EQUALS(stdfStr.to_string(), "0,0,0,0,0,0,0,0,0,0");
    }

    void testConstructor2()
    {
      const size_t size = 100;
      JxTYPE<R4> stdfStr;
      R4 data[size];
      for(size_t i = 0; i < size; i++)
      {
        data[i] = i;
        stdfStr.add(data[i]);
      }
      TS_ASSERT_EQUALS(stdfStr.size(), size);
      TS_ASSERT_EQUALS(stdfStr.storage(), 4*size);
      TS_ASSERT_EQUALS(stdfStr[88].getValue(), (float)88);
      TS_ASSERT(isEqual(stdfStr[88].getValue(), 88));
      TS_ASSERT_EQUALS(stdfStr[88].to_string(), data[88].to_string());
      TS_ASSERT_EQUALS(stdfStr[99].getValue(), (float)99);
      TS_ASSERT(isEqual(stdfStr[99].getValue(), 99));
      TS_ASSERT_EQUALS(stdfStr[99].to_string(), data[99].to_string());
      std::stringstream ss;
      for(size_t i = 0; i < size-1; i++) ss << i << ","; ss << size-1;
      TS_ASSERT_EQUALS(stdfStr.to_string(), ss.str());
      stdfStr.clear();
      TS_ASSERT_EQUALS(stdfStr.to_string(), "");
    }

    void testConstructor3()
    {
      const size_t size = 100;
      JxTYPE<R4> stdfStr;
      R4 data[size];
      for(int i = 0; (size_t)i < size; i++)
      {
        data[i] = -i;
        stdfStr.add(data[i]);
      }
      TS_ASSERT_EQUALS(stdfStr.size(), size);
      TS_ASSERT_EQUALS(stdfStr.storage(), 4*size);
      TS_ASSERT_EQUALS(stdfStr[88].getValue(), -88);
      TS_ASSERT_EQUALS(stdfStr[88].to_string(), data[88].to_string());
      TS_ASSERT_EQUALS(stdfStr[99].getValue(), -99);
      TS_ASSERT_EQUALS(stdfStr[99].to_string(), data[99].to_string());
      TS_ASSERT_EQUALS(stdfStr.to_string(), "0,-1,-2,-3,-4,-5,-6,-7,-8,-9,-10,-11,-12,-13,-14,-15,-16,-17,-18,-19,-20,-21,-22,-23,-24,-25,-26,-27,-28,-29,-30,-31,-32,-33,-34,-35,-36,-37,-38,-39,-40,-41,-42,-43,-44,-45,-46,-47,-48,-49,-50,-51,-52,-53,-54,-55,-56,-57,-58,-59,-60,-61,-62,-63,-64,-65,-66,-67,-68,-69,-70,-71,-72,-73,-74,-75,-76,-77,-78,-79,-80,-81,-82,-83,-84,-85,-86,-87,-88,-89,-90,-91,-92,-93,-94,-95,-96,-97,-98,-99");
      stdfStr.clear();
      TS_ASSERT_EQUALS(stdfStr.to_string(), "");
    }

    void testConstructor4()
    {
      const size_t size = 100;
      JxTYPE<R4> stdfStr;
      R4 data[size];
      for(size_t i = 0; i < size; i++)
      {
        data[i] = ((float)i)/100;
        stdfStr.add(data[i]);
      }
      TS_ASSERT_EQUALS(stdfStr.size(), size);
      TS_ASSERT_EQUALS(stdfStr.storage(), 4*size);
      TS_ASSERT_EQUALS(stdfStr[88].getValue(), data[88].getValue());
      TS_ASSERT_EQUALS(stdfStr[88].to_string(), data[88].to_string());
      TS_ASSERT_EQUALS(stdfStr[99].getValue(), data[99].getValue());
      TS_ASSERT_EQUALS(stdfStr[99].to_string(), data[99].to_string());
      TS_ASSERT_EQUALS(stdfStr.to_string(), "0,0.01,0.02,0.03,0.04,0.05,0.06,0.07,0.08,0.09,0.1,0.11,0.12,0.13,0.14,0.15,0.16,0.17,0.18,0.19,0.2,0.21,0.22,0.23,0.24,0.25,0.26,0.27,0.28,0.29,0.3,0.31,0.32,0.33,0.34,0.35,0.36,0.37,0.38,0.39,0.4,0.41,0.42,0.43,0.44,0.45,0.46,0.47,0.48,0.49,0.5,0.51,0.52,0.53,0.54,0.55,0.56,0.57,0.58,0.59,0.6,0.61,0.62,0.63,0.64,0.65,0.66,0.67,0.68,0.69,0.7,0.71,0.72,0.73,0.74,0.75,0.76,0.77,0.78,0.79,0.8,0.81,0.82,0.83,0.84,0.85,0.86,0.87,0.88,0.89,0.9,0.91,0.92,0.93,0.94,0.95,0.96,0.97,0.98,0.99");
      stdfStr.clear();
      TS_ASSERT_EQUALS(stdfStr.to_string(), "");
    }

    void testWriteRead1()
    {
      const char *filename = "TestJxR4.testWriteRead1.txt";

      const size_t size = 1;

      JxTYPE<R4> stdfStrIn(size);
      std::ofstream outfile(filename, std::ofstream::binary);
      stdfStrIn.write(outfile);
      outfile.close();

      JxTYPE<R4> stdfStrOut;
      std::ifstream infile(filename, std::ifstream::binary);
      stdfStrOut.read(infile, size);
      outfile.close();

      TS_ASSERT_EQUALS(stdfStrIn.to_string(), stdfStrOut.to_string())
    }

    void testWriteRead2()
    {
      const char *filename = "TestJxR4.testWriteRead2.txt";

      const size_t size = 10;

      JxTYPE<R4> stdfStrIn(size);
      std::ofstream outfile(filename, std::ofstream::binary);
      stdfStrIn.write(outfile);
      outfile.close();

      JxTYPE<R4> stdfStrOut;
      std::ifstream infile(filename, std::ifstream::binary);
      stdfStrOut.read(infile, size);
      outfile.close();

      TS_ASSERT_EQUALS(stdfStrIn.to_string(), stdfStrOut.to_string())
    }

    void testWriteRead3()
    {
      const char *filename = "TestJxR4.testWriteRead3.txt";

      const size_t size = 20;
      R4 data[size];

      JxTYPE<R4> stdfStrIn;
      for(size_t i = 0; i < size; i++)
      {
        data[i] = i;
        stdfStrIn.add(data[i]);
      }
      std::ofstream outfile(filename, std::ofstream::binary);
      stdfStrIn.write(outfile);
      outfile.close();

      JxTYPE<R4> stdfStrOut;
      std::ifstream infile(filename, std::ifstream::binary);
      stdfStrOut.read(infile, size);
      outfile.close();

      TS_ASSERT_EQUALS(stdfStrIn.to_string(), stdfStrOut.to_string())
      TS_ASSERT_EQUALS(stdfStrIn.to_string(), "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19");
      TS_ASSERT_EQUALS(stdfStrOut.to_string(), "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19");
    }

};
