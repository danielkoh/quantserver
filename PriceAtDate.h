#pragma once

#include <string>
#include <boost/shared_ptr.hpp>
#include "ql/time/date.hpp"
#include "ScriptManager.h"

namespace quantserver
{
	typedef long double BIGDECIMAL  ;
	typedef boost::shared_ptr<QuantLib::Date> DatePtr;

	class PriceAtDate
	{
		public:
			static ScriptManager& chai(ScriptManager& scriptManager);

			PriceAtDate(void);
			PriceAtDate(DatePtr& datePtr , const std::string& valueString);
			PriceAtDate(DatePtr& datePtr , const BIGDECIMAL& value);
			PriceAtDate(const std::string& datestr , const std::string& valueString);
			PriceAtDate(const PriceAtDate& copy);
			virtual ~PriceAtDate(void);

			QuantLib::Date& getDate();
			DatePtr& getPointerToDate();
			BIGDECIMAL& getPrice();
			BIGDECIMAL& val();


			//Some math operations
			PriceAtDate log();
			PriceAtDate exp();

			//Operator overloads			
			//Binary modifying
			PriceAtDate& operator=(const PriceAtDate& rhs);
			PriceAtDate& operator=(const BIGDECIMAL& rhs);
			PriceAtDate& operator+=(const PriceAtDate& rhs);
			PriceAtDate& operator+=(const BIGDECIMAL& rhs);
			PriceAtDate& operator-=(const PriceAtDate& rhs);
			PriceAtDate& operator-=(const BIGDECIMAL& rhs);
			PriceAtDate& operator/=(const PriceAtDate& rhs);
			PriceAtDate& operator/=(const BIGDECIMAL& rhs);
			PriceAtDate& operator*=(const PriceAtDate& rhs);
			PriceAtDate& operator*=(const BIGDECIMAL& rhs);
			
			//Unary non modifying
			PriceAtDate operator-();

			//Binary non modifying
			PriceAtDate operator+(const PriceAtDate& rhs);
			PriceAtDate operator+(const BIGDECIMAL& rhs);
			PriceAtDate operator-(const PriceAtDate& rhs);
			PriceAtDate operator-(const BIGDECIMAL& rhs);
			PriceAtDate operator*(const PriceAtDate& rhs);
			PriceAtDate operator*(const BIGDECIMAL& rhs);
			PriceAtDate operator/(const PriceAtDate& rhs);
			PriceAtDate operator/(const BIGDECIMAL& rhs);

			//Binary comparison
			bool  operator==(const PriceAtDate& rhs);
			bool  operator>(const PriceAtDate& rhs);
			bool  operator>=(const PriceAtDate& rhs);
			bool  operator<(const PriceAtDate& rhs);
			bool  operator<=(const PriceAtDate& rhs);

			//Date parsing
			static DatePtr parseDate(const std::string& datestr , std::string formatString = "dd/mm/yyyy");
			static DatePtr parseDateIso(const std::string& datestr);

		protected:
			DatePtr date ;
			BIGDECIMAL price ;
	};
}

