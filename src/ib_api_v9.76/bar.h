/* Copyright (C) 2019 Interactive Brokers LLC. All rights reserved. This code is subject to the terms
 * and conditions of the IB API Non-Commercial License or the IB API Commercial License, as applicable. */

#pragma once
#ifndef TWS_API_CLIENT_BAR_H
#define TWS_API_CLIENT_BAR_H

#include <string>

struct Bar
{
	std::string time;
	double high{ 0.0 };
	double low{ 0.0 };
	double open{ 0.0 };
	double close{ 0.0 };
	double wap{ 0.0 };
	long long volume{ 0 };
	int count{ 0 };
};

#endif