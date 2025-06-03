#define CATCH_CONFIG_MAIN
#include <catch.hpp>
#include "../HttpUrl/CHttpUrl.h"
#include "../HttpUrl/CUrlParsingError.h"

const std::string INVALID_PROTOCOL_URL = "ftp://example.com/first_test/2";
const std::string INVALID_DOMAIN_URL = "https://examplec_om/first_test/2";
const std::string INVALID_PORT_URL = "http://example.com:1aa/first_test/2";
const std::string INVALID_DOCUMENT_URL = "http://example.com:100/first_test/forward- v    2";

TEST_CASE("Valid url constructor")
{
	CHECK_NOTHROW(CHttpUrl("HtTps://example.com/first_test/2"));
	CHttpUrl url1("HTTPs://example.com/first_test/2");
	CHECK(url1.GetProtocol() == Protocol::HTTPS);
	CHECK(url1.GetDomain() == "example.com");
	CHECK(url1.GetPort() == DEFAULT_HTTPS_PORT);
	CHECK(url1.GetDocument() == "/first_test/2");
	CHECK(url1.GetURL() == "https://example.com/first_test/2");

	CHECK_NOTHROW(CHttpUrl("example.com", "second_test/1@1"));
	CHttpUrl url2("example.com", "second_test/11");
	CHECK(url2.GetProtocol() == Protocol::HTTP);
	CHECK(url2.GetDomain() == "example.com");
	CHECK(url2.GetPort() == DEFAULT_HTTP_PORT);
	CHECK(url2.GetDocument() == "/second_test/11");
	CHECK(url2.GetURL() == "http://example.com/second_test/11");

	CHECK_NOTHROW(CHttpUrl("example.com", "/third_test/1&7", Protocol::HTTPS, 1299));
	CHttpUrl url3("example.com", "third_test/1&7", Protocol::HTTPS, 1299);
	CHECK(url3.GetProtocol() == Protocol::HTTPS);
	CHECK(url3.GetDomain() == "example.com");
	CHECK(url3.GetPort() == 1299);
	CHECK(url3.GetDocument() == "/third_test/1&7");
	CHECK(url3.GetURL() == "https://example.com:1299/third_test/1&7");
}

TEST_CASE("Invalid url with CUrlParsingError")
{
	CHECK_THROWS_AS(CHttpUrl(INVALID_PROTOCOL_URL), CUrlParsingError);
	CHECK_THROWS_AS(CHttpUrl(INVALID_DOMAIN_URL), CUrlParsingError);
	CHECK_THROWS_AS(CHttpUrl(INVALID_PORT_URL), CUrlParsingError);
	CHECK_THROWS_AS(CHttpUrl(INVALID_DOCUMENT_URL), CUrlParsingError);
}

TEST_CASE("Invalid url with invalid_argument")
{
	CHECK_THROWS_AS(CHttpUrl("  ", "/fifth667"), std::invalid_argument);
	CHECK_THROWS_AS(CHttpUrl("ert.ru", "/fift  h667"), std::invalid_argument);
	CHECK_THROWS_AS(CHttpUrl("example.ru", "/fifth245", Protocol::HTTP, MIN_PORT - 1), std::invalid_argument);
	CHECK_THROWS_AS(CHttpUrl("example.ru", "/fifth246", Protocol::HTTP, MAX_PORT + 1), std::invalid_argument);
}

