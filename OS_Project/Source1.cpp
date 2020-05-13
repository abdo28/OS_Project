#include<iostream>
#include<fstream>
#include<vector>
#include<algorithm>
#include<random>

using namespace std;

struct pcb {
	int id;
	int arrivalTime;
	int cpuBurst;
	int proccesSize;
	int turnedArounedTime;
	int waitingTime;
	int finishTime;
};

// the frame in physical memory
struct frame {
	//int pid;
	int fnum;
	int used;
};


bool compFCFS(pcb a, pcb b) {
	return a.arrivalTime < b.arrivalTime;
}

void toSortProcessesFCFS(vector<pcb>& arr) {
	sort(arr.begin(), arr.end(), compFCFS);
}

int randomGeneratours(vector<int> & avframe) {

	int genindex = rand() % avframe.size();
	int result = avframe[genindex];
	avframe.erase(avframe.begin()+genindex);
	return result;
}
int main() {
	ifstream pin;
	pin.open("process.txt");
	int phym;
	int pages;
	int q;
	int cs;
	vector<pcb>arr(5);//array of struct that have the processes states (pcb)
	pin >> phym;
	pin >> pages;
	pin >> q;
	pin >> cs;
	for (int i = 0; i < 5; i++) {
		pin >> arr[i].id >> arr[i].arrivalTime >> arr[i].cpuBurst >> arr[i].proccesSize;
	}
	
    // number of frames

	
	int frnum = phym / pages;
	// this is litrally the physical memory 
	vector<frame>phymem(frnum);
	vector<int>avframes(frnum);
	for (int i = 0; i < frnum; i++) {
		avframes[i] = i;
	}
	


	// here we are creating the page table for each proccess
	// we can create vector of vector but here we want to create five seperate vectors for the process
	// here we are depending on the indexing of the array not hte process id when it comes on pagetablep*
	//  int innerfreg; we will add this if thet innerfreg is possible at 
	// declaring proccess table for all the processes
	
	toSortProcessesFCFS(arr);
	vector<vector<int>>pagetable(5);
	for (int  i = 0; i < 5; i++)
	{
		vector<int>v;
		pagetable[i] = v;
	}
	// first process " arr index 0 "
	// random generatour
	int avSize = phym;
	for (int i = 0; i < arr.size(); i++)
	{
		if (arr[i].proccesSize <= avSize) {
			int framenum = arr[i].proccesSize / pages;
			for (int j = 0; j <framenum; j++)
			{
				int f = randomGeneratours(avframes);
				pagetable[i].push_back(f);
			
			}
			avSize -= arr[i].proccesSize;
		}
		
		else {
			continue;
		}
	}
	for (int i = 0; i < phymem.size(); i++) {
		phymem[i].fnum = -1;
	}
	for (int i = 0; i < pagetable.size(); i++)
	{
		if (pagetable[i].size() == 0) {
			cout << "there was no room for the procces #"<< arr[i].id;
		}
		else {
			cout << "page table for procces #"<< arr[i].id <<" :";
			for (int j = 0; j < pagetable[i].size(); j++)
			{
				cout << pagetable[i][j] << "   ";
				phymem[pagetable[i][j]].fnum = arr[i].id;
			}
		}
		cout << endl;
	}
	for (int i = 0; i < phymem.size(); i++) {
		for (int j = 0; j < 11; j++) {
			cout << '\'' ;
		}
		cout << endl;
		cout << "|";
		if (phymem[i].fnum == -1) {
			cout << "  ";
			cout << "empty";
			cout << "  ";
		}
		else {
			cout << "    ";
			cout << "p" << phymem[i].fnum;
			cout << "   ";
		}
		cout << "|" << endl;

	}
	for (int j = 0; j < 11; j++) {
		cout << '\'';
	}
	cout << endl;
	int logicalAddr, prid;
	cout << "can you please enter the process id:" << endl;
	cin >> prid;
	cout << "can you please enter a logical address:" << endl;

	cin >> logicalAddr;
	

	int i;
	for (i = 0; i < pagetable.size(); i++)
	{
		if (arr[i].id == prid) {
			break;
		}
	}
	if (pagetable[i].size() == 0) {
		cout << "Warning your proccess is not stored" << endl;
	}
	else {
		int pagenumber = logicalAddr / pages;
		int offset = logicalAddr % pages;
		int pyaddr =( (pagetable[i][pagenumber])*(1+pages))+offset;
		cout << "the physical address : "<<pyaddr << endl;
	}

	



	system("pause");
	return 0;

	
}