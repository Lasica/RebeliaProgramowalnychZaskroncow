#include <iostream>
#include <boost/asio.hpp>
#include <boost/thread/thread.hpp>
#include <boost/bind.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>
#include "HandshakeRaw.hpp"

using namespace boost::asio;

class client {
	public:
	client(std::string ad, short port, io_service& io): edp_(ip::tcp::endpoint(ip::address::from_string(ad), port)), socket_(ip::tcp::socket(io))
	{
	}
	void start(){
		try{
		socket_.connect(edp_);
		}
		catch(std::exception ex){
			std::cerr <<"Błąd połączenia";
		}
		}


	void send(HandshakeRaw&);
	void read();

	private:
	ip::tcp::endpoint edp_;
	ip::tcp::socket socket_;
        HandshakeRaw RestoredPack_;
	streambuf response_;
	void	handle_read(const boost::system::error_code &/*error*/, std::size_t /*bytes_transferred*/ );
	void	handle_write(const boost::system::error_code &/*error*/, std::size_t /*bytes_transferred*/);
};
