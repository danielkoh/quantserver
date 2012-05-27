#include "PriceAtDate.h"
#include "ql/utilities/dataparsers.hpp"
#include <boost/lexical_cast.hpp>
#include <math.h>
#include <chaiscript/utility/utility.hpp>

using namespace quantserver;

ScriptManager& PriceAtDate::chai(ScriptManager& scriptManager)
{
	chaiscript::ModulePtr m = chaiscript::ModulePtr(new chaiscript::Module());
	CHAISCRIPT_CLASS( m, 
       PriceAtDate,
       (PriceAtDate())
	   (PriceAtDate (const PriceAtDate &))
	   (PriceAtDate (const std::string&, const std::string&)),
	   ((val))
	   ((getDate))
	   ((getPrice))
	   ((log))
	   ((exp))
	   ((operator=)(PriceAtDate& (PriceAtDate::*)(const PriceAtDate&)))
       ((operator=)(PriceAtDate& (PriceAtDate::*)(const BIGDECIMAL&)))
	   ((operator+=)(PriceAtDate& (PriceAtDate::*)(const PriceAtDate&)))
       ((operator+=)(PriceAtDate& (PriceAtDate::*)(const BIGDECIMAL&)))
	   ((operator-=)(PriceAtDate& (PriceAtDate::*)(const PriceAtDate&)))
       ((operator-=)(PriceAtDate& (PriceAtDate::*)(const BIGDECIMAL&)))
	   ((operator/=)(PriceAtDate& (PriceAtDate::*)(const PriceAtDate&)))
       ((operator/=)(PriceAtDate& (PriceAtDate::*)(const BIGDECIMAL&)))
	   ((operator*=)(PriceAtDate& (PriceAtDate::*)(const PriceAtDate&)))
       ((operator*=)(PriceAtDate& (PriceAtDate::*)(const BIGDECIMAL&)))
	   ((operator+)(PriceAtDate (PriceAtDate::*)(const PriceAtDate&)))
       ((operator+)(PriceAtDate (PriceAtDate::*)(const BIGDECIMAL&)))
	   ((operator-)(PriceAtDate (PriceAtDate::*)(const PriceAtDate&)))
       ((operator-)(PriceAtDate (PriceAtDate::*)(const BIGDECIMAL&)))
	   ((operator*)(PriceAtDate (PriceAtDate::*)(const PriceAtDate&)))
       ((operator*)(PriceAtDate (PriceAtDate::*)(const BIGDECIMAL&)))
	   ((operator/)(PriceAtDate (PriceAtDate::*)(const PriceAtDate&)))
       ((operator/)(PriceAtDate (PriceAtDate::*)(const BIGDECIMAL&)))
	   ((operator-)(PriceAtDate (PriceAtDate::*)()))
	   ((operator==))
	   ((operator>))
	   ((operator>=))
	   ((operator<))
	   ((operator<=))  
     );

	scriptManager.engine().add(m) ;
	return scriptManager ;
}

PriceAtDate::PriceAtDate(void)
{
}

DatePtr PriceAtDate::parseDate(const std::string& datestr, std::string formatString)
{
	QuantLib::Date parsedDate = QuantLib::DateParser::parse(datestr , formatString);
	return DatePtr(new QuantLib::Date(parsedDate));
}

DatePtr PriceAtDate::parseDateIso(const std::string& datestr)
{
	QuantLib::Date parsedDate = QuantLib::DateParser::parseISO(datestr);
	return DatePtr(new QuantLib::Date(parsedDate));
}

PriceAtDate::PriceAtDate(const std::string& datestr , const std::string& valueString)
{
	date = parseDate(datestr);
	price = boost::lexical_cast< BIGDECIMAL >( valueString );
}

PriceAtDate::PriceAtDate(DatePtr& datePtr , const BIGDECIMAL& value)
{
	date = datePtr ;
	price = value;
}

PriceAtDate::PriceAtDate(DatePtr& datePtr , const std::string& valueString)
{
	date = datePtr ;
	price = boost::lexical_cast< BIGDECIMAL >( valueString );

}

PriceAtDate::PriceAtDate(const PriceAtDate& copy)
{
	date = copy.date ;
	price = copy.price ;
}


PriceAtDate::~PriceAtDate(void)
{
	date.reset();
}

DatePtr& PriceAtDate::getPointerToDate()
{
	return date;
}

