#include <mailio/certify.hpp>
#if __has_include("boost/certify/https_verification.hpp")
#include <boost/certify/https_verification.hpp>
#include <boost/certify/extensions.hpp>
#define MAILIO_CERTIFY_AVAILABLE true;
#endif

using boost::asio::ssl::context;


context certify::create_context()
{
	context context(context::tls_client);
	context.set_options(context::default_workarounds | context::no_sslv2 | context::no_sslv3
		| context::no_tlsv1 | context::no_tlsv1_1 | context::single_dh_use);

	context.set_verify_mode(context::verify_peer | context::verify_fail_if_no_peer_cert);
	context.set_default_verify_paths();
#ifdef MAILIO_CERTIFY_AVAILABLE
	boost::certify::enable_native_https_server_verification(context);
#endif
	return context;
}

void certify::setup_connection(const std::string& host, boost::asio::ssl::stream<boost::asio::ip::tcp::socket&>& stream)
{
#ifdef MAILIO_CERTIFY_AVAILABLE
	// Sets the expected server hostname, which will be checked during the cert verification
	boost::certify::set_server_hostname(stream, host);
	// Set SNI Hostname (many hosts need this to handshake successfully)
	boost::certify::sni_hostname(stream, host);
#endif
}
