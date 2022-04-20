#pragma once
#include <boost/asio/ssl.hpp>
#include <boost/asio/ip/tcp.hpp>

class certify
{
public:
	certify() = delete;

	static boost::asio::ssl::context create_context();

	static void setup_connection(const std::string &host,
		boost::asio::ssl::stream<boost::asio::ip::tcp::socket&> &stream);
};