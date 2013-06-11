#include <string>

namespace Exchange
{
    class Data
    {
    };

    class TextData : public Data
    {
    };

    class Message
    {
        public :
            Message();
            ~Message();
            void setType(const Type &);
            const Type &getType();
            void setDescriptor(const Descriptor &);
            const Descriptor &getDescriptor();
            void setSource(const Address &);
            const Address &getSource();
            void setDestination(const Address &);
            const Address &getDestination();
            void setData(const Data *data);
            const Data *getData();
            Serialized *serialize();
        private :
            Type type;
            Index index;
            Direction direction;
            Address source;
            Address destination;
            Data *data;
    };

    class Speech
    {
        public :
            void speak();
    };

    class MessageBook
    {
        public :
            const std::string &getTextByIndex(int index);
            const Speech &getSpeechByIndex(int index);
    };

    class TextMessage
    {
        public :
            void processMessage(const Message &message);
    };

    class Controller
    {
        public :
            void showTextMessage(const TextMessage &);
    };

    class Manager
    {
        public :
            void subscribeOnXXX();
    };
}
