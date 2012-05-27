#include <iostream>

#include "PriceAtDate.h"
#include "FinanceDataLoader.h"
#include "CSVParser.h"
#include "Stock.h"
#include "ScriptManager.h"
#include "mean.h"
#include "stdev.h"
#include "mvg.h"
#include "log_series.h"
#include "ValueAtRisk.h"
#include "HttpProcessServer.h"
#include "ScriptEnvironment.h"
#include <iostream>
#include <math.h>


using namespace quantserver ;
using namespace std;

void shouldParsePriceAtDateCorrectly() ;
void shouldDownloadFileCorrectly();
void shoudParseCsvCorrectly();
void shouldParseStockCorrectly();
void shouldRunChaiScript();
void shouldDoAverageStdevAndMvg();
void shouldDoAverageOfLogSeries();
void shouldCalculateVaR() ;
void shouldCreateHttpServer() ;
void shouldShouldCalculateAvgInScript() ;

int main()
{
	std::cout << "Hello world from QuantServer" << std::endl;
	//shouldParsePriceAtDateCorrectly() ;
	//shouldDownloadFileCorrectly() ;
	//shoudParseCsvCorrectly() ;
	//shouldParseStockCorrectly();
	//shouldRunChaiScript();
	//shouldDoAverageStdevAndMvg();
	//shouldDoAverageOfLogSeries();
	//shouldCalculateVaR() ;
	//shouldCreateHttpServer();
	
	//shouldRunChaiScript() ;
	
	shouldShouldCalculateAvgInScript() ;

	system("pause") ;

	return 0;
}

void shouldShouldCalculateAvgInScript()
{
	ScriptEnvironment env ;
	ScriptManager& script = env(); ;

	CSVParser csvParser("C:\\workspaces\\cppFinance\\localfiles\\test1.csv");
	string stockName = "test";
	Stock testStock(stockName);
	testStock.loadData(csvParser);

	script.engine().add(chaiscript::var(testStock) , "stock") ;

	try
	{
		script.engine().eval<BIGDECIMAL>("var c = stock[\"Close\"];var v = mean(c);print(v);");
	}
	catch(std::exception ex)
	{
		cout << ex.what() << endl ;
	}

}

void shouldCreateHttpServer()
{
	HttpProcessServer::start() ;
}

void shouldCalculateVaR()
{
	CSVParser csvParser("C:\\workspaces\\cppFinance\\localfiles\\test1.csv");
	string stockName = "test";
	Stock testStock(stockName);
	testStock.loadData(csvParser);

	cout << "Test Data loaded" << endl;

	log_series logs;
	mean avg;
	stdev sd;
	ValueAtRisk var(0.95) ;

	BIGDECIMAL meanVal = avg(logs(testStock["Close"])) ; 
	BIGDECIMAL lastVal = testStock["Close"][0].val() ; 

	cout << "Average of log is " << meanVal << endl;
	cout << "Stdev of log is " << sd(logs(testStock["Close"])) << endl;

	BIGDECIMAL v = var(logs(testStock["Close"])) ;

	cout << "Value at Risk is " << v << endl;
	cout << "Last Val is " << lastVal << endl; 
	cout << "Value at Risk is " << ((::abs(::exp(v) - lastVal)/lastVal)*100) << " percent" << endl;
}

void shouldDoAverageOfLogSeries()
{
	CSVParser csvParser("C:\\workspaces\\cppFinance\\localfiles\\test1.csv");
	string stockName = "test";
	Stock testStock(stockName);
	testStock.loadData(csvParser);

	cout << "Test Data loaded" << endl;

	log_series logs;
	mean avg;
	stdev sd;

	cout << "Average of log is " << avg(logs(testStock["Close"])) << endl;
	cout << "Stdev of log is " << sd(logs(testStock["Close"])) << endl;
}

void shouldDoAverageStdevAndMvg()
{
	CSVParser csvParser("C:\\workspaces\\cppFinance\\localfiles\\test1.csv");
	string stockName = "test";
	Stock testStock(stockName);
	testStock.loadData(csvParser);

	cout << "Test Data loaded" << endl;

	//Now that we have the stock data, lets print out some values
	mean avg;
	cout << "Average is " << avg(testStock["Close"]) << endl;

	stdev sd;
	cout << "Stdev is " << sd(testStock["Close"]) << endl;

	mvg mvg3;
	TimeSeries& movingAvgRes = mvg3(testStock["Close"]);

	for(int i = 0 ; i < movingAvgRes.size() ; i++)
	{
		cout << "day[" << i << "] = " << movingAvgRes[i].val() << endl ;
	}


}

void shouldRunChaiScript()
{
	ScriptManager scriptManager;
	scriptManager.engine().eval("print(\"hello world from chai\")");
	double d = scriptManager.engine().eval<double>("3 + 4.75;");

	cout << "Chai simple add (3 + 4.75): " << d << endl ;
}

void shouldParseStockCorrectly()
{
	CSVParser csvParser("C:\\workspaces\\cppFinance\\localfiles\\test.csv");
	string stockName = "test";
	Stock testStock(stockName);
	testStock.loadData(csvParser);

	cout << "Data loaded" << endl;

	//Now that we have the stock data, lets print out some values
	cout << "1st day has date of: " << testStock["High"][0].getDate() << endl;
	cout << "2nd day closed at: " << testStock["Close"][1].val() << endl;
	cout << "7st day has volume of: " << testStock["Volume"][6].val() << endl;
}

void shoudParseCsvCorrectly()
{
	CSVParser csvParser("C:\\workspaces\\cppFinance\\localfiles\\test.csv");

	int numberOfLines = csvParser.getNumberOfLines();
	int numberOfColumns = csvParser.getNumberOfColumns() ;

	for(int i = 0 ; i < numberOfColumns ; i++ )
	{
		std::cout << csvParser.getHeaderOfIndex(i) << " , " ;
	}

	std::cout << std::endl;

	std::cout << "Data read: " << numberOfLines << " lines" << endl;

}

void shouldDownloadFileCorrectly()
{
	cout << " --- Downloading from http://ichart.finance.yahoo.com/table.csv?s=INTC ---" << endl;
	string url = "http://ichart.finance.yahoo.com/table.csv?s=INTC" ;
	FinanceDataLoader financeDataLoader(url , true);
	cout << "Data available at: " << financeDataLoader.getLocalReadable() << endl;

}

void shouldParsePriceAtDateCorrectly()
{
	cout << " --- Parsing PriceAtDate values ---" << endl;
	PriceAtDate priceAtDate("14/4/2009" , "10.2");
	cout << "Date is: " << priceAtDate.getDate() << endl ;
	cout << "Price is: " << priceAtDate.getPrice() << endl ;
	cout << " --- Done ---" << endl;
}
