#include<bits/stdc++.h>
using namespace std;

#define NUM_THREADS 3
int val=0;
mutex m;

class myclass {
   static myclass *instance;
   int data;
   atomic_flag lock = ATOMIC_FLAG_INIT;
 
   // Private constructor so that no objects can be created.
   myclass() {
      data = 0;
      cout<<"Constructor called!\n";
   }

   public:
   static myclass *getInstance() {
      if (!instance)
      instance = new myclass;
      return instance;
   }

   int getData() {
      return this -> data;
   }

   void setData(int data) {
      this -> data = data;
   }
   
   void addVal(int val){
   	while(atomic_flag_test_and_set_explicit(&lock,memory_order_acquire));
   	int new_data = this -> data;
   	cout<<this_thread::get_id()<<" going for rest\n";
   	this_thread::sleep_for(chrono::milliseconds(1000));
    cout<<this_thread::get_id()<<" has come from rest\n";	
	new_data = new_data + val;
   	this -> data = new_data;
   	atomic_flag_clear_explicit(&lock,memory_order_release);
   }
};

//Initialize pointer to zero so that it can be initialized in first call to getInstance
myclass *myclass::instance = 0;

void fun(int val){
	myclass *p;
	p=p->getInstance();
	p->addVal(val);
}

int main(void){
	myclass *p = p->getInstance();
	thread t1(fun,1);
	thread t2(fun,2);
	thread t3(fun,3);
	thread t4(fun,4);
	t1.join();
	t2.join();
	t3.join();
	t4.join();
	cout<<p->getData()<<endl;
	return 0;
}
