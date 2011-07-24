#ifndef _DEBUG_H_
#define _DEBUG_H_

#include "assert.h"
#include "errno.h"
#include "stdio.h"
#include "string.h"

#ifndef E_FAIL
#define E_FAIL	(-1)
#endif /* E_FAIL */

#ifndef S_OK
#define S_OK	(0)
#endif /* S_OK */

#if (defined(WIN32) || defined(_WIN32))
	static void __printf(const _TCHAR *fmt, ...)
	{
		_TCHAR buff[1024] = {0};
		va_list args;
		va_start(args, text);
		_vsntprintf_s(buff, sizeof(buff), _tcslen(text), fmt, args);
		va_end(args);
		OutputDebugString(buff);
	}
#	define _assert			assert
#	define _perror			__printf
#	define _printf			__printf
#else
#	include <stdio.h>
#	include <unistd.h>
#	define _assert			assert
#	define _perror			perror
#	define _printf			printf
#endif /* WIN32 || _WIN32 */

#if (defined(DEBUG) || defined(_DEBUG))
#	define PERROR(format, args...)		dprintf(STDERR_FILENO, "!!! %s:%d "format": %m\n", __FILE__, __LINE__, ##args)
#	define PRINTF(format, args...)		_printf("*** %s:%d "format, __FILE__, __LINE__, ##args)
#	define ERROR(format, args...)		_printf("!!! %s:%d "format, __FILE__, __LINE__, ##args)
#	define INFO(format, args...)		_printf("::: " format, ##args)
#	define ASSERT(expr)					_assert(expr)
#else
#	define PERROR(format, args...)		do { break; } while(0)
#	define PRINTF(format, args...)		do { break; } while(0)
#	define ERROR(format, args...)		do { break; } while(0)
#	define INFO(format, args...)		do { break; } while(0)
#	define ASSERT(expr)					do { break; } while(0)
#endif /* DEBUG || _DEBUG */

#endif /* _DEBUG_H_ */

