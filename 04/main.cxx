#include <iostream>
#include <thread>
//#include <condition_variable>
#include <mutex>
#include <string>

using namespace std;
using namespace std::chrono;

// Global variables
mutex mut;
//condition_variable cv;
bool ready{false};
string sdata{"Empty"};

// Waiting thread
void reader() {
	unique_lock<std::mutex> guard(mut);            // Acquire lock
	//cv.wait(guard);                                // Wait for condition variable to be notified
    while(!ready) {
        mut.unlock();
        this_thread::sleep_for(100ms);
        mut.lock();
    }
	cout << "Data is " << sdata << endl;           // Wake up and use the new value
}

// Modyifing thread
void writer() {
	cout << "Writing data..." << endl;
	{
		//lock_guard<std::mutex> lg(mut);            // Acquire lock
		std::this_thread::sleep_for(2s);           // Pretend to be busy...
		lock_guard<std::mutex> lg(mut);
        ready = true;
		sdata = "Populated";                       // Modify the data
	}
	//cv.notify_one();                               // Notify the condition variable
}

int main() {
	cout << "Data is " << sdata << endl;
	thread read{reader};
    thread write{writer};
	/*
	// If the writer thread finishes before the reader thread starts, the notification is lost
	thread write{writer};
	std::this_thread::sleep_for(500ms);
	thread read{reader};
	*/
	write.join();
	read.join();
}
