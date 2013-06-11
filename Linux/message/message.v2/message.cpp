#include "message.h"
//#include "string.h"

namespace Exchange
{
    void TextMessage::processMessage(const TextData &message)
    {
        controller->showTextMessage(message);
        Speech speech = messageBook.getSpeechByName(message);
        speech.speak();
    }
}
