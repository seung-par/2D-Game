#pragma once
// 2D 게임 프로그래밍
// gameError.h v1.o
// 게임 엔진에서 던지는 Error 클래스

#define WIN32_LEAN_AND_MEAN
#include <string>
#include <exception>
namespace gameErrorNS
{
    // 에러 코드
    // 음수는 게임을 강제 종료시켜야 하는 치명적인 에러를 나타낸다.
    // 양수는 게임을 강제 종료시킬 필요가 없는 경고를 나타낸다.
    const int FATAL_ERROR = -1;
    const int WARNING = 1;
}

// GameError 클래스. 게임 엔진을 통해 에러가 감지됐을 때 던져진다.
// std::exception을 상속받는다.
class GameError : public std::exception
{
private:
    int         errorCode;
    std::string message;
public:
    // 디폴트 생성자
    GameError() throw() : errorCode(gameErrorNS::FATAL_ERROR), message("Undefined Error in game.") {}
    // 복사 생성자
    GameError(const GameError &e) throw() : std::exception(e), errorCode(e.errorCode), message(e.message) {}
    // 매개변수가 있는 생성자
    GameError(int code, const std::string& s) throw() : errorCode(code), message(s) {}
    // 할당 연산자
    GameError& operator=(const GameError& rhs) throw()
    {
        std::exception::operator=(rhs);
        this->errorCode = rhs.errorCode;
        this->message = rhs.message;
    }
    // 소멸자
    virtual ~GameError() throw() {};
    // 베이스(Base) 클래스로부터 재정의하는 메소드
    virtual const char* what() const throw() { return this->getMessage(); }
    const char* getMessage() const throw() { return message.c_str(); }
    int getErrorCode() const throw() { return errorCode; }
};

/*
* 게임을 중단해야 하는 중대한 에러를 감지한 경우 다음과 같이 errorCode와 message 매개변수를 가진 GameError 클래스를 던지면 된다.
* if (FAILED(result))
*   throw (GameError(gameErrorNS::FATAL_ERROR, "Error creating Direct3D device"));
* GameError 클래스는 표준 예외 클래스인 std::exception을 상속받는다.
* 표준 라이브러리에 의해 던져진 모든 예외는 std::exception을 상속받는다.
* std::exception으로 예외를 잡으면 자신이 만든 클래스를 포함해 std::exception으로부터 상속받은 모든 클래스를 잡을 수 있다.
*/