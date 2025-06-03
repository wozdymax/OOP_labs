#include "CHttpUrl.h"
#include <iostream>

void PrintUrl(const CHttpUrl& url)
{
	std::cout << "URL: " << url.GetURL() << "\n"
		<< "Protocol: " << ((url.GetProtocol() == Protocol::HTTP) ? "http" : "https") << "\n"
		<< "Port: " << url.GetPort() << "\n"
		<< "Domain: " << url.GetDomain() << "\n"
		<< "Document: " << url.GetDocument() << "\n";
}

int main()
{
	std::string line;
	while (getline(std::cin, line))
	{
		try
		{
			CHttpUrl url(line);
			PrintUrl(url);
		}
		catch (const std::exception& e)
		{
			std::cout << e.what();
		}
	}

	return 0;
}
