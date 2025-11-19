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

int32_t UserDBTask::GetUserId()
{
	return _user->GetId();
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
	std::cout << "UpdateUserExp로 Task을 실행해 결과를 변수에 저장합니다..." << std::endl 
			<< "현재 DB 스레드 ID : " << std::this_thread::get_id() << "현재 유저 ID : " << GetUserId() << "\n\n";
	// Something DB Task...
	return true;
}

void UpdateUserExp::Apply()
{
	std::cout << "DB저장이 완료되었다고 가정하고 Memory에 업데이트 합니다.\n"
			 << "현재 유저 스레드 ID : " << std::this_thread::get_id() << "현재 유저 ID : " << GetUserId() << "\n\n";
	int beforeExp = _user->GetExp();
	_user->AddExp(_amount);

	std::cout << "Before Exp : " << beforeExp << " Updated Exp " << _user->GetExp() << std::endl << "\n\n";
	std::cout << "------------------------------------------------------------------------------------\n";
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
	std::cout << "UpdateUserLevel로 Task을 실행해 결과를 변수에 저장합니다..." << std::endl
			 << "현재 DB 스레드 ID : " << std::this_thread::get_id() << "현재 유저 ID : " << GetUserId() << std::endl;
	// Something DB Task...
	return true;
}

void UpdateUserLevel::Apply()
{
	std::cout << "DB저장이 완료되었다고 가정하고 Memory에 업데이트 합니다.\n" 
			<< "현재 유저 스레드 ID : " << std::this_thread::get_id() << "현재 유저 ID : " << GetUserId() << "\n\n";
	int beforeLevel = _user->GetLevel();
	_user->AddLevel(_amount);
	std::cout << "Before Exp : " << beforeLevel << " Updated Exp " << _user->GetLevel() << std::endl << "\n\n";
	std::cout << "------------------------------------------------------------------------------------\n";

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
	std::cout << "UpdateUserMoney로 Task을 실행해 결과를 변수에 저장합니다..." << std::endl
			<< "현재 DB 스레드 ID : " << std::this_thread::get_id() << "현재 유저 ID : " << GetUserId() << std::endl;
	// Something DB Task...
	return true;
}

void UpdateUserMoney::Apply()
{
	std::cout << "DB저장이 완료되었다고 가정하고 Memory에 업데이트 합니다."
			<< "현재 유저 스레드 ID : " << std::this_thread::get_id() << "현재 유저 ID : " << GetUserId() << "\n\n";
	int beforeMoney = _user->GetMoney();
	_user->AddMoney(_amount);
	std::cout << "Before Money : " << beforeMoney << " Updated Exp " << _user->GetMoney() << std::endl << "\n\n";
	std::cout << "------------------------------------------------------------------------------------\n";
}
