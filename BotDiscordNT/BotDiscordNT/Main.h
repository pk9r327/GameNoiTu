#pragma once
#include <iostream>
#include <tuple> // std::ignore
#include <corecrt_io.h> // _setmode
#include <fcntl.h> // _O_WTEXT
#include <dpp/dpp.h> // Bot Discord
#include <AtlBase.h> // CA2W
#include <ctime>
#include "GameManagement.h"
#include "CommonConstants.h"

// => {{ global variable }}

// -- Discord
std::string token;
dpp::snowflake idChannel = 0;

// => {{ define function }}

void config();
std::string getString(const wchar_t*, ...);
void performCommand(GameManagement&, dpp::cluster&, const dpp::message_create_t&);
void printTimeOS();