QuantLib::Date& PriceAtDate::getDate()
{
	return *date ;
}
BIGDECIMAL& PriceAtDate::getPrice()
{
	return price;
}

BIGDECIMAL& PriceAtDate::val()
{
	return price;
}

PriceAtDate PriceAtDate::operator-()
{
	PriceAtDate toRt(*this);
	toRt.price *= -1;

	return toRt;
}

PriceAtDate PriceAtDate::operator+(const PriceAtDate& rhs)
{
	PriceAtDate toRt(*this);
	toRt.price += rhs.price;
	return toRt;
}
PriceAtDate PriceAtDate::operator+(const BIGDECIMAL& rhs)
{
	PriceAtDate toRt(*this);
	toRt.price += rhs;
	return toRt;
}
PriceAtDate PriceAtDate::operator-(const PriceAtDate& rhs)
{
	PriceAtDate toRt(*this);
	toRt.price -= rhs.price;
	return toRt;
}
PriceAtDate PriceAtDate::operator-(const BIGDECIMAL& rhs)
{
	PriceAtDate toRt(*this);
	toRt.price -= rhs;
	return toRt;
}
PriceAtDate PriceAtDate::operator*(const PriceAtDate& rhs)
{
	PriceAtDate toRt(*this);
	toRt.price *= rhs.price;
	return toRt;
}
PriceAtDate PriceAtDate::operator*(const BIGDECIMAL& rhs)
{
	PriceAtDate toRt(*this);
	toRt.price *= rhs;
	return toRt;
}
PriceAtDate PriceAtDate::operator/(const PriceAtDate& rhs)
{
	PriceAtDate toRt(*this);
	toRt.price /= rhs.price;
	return toRt;
}
PriceAtDate PriceAtDate::operator/(const BIGDECIMAL& rhs)
{
	PriceAtDate toRt(*this);
	toRt.price /= rhs;
	return toRt;
}


PriceAtDate& PriceAtDate::operator=(const PriceAtDate& rhs)
{
	if(this != &rhs)
	{
		price = rhs.price;
		date = rhs.date;
	}
	return *this;
}

PriceAtDate& PriceAtDate::operator=(const BIGDECIMAL& rhs)
{
	price = rhs;
	return *this;
}

PriceAtDate& PriceAtDate::operator+=(const PriceAtDate& rhs)
{
	price += rhs.price;
	return *this;
}
PriceAtDate& PriceAtDate::operator+=(const BIGDECIMAL& rhs)
{
	price += rhs;
	return *this;
}
PriceAtDate& PriceAtDate::operator-=(const PriceAtDate& rhs)
{
	price -= rhs.price;
	return *this;
}
PriceAtDate& PriceAtDate::operator-=(const BIGDECIMAL& rhs)
{
	price -= rhs;
	return *this;
}
PriceAtDate& PriceAtDate::operator/=(const PriceAtDate& rhs)
{
	price /= rhs.price;
	return *this;
}
PriceAtDate& PriceAtDate::operator/=(const BIGDECIMAL& rhs)
{
	price /= rhs;
	return *this;
}
PriceAtDate& PriceAtDate::operator*=(const PriceAtDate& rhs)
{
	price *= rhs.price;
	return *this;
}
PriceAtDate& PriceAtDate::operator*=(const BIGDECIMAL& rhs)
{
	price *= rhs;
	return *this;
}

bool PriceAtDate::operator==(const PriceAtDate& rhs)
{
	return	((*date) == (*rhs.date)) && (price == rhs.price);
}
bool  PriceAtDate::operator>(const PriceAtDate& rhs)
{
	return	(price > rhs.price);
}

bool  PriceAtDate::operator>=(const PriceAtDate& rhs)
{
	return	(price >= rhs.price);
}
bool  PriceAtDate::operator<(const PriceAtDate& rhs)
{
	return	(price < rhs.price);
}
bool  PriceAtDate::operator<=(const PriceAtDate& rhs)
{
	
	return	(price <= rhs.price);
}

PriceAtDate PriceAtDate::log()
{
	PriceAtDate toRt(*this);

	toRt.price = ::log(toRt.price);

	return toRt ;
}
PriceAtDate PriceAtDate::exp()
{
	PriceAtDate toRt(*this);

	toRt.price = ::exp(toRt.price);

	return toRt ;
}