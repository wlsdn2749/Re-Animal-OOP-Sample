#pragma once
class BaseTask
{
public:
	BaseTask()
	{

	}
	virtual ~BaseTask()
	{

	}

public:
	virtual bool Execute()
	{
		return true;
	}

	
};

