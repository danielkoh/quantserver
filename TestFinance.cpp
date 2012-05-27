#include <boost/test/unit_test.hpp>
using namespace boost::unit_test;

void helloWorldTest()
{
	BOOST_CHECK(2 == 1);
}

test_suite*
init_unit_test_suite( int, char* [] ) {
    framework::master_test_suite().p_name.value = "Unit test example 02";
    framework::master_test_suite().add( BOOST_TEST_CASE( &helloWorldTest ), 1 );

	return 0;
}
