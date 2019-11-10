#ifndef __DATA_TYPES_H__
#define __DATA_TYPES_H__

#include <stdint.h>
#include <mutex>
#include <functional>
#include <condition_variable>

typedef uint8_t             u8;
typedef int_least8_t        s8;
typedef uint16_t            u16;
typedef int_least16_t       s16;
typedef uint32_t            u32;
typedef int_least32_t       s32;
typedef uint64_t            u64;
typedef int_least64_t       s64;

typedef std::mutex                    Mutex;
typedef std::function<void()>         Task;
typedef std::condition_variable       Condition;
typedef std::unique_lock<std::mutex>  UniqueLock;

#endif // __DATA_TYPES_H__
