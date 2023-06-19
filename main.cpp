#include "Chat.h"
#include <iostream>

int main()
{
	system("chcp 1251");

	Chat chat;

	chat.start();

	while (chat.ChatWork()) {

		chat.showLogMenu();

		while (chat.getCurrentUser()) {
			chat.showUserMenu();
		}
	}
	return 0;
}