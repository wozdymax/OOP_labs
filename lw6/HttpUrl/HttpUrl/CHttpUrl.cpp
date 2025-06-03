#include "CHttpUrl.h"
#include "CUrlParsingError.h"
#include <regex>
#include <algorithm>


const std::string URL_ERROR = "URL parse is failed";
const std::string PROTOCOL_ERROR = "Invalid protocol";
const std::string DOMAIN_ERROR = "Invalid domain format: ";
const std::string PARSE_INT_ERROR = "Invalid integer format\n";
const std::string PORT_ERROR = "Port must be between 1 and 65535";
const std::string DOCUMENT_ERROR = "Invalid document format: ";

std::smatch UrlRegexMatch(const std::string& url)
{
	std::smatch matches;
	const std::regex urlRegex(
		R"(^(http[s]?)://)"
		R"(([a-z0-9-]+(\.[a-z0-9-]+)*\.[a-z]{2,}))"
		R"((?::(\d+))?)"
		R"((/[-a-zA-Z0-9._~!$&'()*+,;=:@/%]*)?)",
		std::regex::icase
	);

	if (!std::regex_match(url, matches, urlRegex))
	{
		throw CUrlParsingError(URL_ERROR);
	}
	return matches;
}

Protocol ParseProtocol(const std::string& protocol)
{
	std::string lowerProtocol = protocol;
	std::transform(lowerProtocol.begin(), lowerProtocol.end(), lowerProtocol.begin(), ::towlower);
	if (lowerProtocol == "http")
	{
		return Protocol::HTTP;
	}
	else if (lowerProtocol == "https")
	{
		return Protocol::HTTPS;
	}
	throw CUrlParsingError(PROTOCOL_ERROR);
}

std::string ParseDomain(const std::string& domain)
{
	const std::regex domainRegex(R"(([a-z0-9-]+(\.[a-z0-9-]+)*\.[a-z]{2,}))");
	if (!std::regex_match(domain, domainRegex))
	{
		throw CUrlParsingError(DOMAIN_ERROR + domain);
	}

	return domain;
} 

int ParseInt(std::string str)
{
	int num;
	try
	{
		num = stoi(str);
	}
	catch(const std::exception& e)
	{
		throw std::invalid_argument(PARSE_INT_ERROR);
	}
}

unsigned short ParsePort(const Protocol& protocol, std::string sPort)
{
	if (sPort.empty())
	{
		return (protocol == Protocol::HTTPS) ? DEFAULT_HTTPS_PORT : DEFAULT_HTTP_PORT;
	}

	try
	{
		int port = ParseInt(sPort);
		if (port < MIN_PORT || port > MAX_PORT)
		{
			throw std::out_of_range(PORT_ERROR);
		}

		return port;
	}
	catch (const std::exception& e)
	{
		throw CUrlParsingError(e.what());
	}
}

std::string ParseDocument(const std::string& document)
{
	const std::regex documentRegex(R"(([/]?[-a-zA-Z0-9._~!$&'()*+,;=:@/%]*)?)", std::regex::icase);
	if (!std::regex_match(document, documentRegex))
	{
		throw CUrlParsingError(DOCUMENT_ERROR + document);
	}
	if (document[0] != '/')
	{
		return "/" + document;
	}
	return document;
}

CHttpUrl::CHttpUrl(std::string const& url)
{
	std::smatch matches = UrlRegexMatch(url);
	m_protocol = ParseProtocol(matches[1]);
	m_domain = ParseDomain(matches[2]);
	m_port = ParsePort(m_protocol, matches[4]);
	m_document = matches[5];
	m_url = FormUrl();
}

CHttpUrl::CHttpUrl(std::string const& domain, std::string const& document, Protocol protocol)
	:CHttpUrl(domain, document, protocol, (protocol == Protocol::HTTP) ? DEFAULT_HTTP_PORT : DEFAULT_HTTPS_PORT)
{
}

CHttpUrl::CHttpUrl(std::string const& domain, std::string const& document, Protocol protocol, unsigned short port)
{
	try
	{
		m_domain = ParseDomain(domain); 
		m_document = ParseDocument(document); 

		if (port < MIN_PORT || port > MAX_PORT) 
		{
			throw std::out_of_range(PORT_ERROR);
		}
	}
	catch (const std::exception& e) 
	{
		throw std::invalid_argument(e.what()); 
	}

	m_protocol = protocol;
	m_port = port;
	m_url = FormUrl();
}

std::string CHttpUrl::GetURL() const
{
	return m_url;
}

std::string CHttpUrl::GetDomain() const
{
	return m_domain;
}

std::string CHttpUrl::GetDocument() const
{
	return m_document;
}

Protocol CHttpUrl::GetProtocol() const
{
	return m_protocol;
}

unsigned short CHttpUrl::GetPort() const
{
	return m_port;
}

bool IsDefaultPortProtocol(Protocol protocol, unsigned short port)
{
	return (protocol == Protocol::HTTP && port == DEFAULT_HTTP_PORT) ||
		(protocol == Protocol::HTTPS && port == DEFAULT_HTTPS_PORT);
}

std::string CHttpUrl::FormUrl()
{
	std::string url;

	url += (m_protocol == Protocol::HTTP) ? "http://" : "https://";
	url += m_domain;
	url += IsDefaultPortProtocol(m_protocol, m_port) ? "" : (":" + std::to_string(m_port));
	url += m_document;

	return url;
}
