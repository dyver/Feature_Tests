#include "message.h"
#include "string.h"

namespace Exchange
{
    const Text Text::INJURED("Injured");
    Text::Text(const char *data)
    {
        this->data = new char[strlen(data) + 1];
        strcpy(this->data, data);
    }

    Serialized *Text::serialize()
    {
        static char buf[10];
        return (Serialized *)buf;
    }

    Message::Message()
    {
    }

    Message::~Message()
    {
    }

    void Message::setType(const Type &)
    {
    }

    const Type &Message::getType()
    {
        return type;
    }

    void Message::setData(const Data *data)
    {
        this->data = const_cast<Data *>(data);
    }

    const Data *Message::getData()
    {
        return data;
    }

    Serialized *Message::serialize()
    {
        static uint8_t buffer[100];
/*        int dataSize = data->serialize()->getSize();
        buffer[0] = 0;
        Type type;
        Descriptor descriptor;
        Address from;
        Address to;
*/        buffer[0] = 5;
        buffer[4] = 51;
        buffer[5] = 0;
        return (Serialized *)buffer;
    }

    void Exchanger::send(const Message &message)
    {
    }
}

//INFO("%s", mess.serialize()->getData());
//INFO("Size=%d", mess.serialize()->getSize());
