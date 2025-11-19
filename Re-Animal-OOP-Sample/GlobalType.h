#include <memory>

class Animal;
class User;


using AnimalSharedPtr	= std::shared_ptr<Animal>;
using UserSharedPtr		= std::shared_ptr<User>;