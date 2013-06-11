#include "message.h"
#include <string>
#include <list>

std::list<TextMessage::Message *> list;
using namespace Storage::Operations;

TextMessageJournal::~TextMessageJournal()
{
    delAll();
}

bool TextMessageJournal::put(TextMessage::Message *mess)
{
    list.push_back(mess);
    return true;
}

bool TextMessageJournal::getLast(TextMessage::Message &mess)
{
    mess = *list.back();
    return true;
}

bool TextMessageJournal::getByIndex(int, TextMessage::Message &)
{
    return true;
}

bool TextMessageJournal::delByIndex(int index)
{
    if (index < 0 || index >= int(list.size())) return false;
    int i = 0;
    for (auto it = list.begin(); it != list.end(); ++it, ++i) {
        if (i == index) {
            delete *it;
            list.erase(it);
            return true;
        }
    }
    return false;
}

bool TextMessageJournal::delAll()
{
    for (auto i : list) delete i;
    list.clear();
    return true;
}

int TextMessageJournal::getTotal()
{
    return list.size();
}

