/*
    ShellBot
    Created by alimovlex.
    Copyright (c) 2020 alimovlex. All rights reserved.
*/

#include <string>
#include <tgbot/tgbot.h>
#include <unistd.h>

using namespace TgBot;
using namespace std;
using namespace StringTools;

static bool running = false;
InlineKeyboardMarkup::Ptr keyboard;

void escape_html(string &html) {
    string tmp;
    tmp.reserve(html.size());
    for (size_t pos = 0; pos != html.size(); ++pos) {
        switch (html[pos]) {
            case '&':
                tmp.append("&amp;");
                break;
            case '\"':
                tmp.append("&quot;");
                break;
            case '\'':
                tmp.append("&apos;");
                break;
            case '<':
                tmp.append("&lt;");
                break;
            case '>':
                tmp.append("&gt;");
                break;
            default:
                tmp.append(&html[pos], 1);
                break;
        }
    }
    html.swap(tmp);
}

string runcommands(const char *command) {
    FILE *cp;
    string out_string;
    array<char, PATH_MAX> rst;
    cp = popen(command, "r");
    if (cp == NULL)
        return string();
    else {
        while (fgets(rst.data(), PATH_MAX, cp) != NULL)
            out_string += rst.data();
    }
    auto ret = pclose(cp);
    if (ret == -1) {
        free(cp);
    }
    return out_string;
}

void runBot(Bot &build) {
    vector<BotCommand::Ptr> commands;
    BotCommand::Ptr cmdarray(new BotCommand);
    cmdarray->command = "command";
    cmdarray->description = "run whatever you want in bash terminal";
    commands.push_back(cmdarray);
    build.getApi().setMyCommands(commands);
    vector<BotCommand::Ptr> vectCmd;
    vectCmd = build.getApi().getMyCommands();
    build.getEvents().onCommand("command", [&build](Message::Ptr message) {
        build.getApi().sendMessage(message->chat->id, "Enter the command");
        running = true;
    });
    build.getEvents().onAnyMessage([&build](Message::Ptr message) {
        if (running) {
            string out = runcommands(message->text.c_str());
            if (out.empty()) {
                build.getApi().sendMessage(message->chat->id, "<b>Output:-</b> \n \n<code>" + out + "</code>", true,
                                           0, keyboard, "HTML");
            } else {
                escape_html(out);
                build.getApi().sendMessage(message->chat->id, "<b>Output:-</b> \n \n<code>" + out + "</code>", true,
                                           0, keyboard, "HTML");
            }
            running = false;
        }
    });
}