#include "rw_lock.h"

//lock & unlock
void rw_lock::lock_read(){
	std::unique_lock<std::mutex> L(m);

	assert(reading.find(std::this_thread::get_id()) == reading.end());
	while (writing != std::thread::id())
		cv.wait(L);	
	
	reading.insert(std::this_thread::get_id());
	L.unlock();
}

void rw_lock::unlock_read(){
	std::unique_lock<std::mutex> L(m);
	
	assert(reading.erase(std::this_thread::get_id()) == 1);
		
	if (reading.empty())
		cv.notify_one();
	
	L.unlock();
}

void rw_lock::lock_write(){
	std::unique_lock<std::mutex> L(m);
	
	assert(writing != std::this_thread::get_id());
	while(writing != std::thread::id() || !reading.empty())
		cv.wait(L);
	
	writing = std::this_thread::get_id();

	L.unlock();
}

void rw_lock::unlock_write(){
	std::unique_lock<std::mutex> L(m);

	assert(writing == std::this_thread::get_id());
	writing = std::thread::id();

	cv.notify_all();

	L.unlock();
}