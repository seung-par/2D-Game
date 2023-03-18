#pragma once
// 2D ���� ���α׷���
// gameError.h v1.o
// ���� �������� ������ Error Ŭ����

#define WIN32_LEAN_AND_MEAN
#include <string>
#include <exception>
namespace gameErrorNS
{
    // ���� �ڵ�
    // ������ ������ ���� ������Ѿ� �ϴ� ġ������ ������ ��Ÿ����.
    // ����� ������ ���� �����ų �ʿ䰡 ���� ��� ��Ÿ����.
    const int FATAL_ERROR = -1;
    const int WARNING = 1;
}

// GameError Ŭ����. ���� ������ ���� ������ �������� �� ��������.
// std::exception�� ��ӹ޴´�.
class GameError : public std::exception
{
private:
    int         errorCode;
    std::string message;
public:
    // ����Ʈ ������
    GameError() throw() : errorCode(gameErrorNS::FATAL_ERROR), message("Undefined Error in game.") {}
    // ���� ������
    GameError(const GameError &e) throw() : std::exception(e), errorCode(e.errorCode), message(e.message) {}
    // �Ű������� �ִ� ������
    GameError(int code, const std::string& s) throw() : errorCode(code), message(s) {}
    // �Ҵ� ������
    GameError& operator=(const GameError& rhs) throw()
    {
        std::exception::operator=(rhs);
        this->errorCode = rhs.errorCode;
        this->message = rhs.message;
    }
    // �Ҹ���
    virtual ~GameError() throw() {};
    // ���̽�(Base) Ŭ�����κ��� �������ϴ� �޼ҵ�
    virtual const char* what() const throw() { return this->getMessage(); }
    const char* getMessage() const throw() { return message.c_str(); }
    int getErrorCode() const throw() { return errorCode; }
};

/*
* ������ �ߴ��ؾ� �ϴ� �ߴ��� ������ ������ ��� ������ ���� errorCode�� message �Ű������� ���� GameError Ŭ������ ������ �ȴ�.
* if (FAILED(result))
*   throw (GameError(gameErrorNS::FATAL_ERROR, "Error creating Direct3D device"));
* GameError Ŭ������ ǥ�� ���� Ŭ������ std::exception�� ��ӹ޴´�.
* ǥ�� ���̺귯���� ���� ������ ��� ���ܴ� std::exception�� ��ӹ޴´�.
* std::exception���� ���ܸ� ������ �ڽ��� ���� Ŭ������ ������ std::exception���κ��� ��ӹ��� ��� Ŭ������ ���� �� �ִ�.
*/