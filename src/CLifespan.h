#pragma once

class CLifespan
{
public:
	const int total = 0;
	int remaining = 0;

	CLifespan(int total)
		: total(total)
		, remaining(total)
	{}
};