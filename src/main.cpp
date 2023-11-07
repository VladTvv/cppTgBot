#include <csignal>
#include <cstdio>
#include <cstdlib>
#include <exception>
#include <string>
#include <tgbot/tgbot.h>

using namespace std;
using namespace TgBot;

int main() {
    TgBot::Bot bot("6476127384:AAGQHt8MJe_vhudX2OF-1gTk5aMIpgyXS4M");


    InlineKeyboardMarkup::Ptr keyboard(new InlineKeyboardMarkup);
    vector<InlineKeyboardButton::Ptr> buttons;
    InlineKeyboardButton::Ptr chat_gpt(new InlineKeyboardButton), weather(new InlineKeyboardButton), about(new InlineKeyboardButton);
    chat_gpt->text = "Chat";
    chat_gpt->callbackData = "chat";
    buttons.push_back(chat_gpt);

    weather->text = "Weather";
    weather->callbackData = "weather";
    buttons.push_back(weather);

    about->text = "About";
    about->callbackData = "about";
    buttons.push_back(about);

    keyboard->inlineKeyboard.push_back(buttons);



    bot.getEvents().onCommand("start", [&bot, &keyboard](TgBot::Message::Ptr message) {
        bot.getApi().sendMessage(message->chat->id, "Hi!", false, 0, keyboard);
        });

    bot.getEvents().onAnyMessage([&bot](TgBot::Message::Ptr message) {
        printf("User wrote %s\n", message->text.c_str());
        if (StringTools::startsWith(message->text, "/start")) {
            return;
        }
        bot.getApi().sendMessage(message->chat->id, "Sorry, I don't know");
        });


    bot.getEvents().onCallbackQuery([&bot, &keyboard](CallbackQuery::Ptr query) {
        if (StringTools::startsWith(query->data, "chat")) {
            string response = "Not Added1";
            bot.getApi().sendMessage(query->message->chat->id, response, false, 0, keyboard, "Markdown");
        }

        });
    bot.getEvents().onCallbackQuery([&bot, &keyboard](CallbackQuery::Ptr query) {
        if (StringTools::startsWith(query->data, "weather")) {
            string response = "Not Added2";
            bot.getApi().sendMessage(query->message->chat->id, response, false, 0, keyboard, "Markdown");
        }
        });

    bot.getEvents().onCallbackQuery([&bot, &keyboard](CallbackQuery::Ptr query) {
        if (StringTools::startsWith(query->data, "about")) {
            string response = "Creator: Vlad T. https://t.me/Avieel";
            bot.getApi().sendMessage(query->message->chat->id, response, false, 0, keyboard, "Markdown");
        }
        });

    try {
        printf("Bot username: %s\n", bot.getApi().getMe()->username.c_str());
        TgBot::TgLongPoll longPoll(bot);
        while (true) {
            printf("Long poll started\n");
            longPoll.start();
        }
    }
    catch (TgBot::TgException& e) {
        printf("error: %s\n", e.what());
    }
    return 0;
}