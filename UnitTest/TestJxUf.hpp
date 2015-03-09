#include <cxxtest/TestSuite.h>

#include "DataTypes.hpp"

class TestJxUf : public CxxTest::TestSuite 
{
  private:
    typedef Uf<1> Uf1;
    typedef Uf<2> Uf2;
    typedef Uf<4> Uf4;
    typedef Uf<8> Uf8;

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
      JxTYPE<Uf1> stdfStr(size);
      TS_ASSERT_EQUALS(stdfStr.size(), size);
      TS_ASSERT_EQUALS(stdfStr.storage(), size);
      TS_ASSERT_EQUALS(stdfStr.to_string(), "");
    }

    void testConstructor1()
    {
      const size_t size = 10;
      JxTYPE<Uf1> stdfStr(size);
      TS_ASSERT_EQUALS(stdfStr.size(), size);
      TS_ASSERT_EQUALS(stdfStr.storage(), size);
      std::stringstream ss; for(size_t i = 0; i < size-1; i++) ss << "0,"; ss << "0";
      TS_ASSERT_EQUALS(stdfStr.to_string(), ss.str());
    }

    void testConstructor2()
    {
      const size_t size = 100;
      JxTYPE<Uf1> stdfStr(size);
      Uf1 data[size];
      for(size_t i = 0; i < size; i++)
      {
        stdfStr[i] = data[i] = i;
      }

      TS_ASSERT_EQUALS(stdfStr.size(), size);
      TS_ASSERT_EQUALS(stdfStr.storage(), size);
      for(size_t i = 0; i < size; i++)
      {
        TS_ASSERT_EQUALS((stdfStr[i]).getValue(), data[i].getValue());
        TS_ASSERT_EQUALS(stdfStr[i].to_string(), data[i].to_string());
      }
      std::stringstream ss; for(size_t i = 0; i < size-1; i++) ss << i << ','; ss << size-1;
      TS_ASSERT_EQUALS(stdfStr.to_string(), ss.str());
      stdfStr.clear();
      TS_ASSERT_EQUALS(stdfStr.to_string(), "");
    }

    void testCopyConstructor1()
    {
      const size_t size = 100;
      JxTYPE<Uf1> source(size);
      Uf1 data[size];
      for(size_t i = 0; i < size; i++)
      {
        source[i] = data[i] = i;
      }
      JxTYPE<Uf1> stdfStr(source);

      for(size_t i = 0; i < size; i++)
      {
        TS_ASSERT_EQUALS((stdfStr[i]).getValue(), data[i].getValue());
        TS_ASSERT_EQUALS(stdfStr[i].to_string(), data[i].to_string());
      }
      std::stringstream ss; for(size_t i = 0; i < size-1; i++) ss << i << ','; ss << size-1;
      TS_ASSERT_EQUALS(stdfStr.to_string(), ss.str());
      TS_ASSERT_EQUALS(source.to_string(), ss.str());
      stdfStr.clear();
      TS_ASSERT_EQUALS(source.to_string(), ss.str());
      source = stdfStr;
      ss.str("");
      TS_ASSERT_EQUALS(stdfStr.to_string(), ss.str());
      TS_ASSERT_EQUALS(source.to_string(), ss.str());
    }

    void testClone1()
    {
      const size_t size = 100;
      JxTYPE<Uf1> source(size);
      Uf1 data[size];
      for(size_t i = 0; i < size; i++)
      {
        source[i] = data[i] = i;
      }
      DataType::DataTypeSharedPtr stdfStr = source.clone();

      std::stringstream ss; for(size_t i = 0; i < size-1; i++) ss << i << ','; ss << size-1;
      TS_ASSERT_EQUALS(stdfStr->to_string(), ss.str());
      TS_ASSERT_EQUALS(source.to_string(), ss.str());
      stdfStr->clear();
      TS_ASSERT_EQUALS(source.to_string(), ss.str());
      source = *(boost::dynamic_pointer_cast<JxTYPE<Uf1>, DataType>(stdfStr));
      ss.str("");
      TS_ASSERT_EQUALS(stdfStr->to_string(), ss.str());
      TS_ASSERT_EQUALS(source.to_string(), ss.str());
    }

    void testWriteRead11()
    {
      const char *filename = "TestJxUf.testWriteRead11.txt";

      const size_t size = 1;

      JxTYPE<Uf1> stdfStrIn(size);
      std::ofstream outfile(filename, std::ofstream::binary);
      stdfStrIn.write(outfile);
      outfile.close();

      JxTYPE<Uf1> stdfStrOut;
      std::ifstream infile(filename, std::ifstream::binary);
      stdfStrOut.read(infile, size);
      outfile.close();

      for(size_t i = 0; i < size; i++)
      {
        TS_ASSERT_EQUALS(stdfStrIn[i].getValue(), stdfStrOut[i].getValue());
        TS_ASSERT_EQUALS(stdfStrIn[i].to_string(), stdfStrOut[i].to_string());
        TS_ASSERT_EQUALS(stdfStrIn[i].storage(), stdfStrOut[i].storage());
      }
      TS_ASSERT_EQUALS(stdfStrIn.size(), stdfStrOut.size());
      TS_ASSERT_EQUALS(stdfStrIn.storage(), stdfStrOut.storage());
      TS_ASSERT_EQUALS(stdfStrIn.to_string(), stdfStrOut.to_string())
    }

    void testWriteRead21()
    {
      const char *filename = "TestJxUf.testWriteRead21.txt";

      const size_t size = 1;

      JxTYPE<Uf2> stdfStrIn(size);
      std::ofstream outfile(filename, std::ofstream::binary);
      stdfStrIn.write(outfile);
      outfile.close();

      JxTYPE<Uf2> stdfStrOut;
      std::ifstream infile(filename, std::ifstream::binary);
      stdfStrOut.read(infile, size);
      outfile.close();

      for(size_t i = 0; i < size; i++)
      {
        TS_ASSERT_EQUALS(stdfStrIn[i].getValue(), stdfStrOut[i].getValue());
        TS_ASSERT_EQUALS(stdfStrIn[i].to_string(), stdfStrOut[i].to_string());
        TS_ASSERT_EQUALS(stdfStrIn[i].storage(), stdfStrOut[i].storage());
      }
      TS_ASSERT_EQUALS(stdfStrIn.size(), stdfStrOut.size());
      TS_ASSERT_EQUALS(stdfStrOut.storage(), stdfStrOut.storage());
      TS_ASSERT_EQUALS(stdfStrIn.to_string(), stdfStrOut.to_string())
    }

    void testWriteRead41()
    {
      const char *filename = "TestJxUf.testWriteRead41.txt";

      const size_t size = 1;

      JxTYPE<Uf4> stdfStrIn(size);
      std::ofstream outfile(filename, std::ofstream::binary);
      stdfStrIn.write(outfile);
      outfile.close();

      JxTYPE<Uf4> stdfStrOut;
      std::ifstream infile(filename, std::ifstream::binary);
      stdfStrOut.read(infile, size);
      outfile.close();

      for(size_t i = 0; i < size; i++)
      {
        TS_ASSERT_EQUALS(stdfStrIn[i].getValue(), stdfStrOut[i].getValue());
        TS_ASSERT_EQUALS(stdfStrIn[i].to_string(), stdfStrOut[i].to_string());
        TS_ASSERT_EQUALS(stdfStrIn[i].storage(), stdfStrOut[i].storage());
      }
      TS_ASSERT_EQUALS(stdfStrIn.size(), stdfStrOut.size());
      TS_ASSERT_EQUALS(stdfStrOut.storage(), stdfStrOut.storage());
      TS_ASSERT_EQUALS(stdfStrIn.to_string(), stdfStrOut.to_string())
    }

    void testWriteRead81()
    {
      const char *filename = "TestJxUf.testWriteRead81.txt";

      const size_t size = 1;

      JxTYPE<Uf8> stdfStrIn(size);
      std::ofstream outfile(filename, std::ofstream::binary);
      stdfStrIn.write(outfile);
      outfile.close();

      JxTYPE<Uf8> stdfStrOut;
      std::ifstream infile(filename, std::ifstream::binary);
      stdfStrOut.read(infile, size);
      outfile.close();

      for(size_t i = 0; i < size; i++)
      {
        TS_ASSERT_EQUALS(stdfStrIn[i].getValue(), stdfStrOut[i].getValue());
        TS_ASSERT_EQUALS(stdfStrIn[i].to_string(), stdfStrOut[i].to_string());
        TS_ASSERT_EQUALS(stdfStrIn[i].storage(), stdfStrOut[i].storage());
      }
      TS_ASSERT_EQUALS(stdfStrIn.size(), stdfStrOut.size());
      TS_ASSERT_EQUALS(stdfStrOut.storage(), stdfStrOut.storage());
      TS_ASSERT_EQUALS(stdfStrIn.to_string(), stdfStrOut.to_string())
    }

    void testWriteRead12()
    {
      const char *filename = "TestJxUf.testWriteRead12.txt";

      const size_t size = 10;

      JxTYPE<Uf1> stdfStrIn(size);
      std::ofstream outfile(filename, std::ofstream::binary);
      stdfStrIn.write(outfile);
      outfile.close();

      JxTYPE<Uf1> stdfStrOut;
      std::ifstream infile(filename, std::ifstream::binary);
      stdfStrOut.read(infile, size);
      outfile.close();

      for(size_t i = 0; i < size; i++)
      {
        TS_ASSERT_EQUALS(stdfStrIn[i].getValue(), stdfStrOut[i].getValue());
        TS_ASSERT_EQUALS(stdfStrIn[i].to_string(), stdfStrOut[i].to_string());
        TS_ASSERT_EQUALS(stdfStrIn[i].storage(), stdfStrOut[i].storage());
      }
      TS_ASSERT_EQUALS(stdfStrIn.size(), stdfStrOut.size());
      TS_ASSERT_EQUALS(stdfStrOut.storage(), stdfStrOut.storage());
      TS_ASSERT_EQUALS(stdfStrIn.to_string(), stdfStrOut.to_string())
    }

    void testWriteRead22()
    {
      const char *filename = "TestJxUf.testWriteRead22.txt";

      const size_t size = 10;

      JxTYPE<Uf2> stdfStrIn(size);
      std::ofstream outfile(filename, std::ofstream::binary);
      stdfStrIn.write(outfile);
      outfile.close();

      JxTYPE<Uf2> stdfStrOut;
      std::ifstream infile(filename, std::ifstream::binary);
      stdfStrOut.read(infile, size);
      outfile.close();

      for(size_t i = 0; i < size; i++)
      {
        TS_ASSERT_EQUALS(stdfStrIn[i].getValue(), stdfStrOut[i].getValue());
        TS_ASSERT_EQUALS(stdfStrIn[i].to_string(), stdfStrOut[i].to_string());
        TS_ASSERT_EQUALS(stdfStrIn[i].storage(), stdfStrOut[i].storage());
      }
      TS_ASSERT_EQUALS(stdfStrIn.size(), stdfStrOut.size());
      TS_ASSERT_EQUALS(stdfStrOut.storage(), stdfStrOut.storage());
      TS_ASSERT_EQUALS(stdfStrIn.to_string(), stdfStrOut.to_string())
    }

    void testWriteRead42()
    {
      const char *filename = "TestJxUf.testWriteRead42.txt";

      const size_t size = 10;

      JxTYPE<Uf4> stdfStrIn(size);
      std::ofstream outfile(filename, std::ofstream::binary);
      stdfStrIn.write(outfile);
      outfile.close();

      JxTYPE<Uf4> stdfStrOut;
      std::ifstream infile(filename, std::ifstream::binary);
      stdfStrOut.read(infile, size);
      outfile.close();

      for(size_t i = 0; i < size; i++)
      {
        TS_ASSERT_EQUALS(stdfStrIn[i].getValue(), stdfStrOut[i].getValue());
        TS_ASSERT_EQUALS(stdfStrIn[i].to_string(), stdfStrOut[i].to_string());
        TS_ASSERT_EQUALS(stdfStrIn[i].storage(), stdfStrOut[i].storage());
      }
      TS_ASSERT_EQUALS(stdfStrIn.size(), stdfStrOut.size());
      TS_ASSERT_EQUALS(stdfStrOut.storage(), stdfStrOut.storage());
      TS_ASSERT_EQUALS(stdfStrIn.to_string(), stdfStrOut.to_string())
    }

    void testWriteRead82()
    {
      const char *filename = "TestJxUf.testWriteRead82.txt";

      const size_t size = 10;

      JxTYPE<Uf8> stdfStrIn(size);
      std::ofstream outfile(filename, std::ofstream::binary);
      stdfStrIn.write(outfile);
      outfile.close();

      JxTYPE<Uf8> stdfStrOut;
      std::ifstream infile(filename, std::ifstream::binary);
      stdfStrOut.read(infile, size);
      outfile.close();

      for(size_t i = 0; i < size; i++)
      {
        TS_ASSERT_EQUALS(stdfStrIn[i].getValue(), stdfStrOut[i].getValue());
        TS_ASSERT_EQUALS(stdfStrIn[i].to_string(), stdfStrOut[i].to_string());
        TS_ASSERT_EQUALS(stdfStrIn[i].storage(), stdfStrOut[i].storage());
      }
      TS_ASSERT_EQUALS(stdfStrIn.size(), stdfStrOut.size());
      TS_ASSERT_EQUALS(stdfStrOut.storage(), stdfStrOut.storage());
      TS_ASSERT_EQUALS(stdfStrIn.to_string(), stdfStrOut.to_string())
    }

    void testWriteRead13()
    {
      const char *filename = "TestJxUf.testWriteRead13.txt";

      const size_t size = 20;
      Uf1 data[size];

      JxTYPE<Uf1> stdfStrIn(size);
      for(size_t i = 0; i < size; i++)
      {
        stdfStrIn[i] = data[i] = i;
      }
      std::ofstream outfile(filename, std::ofstream::binary);
      stdfStrIn.write(outfile);
      outfile.close();

      JxTYPE<Uf1> stdfStrOut;
      std::ifstream infile(filename, std::ifstream::binary);
      stdfStrOut.read(infile, size);
      outfile.close();

      for(size_t i = 0; i < size; i++)
      {
        TS_ASSERT_EQUALS(stdfStrIn[i].getValue(), data[i].getValue());
        TS_ASSERT_EQUALS(stdfStrIn[i].to_string(), data[i].to_string());
        TS_ASSERT_EQUALS(stdfStrIn[i].storage(), data[i].storage());
        TS_ASSERT_EQUALS(stdfStrIn[i].getValue(), stdfStrOut[i].getValue());
        TS_ASSERT_EQUALS(stdfStrIn[i].to_string(), stdfStrOut[i].to_string());
        TS_ASSERT_EQUALS(stdfStrIn[i].storage(), stdfStrOut[i].storage());
      }
      TS_ASSERT_EQUALS(stdfStrOut.storage(), stdfStrOut.storage());
      TS_ASSERT_EQUALS(stdfStrIn.storage(), size);
      TS_ASSERT_EQUALS(stdfStrOut.storage(), size);
      TS_ASSERT_EQUALS(stdfStrIn.to_string(), stdfStrOut.to_string())
      std::stringstream ss; for(size_t i = 0; i < size-1; i++) ss << i << ','; ss << size-1;
      TS_ASSERT_EQUALS(stdfStrIn.to_string(), ss.str());
      TS_ASSERT_EQUALS(stdfStrOut.to_string(), ss.str());
    }

    void testWriteRead23()
    {
      const char *filename = "TestJxUf.testWriteRead23.txt";

      const size_t size = 20;
      Uf2 data[size];

      JxTYPE<Uf2> stdfStrIn(size);
      for(size_t i = 0; i < size; i++)
      {
        stdfStrIn[i] = data[i] = i;
      }
      std::ofstream outfile(filename, std::ofstream::binary);
      stdfStrIn.write(outfile);
      outfile.close();

      JxTYPE<Uf2> stdfStrOut;
      std::ifstream infile(filename, std::ifstream::binary);
      stdfStrOut.read(infile, size);
      outfile.close();

      for(size_t i = 0; i < size; i++)
      {
        TS_ASSERT_EQUALS(stdfStrIn[i].getValue(), data[i].getValue());
        TS_ASSERT_EQUALS(stdfStrIn[i].to_string(), data[i].to_string());
        TS_ASSERT_EQUALS(stdfStrIn[i].storage(), data[i].storage());
        TS_ASSERT_EQUALS(stdfStrIn[i].getValue(), stdfStrOut[i].getValue());
        TS_ASSERT_EQUALS(stdfStrIn[i].to_string(), stdfStrOut[i].to_string());
        TS_ASSERT_EQUALS(stdfStrIn[i].storage(), stdfStrOut[i].storage());
      }
      TS_ASSERT_EQUALS(stdfStrOut.storage(), stdfStrOut.storage());
      TS_ASSERT_EQUALS(stdfStrIn.storage(), 2*size);
      TS_ASSERT_EQUALS(stdfStrOut.storage(), 2*size);
      TS_ASSERT_EQUALS(stdfStrIn.to_string(), stdfStrOut.to_string())
      std::stringstream ss; for(size_t i = 0; i < size-1; i++) ss << i << ','; ss << size-1;
      TS_ASSERT_EQUALS(stdfStrIn.to_string(), ss.str());
      TS_ASSERT_EQUALS(stdfStrOut.to_string(), ss.str());
    }

    void testWriteRead43()
    {
      const char *filename = "TestJxUf.testWriteRead43.txt";

      const size_t size = 20;
      Uf4 data[size];

      JxTYPE<Uf4> stdfStrIn(size);
      for(size_t i = 0; i < size; i++)
      {
        stdfStrIn[i] = data[i] = i;
      }
      std::ofstream outfile(filename, std::ofstream::binary);
      stdfStrIn.write(outfile);
      outfile.close();

      JxTYPE<Uf4> stdfStrOut;
      std::ifstream infile(filename, std::ifstream::binary);
      stdfStrOut.read(infile, size);
      outfile.close();

      for(size_t i = 0; i < size; i++)
      {
        TS_ASSERT_EQUALS(stdfStrIn[i].getValue(), data[i].getValue());
        TS_ASSERT_EQUALS(stdfStrIn[i].to_string(), data[i].to_string());
        TS_ASSERT_EQUALS(stdfStrIn[i].storage(), data[i].storage());
        TS_ASSERT_EQUALS(stdfStrIn[i].getValue(), stdfStrOut[i].getValue());
        TS_ASSERT_EQUALS(stdfStrIn[i].to_string(), stdfStrOut[i].to_string());
        TS_ASSERT_EQUALS(stdfStrIn[i].storage(), stdfStrOut[i].storage());
      }
      TS_ASSERT_EQUALS(stdfStrOut.storage(), stdfStrOut.storage());
      TS_ASSERT_EQUALS(stdfStrIn.storage(), 4*size);
      TS_ASSERT_EQUALS(stdfStrOut.storage(), 4*size);
      TS_ASSERT_EQUALS(stdfStrIn.to_string(), stdfStrOut.to_string())
      std::stringstream ss; for(size_t i = 0; i < size-1; i++) ss << i << ','; ss << size-1;
      TS_ASSERT_EQUALS(stdfStrIn.to_string(), ss.str());
      TS_ASSERT_EQUALS(stdfStrOut.to_string(), ss.str());
    }

    void testWriteRead83()
    {
      const char *filename = "TestJxUf.testWriteRead83.txt";

      const size_t size = 20;
      Uf8 data[size];

      JxTYPE<Uf8> stdfStrIn(size);
      for(size_t i = 0; i < size; i++)
      {
        stdfStrIn[i] = data[i] = i;
      }
      std::ofstream outfile(filename, std::ofstream::binary);
      stdfStrIn.write(outfile);
      outfile.close();

      JxTYPE<Uf8> stdfStrOut;
      std::ifstream infile(filename, std::ifstream::binary);
      stdfStrOut.read(infile, size);
      outfile.close();

      for(size_t i = 0; i < size; i++)
      {
        TS_ASSERT_EQUALS(stdfStrIn[i].getValue(), data[i].getValue());
        TS_ASSERT_EQUALS(stdfStrIn[i].to_string(), data[i].to_string());
        TS_ASSERT_EQUALS(stdfStrIn[i].storage(), data[i].storage());
        TS_ASSERT_EQUALS(stdfStrIn[i].getValue(), stdfStrOut[i].getValue());
        TS_ASSERT_EQUALS(stdfStrIn[i].to_string(), stdfStrOut[i].to_string());
        TS_ASSERT_EQUALS(stdfStrIn[i].storage(), stdfStrOut[i].storage());
      }
      TS_ASSERT_EQUALS(stdfStrOut.storage(), stdfStrOut.storage());
      TS_ASSERT_EQUALS(stdfStrIn.storage(), 8*size);
      TS_ASSERT_EQUALS(stdfStrOut.storage(), 8*size);
      TS_ASSERT_EQUALS(stdfStrIn.to_string(), stdfStrOut.to_string())
      std::stringstream ss; for(size_t i = 0; i < size-1; i++) ss << i << ','; ss << size-1;
      TS_ASSERT_EQUALS(stdfStrIn.to_string(), ss.str());
      TS_ASSERT_EQUALS(stdfStrOut.to_string(), ss.str());
    }

    void testWriteReadxx()
    {
      const char *filename = "TestJxUf.testWriteReadxx.txt";

      const size_t size = 20;
      Uf4 data[size];

      JxTYPE<Uf4> stdfStrIn(size);
      for(size_t i = 0; i < size; i++)
      {
        stdfStrIn[i] = data[i] = i+0xFFFF;
      }
      std::ofstream outfile(filename, std::ofstream::binary);
      stdfStrIn.write(outfile);
      outfile.close();

      JxTYPE<Uf4> stdfStrOut;
      std::ifstream infile(filename, std::ifstream::binary);
      stdfStrOut.read(infile, size);
      outfile.close();

      for(size_t i = 0; i < size; i++)
      {
        TS_ASSERT_EQUALS(stdfStrIn[i].getValue(), data[i].getValue());
        TS_ASSERT_EQUALS(stdfStrIn[i].to_string(), data[i].to_string());
        TS_ASSERT_EQUALS(stdfStrIn[i].storage(), data[i].storage());
        TS_ASSERT_EQUALS(stdfStrIn[i].getValue(), stdfStrOut[i].getValue());
        TS_ASSERT_EQUALS(stdfStrIn[i].to_string(), stdfStrOut[i].to_string());
        TS_ASSERT_EQUALS(stdfStrIn[i].storage(), stdfStrOut[i].storage());
      }
      TS_ASSERT_EQUALS(stdfStrIn.to_string(), stdfStrOut.to_string())
      std::stringstream ss; for(size_t i = 0; i < size-1; i++) ss << i+0xFFFF << ','; ss << size-1+0xFFFF;
      TS_ASSERT_EQUALS(stdfStrIn.to_string(), ss.str());
      TS_ASSERT_EQUALS(stdfStrOut.to_string(), ss.str());
    }

};
