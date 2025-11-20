#include "User.h"
#include <thread>

void User::Update()
{
	OnUpdate();
	Post(GetThreadKey(), [self = shared_from_this()]() // TODO: shared_from_this로 교체
		{
			self->Post(self->GetThreadKey(), [self]()
			{
				self->Update();
			});
		}, 1000); // 1초뒤 호출

}

void User::OnUpdate()
{
	std::cout << "Update 호출됨 " 
		<< " 현재 ThreadId: " << std::this_thread::get_id()
		<< " 현재 UserThreadKey " << GetThreadKey()
		<< " 현재 State : "
		<< " Exp : " << GetExp() 
		<< " Level : " << GetLevel()
		<< " Money : " << GetMoney()
		<< "\n";

} 
