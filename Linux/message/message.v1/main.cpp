#include "dlog.h"
#include "message.h"

using namespace Exchange;

Exchanger exchanger;

int main(int argc, char **argv)
{
    Message mess;
    //mess.setType(TypeKinds::USER); /* automatic */
    mess.setDestination(Address::COMMANDER);
    mess.setData(&Text::INJURED);
    exchanger.send(mess);
    return 0;
}
