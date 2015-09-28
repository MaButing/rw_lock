#ifndef __RW_LOCK_H__
#define __RW_LOCK_H__

#include <mutex>
#include <set>
#include <condition_variable>
#include <cassert> 
#include <thread>

class rw_lock
{
	std::mutex m;
	std::condition_variable cv;
	std::set<std::thread::id> reading;
	std::thread::id writing;

public:
	// rw_lock();
	// rw_lock(const rw_lock&) = delete;
	// rw_lock(const rw_lock&&) = delete;
	// rw_lock& operator =(const rw_lock&) = delete;
	// rw_lock&& operator =(const rw_lock&&) = delete;
	// ~rw_lock();

	void lock_read();
	void unlock_read();
	void lock_write();
	void unlock_write();
};




#endif