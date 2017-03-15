
#include <Rcpp.h>
#include <vector>
#include <string>
#include "libzippp/src/libzippp.h"

using namespace libzippp;
using namespace Rcpp;
using namespace std;

// use C++11 here but does not seem to work, instead we use the Makevars to specify C++11 with PKG_CXXFLAGS = -std=c++11
// [[Rcpp::plugins("cpp11")]]

/*
unzips testfile.txt from test.zip
and puts it in a string
 int main(int argc, char *argv[]) {
 string string_buffer = readZipFile("test.zip", "testfile.txt");
 cout << string_buffer << endl;
 return 0;
 }
 foo <- readMatrixFromZip("GeneSurvey.zip", "combined/illuminahiseq_mirnaseq_isoform/platform.tsv")
 foo <- readMatrixFromZip("GeneSurvey.zip", "combined/genome_wide_snp_6_hg19nocnvWxy/platform.tsv")
 foo[1:4,1:4]
 bar <- read.csv("platform.tsv",header=TRUE, sep="\t", as.is=TRUE, check.names=FALSE, stringsAsFactors=FALSE)
 bar[1:4,1:5]
 */

void split( vector<string> & theStringVector,  /* Altered/returned value */
          const  string  & theString, const  string  & theDelimiter)
{
  size_t  start = 0, end = 0;
  while ( end != string::npos)
  {
    end = theString.find( theDelimiter, start);
    // If at end, use length=maxLength.  Else use length=end-start.
    theStringVector.push_back( theString.substr( start, (end == string::npos) ? string::npos : end - start));
    // If at end, use start=maxSize.  Else use start=end+delimiter.
    start = (   ( end > (string::npos - theDelimiter.size()) ) ?  string::npos  :  end + theDelimiter.size());
  }
}

// [[Rcpp::export]]
NumericMatrix readMatrixFromZip(const std::string & theZipFile, const std::string & theMatrixFile)
{
  Rcout << "ReadMatrixRcpp 2017-03-13-1630" << std::endl;
  //CharacterVector x = CharacterVector::create( "foo", "bar" )  ;
  //NumericVector y   = NumericVector::create( 0.0, 1.0 ) ;
  //List z            = List::create( x, y ) ;

  ZipArchive zf(theZipFile);
  zf.open(ZipArchive::READ_ONLY);
  string wantFile = theMatrixFile;

  vector<ZipEntry> entries = zf.getEntries();
  vector<ZipEntry>::iterator it;
  for(it=entries.begin() ; it!=entries.end(); ++it)
  {
    ZipEntry entry = *it;
    string name = entry.getName();
    if (0==name.compare(wantFile))
    {
      int size(entry.getSize());
      //Rcout << "Before Doc:" << name << std::endl;
      //Rcout << textData << std::endl;
      vector<string> textVector;
      // scope for memory
      {
        //the length of textData will be size
        string textData = entry.readAsText();
        split(textVector, textData, "\n");
      }
      long lines(0);
      long columns(0);
      //for(auto lineString : textVector)
      for(vector<string>::const_iterator i = textVector.begin(); i != textVector.end(); ++i)
      {
        if (0!=(*i).compare(""))
        {
          if (0==columns)
          {
            vector<string> columnVector;
            split(columnVector, *i, "\t");
            columns = columnVector.size();
          }
          lines += 1;
        }
        else
        {
          //Rcout << "skip empty line" << std::endl;
        }
      }
      //Rcout << "columns1:" << columns << std::endl;
      //Rcout << "lines1:" << lines << std::endl;
      NumericMatrix returnMatrix(lines-1, columns-1);
      Rcpp::CharacterVector rowNames(lines-1);
      Rcpp::CharacterVector colNames(columns-1);
      bool didColNames(false);
      lines = 0;
      long rows(0);
      columns = 0;
      for(vector<string>::const_iterator i = textVector.begin(); i != textVector.end(); ++i)
      {
        if (0!=(*i).compare(""))
        {
          lines += 1;
          //Rcout << "top of for" << std::endl;
          vector<string> columnVector;
          split(columnVector, *i, "\t");
          if (false==didColNames)
          {
            //Rcout << "false==didColNames" << std::endl;
            for(vector<string>::const_iterator x = columnVector.begin(); x != columnVector.end(); ++x)
            {
              //Rcout << "push" << std::endl;
              if (x!=columnVector.begin())
              {
                colNames[columns] = *x;
                columns += 1;
                //Rcout << "loop colNames:" << colNames.size() << std::endl;
                //Rcout << "colNames:" << colNames << std::endl;
              }
            }
            didColNames = true;
          }
          else
          {
            //Rcout << "true==didColNames" << std::endl;
            long matrixCol(0);
            for(vector<string>::const_iterator x = columnVector.begin(); x != columnVector.end(); ++x)
            {
              //Rcout << "push" << std::endl;
              if (x!=columnVector.begin())
              {
                returnMatrix(rows,matrixCol) = std::stod(*x);
                matrixCol += 1;
              }
              else
              {
                rowNames[rows] = *x;
              }
            }
            rows += 1;
          }
        }
      }
      // set rows and columns
      Rcpp::List dimnms = Rcpp::List::create(rowNames, colNames);
      returnMatrix.attr("dimnames") = dimnms;
      //
      //Rcout << "lines3:" << lines << std::endl;
      //Rcout << "colNames:" << colNames.size() << std::endl;
      //Rcout << "rowNames:" << rowNames.size() << std::endl;
      //Rcout << "manual col:9695" << std::endl;
      //Rcout << "manual row:980" << std::endl;
      //Rcout << "rowNames:" << rowNames << std::endl;
      //Rcout << "textVector.size()=" << textVector.size() << std::endl;
/*      long backN = 0;
      long backR = 0;
      for(std::string::size_type i = 0; i < textData.size(); ++i)
      {
        //Rcout << textData[i];
        if ('\r'==textData[i])
        {
          backR += 1;
        }
        if ('\n'==textData[i])
        {
          backN += 1;
        }
      }
      Rcout << "backR:" << backR << std::endl;
      Rcout << "backN:" << backN << std::endl;*/
      //Rcout << "After Doc:" << name << std::endl;

      zf.close();
      Rcout << "returnMatrix" << std::endl;
      //Rcout << returnMatrix(1,1) << std::endl;
      //return z ;
      return returnMatrix ;

    }

  }
  Rcout << "matrix file not found" << std::endl;
  zf.close();
  return NumericMatrix();
}
