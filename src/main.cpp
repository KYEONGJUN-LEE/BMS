#include <iostream>
#include <windows.h>
#include <mysql/jdbc.h>
#include "book_controller.h"
#include "member_controller.h"
#include "rental_controller.h"

using namespace std;

std::unique_ptr<sql::Connection> con;

void showMenu() {
    cout << "\n===== 도서 관리 시스템 =====\n";
    cout << "1. 도서 등록\n";
    cout << "2. 도서 목록 보기\n";
    cout << "3. 도서 정보 수정\n";
    cout << "4. 도서 삭제\n";
    cout << "5. 회원 등록\n";
    cout << "6. 회원 목록 보기\n";
    cout << "7. 회원 정보 수정\n";
    cout << "8. 회원 삭제\n";
    cout << "9. 도서 대여\n";
    cout << "10. 도서 반납\n";
    cout << "11. 대여 현황 조회\n";
    cout << "0. 종료\n";
    cout << "===================================\n";
    cout << "선택: ";
}

int main() {
    // 콘솔 출력 인코딩을 UTF-8로 설정 (한글 깨짐 방지)
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    try {
        // mysql 드라이버 생성
        sql::mysql::MySQL_Driver* driver = sql::mysql::get_driver_instance();
        // 데이터베이스 서버에 연결
        con.reset(driver->connect("tcp://127.0.0.1:3306", "root", "1234"));
        // 연결된 클라이언트의 문자셋을 UTF-8로 설정
        con->setClientOption("CHARSET", "utf8mb4");
        // 사용할 데이터베이스를 설정
        con->setSchema("book_management_db");
        cout << "DB 연결 성공!!\n";

        int choice;
        while (true) {
            showMenu();
            cin >> choice;

            switch (choice) {
            case 1: createBook(con); break;
            case 2: listBooks(con); break;
            case 3: updateBook(con); break;
            case 4: deleteBook(con); break;
            case 5: createMember(con); break;
            case 6: listMembers(con); break;
            case 7: updateMember(con); break;
            case 8: deleteMember(con); break;
            case 9: rentBook(con); break;
            case 10: returnBook(con); break;
            case 11: showRentalStatus(con); break;
                
            case 0:
                cout << "프로그램을 종료합니다.\n";
                return 0;

            default:
                cout << "다시 시도해주세요.\n";
                break;
            }
        }
    }
    catch (sql::SQLException& e) {
        cerr << "연결 실패: " << e.what() << endl;
    }
}
