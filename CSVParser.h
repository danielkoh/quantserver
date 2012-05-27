#pragma once

#include <vector>
#include <boost/shared_ptr.hpp>
#include <string>

namespace quantserver
{
	typedef boost::shared_ptr<std::vector<std::string>> PtrStringVector;

	class CSVParser
	{
	public:
		CSVParser(const std::string& filename , int minimalNumberOfTokensToAccept = 2, bool hasHeaders = true );
		virtual ~CSVParser(void);

		const std::string& getHeaderOfIndex(int index);
		int getNumberOfLines();
		int getNumberOfColumns();
		PtrStringVector getDataAt(int index);

	protected:
		PtrStringVector headers;
		std::vector<PtrStringVector> data;
		void parseCsvFile(const std::string& filename , int minimalNumberOfTokensToAccept , bool hasHeaders);
		

	

	};
}

