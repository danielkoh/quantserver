#include "CSVParser.h"

#include <boost/tokenizer.hpp>
#include <iostream>
#include <fstream>

using namespace boost;
using namespace quantserver;

CSVParser::CSVParser(const std::string& filename , int minimalNumberOfTokensToAccept, bool hasHeaders)
{
	parseCsvFile(filename , minimalNumberOfTokensToAccept , hasHeaders);
}


CSVParser::~CSVParser(void)
{
	data.clear();
}

void CSVParser::parseCsvFile(const std::string& filename , int minimalNumberOfTokensToAccept, bool hasHeaders)
{
	  std::string line;
	  std::ifstream fileToParse (filename);
	  data.clear();

	  if (fileToParse.is_open())
	  {
		  while ( fileToParse.good() )
		  {
			  std::getline(fileToParse,line);
			  PtrStringVector currVector(new std::vector<std::string>);

			  tokenizer<escaped_list_separator<char> > tk(line, escaped_list_separator<char>('\\', ',', '\"'));
			  int elementCount = 0 ;

			  for (tokenizer<escaped_list_separator<char> >::iterator i(tk.begin());i!=tk.end();++i) 
			  {
				  currVector->push_back(*i);
				  elementCount++ ;
			  }


			  if(elementCount >= minimalNumberOfTokensToAccept)
			  {
				  if(!headers && hasHeaders)
				  {
					  headers = currVector;
				  }
				  else
				  {
					  data.push_back(currVector);
				  }
			  }
		  }

	  }

	  if(hasHeaders)
	  {
		std::cout << "Headers parsed: " << headers << std::endl;
	  }
	  std::cout << "data rows read: " << data.size() << std::endl;
}

int CSVParser::getNumberOfColumns()
{
	if(!headers)
	{
		return 0;
	}
	else
	{
		return headers->size();
	}
}

const std::string& CSVParser::getHeaderOfIndex(int index)
{
	return headers->at(index);
}
int CSVParser::getNumberOfLines()
{
	return data.size();
}
PtrStringVector CSVParser::getDataAt(int index)
{
	return data.at(index);
}
