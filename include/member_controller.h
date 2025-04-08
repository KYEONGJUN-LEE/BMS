#pragma once
#include <memory>
#include <mysql/jdbc.h>

void createMember(std::unique_ptr<sql::Connection>& con);
void listMembers(std::unique_ptr<sql::Connection>& con);
void updateMember(std::unique_ptr<sql::Connection>& con);
void deleteMember(std::unique_ptr<sql::Connection>& con);
