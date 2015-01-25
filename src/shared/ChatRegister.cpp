#include "shared/ChatRegister.hpp"
#include <boost/shared_ptr.hpp>
#include "shared/Packet.hpp"

void ChatRegister::register_message(ChatEntryRaw &message) {

    std::cout << "* Nowa wiadomość od "<< message.nick_ << ": " << message.message_ << std::endl;
    chatLog_.push_back(message);
    Packet p(Packet::UPDATED_RESOURCE, nullptr, new ChatEntryRaw(message));
    notify(p);
}

// przesyła całą historię czatu
void ChatRegister::synchronise(Observer* /*obs*/) {
  /* z czatem nie przewidujemy synchronizacji.
    for(auto r: chatLog_) {
        boost::scoped_ptr<Resource> notification( new ChatEntryRaw(r));
        Packet::Tag tag(Packet::UPDATED_RESOURCE);
        // woła update() tylko dla tego pojedynczego klienta
        obs->update(notification.get(), tag);
    }
*/
}
