#ifndef QK_LOG_H
#define QK_LOG_H

#ifndef QK_LOG_ENABLED
#define QK_LOG_ENABLED	0
#endif


// 0 - (don't log)
// 1 - Fatal
// 2 - Error
// 3 - Warning
// 4 - Info
// 5 - Debug
#ifndef QK_LOG_LEVEL
#define QK_LOG_LEVEL	5
#endif

#if QK_LOG_ENABLED
extern char *_qk_log_hdr[];

#define _QK_LOG(level, ...) {						\
	if(level <= QK_LOG_LEVEL) { 					\
		qk_printf("%-5s | ", _qk_log_hdr[level-1]);	\
		qk_printf(__VA_ARGS__); 					\
	}}

#else
#define _QK_LOG(level, ...)		{}
#endif /* QK_LOG_ENABLED */

#define QK_LOG_FATAL(...)		_QK_LOG(1, __VA_ARGS__)
#define QK_LOG_ERROR(...)		_QK_LOG(2, __VA_ARGS__)
#define QK_LOG_WARNING(...)		_QK_LOG(3, __VA_ARGS__)
#define QK_LOG_INFO(...)		_QK_LOG(4, __VA_ARGS__)
#define QK_LOG_DEBUG(...)		_QK_LOG(5, __VA_ARGS__)

#endif /* QK_LOG_H */
