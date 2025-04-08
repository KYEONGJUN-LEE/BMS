#include "member_controller.h"
#include <iostream>

using namespace std;

void createMember(std::unique_ptr<sql::Connection>& con) {
    try {
        string name, email, phone;
        
        cout << "회원 이름: ";
        cin.ignore();  // 버퍼 비우기
        getline(cin, name);
        
        cout << "이메일: ";
        getline(cin, email);
        
        cout << "전화번호: ";
        getline(cin, phone);

        unique_ptr<sql::PreparedStatement> createMember(
            con->prepareStatement(
                "INSERT INTO members (name, email, phone, registered_at) "
                "VALUES (?, ?, ?, NOW())"
            )
        );
        createMember->setString(1, name);
        createMember->setString(2, email);
        createMember->setString(3, phone);

        int result = createMember->executeUpdate();
        cout << result << "회원이 등록되었습니다.\n";
    }
    catch (sql::SQLException& e) {
        cerr << "회원 등록 실패: " << e.what() << endl;
    }
}

void listMembers(std::unique_ptr<sql::Connection>& con) {
    try {
        unique_ptr<sql::PreparedStatement> selectQuery(
            con->prepareStatement("SELECT member_id, name, email, phone, registered_at FROM members")
        );
        unique_ptr<sql::ResultSet> res(selectQuery->executeQuery());

        cout << "\n[ 회원 목록 ]\n";
        while (res->next()) {
            cout << "[" << res->getInt("member_id") << "] "
                 << res->getString("name") << " / "
                 << res->getString("email") << " / "
                 << res->getString("phone") << " / "
                 << res->getString("registered_at") << "\n";
        }
    }
    catch (sql::SQLException& e) {
        cerr << "회원 조회 실패: " << e.what() << endl;
    }
}

void updateMember(std::unique_ptr<sql::Connection>& con) {
    try {
        int member_id;
        string name, email, phone;

        cout << "수정할 회원 ID를 입력하세요: ";
        cin >> member_id;
        cin.ignore();

        cout << "새로운 이름: ";
        getline(cin, name);
        cout << "새로운 이메일: ";
        getline(cin, email);
        cout << "새로운 전화번호: ";
        getline(cin, phone);

        unique_ptr<sql::PreparedStatement> updateQuery(
            con->prepareStatement(
                "UPDATE members SET name = ?, email = ?, phone = ? WHERE member_id = ?"
            )
        );
        updateQuery->setString(1, name);
        updateQuery->setString(2, email);
        updateQuery->setString(3, phone);
        updateQuery->setInt(4, member_id);

        int result = updateQuery->executeUpdate();
        if (result > 0)
            cout << result << "회원 정보가 수정되었습니다.\n";
        else
            cout << "해당 ID의 회원을 찾을 수 없습니다.\n";
    }
    catch (sql::SQLException& e) {
        cerr << "회원 수정 실패: " << e.what() << endl;
    }
}

void deleteMember(std::unique_ptr<sql::Connection>& con) {
    try {
        int member_id;
        cout << "삭제할 회원 ID를 입력하세요: ";
        cin >> member_id;

        unique_ptr<sql::PreparedStatement> deleteQuery(
            con->prepareStatement("DELETE FROM members WHERE member_id = ?")
        );
        deleteQuery->setInt(1, member_id);

        int result = deleteQuery->executeUpdate();
        if (result > 0)
            cout << result << "회원이 삭제되었습니다.\n";
        else
            cout << "해당 ID의 회원을 찾을 수 없습니다.\n";
    }
    catch (sql::SQLException& e) {
        cerr << "회원 삭제 실패: " << e.what() << endl;
    }
}
