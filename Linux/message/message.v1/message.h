#include <stdint.h>

namespace Exchange
{
    enum TypeKinds
    {
        SYSTEM_TYPE,
        USER_TYPE
    };

    typedef uint8_t Type;
    typedef uint32_t Descriptor;
    typedef uint32_t Address;

    class Serialized;

    class Data
    {
        public :
            virtual Serialized *serialize() = 0;
    };

    class Text : public Data
    {
        public :
            static const Text INJURED;
            virtual Serialized *serialize();
        private :
            Text(const char *);
            char *data;
    };

    class Photo : public Data
    {
        public :
            virtual Serialized *serialize();
    };

    class Video : public Data
    {
        public :
            virtual Serialized *serialize();
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
            Descriptor descriptor;
            Address source;
            Address destination;
            Data *data;
    };

    class Exchanger
    {
        public :
            void send(const Message &);
            void receive(Message &);
    };

    class Serialized
    {
        public :
            uint8_t *getData() { return &data; }
            uint32_t getSize() { return size; }
            uint8_t *getRaw() { return &raw; }
        private :
            union {
                struct {
                    uint32_t size;
                    uint8_t data;
                };
                uint8_t raw;
            };
    };
}
