#pragma once
#include <string>

const unsigned short DEFAULT_HTTP_PORT = 80;
const unsigned short DEFAULT_HTTPS_PORT = 443;
const unsigned short MAX_PORT = 65535;
const unsigned short MIN_PORT = 1;

enum class Protocol
{
    HTTP,
    HTTPS
};

class CHttpUrl
{
public:
    CHttpUrl(std::string const& url);

    CHttpUrl(
        std::string const& domain,
        std::string const& document,
        Protocol protocol = Protocol::HTTP);

    CHttpUrl(
        std::string const& domain,
        std::string const& document,
        Protocol protocol,
        unsigned short port);

    std::string GetURL()const;
    std::string GetDomain()const;
    std::string GetDocument()const;
    Protocol GetProtocol()const;
    unsigned short GetPort()const;

private:
    std::string FormUrl();
    std::string m_url;
    Protocol m_protocol;
    std::string m_domain;
    std::string m_document;
    unsigned short m_port;
};