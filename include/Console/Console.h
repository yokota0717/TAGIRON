//���̃w�b�_���C���N���[�h���AShowConsole()���ĂԂ��ƂŁA�f�o�b�O�p�R���\�[�����o�����܂��B
//printf() scanf() cin cout�ȂǁA�W���I�ȓ��o�͂��\�ƂȂ�܂�
//<����>
//ShowConsole()���X�R�[�v���甲����ƁA�R���\�[���͔j������܂��I

#pragma once
#include <windows.h>
#include <cstdio>
#include <iostream>
namespace ci_ext
{

	//Win32�A�v����cin�Acout��������N���X
	class Console
	{
		std::FILE* in_;
		std::FILE* out_;
	public:
		Console()
		{
			AllocConsole();
			freopen_s(&out_, "CONOUT$", "w", stdout); //�W���o�͂��R���\�[���ɂ���
			freopen_s(&in_, "CONIN$", "r", stdin);  //�W�����͂��R���\�[���ɂ���
		}
		~Console()
		{
			std::fclose(in_);
			std::fclose(out_);
			FreeConsole();
		}
	};

	//cout�Ńf�o�b�O�E�C���h�E�ɏo�͂ł���悤�ɂȂ�N���X
	class coutDbgString
	{
		class DbgStreambuf : public std::streambuf
		{
		public:
			std::streamsize xsputn(const char* s, std::streamsize n)
			{
				OutputDebugString(s);
				return n;
			}
			int_type overflow(int_type c = EOF)
			{
				if (c != EOF)
				{
					char buf[2] = { c, '\0' };
					OutputDebugString(buf);
				}
				return c;
			}
		};
		std::streambuf* default_stream;
		DbgStreambuf debug_stream;
	public:
		coutDbgString()
		{
			default_stream = std::cout.rdbuf(&debug_stream);
		}
		~coutDbgString()
		{
			std::cout.rdbuf(default_stream);
		}
	};

#ifdef _DEBUG
	//�����̓T�|�[�g���Ȃ�
# define ShowConsole() ci_ext::Console c
# define StartOutputDbgString() ci_ext::coutDbgString c
#else
# define ShowConsole() __noop
# define StartOutputDbgString() __noop
#endif

#define dout std::cout << __FUNCTION__ << ":"
#define FILENAME_AND_LINE __FILE__ << ":" << __LINE__
}