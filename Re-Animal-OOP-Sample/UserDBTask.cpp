#include "UserDBTask.h"
#include "User.h"

User* UserDBTask::GetUser()
{
	return _user.get();
}

UserSharedPtr UserDBTask::GetUserPtr()
{
	return _user;
}

int32_t UserDBTask::GetUserKey()
{
	return _user->GetThreadKey();
}

// Update User Exp
UpdateUserExp::UpdateUserExp(UserSharedPtr user, size_t amount)
	: UserDBTask(user)
	, _amount(amount)
{
	
}


UpdateUserExp::~UpdateUserExp()
{
}

bool UpdateUserExp::Execute()
{
	std::cout << "UpdateUserExp로 Task을 실행해 결과를 변수에 저장합니다..." << std::endl;
	// Something DB Task...
	return true;
}

void UpdateUserExp::Apply()
{
	std::cout << "DB저장이 완료되었다고 가정하고 Memory에 업데이트 합니다.";
	int beforeExp = _user->GetExp();
	_user->AddExp(_amount);

	std::cout << "Before Exp : " << beforeExp << " Updated Exp " << _user->GetExp() << std::endl;
}


// Update User Level
UpdateUserLevel::UpdateUserLevel(UserSharedPtr user, size_t amount)
	: UserDBTask(user)
	, _amount(amount)
{
}

UpdateUserLevel::~UpdateUserLevel()
{
}

bool UpdateUserLevel::Execute()
{
	std::cout << "UpdateUserLevel로 Task을 실행해 결과를 변수에 저장합니다..." << std::endl;
	// Something DB Task...
	return true;
}

void UpdateUserLevel::Apply()
{
	std::cout << "DB저장이 완료되었다고 가정하고 Memory에 업데이트 합니다.";
	int beforeLevel = _user->GetLevel();
	_user->AddLevel(_amount);
	std::cout << "Before Exp : " << beforeLevel << " Updated Exp " << _user->GetLevel() << std::endl;

}

// Update User Money
UpdateUserMoney::UpdateUserMoney(UserSharedPtr user, size_t amount)
	: UserDBTask(user)
	, _amount(amount)
{
}

UpdateUserMoney::~UpdateUserMoney()
{
	
}

bool UpdateUserMoney::Execute()
{
	std::cout << "UpdateUserMoney로 Task을 실행해 결과를 변수에 저장합니다..." << std::endl;
	// Something DB Task...
	return true;
}

void UpdateUserMoney::Apply()
{
	std::cout << "DB저장이 완료되었다고 가정하고 Memory에 업데이트 합니다.";
	int beforeMoney = _user->GetMoney();
	_user->AddMoney(_amount);
	std::cout << "Before Money : " << beforeMoney << " Updated Exp " << _user->GetMoney() << std::endl;
}
