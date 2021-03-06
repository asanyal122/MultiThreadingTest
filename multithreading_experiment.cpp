#include<bits/stdc++.h>
using namespace std;

int val1=0,val2=0,val3=0;

void critical1(int num){
	int temp = val1;
	cout<<"Thread "<<this_thread::get_id()<<" going to sleep\n";
	this_thread::sleep_for(chrono::milliseconds(1000));
	cout<<"Thread "<<this_thread::get_id()<<" going to start\n";
	temp+=1;
	val1=temp;
	return;
}


void critical2(int num){
	int temp = val2;
	cout<<"Thread "<<this_thread::get_id()<<" going to sleep\n";
	this_thread::sleep_for(chrono::milliseconds(1000));
	cout<<"Thread "<<this_thread::get_id()<<" going to start\n";
	temp+=1;
	val2=temp;
	return;
}


void critical3(int num){
	int temp = val3;
	cout<<"Thread "<<this_thread::get_id()<<" going to sleep\n";
	this_thread::sleep_for(chrono::milliseconds(1000));
	cout<<"Thread "<<this_thread::get_id()<<" going to start\n";
	temp+=1;
	val3=temp;
	return;
}
int main(void){
	map<int,vector<int>> group;
	group[1].push_back(1);
	group[1].push_back(2);
	group[1].push_back(3);
	group[2].push_back(4);
	group[2].push_back(5);
	
	
	for(auto it:group){
		vector<thread> v;
		for(auto id:it.second){
			if(id%3==1){
				v.push_back(move(thread(critical1,id)));
			}
			else if(id%3==2){
				v.push_back(move(thread(critical2,id)));
			}
			else{
				v.push_back(move(thread(critical3,id)));
			}
		}
		for(auto& t:v){
			t.join();
		}
	}
	
	cout<<val1<<" "<<val2<<" "<<val3<<endl;
	
	return 0;
}
