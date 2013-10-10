#include "stdafx.h"
#include "tcm_config.h"

namespace tcm
{
	Config* Config::_Instance = NULL;

	Config::Config()
	{
		_Flag = new Flag();
	}

	Config::~Config()
	{
		Clear(_Flag);
	}

	Config* Config::GetInstance()
	{
		if(Config::_Instance == NULL)
			Config::_Instance = new Config();
		return Config::_Instance;
	}

	Flag* Config::GetFlag()
	{
		return _Flag;
	}
}