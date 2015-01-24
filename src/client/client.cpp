#include "client.hpp"
void client::read(){
 async_read(socket_, response_,boost::bind(&client::handle_read,
                            this,
                            boost::asio::placeholders::error,
                            boost::asio::placeholders::bytes_transferred));
}	
void client::handle_read(const boost::system::error_code &/*error*/, std::size_t /*bytes_transferred*/) {
    boost::archive::text_iarchive ia(&response_);
     ia >> restoredPack_;
    // if(restoredPacket_. )
     //restoredPacket_.show_content();
}

void client::handle_write(const boost::system::error_code &/*error*/, std::size_t /*bytes_transferred*/) {



}

void client::send(HandshakeRaw& hdsr)
{
	boost::asio::streambuf buff;
   /*   boost::archive::text_oarchive oa(ofs);
     oa << samplePacket;*/
  async_write(socket_, buff,boost::bind(&client::handle_write,
                            this,
                            boost::asio::placeholders::error,
                            boost::asio::placeholders::bytes_transferred));

}
