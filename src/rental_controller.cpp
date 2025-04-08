#include "rental_controller.h"
#include <iostream>

using namespace std;

// 도서 대여 함수
void rentBook(std::unique_ptr<sql::Connection>& con) {
    try {
        int book_id, member_id;

        cout << "대여할 책의 ID를 입력해주세요: ";
        cin >> book_id;

        cout << "대여할 회원의 ID를 입력해주세요: ";
        cin >> member_id;

        // 1. 해당 책이 대여 가능한지 확인하고 '대여중'으로 상태 변경
        unique_ptr<sql::PreparedStatement> updateBookStatus(
            con->prepareStatement(
                "UPDATE books SET status = '대여중' WHERE book_id = ? AND status = '대여가능'"
            )
        );
        updateBookStatus->setInt(1, book_id);
        int updated = updateBookStatus->executeUpdate();

        if (updated == 0) {
            cout << "이미 대여중인 책입니다..\n";
            return;
        }

        // 2. rentals 테이블에 대여 기록 삽입 (returned_at은 NULL)
        unique_ptr<sql::PreparedStatement> insertRental(
            con->prepareStatement(
                "INSERT INTO rentals (book_id, member_id, rented_at, returned_at) "
                "VALUES (?, ?, NOW(), NULL)"
            )
        );
        insertRental->setInt(1, book_id);
        insertRental->setInt(2, member_id);
        insertRental->executeUpdate();

        cout << "성공적인 대여입니다.\n";
    }
    catch (sql::SQLException& e) {
        cerr << "도서 대여 실패: " << e.what() << endl;
    }
}

// 도서 반납 함수
void returnBook(std::unique_ptr<sql::Connection>& con) {
    try {
        int book_id, member_id;

        cout << "반납할 책의 ID를 입력해주세요: ";
        cin >> book_id;
        cout << "반납하는 회원의 ID를 입력해주세요: ";
        cin >> member_id;

        // 1. rentals 테이블에서 반납일 갱신
        unique_ptr<sql::PreparedStatement> updateRental(
            con->prepareStatement(
                "UPDATE rentals SET returned_at = NOW() "
                "WHERE book_id = ? AND member_id = ? AND returned_at IS NULL"
            )
        );
        updateRental->setInt(1, book_id);
        updateRental->setInt(2, member_id);
        int updatedRental = updateRental->executeUpdate();

        if (updatedRental == 0) {
            cout << "대여중이 아닙니다.\n";
            return;
        }

        // 2. books 테이블 상태를 '대여가능'으로 변경
        unique_ptr<sql::PreparedStatement> updateBookStatus(
            con->prepareStatement(
                "UPDATE books SET status = '대여가능' WHERE book_id = ?"
            )
        );
        updateBookStatus->setInt(1, book_id);
        updateBookStatus->executeUpdate();

        cout << "도서가 반납되었습니다.\n";
    }
    catch (sql::SQLException& e) {
        cerr << "도서 반납 실패: " << e.what() << endl;
    }
}

// 대여 현황 조회 함수
void showRentalStatus(std::unique_ptr<sql::Connection>& con) {
    try {
        unique_ptr<sql::PreparedStatement> rentalStatusQuery(
            con->prepareStatement(
                "SELECT b.book_id, b.title, b.author, r.member_id, m.name, r.rented_at, r.returned_at "
                "FROM rentals r "
                "JOIN books b ON r.book_id = b.book_id "
                "JOIN members m ON r.member_id = m.member_id "
                "WHERE r.returned_at IS NULL"
            )
        );
        unique_ptr<sql::ResultSet> res(rentalStatusQuery->executeQuery());

        cout << "\n[ 대여 현황 ]\n";
        while (res->next()) {
            cout << "책 ID: " << res->getInt("book_id") << " / "
                << "책 제목: " << res->getString("title") << " / "
                << "저자: " << res->getString("author") << " / "
                << "회원 ID: " << res->getInt("member_id") << " / "
                << "회원 이름: " << res->getString("name") << " / "
                << "대여일: " << res->getString("rented_at") << "\n";
        }
    }
    catch (sql::SQLException& e) {
        cerr << "대여 현황 조회 실패: " << e.what() << endl;
    }
}