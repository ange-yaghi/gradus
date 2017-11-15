#define BOOST_TEST_MODULE Gradus_UnitTestingMain
#include <boost/test/unit_test.hpp>
#include <time.h>
#include <iostream>
#include <fstream>
#include <iomanip>

/* Test change */

struct Gradus_UnitTestConfiguration
{
	Gradus_UnitTestConfiguration()
	{

		time_t currentTime;

		time(&currentTime);
		struct tm *timeInfo = localtime(&currentTime);

		int year = timeInfo->tm_year+1900;
		int month = timeInfo->tm_mon + 1;
		int day = timeInfo->tm_mday;
		int hour = (timeInfo->tm_hour);
		int minute = timeInfo->tm_min;
		int second = timeInfo->tm_sec;

		std::stringstream ss;

		ss << std::setfill('0') << std::setw(2) << year << "-" << month << "-" << day << " " << hour << "_" << minute << "_" << second;

		std::string fname = "Logs/gradus_unit_test_log_" + ss.str() + ".log";

		m_testLog.open(fname);

		boost::unit_test::unit_test_log.set_stream(m_testLog);

		boost::unit_test::unit_test_log.set_threshold_level(boost::unit_test::log_warnings);

	}

	~Gradus_UnitTestConfiguration()
	{

		boost::unit_test::unit_test_log.set_stream(std::cout);

	}

	std::ofstream m_testLog;

};

BOOST_GLOBAL_FIXTURE(Gradus_UnitTestConfiguration);

BOOST_AUTO_TEST_SUITE(SanityCheckSuite);

BOOST_AUTO_TEST_CASE(SanityTest)
{

	BOOST_TEST(true);

}

BOOST_AUTO_TEST_SUITE_END()