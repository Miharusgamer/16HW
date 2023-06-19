#include <iostream>
#include "Chat.h"

void Chat::start() {
	ChatWork_ = true;
}

std::shared_ptr<User> Chat::getUserByLogin(const std::string& login) const
{
	for (auto& user : users_)
	{
		if (login == user.getUserLogin())
			return std::make_shared<User>(user);
	}

	return nullptr;
}

std::shared_ptr<User> Chat::getUserByName(const std::string& name) const
{
	for (auto& user : users_)
	{
		if (name == user.getUserName())
			return std::make_shared<User>(user);
	}

	return nullptr;
}

void Chat::loginUser()
{
	std::string login, password;
	char c;

	do
	{
		std::cout << "логин: ";
		std::cin >> login;
		std::cout << "пароль: ";
		std::cin >> password;

		currentUser_ = getUserByLogin(login);

		if (currentUser_ == nullptr || (password != currentUser_->getUserPassword()))
		{
			currentUser_ = nullptr;

			std::cout << "ошибка входа..." << std::endl;
			std::cout << "(0)выход или (любую клавишу)повторить: ";
			std::cin >> c;

			if (c == '0')
				break;
		}

	} while (!currentUser_);
}

void Chat::signUp()
{
	std::string login, password, name;

	std::cout << "логин: ";
	std::cin >> login;
	std::cout << "пароль: ";
	std::cin >> password;
	std::cout << "имя: ";
	std::cin >> name;

	if (getUserByLogin(login) || login == "all")
	{
		throw UserLoginExp();
	}

	if (getUserByName(name) || name == "all")
	{
		throw UserNameExp();
	}

	User user = User(login, password, name);
	users_.push_back(user);
	currentUser_ = std::make_shared<User>(user);
}

void Chat::showChat() const
{
	std::string from;
	std::string to;

	std::cout << "-------чат-------" << std::endl;

	for (auto& mess : messages_)
	{

		if (currentUser_->getUserLogin() == mess.getFrom() || currentUser_->getUserLogin() == mess.getTo() || mess.getTo() == "all")
		{

			from = (currentUser_->getUserLogin() == mess.getFrom()) ? "me" : getUserByLogin(mess.getFrom())->getUserName();

			if (mess.getTo() == "all")
			{
				to = "(all)";
			}
			else
			{
				to = (currentUser_->getUserLogin() == mess.getTo()) ? "me" : getUserByLogin(mess.getTo())->getUserName();
			}

			std::cout << "Сообщение от " << from << " для " << to << std::endl;
			std::cout << "текст: " << mess.getText() << std::endl;
		}
	}

	std::cout << "-----------------" << std::endl;
}

void Chat::showLogMenu()
{
	currentUser_ = nullptr;

	char c;

	do
	{
		std::cout << "-------------------------" << std::endl;
		std::cout << "|Добро пожаловать в чат!|" << std::endl;
		std::cout << "-------------------------" << std::endl;
		std::cout << std::endl;
		std::cout << "Войти - 1" << std::endl;
		std::cout << "Регистрация - 2" << std::endl;
		std::cout << "Выход - 0" << std::endl;
		std::cout << std::endl;
		std::cout << ">> ";
		std::cin >> c;

		switch (c)
		{
		case '1':
			loginUser();
			break;
		case '2':
			try
			{
				signUp();
			}
			catch (const std::exception& e)
			{
				std::cout << e.what() << std::endl;
			}
			break;
		case '0':
			ChatWork_ = false;
			break;
		default:
			std::cout << "1 или 2..." << std::endl;
			break;
		}

	} while (!currentUser_ && ChatWork_);
}

void Chat::showUserMenu()
{
	char operation;

	std::cout << "Привет, " << currentUser_->getUserName() << std::endl;

	while (currentUser_) {
		std::cout << "___________________________" << std::endl;
		std::cout << "Меню:" << std::endl;
		std::cout << "Показать сообщения - 1" << std::endl;
		std::cout << "Добавить сообщение - 2" << std::endl;
		std::cout << "Показать пользователей - 3" << std::endl;
		std::cout << "Выход - 0" << std::endl;
		std::cout << "__________________________" << std::endl;
		std::cout << std::endl;
		std::cout << ">> ";
		std::cin >> operation;

		switch (operation)
		{
		case '1':
			showChat();
			break;
		case '2':
			addMessage();
			break;
		case '3':
			showUsers();
			break;
		case '0':
			currentUser_ = nullptr;
			break;
		default:
			std::cout << "неизвестный выбор " << std::endl;
			break;
		}
	}
}

void Chat::showUsers() const
{
	std::cout << "------Пользователи------" << std::endl;
	for (auto& user : users_)
	{
		std::cout << user.getUserName();

		if (currentUser_->getUserLogin() == user.getUserLogin())
			std::cout << "(я)";
		std::cout << std::endl;
	}
	std::cout << "------------------------" << std::endl;
}

void Chat::addMessage()
{
	std::string to, text;
	std::cout << "Для (name или all): ";
	std::cin >> to;
	std::cout << "Текст: ";
	std::cin.ignore();
	getline(std::cin, text);

	if (!(to == "all" || getUserByName(to)))
	{
		std::cout << "ошибка отправки сообщения " << to << std::endl;
		return;
	}

	if (to == "all")
		messages_.push_back(Message{ currentUser_->getUserLogin(), "all", text });
	else
		messages_.push_back(Message{ currentUser_->getUserLogin(), getUserByName(to)->getUserLogin(), text });
}