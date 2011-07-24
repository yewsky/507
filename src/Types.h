#ifndef _TYPES_H_
#define _TYPES_H_

#if (defined(WIN32) || defined(_WIN32))
#	ifndef WIN32_LEAN_AND_MEAN
#		define WIN32_LEAN_AND_MEAN
#	endif
#	include <windows.h>
#   include <guiddef.h>
#endif /* WIN32 */

#if (defined(_WIN32) || defined(WIN32)) 

#else
	typedef struct _GUID {
		unsigned long  Data1;
		unsigned short Data2;
		unsigned short Data3;
		unsigned char  Data4[8];
	} GUID;
#endif /* defined(_WIN32) || defined(WIN32) */
typedef GUID UUID;
#define uuid_t UUID

#ifndef _BOOL_T_DEFINED_
#	define _BOOL_T_DEFINED_
	typedef unsigned char		bool_t;
#	ifndef false
#		define false			0
#	endif /* false */
#	ifndef true
#		define true				1
#	endif /* true */
#endif /* _BOOL_T_DEFINED_ */

/** char_t
 */
#ifndef _CHAR_T_DEFINED_
#	define _CHAR_T_DEFINED_
#	if (defined(UNICODE) || defined(_UNICODE))
#		include <wchar.h>
		typedef wchar_t			char_t;
		typedef wchar_t			uchar_t;
#	else
		typedef char			char_t;
		typedef unsigned char	uchar_t;
#	endif /* UNICODE */
#endif /* _CHAR_T_DEFINED_ */

/** standard int
 */
#ifndef _STDINT_T_DEFINED_
#	define _STDINT_T_DEFINED_
#	if _MSC_VER < 0x1000
		typedef	int					int_t;
		typedef	unsigned int		uint_t;
		typedef signed char			int8_t;
		typedef signed short		int16_t;
		typedef signed int			int32_t;
		typedef signed long long	int64_t;
		typedef unsigned char		uint8_t;
		typedef unsigned short		uint16_t;
		typedef unsigned int		uint32_t;
		typedef unsigned long long	uint64_t;
#	else /* _MSC_VER >= 0x1000 */
#		include <stdint.h>
#	endif /* _MSC_VER */
#endif /* _STDINT_T_DEFINED_ */

#if (defined(WIN32) || defined(_WIN32))
#	define ndvr_decl		__stdcall
#else
#	define ndvr_decl
#endif /* WIN32 */

#ifdef __cplusplus /* c++ support */
#	define ndvr_extern		extern "C"
#else
#	define ndvr_extern
#endif /* __cplusplus */

#endif /* _TYPES_H_ */
