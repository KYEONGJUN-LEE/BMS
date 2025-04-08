#include "book_controller.h"
#include <iostream>

using namespace std;

// 도서 등록
void createBook(std::unique_ptr<sql::Connection>& con) {
    try {
        string title, author, published_at;
        int price;

        cin.ignore();
        cout << "책 제목: ";
        getline(cin, title);
        cout << "저자: ";
        getline(cin, author);
        cout << "출판일: ";
        getline(cin, published_at);
        cout << "가격: ";
        cin >> price;

        unique_ptr<sql::PreparedStatement> createBook(
            con->prepareStatement(
                "INSERT INTO books (title, author, published_at, price, status) "
                "VALUES (?, ?, ?, ?, '대여가능')"
            )
        );
        createBook->setString(1, title);
        createBook->setString(2, author);
        createBook->setString(3, published_at);
        createBook->setInt(4, price);

        int result = createBook->executeUpdate();
        cout << result << "책이 추가되었습니다.\n";
    }
    catch (sql::SQLException& e) {
        cerr << "책 등록 실패: " << e.what() << endl;
    }
}
// 도서 리스트 확인
void listBooks(std::unique_ptr<sql::Connection>& con) {
    try {
        unique_ptr<sql::PreparedStatement> selectQuery(
            con->prepareStatement(
                "SELECT book_id, title, author, published_at, price, status FROM books"
            )
        );
        unique_ptr<sql::ResultSet> res(selectQuery->executeQuery());

        cout << "\n[ 도서 목록 ]\n";
        while (res->next()) {
            cout << "[" << res->getInt("book_id") << "] "
                << res->getString("title") << " / "
                << res->getString("author") << " / "
                << res->getString("published_at") << " / "
                << res->getInt("price") << " 원 / "
                << res->getString("status") << "\n";
        }
    }
    catch (sql::SQLException& e) {
        cerr << "책 조회 실패: " << e.what() << endl;
    }
}
// 도서 내역 갱신
void updateBook(std::unique_ptr<sql::Connection>& con) {
    try {
        int book_id, price;
        string title, author, published_at, status;

        cout << "수정할 책 ID를 입력하세요: ";
        cin >> book_id;
        cin.ignore();

        cout << "새로운 제목: ";
        getline(cin, title);
        cout << "새로운 저자: ";
        getline(cin, author);
        cout << "새로운 출판일 (YYYY-MM-DD): ";
        getline(cin, published_at);
        cout << "새로운 가격: ";
        cin >> price;
        cin.ignore();
        // 대여 가능일 때만 때만 대여가 가능 하게 rental_controller.cpp에서 쿼리문 작성
        cout << "새로운 상태 (대여가능 또는 대여중): ";
        getline(cin, status);
        unique_ptr<sql::PreparedStatement> updateQuery(
            con->prepareStatement(
                "UPDATE books SET title = ?, author = ?, published_at = ?, price = ?, status = ? WHERE book_id = ?"
            )
        );
        updateQuery->setString(1, title);
        updateQuery->setString(2, author);
        updateQuery->setString(3, published_at);
        updateQuery->setInt(4, price);
        updateQuery->setString(5, status);
        updateQuery->setInt(6, book_id);

        int result = updateQuery->executeUpdate();
        if (result > 0)
            cout << result << "책이 수정되었습니다.\n";
        else
            cout << "주어진 ID에 해당하는 책을 찾을 수 없습니다.\n";
    }
    catch (sql::SQLException& e) {
        cerr << "책 수정 실패: " << e.what() << endl;
    }
}

// 도서 삭제
void deleteBook(std::unique_ptr<sql::Connection>& con) {
    try {
        int book_id;
        cout << "삭제할 책 ID를 입력하세요: ";
        cin >> book_id;

        unique_ptr<sql::PreparedStatement> deleteQuery(
            con->prepareStatement("DELETE FROM books WHERE book_id = ?")
        );
        deleteQuery->setInt(1, book_id);

        int result = deleteQuery->executeUpdate();
        if (result > 0)
            cout << result << "책이 삭제되었습니다.\n";
        else
            cout << "ID에 해당하는 책을 찾을 수 없습니다.\n";
    }
    catch (sql::SQLException& e) {
        cerr << "책 삭제 실패: " << e.what() << endl;
    }
}
