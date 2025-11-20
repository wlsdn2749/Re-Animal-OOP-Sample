#include "User.h"
#include <thread>
#include <chrono>

class UpdateUserExp;

int main()
{
	
	auto user = std::make_shared<User>();

	//for(int i=0; i<5; ++i)
	//{ 
	//	if (i == 3) // 유저가 다른곳으로 이동
	//	{
	//		user->ChangeThreadKey(); // 0에서 1로 
	//	}

	//	user->PostDBTask<UpdateUserExp>(5);
	//	user->PostDBTask<UpdateUserMoney>(100);
	//	user->PostDBTask<UpdateUserLevel>(1);

	//	std::this_thread::sleep_for(std::chrono::milliseconds(1000));
	//}

	GlobalTimerQueue::Instance().Initialize();
	user->PostDBTaskDelay<UpdateUserExp>(5000, 5); // 5000ms
	user->PostDBTaskDelay<UpdateUserMoney>(3000, 3); // 3000ms
	user->PostDBTaskDelay<UpdateUserLevel>(10000, 10); // 10000ms

	std::this_thread::sleep_for(std::chrono::milliseconds(7000));
	user->ChangeThreadKey(); // 0에서 1로  .. 7초 후에 이동

	while (true)
	{

	}
}