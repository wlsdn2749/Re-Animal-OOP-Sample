#pragma once
#include "BaseDBTask.h"
#include "GlobalType.h"
#include <iostream>

class User;

class UserDBTask : public BaseDBTask
{
public:
	UserDBTask(UserSharedPtr user)
		: _user(user)
	{

	}

	virtual ~UserDBTask()
	{

	}

public:
	virtual bool Execute() override
	{
		return true;
	}

	User*				GetUser();
	UserSharedPtr		GetUserPtr();
	int32_t				GetUserKey();

protected:
	UserSharedPtr _user;
};


// =================Update User Exp===========================================================
//
class UpdateUserExp : public UserDBTask
{
public:
	UpdateUserExp(UserSharedPtr user, size_t amount);
	virtual ~UpdateUserExp();

public:
	virtual bool Execute() override;
	virtual void Apply() override;

private:
	size_t _amount;
};

// =================Update User Level===========================================================
//
class UpdateUserLevel : public UserDBTask
{
public:
	UpdateUserLevel(UserSharedPtr user, size_t amount);
	virtual ~UpdateUserLevel();

public:
	virtual bool Execute() override;
	virtual void Apply() override;

private:
	size_t _amount;
};

// =================Update User Money===========================================================
//
class UpdateUserMoney : public UserDBTask
{
public:
	UpdateUserMoney(UserSharedPtr user, size_t amount);
	virtual ~UpdateUserMoney();

public:
	virtual bool Execute() override;
	virtual void Apply() override;

private:
	size_t _amount;
};


