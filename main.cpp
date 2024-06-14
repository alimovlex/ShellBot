#include <iostream>
#include <string>
#include "bot_api.h"

using namespace std;
using namespace StringTools;

#define TG_API_KEY "" /*Telegram API KEY*/

int main() {
    Bot bot(TG_API_KEY);
    cout << "Starting bot" << endl;
    runBot(bot);
    TgLongPoll longpoll(bot);
    signal(SIGINT, [](int sig) {
        cout << "SIGINT got" << endl;
        exit(0);
    });
    while (true) {
        longpoll.start();
    }

}


