#pragma once
#pragma once
#include <memory>
#include <mysql/jdbc.h>

void rentBook(std::unique_ptr<sql::Connection>& con);
void returnBook(std::unique_ptr<sql::Connection>& con);
void showRentalStatus(std::unique_ptr<sql::Connection>& con);
