#include "dlog.h"
#include "message.h"
#include <iostream>
#include <stdlib.h>

Storage::TypesCore *storageTypes;

void useTextMessageExample()
{
    Storage::Operations::TextMessageJournal &im = storageTypes->getTextMessageJournal();
    im.put(new TextMessage::Message("Abracadabra"));
    im.put(new TextMessage::Message("Help me!!!"));
    TextMessage::Message mess;
    im.getLast(mess);
    std::cout << "Total messages in journal : " << im.getTotal() << std::endl;
    std::cout << "Last message is : " << mess.getText() << std::endl;
    int index = 0;
    bool delres = im.delByIndex(index);
    std::cout << "Deleting of " << index << " message was " << (delres ? "successfull" : "unsuccessfull") << std::endl;

    //char strRes[100];
    std::cout << "АБВГДЕ\n";
    long cppver = __cplusplus;
    std::cout << cppver << "\n";
    printf("СОБСТВ.КООРД: X=%.0f Y=%.0f H=%.0f; ГЕО.КООРД: lat.=%f L.=%f H=%f", 10.1, 20.1, 30.1, 40.1, 50.1, 60.1 );
}

int main(int argc, char **argv)
{
    storageTypes = new Storage::TypesCore;
    useTextMessageExample();
    delete storageTypes;
    return 0;
}
