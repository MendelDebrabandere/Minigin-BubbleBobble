#pragma once
#include "GameObject.h"

namespace dae
{
	class Command
	{
	public:
		explicit Command() = default;
		virtual ~Command() = default;
		Command(const Command& other) = delete;
		Command& operator=(const Command& rhs) = delete;
		Command(Command&& other) = delete;
		Command& operator=(Command&& rhs) = delete;


		virtual void Execute() = 0;
	};
}

