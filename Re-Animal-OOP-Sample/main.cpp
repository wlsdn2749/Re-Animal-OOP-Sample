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

	user->PostDBTaskDelay<UpdateUserExp>(10, 5); // 1000ms

	while (true)
	{

	}
}