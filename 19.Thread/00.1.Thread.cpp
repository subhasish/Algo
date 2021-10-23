/*
 * 00.Thread.cpp
 *
 * Problem: Implement basic thread in C++
 *
 *  Created on: Jul 22, 2018
 *      Author: subha
 */


#include <bits/stdc++.h>
//#include <thread>

using namespace std;

// Solution:
//			Thread runs when constructed.
//			Constructor takes function to run and its parameters as comma separated parameter
//			following the function name.
//
//			Thread.join() will cause main thread to wait for the specific thread to complete.
//			Another way is to detach the thread and let it finish by calling detach(). Main thread
//			should give enough time for it to finish, may sleep for some time.
//
//			this_thread::get_id() prints id of the thread.
//			this_thread::sleep_for(chrono::seconds(n)) sleeps the current thread for n seconds.
//
//			Reference can be passed using ref(variable) syntax.
//			Lambdas are useful in threading as we can pass all available functions to
//			lambda functions easily using capture list.
//
//			Template function can also be used in thread.
//			typeid(Type).name() prints the type name of the type.
//
//			STL constructs can also be passed to thread function. But they have to be explicitly
//			created before passing. Example, passing {...} will not pass value to vector.
//
//			Note that output of two threads can come out as interleaved.
//
//			Number of hardware threads can be estimated from thread::hardware_concurrency()

void ThreadFn(int& v1, int v2)
{
	cout << "T1: Inside the thread function." << endl;
	cout << "T1: Incremented value 1 => " << ++v1 << endl;
//	this_thread::sleep_for(chrono::seconds(1));
	cout << "T1: Value 2 => " << v2 << endl;
	cout << "T1: Id => " << this_thread::get_id() << endl;
}

template<typename T>
void TemplateThreadFn()
{
	cout << "Type is => " << typeid(T).name() << endl; // @suppress("Method cannot be resolved") // @suppress("Invalid overload")
}

void ThreadSTLFn(vector<int> v)
{
	cout << "Size of vector => " << v.size() << endl;
}

int main()
{
	int localval = 100;

	int Num_Threads = thread::hardware_concurrency();
	cout << "Number of hardware threads => " << Num_Threads << endl;

	thread t1 {ThreadFn, ref(localval), 2000};

	// t1.join();  // Not doing it here cause output to be interleaved

	thread t2 {[&](){
		cout << "T2: Inside the thread function." << endl;
		cout << "T2: Incremented value 1 => " << ++localval << endl;
		cout << "T2: Id => " << this_thread::get_id() << endl;
	}};


	t1.join();
	t2.join();

	cout << "Main: value 1 => " << localval << endl;
	cout << "Main: Id => " << this_thread::get_id() << endl;

	thread t3{TemplateThreadFn<int>};
	this_thread::sleep_for(chrono::seconds(1));

	thread t4{TemplateThreadFn<float>};

	t3.join();
	t4.join();

	vector<int> v = {1, 2, 3, 4 , 5};
	thread t5(ThreadSTLFn, v);

	t5.join();

	thread(ThreadFn, ref(localval), 133).detach();
	this_thread::sleep_for(chrono::seconds(1));

}
