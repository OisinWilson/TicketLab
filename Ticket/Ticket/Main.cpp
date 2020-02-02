#include <iostream>
#include <atomic>
#include <thread>
#include <mutex>
#include <sstream>
#include <SFML/Graphics.hpp>


using namespace std;

const int MAX_TICKETS = 100;

const int n = 5;
atomic_int m_number;
atomic_int m_exitNum;
atomic_int m_turnOrder[n];
int numThreads;
mutex coutMutex;

sf::Vector2f playerVar = { 0 , 0 };

void incrementX() {
	int i = numThreads++;  //Intentional post-increment

	coutMutex.lock();
	cout << "Starting Thread " << i << endl;
	coutMutex.unlock();

	this_thread::sleep_for(chrono::milliseconds(rand() % 500 + 500));

	while (m_number <= MAX_TICKETS)
	{
		//Take a ticket
		m_turnOrder[i] = m_number.fetch_add(1);

		//Using a mutex for output so that threads don't uppercut each other on the console.
		coutMutex.lock();
		cout << "X++ t" << i << "\tTicket No: " << m_turnOrder[i] << endl;
		coutMutex.unlock();

		//Slow down the program so that we can read the console.
		this_thread::sleep_for(chrono::milliseconds(rand() % 500 + 500));

		while (m_turnOrder[i] != m_exitNum)
		{
			continue;
		}

		coutMutex.lock();
		cout << "X++ t" << i << "\tStart Code" << endl;
		coutMutex.unlock();

		//critical section
		playerVar.x++;
		cout << "\tx=" << playerVar.x << " y=" << playerVar.y << endl << endl;

		//exit protocol
		m_exitNum += 1;

		coutMutex.lock();
		//cout << data.str() << endl;
		cout << "X++ t" << i << "\tNext Ticket = " << m_exitNum << endl;
		coutMutex.unlock();
	}
}

void multXYTwo() {
	int i = numThreads++;  //Intentional post-increment

	coutMutex.lock();
	cout << "Starting Thread " << i << endl;
	coutMutex.unlock();

	this_thread::sleep_for(chrono::milliseconds(rand() % 500 + 500));

	while (m_number <= MAX_TICKETS)
	{
		//Take a ticket
		m_turnOrder[i] = m_number.fetch_add(1);

		//Using a mutex for output so that threads don't uppercut each other on the console.
		coutMutex.lock();
		cout << "XY*2 t" << i << "\tTicket No: " << m_turnOrder[i] << endl;
		coutMutex.unlock();

		//Slow down the program so that we can read the console.
		this_thread::sleep_for(chrono::milliseconds(rand() % 500 + 500));

		while (m_turnOrder[i] != m_exitNum)
		{
			continue;
		}

		coutMutex.lock();
		cout << "XY*2 t" << i << "\tStart Code" << endl;
		coutMutex.unlock();

		//critical section
		playerVar.x *= 2;
		playerVar.y *= 2;

		cout << "\tx=" << playerVar.x << " y=" << playerVar.y << endl << endl;
		//exit protocol
		m_exitNum += 1;

		coutMutex.lock();
		//cout << data.str() << endl;
		cout << "XY*2 t" << i << "\tNext Ticket = " << m_exitNum << endl;
		coutMutex.unlock();
	}
}

void decrementY() {
	int i = numThreads++;  //Intentional post-increment

	coutMutex.lock();
	cout << "Starting Thread " << i << endl;
	coutMutex.unlock();

	this_thread::sleep_for(chrono::milliseconds(rand() % 500 + 500));

	while (m_number <= MAX_TICKETS)
	{
		//Take a ticket
		m_turnOrder[i] = m_number.fetch_add(1);

		//Using a mutex for output so that threads don't uppercut each other on the console.
		coutMutex.lock();
		cout << "Y-- t" << i << "\tTicket No: " << m_turnOrder[i] << endl;
		coutMutex.unlock();

		//Slow down the program so that we can read the console.
		this_thread::sleep_for(chrono::milliseconds(rand() % 500 + 500));

		while (m_turnOrder[i] != m_exitNum)
		{
			continue;
		}

		coutMutex.lock();
		cout << "Y-- t" << i << "\tStart Code" << endl;
		coutMutex.unlock();

		//critical section
		playerVar.y--;
		cout << "\tx=" << playerVar.x << " y=" << playerVar.y << endl << endl;

		//exit protocol
		m_exitNum += 1;

		coutMutex.lock();
		//cout << data.str() << endl;
		cout << "Y-- t" << i << "\tNext Ticket = " << m_exitNum << endl;
		coutMutex.unlock();
	}
}

void devideXYTwo() {
	int i = numThreads++;  //Intentional post-increment

	coutMutex.lock();
	cout << "Starting Thread " << i << endl;
	coutMutex.unlock();

	this_thread::sleep_for(chrono::milliseconds(rand() % 500 + 500));

	while (m_number <= MAX_TICKETS)
	{
		//Take a ticket
		m_turnOrder[i] = m_number.fetch_add(1);

		//Using a mutex for output so that threads don't uppercut each other on the console.
		coutMutex.lock();
		cout << "XY/2 t" << i << "\tTicket No: " << m_turnOrder[i] << endl;
		coutMutex.unlock();

		//Slow down the program so that we can read the console.
		this_thread::sleep_for(chrono::milliseconds(rand() % 500 + 500));

		while (m_turnOrder[i] != m_exitNum)
		{
			continue;
		}

		coutMutex.lock();
		cout << "XY/2 t" << i << "\tStart Code" << endl;
		coutMutex.unlock();

		//critical section
		playerVar.x /= 2;
		playerVar.y /= 2;
		cout << "\tx=" << playerVar.x << " y=" << playerVar.y << endl << endl;

		//exit protocol
		m_exitNum += 1;

		coutMutex.lock();
		//cout << data.str() << endl;
		cout << "XY/2 t" << i << "\tNext Ticket = " << m_exitNum << endl;
		coutMutex.unlock();
	}
}


int main(int argc [])
{
	srand(time(NULL));

	numThreads = 0;
	m_number = 1;
	m_exitNum = 1;
	for (int i = 0; i < n; i++)
	{
		m_turnOrder[i] = 0;
	}

	thread t1 = thread(incrementX);
	thread t2 = thread(multXYTwo);
	thread t3 = thread(decrementY);
	thread t4 = thread(devideXYTwo);

	t1.join();
	t2.join();
	t3.join();
	t4.join();

	return 0;
}