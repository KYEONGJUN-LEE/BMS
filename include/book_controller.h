#pragma once

#include <memory>
#include <mysql/jdbc.h>

void createBook(std::unique_ptr<sql::Connection>& con);
void listBooks(std::unique_ptr<sql::Connection>& con);
void updateBook(std::unique_ptr<sql::Connection>& con);
void deleteBook(std::unique_ptr<sql::Connection>& con);
