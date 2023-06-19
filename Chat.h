#pragma once
#include <vector>
#include <exception>
#include <memory>
#include "Message.h"

struct UserLoginExp : public std::exception
{
	const char* what() const noexcept override { return "<<<ошибка: логин пользователя занят>>>"; }
};

struct UserNameExp : public std::exception
{
	const char* what() const noexcept override { return "<<<ошибка: имя пользователя занято>>>"; }
};

class Chat {
public:
	void start();
	bool ChatWork() const { return ChatWork_; }
	std::shared_ptr<User> getCurrentUser() const { return currentUser_; }
	void showLogMenu();
	void showUserMenu();

private:
	bool ChatWork_ = false;
	std::vector<User> users_;
	std::vector<Message> messages_;
	std::shared_ptr<User> currentUser_;
	void loginUser();
	void signUp();
	void showChat() const;
	void showUsers() const;
	void addMessage();
	std::vector<User>& getAllUsers() { return users_; }
	std::vector<Message>& getAllMessages() { return messages_; }
	std::shared_ptr<User> getUserByLogin(const std::string& login) const;
	std::shared_ptr<User> getUserByName(const std::string& name) const;
};