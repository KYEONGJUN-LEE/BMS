# 📚 Book Management System

이 프로젝트는 C++로 작성된 도서 대여/반납 관리 시스템으로, MySQL과 연동하여 데이터를 관리합니다.

---

## 📁 폴더 구조

```
book_management/
├── include/   # 헤더 파일 (.h)
│   ├── book_controller.h
│   ├── member_controller.h
│   └── rental_controller.h
├── src/       # 소스 파일 (.cpp)
│   ├── main.cpp
│   ├── book_controller.cpp
│   ├── member_controller.cpp
│   └── rental_controller.cpp
```

---

## ⚙️ 빌드 및 실행 방법

### ✅ Visual Studio 2022에서 빌드하는 방법:
1. **빈 C++ 콘솔 프로젝트 생성**
2. `src/` 폴더 안의 `.cpp` 파일 전부 추가
3. `include/` 폴더 안의 `.h` 파일 전부 추가
4. 프로젝트 우클릭 → `속성(Properties)` →  
   `C/C++ > 일반 > 추가 포함 디렉터리`에 `include` 경로 추가
5. `링커 > 일반 > 추가 라이브러리 디렉터리`에 MySQL 라이브러리 경로 추가
6. `링커 > 입력 > 추가 종속성`에 `libmysql.lib` 추가
7. MySQL 서버 실행 및 DB 연결 정보 확인
8. 빌드 후 실행 (Ctrl + F5)

---

## 🔧 사용 기술 및 구조

- 언어: C++
- 개발 환경: Visual Studio 2022
- DB 연동: MySQL (도서, 회원, 대여 정보 테이블 관리)
- 연동 라이브러리: MySQL Connector/C++
- 설계 구조: 기능별로 분리된 Controller 기반 구조 (book, member, rental)

---

## ✨ 주요 기능

- 도서 등록 및 삭제 (MySQL 저장)
- 회원 등록 및 삭제 (MySQL 저장)
- 도서 대여 및 반납 처리 (MySQL 저장)
- DB 연결 예외 처리 및 쿼리 실행 기능 포함

---

## 🧠 학습 포인트

- C++ 객체지향 설계 및 기능 분리 실습
- 외부 데이터베이스(MySQL) 연동 실습
- SQL 쿼리 작성 및 C++ 연동 경험
- Visual Studio 2022 환경에서의 실제 프로젝트 구성
