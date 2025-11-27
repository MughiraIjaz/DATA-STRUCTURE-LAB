#include <iostream>
#include <queue>
#include <unistd.h>

using namespace std;

int main() {
	queue<int> store;
queue<int> mag;

int total = 100;
int magCap = 20;
int secs = 0;

for(int i=0;i<total;i++){
    store.push(1);
}

for(int i=0;i<magCap && !store.empty();i++){
    mag.push(store.front());
    store.pop();
}

cout << "Starting load: " << mag.size() << " bullets\n";

while(!mag.empty()){

    sleep(1);
    secs++;
    mag.pop();
    cout << "Fired 1 bullet, mag left: " << mag.size() << endl;

    if(!store.empty()){
        sleep(1);
        secs++;
        mag.push(store.front());
        store.pop();
        cout << "Reloaded 1 bullet, mag now: " << mag.size() << endl;
    }
}

cout << "All bullets fired in " << secs << " seconds" << endl;

return 0;
}