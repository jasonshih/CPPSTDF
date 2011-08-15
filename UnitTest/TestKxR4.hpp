#include <cxxtest/TestSuite.h>

#include <cfloat>
#include "../src/DataTypes.hpp"

class TestKxR4 : public CxxTest::TestSuite 
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
      KxTYPE<R4, size> stdfStr;
      TS_ASSERT_EQUALS(stdfStr.max_size(), size);
      TS_ASSERT_EQUALS(stdfStr.storage(), size);
      TS_ASSERT_EQUALS(stdfStr.to_string(), "");
    }

    void testConstructor1()
    {
      const size_t size = 10;
      KxTYPE<R4, size> stdfStr;
      TS_ASSERT_EQUALS(stdfStr.max_size(), size);
      TS_ASSERT_EQUALS(stdfStr.storage(), 4*size);
      TS_ASSERT_EQUALS(stdfStr.to_string(), "0,0,0,0,0,0,0,0,0,0");
    }

    void testConstructor2()
    {
      const size_t size = 100;
      KxTYPE<R4, size> stdfStr;
      R4 data[size];
      for(size_t i = 0; i < size; i++)
      {
        stdfStr[i] = data[i] = i;
      }
      TS_ASSERT_EQUALS(stdfStr.max_size(), size);
      TS_ASSERT_EQUALS(stdfStr.storage(), 4*size);
      R4 data88 = stdfStr[88];
      TS_ASSERT_EQUALS(data88.getValue(), (float)88);
      TS_ASSERT(isEqual(data88.getValue(), 88));
      TS_ASSERT_EQUALS(data88.to_string(), data[88].to_string());
      R4 data99 = stdfStr[99];
      TS_ASSERT_EQUALS(data99.getValue(), (float)99);
      TS_ASSERT(isEqual(data99.getValue(), 99));
      TS_ASSERT_EQUALS(data99.to_string(), data[99].to_string());
      std::stringstream ss;
      for(size_t i = 0; i < size-1; i++) ss << i << ","; ss << size-1;
      TS_ASSERT_EQUALS(stdfStr.to_string(), ss.str());
      stdfStr.clear();
      ss.str(""); for(size_t i = 0; i < size-1; i++) ss << "0,"; ss << '0';
      TS_ASSERT_EQUALS(stdfStr.to_string(), ss.str());
    }

    void testConstructor3()
    {
      const size_t size = 100;
      KxTYPE<R4, size> stdfStr;
      R4 data[size];
      for(int i = 0; (size_t)i < size; i++)
      {
        stdfStr[i] = data[i] = -i;
      }
      TS_ASSERT_EQUALS(stdfStr.max_size(), size);
      TS_ASSERT_EQUALS(stdfStr.storage(), 4*size);
      R4 data88 = stdfStr[88];
      TS_ASSERT_EQUALS(data88.getValue(), -88);
      TS_ASSERT_EQUALS(data88.to_string(), data[88].to_string());
      R4 data99 = stdfStr[99];
      TS_ASSERT_EQUALS(data99.getValue(), -99);
      TS_ASSERT_EQUALS(data99.to_string(), data[99].to_string());
      TS_ASSERT_EQUALS(stdfStr.to_string(), "0,-1,-2,-3,-4,-5,-6,-7,-8,-9,-10,-11,-12,-13,-14,-15,-16,-17,-18,-19,-20,-21,-22,-23,-24,-25,-26,-27,-28,-29,-30,-31,-32,-33,-34,-35,-36,-37,-38,-39,-40,-41,-42,-43,-44,-45,-46,-47,-48,-49,-50,-51,-52,-53,-54,-55,-56,-57,-58,-59,-60,-61,-62,-63,-64,-65,-66,-67,-68,-69,-70,-71,-72,-73,-74,-75,-76,-77,-78,-79,-80,-81,-82,-83,-84,-85,-86,-87,-88,-89,-90,-91,-92,-93,-94,-95,-96,-97,-98,-99");
      stdfStr.clear();
      TS_ASSERT_EQUALS(stdfStr.to_string(), "0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0");
    }

    void testConstructor4()
    {
      const size_t size = 100;
      KxTYPE<R4, size> stdfStr;
      R4 data[size];
      for(int i = 0; (size_t)i < size; i++)
      {
        stdfStr[i] = data[i] = -i*0.1;
      }
      TS_ASSERT_EQUALS(stdfStr.max_size(), size);
      TS_ASSERT_EQUALS(stdfStr.storage(), 4*size);
      R4 data88 = stdfStr[88];
      TS_ASSERT(isEqual(data88.getValue(), -88));
      TS_ASSERT_EQUALS(data88.getValue(), (float)-8.8);
      TS_ASSERT_EQUALS(data88.to_string(), data[88].to_string());
      R4 data99 = stdfStr[99];
      TS_ASSERT(isEqual(data99.getValue(), -99));
      TS_ASSERT_EQUALS(data99.getValue(), (float)-9.9);
      TS_ASSERT_EQUALS(data99.to_string(), data[99].to_string());
      TS_ASSERT_EQUALS(stdfStr.to_string(), "0,-0.1,-0.2,-0.3,-0.4,-0.5,-0.6,-0.7,-0.8,-0.9,-1,-1.1,-1.2,-1.3,-1.4,-1.5,-1.6,-1.7,-1.8,-1.9,-2,-2.1,-2.2,-2.3,-2.4,-2.5,-2.6,-2.7,-2.8,-2.9,-3,-3.1,-3.2,-3.3,-3.4,-3.5,-3.6,-3.7,-3.8,-3.9,-4,-4.1,-4.2,-4.3,-4.4,-4.5,-4.6,-4.7,-4.8,-4.9,-5,-5.1,-5.2,-5.3,-5.4,-5.5,-5.6,-5.7,-5.8,-5.9,-6,-6.1,-6.2,-6.3,-6.4,-6.5,-6.6,-6.7,-6.8,-6.9,-7,-7.1,-7.2,-7.3,-7.4,-7.5,-7.6,-7.7,-7.8,-7.9,-8,-8.1,-8.2,-8.3,-8.4,-8.5,-8.6,-8.7,-8.8,-8.9,-9,-9.1,-9.2,-9.3,-9.4,-9.5,-9.6,-9.7,-9.8,-9.9");
      stdfStr.clear();
      TS_ASSERT_EQUALS(stdfStr.to_string(), "0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0");
    }

    void testWriteRead1()
    {
      const char *filename = "TestKxR4.testWriteRead1.txt";

      const size_t size = 1;

      KxTYPE<R4, size> stdfStrIn;
      ofstream outfile(filename, ofstream::binary);
      stdfStrIn.write(outfile);
      outfile.close();

      KxTYPE<R4, size> stdfStrOut;
      ifstream infile(filename, ifstream::binary);
      stdfStrOut.read(infile);
      outfile.close();

      TS_ASSERT_EQUALS(stdfStrIn.to_string(), stdfStrOut.to_string())
    }

    void testWriteRead2()
    {
      const char *filename = "TestKxR4.testWriteRead2.txt";

      const size_t size = 10;

      KxTYPE<R4, size> stdfStrIn;
      ofstream outfile(filename, ofstream::binary);
      stdfStrIn.write(outfile);
      outfile.close();

      KxTYPE<R4, size> stdfStrOut;
      ifstream infile(filename, ifstream::binary);
      stdfStrOut.read(infile);
      outfile.close();

      TS_ASSERT_EQUALS(stdfStrIn.to_string(), stdfStrOut.to_string())
    }

    void testWriteRead3()
    {
      const char *filename = "TestKxR4.testWriteRead3.txt";

      const size_t size = 20;
      R4 data[size];

      KxTYPE<R4, size> stdfStrIn;
      for(size_t i = 0; i < size; i++)
      {
        stdfStrIn[i] = data[i] = i;
      }
      ofstream outfile(filename, ofstream::binary);
      stdfStrIn.write(outfile);
      outfile.close();

      KxTYPE<R4, size> stdfStrOut;
      ifstream infile(filename, ifstream::binary);
      stdfStrOut.read(infile);
      outfile.close();

      TS_ASSERT_EQUALS(stdfStrIn.to_string(), stdfStrOut.to_string())
      TS_ASSERT_EQUALS(stdfStrIn.to_string(), "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19");
      TS_ASSERT_EQUALS(stdfStrOut.to_string(), "0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19");
    }

};
