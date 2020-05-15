//OS_Project
#include<iostream>
#include<fstream>
#include<vector>
#include<algorithm>
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
struct quant {
	int pid;
	int time;
};
// the frame in physical memory
struct frame {
	//int pid;
	int frameNum;
	int frameUsed;
};
int randomGeneratours(vector<int>& avframe) {

	int genindex = rand() % avframe.size();
	int result = avframe[genindex];
	avframe.erase(avframe.begin() + genindex);
	return result;
}

bool isZero(pcb i)
{
	return i.cpuBurst == 0;
}
int finishTimeOfThePreviosProcess;
bool compSJF(pcb a, pcb b)
{
	//give true value based on the burst time and if is arrived 
	if (a.cpuBurst < b.cpuBurst && a.arrivalTime <= finishTimeOfThePreviosProcess)
		return true;
	else return false;
}

bool compFCFS(pcb a, pcb b) {
	//give true if process a arrived before process b
	//to help sorting based on arrival time 
	if (a.arrivalTime < b.arrivalTime)
		return true;
	else return false;
}


void FCFS(vector<pcb>& arr, int cs) {
	sort(arr.begin(), arr.end(), compFCFS);//sort the processes based on arrival time (FCFS)
	arr[0].waitingTime = 0;//initial value of the first process to be executed
	arr[0].finishTime = arr[0].waitingTime + arr[0].cpuBurst;
	for (int i = 1; i < 5; i++)
		arr[i].finishTime = arr[i - 1].finishTime + cs + arr[i].cpuBurst;

	// to find WT
	arr[0].waitingTime = 0;
	for (int i = 1; i < 5; i++)
		arr[i].waitingTime = arr[i - 1].finishTime + cs - arr[i].arrivalTime;

	//to find TT
	for (int i = 0; i < 5; i++)
		arr[i].turnedArounedTime = arr[i].finishTime - arr[i].arrivalTime;

	//to find WT AVG
	int sumForWT = 0;
	for (int i = 0; i < 5; i++) {
		sumForWT += arr[i].waitingTime;
	}
	cout << "the avg W.T = " << (double)sumForWT / 5 << endl;

	//to find TT AVG
	int sumForTT = 0;
	for (int i = 0; i < 5; i++) {
		sumForTT += arr[i].turnedArounedTime;
	}
	cout << "the avg T.T = " << (double)sumForTT / 5 << endl;
}
void SJF(vector<pcb>& arr, int cs) {
	sort(arr.begin(), arr.end(), compFCFS);//sorting array of processes first, based on arrival time
	//initializ the first process 
	arr[0].finishTime = arr[0].cpuBurst + arr[0].arrivalTime;
	arr[0].turnedArounedTime = arr[0].finishTime - arr[0].arrivalTime;
	arr[0].waitingTime = 0;
	for (int i = 1; i < 5; i++)
	{
		finishTimeOfThePreviosProcess = arr[i - 1].finishTime;
		sort(arr.begin() + i, arr.end(), compSJF);
		arr[i - 1].finishTime < arr[i].arrivalTime ? arr[i].finishTime = cs + arr[i].cpuBurst + arr[i].arrivalTime :
			arr[i].finishTime = arr[i - 1].finishTime + cs + arr[i].cpuBurst;
		arr[i].turnedArounedTime = arr[i].finishTime - arr[i].arrivalTime;
		arr[i].waitingTime = arr[i - 1].finishTime + cs - arr[i].arrivalTime;
	}
	//to find WT AVG
	int sumForWT = 0;
	for (int i = 0; i < 5; i++) {
		sumForWT += arr[i].waitingTime;
	}
	cout << "the avg W.T = " << (double)sumForWT / 5 << endl;

	//to find TT AVG
	int sumForTT = 0;
	for (int i = 0; i < 5; i++) {
		sumForTT += arr[i].turnedArounedTime;
	}
	cout << "the avg T.T = " << (double)sumForTT / 5 << endl;
}
void cpuUTILIZATION(vector<pcb>& arr, int cs) {
	//to find cpu utilization
	int sumForcpuUTILIZATION = 0;
	double avg = 0;
	for (int i = 0; i < 5; i++) {
		sumForcpuUTILIZATION += arr[i].cpuBurst;
	}
	avg = (double(sumForcpuUTILIZATION) / double((sumForcpuUTILIZATION + 4 * cs))) * 100;
	cout << "cpu UTILIZATION = " << avg << endl;
}
void GantChartForRR(vector<quant>& v, int cs) {
	if (cs == 0)
	{
		cout << "|-----------|";
		for (int i = 1; i < v.size(); i++) {

			if (i == v.size()-1) {
				cout << "-----------|";
				continue;
			}
			cout << "-----------|";
		}
		cout << endl;
		cout << "|    " << "p " << v[0].pid << "    |";
		for (int i = 1; i < v.size(); i++) {

			if (i == v.size()-1) {
				cout << "    " << "p " << v[i].pid << "    |";
				continue;
			}
			cout << "    " << "p " << v[i].pid << "    |";
		}
		cout << endl;
		cout << "|-----------|";
		for (int i = 1; i < v.size(); i++) {

			if (i == v.size()-1) {
				cout << "-----------|";
				continue;
			}
			cout << "-----------|";
		}
		cout << endl;
		cout << 0 << "         "
			<< v[0].time;
		int timeF = v[0].time;
		for (int i = 1; i < v.size(); i++) {
			if (i == v.size()-1) {
				timeF += v[i].time;
				cout << "        " << timeF;
				continue;
			}
			timeF += v[i].time;
			cout << "           " << timeF + v[i].time;


		}
		cout << endl;
	}
	else {
		cout << "|-----------|---|";
		for (int i = 1; i < v.size(); i++) {

			if (i == v.size()-1) {
				cout << "-----------|";
				continue;
			}
			cout << "-----------|---|";
		}
		cout << endl;
		cout << "|    " << "p " << v[0].pid << "    |cs |";
		for (int i = 1; i < v.size(); i++) {

			if (i == v.size()-1) {
				cout << "    " << "p " << v[i].pid << "    |";
				continue;
			}
			cout << "    " << "p " << v[i].pid << "    |cs |";
		}
		cout << endl;
		cout << "|-----------|---|";
		for (int i = 1; i < v.size(); i++) {

			if (i == v.size()-1) {
				cout << "-----------|";
				continue;
			}
			cout << "-----------|---|";
		}
		cout << endl;
		cout << 0 << "          "
			<< v[0].time << "  " << v[0].time + cs;
		int resTime = v[0].time + cs;
		for (int i = 1; i < v.size(); i++) {
			if (i == v.size()-1) {
				resTime += v[i].time;
				cout << "          " << resTime << "  ";
				continue;
			}
			resTime += v[i].time;
			cout << "          " << resTime << "  " << resTime + cs;
			resTime += cs;

		}
		cout << endl;
	}
}
void GantChartForFCFSANDSJF(vector<pcb>& arr, int cs) {
	if (cs == 0)
	{
		cout << "|-----------|";
		for (int i = 1; i < 5; i++) {

			if (i == 4) {
				cout << "-----------|";
				continue;
			}
			cout << "-----------|";
		}
		cout << endl;
		cout << "|    " << "p " << arr[0].id << "    |";
		for (int i = 1; i < 5; i++) {

			if (i == 4) {
				cout << "    " << "p " << arr[i].id << "    |";
				continue;
			}
			cout << "    " << "p " << arr[i].id << "    |";
		}
		cout << endl;
		cout << "|-----------|";
		for (int i = 1; i < 5; i++) {

			if (i == 4) {
				cout << "-----------|";
				continue;
			}
			cout << "-----------|";
		}
		cout << endl;
		cout << arr[0].finishTime - arr[0].cpuBurst << "         "
			<< arr[0].finishTime;
		for (int i = 1; i < 5; i++) {
			if (i == 4) {
				cout << "        " << arr[i].finishTime;
				continue;
			}
			cout << "           " << arr[i].finishTime;


		}
		cout << endl;
	}
	else {
		cout << "|-----------|---|";
		for (int i = 1; i < 5; i++) {

			if (i == 4) {
				cout << "-----------|";
				continue;
			}
			cout << "-----------|---|";
		}
		cout << endl;
		cout << "|    " << "p " << arr[0].id << "    |cs |";
		for (int i = 1; i < 5; i++) {

			if (i == 4) {
				cout << "    " << "p " << arr[i].id << "    |";
				continue;
			}
			cout << "    " << "p " << arr[i].id << "    |cs |";
		}
		cout << endl;
		cout << "|-----------|---|";
		for (int i = 1; i < 5; i++) {

			if (i == 4) {
				cout << "-----------|";
				continue;
			}
			cout << "-----------|---|";
		}
		cout << endl;
		cout << arr[0].finishTime - arr[0].cpuBurst << "          "
			<< arr[0].finishTime << "  " << arr[0].finishTime + cs;
		for (int i = 1; i < 5; i++) {
			if (i == 4) {
				cout << "          " << arr[i].finishTime << "  ";
				continue;
			}
			cout << "          " << arr[i].finishTime << "  " << arr[i].finishTime + cs;


		}
		cout << endl;
	}


}

void showInformationForFCFSandSJF(vector<pcb>& arr, int cs) {
	cout << "id" << "\t" << "   arival time" << "\t" << "   cpu burst" << "\t"
		<< "waiting time" << "\t" << "turned arouned time" << "\t" << "   finish time" << endl;
	for (int i = 0; i < 5; i++)
		cout << arr[i].id << "\t\t" << arr[i].arrivalTime
		<< "\t\t" << arr[i].cpuBurst
		<< "\t\t" << arr[i].waitingTime
		<< "\t\t" << arr[i].turnedArounedTime
		<< "\t\t\t" << arr[i].finishTime << endl;
	cout << endl << endl;
	cout << endl;
	GantChartForFCFSANDSJF(arr, cs);
	cout << endl;
	cout << "*****************************************************************************************" << endl;

}
void showInfoRR(vector<pcb>& arr) {
	cout << "id" << "\t" << "   arival time" << "\t" << "   cpu burst" << "\t"
		<< "waiting time" << "\t" << "turned arouned time" << "\t" << "   finish time" << endl;
	for (int i = 0; i < 5; i++)
		cout << arr[i].id << "\t\t" << arr[i].arrivalTime
		<< "\t\t" << arr[i].cpuBurst
		<< "\t\t" << arr[i].waitingTime
		<< "\t\t" << arr[i].turnedArounedTime
		<< "\t\t\t" << arr[i].finishTime << endl;
	cout << endl;
	cout << endl;
}
void showInformationForRR(vector<pcb>& arr, int cs, vector<quant>& v) {
	for (int i = 0; i < arr.size(); i++) {
		arr[i].waitingTime = 0;
		arr[i].finishTime = 0;
		arr[i].turnedArounedTime = 0;
	}
	//waitting time calculating

	for (int i = 0; i < arr.size(); i++) {
		int time = 0;
		bool first = true;
		int tSinceLastFinish = 0;
		for (int j = 0; j < v.size(); j++) {
			if (v[j].pid == arr[i].id) {
				if (first) {
					arr[i].waitingTime = time - arr[i].arrivalTime;
					tSinceLastFinish = time + v[j].time;
					first = false;
				}
				else {
					arr[i].waitingTime += time - tSinceLastFinish;
					tSinceLastFinish = time + v[j].time;
				}
			}
			arr[i].finishTime = tSinceLastFinish;
			arr[i].turnedArounedTime = arr[i].finishTime - arr[i].arrivalTime;
			time += v[j].time + cs;

		}
	}
	cout << "for Round Robin..." << endl;
	//to find WT AVG
	int sumForWT = 0;
	for (int i = 0; i < 5; i++) {
		sumForWT += arr[i].waitingTime;
	}
	cout << "the avg W.T = " << (double)sumForWT / 5 << endl;

	//to find TT AVG
	int sumForTT = 0;
	for (int i = 0; i < 5; i++) {
		sumForTT += arr[i].turnedArounedTime;
	}
	cout << "the avg T.T = " << (double)sumForTT / 5 << endl;
	cpuUTILIZATION(arr, cs);
	showInfoRR(arr);
	GantChartForRR(v, cs);

}
vector<quant> RR(vector<pcb>& arr, int cs, int q) {
	vector<pcb>ready;
	vector<quant>v;
	int timect = 0;
	bool notFinshed = true;
	int i = 0;
	int nop = arr.size();
	bool waitfirst = true;
	while (notFinshed) {
		if (i < arr.size()) {
			if (arr[i].arrivalTime <= timect) {
				ready.push_back(arr[i]);
				i++;
				waitfirst = false;

			}

			else {
				if (waitfirst) {
					timect++;
					continue;
				}
			}

		}
		for (int j = 0; j < ready.size(); j++)
		{
			if (i < arr.size()) {
				if (arr[i].arrivalTime <= timect) {
					ready.push_back(arr[i]);
					i++;

				}

			}
			quant qua;
			qua.pid = ready[j].id;
			if (ready[j].cpuBurst >= q) {
				qua.time = q;
				ready[j].cpuBurst -= q;
				timect += cs + q;
				v.push_back(qua);
			}
			else {
				if (ready[j].cpuBurst > 0) {
					qua.time = ready[j].cpuBurst;
					timect += cs + ready[j].cpuBurst;
					ready[j].cpuBurst = 0;
					v.push_back(qua);
				}
			}
			if (i < arr.size()) {
				if (arr[i].arrivalTime <= timect) {
					ready.push_back(arr[i]);

					i++;

				}

			}

		}
		vector<pcb>::iterator newIter = remove_if(ready.begin(), ready.end(), isZero);
		ready.resize(newIter - ready.begin());

		if (ready.size() == 0) {
			notFinshed = false;
		}
	}
	return v;
}



int main() {
	
	ifstream pin;
	pin.open("process.txt");
	int PhysicalMemorySize;
	int pageSize;
	int q;
	int cs;
	vector<pcb>arr(5);//array of struct that have the processes states (pcb)
	pin >> PhysicalMemorySize;
	pin >> pageSize;
	pin >> q;
	pin >> cs;
	for (int i = 0; i < 5; i++) {
		pin >> arr[i].id >> arr[i].arrivalTime >> arr[i].cpuBurst >> arr[i].proccesSize;
	}
	vector<quant> v;
	vector<pcb>temparr;
	//for FCFS
	int ch;
	cout << "__________________Abd___Amor" << endl;
	cout << "enter one of the choices" << endl;
	cout << "1. part1" << endl;
	cout << "2. part2" << endl;
	cout << "3. exit" << endl;
	cin >> ch;
	while (ch != 3) {
		switch (ch) {
		case 1:
			cout << "For FCFS...." << endl;
			FCFS(arr, cs);
			//to find cpu UTILIZATION
			cpuUTILIZATION(arr, cs);
			//show information about FCFS
			showInformationForFCFSandSJF(arr, cs);

			//for SJF 

			cout << "For SJF...." << endl;
			SJF(arr, cs);
			//find CPU utilization
			cpuUTILIZATION(arr, cs);
			//SHOW INFORMATION ABOUT SJF
			showInformationForFCFSandSJF(arr, cs);
			//RR
			
			for (int i = 0; i < arr.size(); i++)
				temparr.push_back(arr[i]);

			sort(temparr.begin(), temparr.end(), compFCFS);
			 v = RR(temparr, cs, q);
			showInformationForRR(temparr, cs, v);
			system("pause");
			break;
		case 2:
			int frameNum = PhysicalMemorySize / pageSize;
			// this is litrally the physical memory 
			vector<frame>physicalMemory(frameNum);
			vector<int>AvailableFrames(frameNum);
			for (int i = 0; i < frameNum; i++) {
				AvailableFrames[i] = i;
			}



			// here we are creating the page table for each proccess
			// we can create vector of vector but here we want to create five seperate vectors for the process
			// here we are depending on the indexing of the array not hte process id when it comes on pagetablep*
			//  int innerfreg; we will add this if thet innerfreg is possible at 
			// declaring proccess table for all the processes

			sort(arr.begin(), arr.end(), compFCFS);//sort processes based on arrival time 
			vector<vector<int>>pageTable(5);
			for (int i = 0; i < 5; i++)
			{
				vector<int>v;
				pageTable[i] = v;
			}
			// first process " arr index 0 "
			// random generatour
			int AvailableSize = PhysicalMemorySize;
			for (int i = 0; i < arr.size(); i++)
			{
				if (arr[i].proccesSize <= AvailableSize) {
					int framenum = arr[i].proccesSize / pageSize;
					for (int j = 0; j < framenum; j++)
					{
						int f = randomGeneratours(AvailableFrames);
						pageTable[i].push_back(f);

					}
					AvailableSize -= arr[i].proccesSize;
				}

				else {
					continue;
				}
			}
			for (int i = 0; i < physicalMemory.size(); i++) {
				physicalMemory[i].frameNum = -1;
			}
			for (int i = 0; i < pageTable.size(); i++)
			{
				if (pageTable[i].size() == 0) {
					cout << "there was no room for the procces #" << arr[i].id;
				}
				else {
					cout << "page table for procces #" << arr[i].id << ":";
					for (int j = 0; j < pageTable[i].size(); j++)
						cout << "page" << j << "\t";
					cout << endl;
					cout << "\t\t\t";
					for (int j = 0; j < pageTable[i].size(); j++)
					{

						cout << "frame" << pageTable[i][j] << "\t";
						physicalMemory[pageTable[i][j]].frameNum = arr[i].id;
					}
				}
				cout << endl;
			}
			cout << endl;
			cout << "Memory Map Part ...." << endl << endl;
			for (int i = 0; i < physicalMemory.size(); i++) {
				for (int j = 0; j < 11; j++) {
					cout << '\'';
				}
				cout << endl;
				cout << "|";
				if (physicalMemory[i].frameNum == -1) {
					cout << "  ";
					cout << "empty";
					cout << "  ";
				}
				else {
					cout << "    ";
					cout << "p" << physicalMemory[i].frameNum;
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
			for (i = 0; i < pageTable.size(); i++)
			{
				if (arr[i].id == prid) {
					break;
				}
			}
			if (pageTable[i].size() == 0) {
				cout << "Warning your proccess is not stored" << endl;
			}
			else {
				int pagenumber = logicalAddr / pageSize;
				int offset = logicalAddr % pageSize;
				int pyaddr = ((pageTable[i][pagenumber]) * (1 + pageSize)) + offset;
				cout << "the physical address : " << pyaddr << endl;
			}
			system("pause");
			break;
		}
		system("cls");
		cout << "__________________Abd___Amor" << endl;
		cout << "enter one of the choices" << endl;
		cout << "1. part1" << endl;
		cout << "2. part2" << endl;
		cout << "3. exit" << endl;
		cin >> ch;
		
		

	}
	
	return 0;
}

/*
//OS_Project
#include<iostream>
#include<fstream>
#include<vector>
#include<algorithm>
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
struct quant {
	int pid;
	int time;
};
struct LogicalAddress {
	int p;//page number
	int d;//page offset
};
bool isZero(pcb i)
{
	return i.cpuBurst == 0;
}
bool compFCFS(pcb a, pcb b) {
	return a.arrivalTime < b.arrivalTime;
}
int x;
bool compSJF(pcb a, pcb b)
{
	return a.cpuBurst < b.cpuBurst && a.arrivalTime <= x;
}
void toSortProcessesFCFS(vector<pcb>& arr) {
	sort(arr.begin(), arr.end(), compFCFS);
}
void toSortProcessesSJF(vector<pcb>& arr, int i) {
	sort(arr.begin() + i, arr.end(), compSJF);
}
void finishTimeForFCFS(vector<pcb>& arr, int cs) {
	arr[0].waitingTime = 0;
	arr[0].finishTime = arr[0].waitingTime + arr[0].cpuBurst;
	for (int i = 1; i < 5; i++)
		arr[i].finishTime = arr[i - 1].finishTime + cs + arr[i].cpuBurst;
}
void WTforFCFS(vector<pcb>& arr, int cs) {
	for (int i = 1; i < 5; i++)
		arr[i].waitingTime = arr[i - 1].finishTime + cs - arr[i].arrivalTime;
}
void showProcesses(vector<pcb>& arr) {
	for (int i = 0; i < 5; i++)
		cout << arr[i].id << " " << arr[i].arrivalTime << " " << arr[i].cpuBurst << endl;
	cout << endl;
}
void TTforFCFS(vector<pcb>& arr) {
	for (int i = 0; i < 5; i++)
		arr[i].turnedArounedTime = arr[i].cpuBurst + arr[i].waitingTime;
}
void avgWT(vector<pcb>& arr) {
	int sumForWT = 0;
	for (int i = 0; i < 5; i++) {
		sumForWT += arr[i].waitingTime;
	}
	cout << "the avg W.T = " << (double)sumForWT / 5 << endl;
}
void avgTT(vector<pcb>& arr) {
	int sumForTT = 0;
	for (int i = 0; i < 5; i++) {
		sumForTT += arr[i].turnedArounedTime;
	}
	cout << "the avg T.T = " << (double)sumForTT / 5 << endl;
}
void cpuUTILIZATION(vector<pcb>& arr, int cs) {
	int sumForcpuUTILIZATION = 0;
	double avg = 0;
	for (int i = 0; i < 5; i++) {
		sumForcpuUTILIZATION += arr[i].cpuBurst;
	}
	avg = (double(sumForcpuUTILIZATION) / double((sumForcpuUTILIZATION + 5 * cs))) * 100;
	cout << "cpu UTILIZATION = " << avg << endl;
}
void showInformation(vector<pcb>& arr) {
	cout << "id    " << "arival time      " << "cpu burst      "
		<< "waiting time     " << "turned arouned time      " << "finish time          " << endl;
	for (int i = 0; i < 5; i++)
		cout << arr[i].id << "      " << arr[i].arrivalTime
		<< "                   " << arr[i].cpuBurst
		<< "                " << arr[i].waitingTime
		<< "                        " << arr[i].turnedArounedTime
		<< "               " << arr[i].finishTime << endl;
	cout << endl << endl;
	int gants = 0;
	for (int hh = 0; hh < arr.size(); hh++) {
		gants += arr[hh].cpuBurst;
	}
	for (int hhh = 0; hhh < gants + arr.size() + 1; hhh++) {
		cout << ",";
	}
	cout << endl;
	cout << "|";
	for (int hh = 0; hh < arr.size(); hh++) {
		if ((arr[hh].cpuBurst - 2) % 2 == 0) {
			for (int k = 0; k < ((arr[hh].cpuBurst - 2) / 2); k++) {
				cout << " ";
			}
			cout << "p" << arr[hh].id;
			for (int k = 0; k < ((arr[hh].cpuBurst - 2) / 2); k++) {
				cout << " ";
			}
			cout << "|";
		}
		else {
			for (int k = 0; k < ((arr[hh].cpuBurst - 2) / 2) + 1; k++) {
				cout << " ";
			}
			cout << "p" << arr[hh].id;
			for (int k = 0; k < ((arr[hh].cpuBurst - 2) / 2); k++) {
				cout << " ";
			}
			cout << "|";
		}

	}
	cout << endl;
	for (int hhh = 0; hhh < gants + arr.size() + 1; hhh++) {
		cout << "\'";
	}
	cout << endl;
	cout << "*****************************************************************************************" << endl;

}
void showInformationRR(vector<pcb>& arr) {
	cout << "id    " << "arival time      " << "cpu burst      "
		<< "waiting time     " << "turned arouned time      " << "finish time          " << endl;
	for (int i = 0; i < 5; i++)
		cout << arr[i].id << "      " << arr[i].arrivalTime
		<< "                   " << arr[i].cpuBurst
		<< "                " << arr[i].waitingTime
		<< "                        " << arr[i].turnedArounedTime
		<< "               " << arr[i].finishTime << endl;
	cout << endl;
	cout << endl;
}
void SJFsortAndFindParameters(vector<pcb>& arr, int cs) {

	//initializ the first process 
	arr[0].finishTime = arr[0].cpuBurst + arr[0].arrivalTime;
	arr[0].turnedArounedTime = arr[0].finishTime - arr[0].arrivalTime;
	arr[0].waitingTime = 0;
	for (int i = 1; i < 5; i++)
	{
		x = arr[i - 1].finishTime;
		toSortProcessesSJF(arr, i);
		if (arr[i - 1].finishTime < arr[i].arrivalTime)
		{
			arr[i].finishTime = cs + arr[i].cpuBurst + arr[i].arrivalTime;
		}
		else
		{
			arr[i].finishTime = arr[i - 1].finishTime + cs + arr[i].cpuBurst;
		}
		arr[i].waitingTime = arr[i - 1].finishTime + cs - arr[i].arrivalTime;
		arr[i].turnedArounedTime = arr[i].cpuBurst + arr[i].waitingTime;
	}
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
	cout << phym << endl;
	cout << pages << endl;
	cout << q << endl;
	cout << cs << endl;
	for (int i = 0; i < 5; i++) {
		cout << arr[i].id << " " << arr[i].arrivalTime << " " << arr[i].cpuBurst << " " << arr[i].proccesSize << endl;
	}
	//for FCFS
	toSortProcessesFCFS(arr);
	//to find finish time 
	finishTimeForFCFS(arr, cs);
	//to find W.T
	WTforFCFS(arr, cs);
	//to find T.T
	TTforFCFS(arr);
	cout << "For FCFS...." << endl;
	//to find avg W.T
	avgWT(arr);
	//to find avgT.T
	avgTT(arr);
	//to find cpu UTILIZATION
	cpuUTILIZATION(arr, cs);
	//show information about FCFS
	showInformation(arr);

	//for SJF 
	toSortProcessesFCFS(arr);//sorting based on arrival time first 
	//to find parameters
	SJFsortAndFindParameters(arr, cs);
	cout << "For SJF...." << endl;
	//to find avg W.T
	avgWT(arr);
	//to find avg T.T
	avgTT(arr);
	//to find cpu UTILIZATION
	cpuUTILIZATION(arr, cs);
	//SHOW INFORMATION ABOUT SJF
	showInformation(arr);



	
	//cout << arr.size() << endl;
	for (int i = 0; i < arr.size(); i++) {
		arr[i].waitingTime = 0;
		arr[i].finishTime = 0;
		arr[i].turnedArounedTime = 0;
	}
	//waitting time calculating

	for (int i = 0; i < arr.size(); i++) {
		int time = 0;
		bool first = true;
		int tSinceLastFinish = 0;
		for (int j = 0; j < v.size(); j++) {
			if (v[j].pid == arr[i].id) {
				if (first) {
					if (time > arr[i].arrivalTime) {
						arr[i].waitingTime = time - arr[i].arrivalTime;
					}
					else {
						arr[i].waitingTime = 0;
					}
					tSinceLastFinish = time + v[j].time;
					first = false;
				}
				else {
					arr[i].waitingTime += time - tSinceLastFinish;
					tSinceLastFinish = time + v[j].time;
				}
			}
			arr[i].finishTime = tSinceLastFinish;
			arr[i].turnedArounedTime = arr[i].finishTime - arr[i].arrivalTime;
			time += v[j].time + cs;

		}
	}
	cout << "for Round Robin..." << endl;
	//to find avg W.T
	avgWT(arr);
	//to find avg TT
	avgTT(arr);

	//to find cpu UTILIZATION
	int sumForcpuUTILIZATION = 0;
	double avg = 0;
	for (int i = 0; i < 5; i++) {
		sumForcpuUTILIZATION += arr[i].cpuBurst;
	}
	int ncs = (v.size()-1)*cs;
	avg = (double(sumForcpuUTILIZATION) / double((sumForcpuUTILIZATION + 4 * ncs))) * 100;
	cout << "cpu UTILIZATION = " << avg << endl;
	showInformationRR(arr);
	int gants = 0;
	for (int hh = 0; hh < v.size(); hh++) {
		gants += v[hh].time;
	}
	for (int hhh = 0; hhh < gants + v.size() + 3; hhh++) {
		cout << ",";
	}
	cout << endl;
	cout << "|";
	for (int hh = 0; hh < v.size(); hh++) {
		if ((v[hh].time - 2) % 2 == 0) {
			for (int k = 0; k < ((v[hh].time - 2) / 2); k++) {
				cout << " ";
			}
			cout << "p" << v[hh].pid;
			for (int k = 0; k < ((v[hh].time - 2) / 2); k++) {
				cout << " ";
			}
			cout << "|";
		}
		else {
			for (int k = 0; k < ((v[hh].time - 2) / 2) + 1; k++) {
				cout << " ";
			}
			cout << "p" << v[hh].pid;
			for (int k = 0; k < ((v[hh].time - 2) / 2); k++) {
				cout << " ";
			}
			cout << "|";
		}

	}
	cout << endl;
	for (int hhh = 0; hhh < gants + v.size() + 3; hhh++) {
		cout << "\'";
	}
	cout << endl;
	cout << "*****************************************************************************************" << endl;

	system("pause");
	return 0;
}*/
/*

#include<iostream>
#include<fstream>
#include<vector>
#include<algorithm>


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
struct quant {
	int pid;
	int time;
};
bool isZero(pcb i )
{
	return i.cpuBurst == 0;
}
bool compFCFS(pcb a, pcb b) {
	return a.arrivalTime < b.arrivalTime;
}
int x;
bool compSJF(pcb a, pcb b)
{
	return a.cpuBurst < b.cpuBurst && a.arrivalTime <= x;
}
void toSortProcessesFCFS(vector<pcb>& arr) {
	sort(arr.begin(), arr.end(), compFCFS);
}
void toSortProcessesSJF(vector<pcb>& arr, int i) {
	sort(arr.begin() + i, arr.end(), compSJF);

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

	//for FCFS
	for (int i = 0; i < 5; i++)
		cout << arr[i].id << " " << arr[i].arrivalTime << " " << arr[i].cpuBurst << endl;
	cout << endl;
	toSortProcessesFCFS(arr);

	//to find finish time 
	arr[0].waitingTime = 0;
	arr[0].finishTime = arr[0].waitingTime + arr[0].cpuBurst;
	for (int i = 1; i < 5; i++)
		arr[i].finishTime = arr[i - 1].finishTime + cs + arr[i].cpuBurst;
	//to find W.T
	for (int i = 1; i < 5; i++)
		arr[i].waitingTime = arr[i - 1].finishTime + cs - arr[i].arrivalTime;
	//to find T.T 
	for (int i = 0; i < 5; i++)
		arr[i].turnedArounedTime = arr[i].cpuBurst + arr[i].waitingTime;
	//to find avg W.T
	int sumForWT = 0;
	for (int i = 0; i < 5; i++) {
		sumForWT += arr[i].waitingTime;
	}
	cout << "the avg W.T = " << sumForWT / 5 << endl;
	//to find avgT.T
	int sumForTT = 0;
	for (int i = 0; i < 5; i++) {
		sumForTT += arr[i].turnedArounedTime;
	}
	cout << "the avg T.T = " << sumForTT / 5 << endl;
	//to find cpu UTILIZATION
	int sumForcpuUTILIZATION = 0;
	double avg = 0;
	for (int i = 0; i < 5; i++) {
		sumForcpuUTILIZATION += arr[i].cpuBurst;
	}
	avg = (double(sumForcpuUTILIZATION) / double((sumForcpuUTILIZATION + 5 * cs))) * 100;
	cout << "cpu UTILIZATION = " << avg << endl;
	cout << "id    " << "arival time      " << "cpu burst      "
		<< "waiting time     " << "turned arouned time      " << "finish time          " << endl;
	for (int i = 0; i < 5; i++)
		cout << arr[i].id << "      " << arr[i].arrivalTime
		<< "                   " << arr[i].cpuBurst
		<< "                " << arr[i].waitingTime
		<< "                        " << arr[i].turnedArounedTime
		<< "               " << arr[i].finishTime << endl;

	cout << "*********************************************************" << endl;
	
	//for SJF 
	toSortProcessesFCFS(arr);//sorting based on arrival time first 
	//to find waiting time 
	//initializ the first process in ready queue
	arr[0].finishTime = arr[0].cpuBurst + arr[0].arrivalTime;
	arr[0].turnedArounedTime = arr[0].finishTime - arr[0].arrivalTime;
	arr[0].waitingTime = 0;
	for (int i = 1; i < 5; i++)
	{
		x = arr[i - 1].finishTime;
		toSortProcessesSJF(arr, i);
		if (arr[i - 1].finishTime < arr[i].arrivalTime)
		{
			arr[i].finishTime = cs + arr[i].cpuBurst + arr[i].arrivalTime;
		}
		else
		{
			arr[i].finishTime = arr[i - 1].finishTime + cs + arr[i].cpuBurst;
		}
		arr[i].waitingTime = arr[i - 1].finishTime + cs - arr[i].arrivalTime;
		arr[i].turnedArounedTime = arr[i].cpuBurst + arr[i].waitingTime;
	}
	//to find avg W.T
	sumForWT = 0;
	for (int i = 0; i < 5; i++) {
		sumForWT += arr[i].waitingTime;
	}
	cout << "the avg W.T = " << sumForWT / 5 << endl;
	//to find avg T.T
	sumForTT = 0;
	for (int i = 0; i < 5; i++) {
		sumForTT += arr[i].turnedArounedTime;
	}
	cout << "the avg T.T = " << sumForTT / 5 << endl;
	//to find cpu UTILIZATION
	sumForcpuUTILIZATION = 0;
	avg = 0;
	for (int i = 0; i < 5; i++) {
		sumForcpuUTILIZATION += arr[i].cpuBurst;
	}
	avg = (double(sumForcpuUTILIZATION) / double((sumForcpuUTILIZATION + 5 * cs))) * 100;
	cout << "cpu UTILIZATION = " << avg << endl;
	cout << "id    " << "arival time      " << "cpu burst      "
		<< "waiting time     " << "turned arouned time      " << "finish time          " << endl;
	for (int i = 0; i < 5; i++)
		cout << arr[i].id << "      " << arr[i].arrivalTime
		<< "                   " << arr[i].cpuBurst
		<< "                " << arr[i].waitingTime
		<< "                        " << arr[i].turnedArounedTime
		<< "               " << arr[i].finishTime << endl;
	cout << "*********************************************************" << endl;




	// RR
	toSortProcessesFCFS(arr);
	// USE q
	vector<pcb> ready;
	vector<quant>v;
	int timect = 0;
	bool notFinshed = true;
	int i = 0;
	int nop = arr.size();
	while (notFinshed) {
		if (i < arr.size()) {
			if (arr[i].arrivalTime <= timect) {
				ready.push_back(arr[i]);
				i++;
			}
			else {
				timect++;
				continue;
			}
		}
		for (int j = 0; j < ready.size(); j++)
		{
			quant qua;
			qua.pid = ready[j].id;
			if (ready[j].cpuBurst > q) {
				qua.time = q;
				ready[j].cpuBurst -= q;
				timect += 1 + q;
				v.push_back(qua);
			}
			else {
				qua.time = ready[j].cpuBurst;
				ready[j].cpuBurst = 0;
				// increase time counter for context swithch and for the time of execution
				timect += 1 + ready[j].cpuBurst;
				v.push_back(qua);
			}
			// make  sure it work if they reach at the same time
			// hint for loop
			if (i < arr.size() ) {
				if (arr[i].arrivalTime <= timect) {
					ready.push_back(arr[i]);
					i++;
				}
			}
			
		}
		
		vector<pcb>::iterator newIter = remove_if(ready.begin(), ready.end(), isZero);
		ready.resize(newIter - ready.begin()); 
		//for (auto ii = ready.begin(); ii != ready.end(); ++ii) {
			//if (ii->cpuBurst == 0) {
				//ready.erase(ii);
					//ii--;
			//}
		// HAHAHAHA
		//}

		if (ready.size()==0) {
			notFinshed = false;
		}
		

	}
	int gants = 0;
	for (int hh = 0; hh < v.size(); hh++) {
		gants += v[hh].time;
	}
	for (int hhh = 0; hhh < gants + v.size()+3; hhh++) {
		cout << ",";
	}
	cout << endl;
	cout << "|";
	for (int hh = 0; hh < v.size(); hh++) {
		if ((v[hh].time - 2) % 2 == 0) {
			for (int k = 0; k < ((v[hh].time-2) / 2);k++) {
				cout << " ";
			}
			cout << "p" << v[hh].pid;
			for (int k = 0; k < ((v[hh].time - 2) / 2); k++) {
				cout << " ";
			}
			cout << "|";
		}
		else {
			for (int k = 0; k < ((v[hh].time - 2) / 2)+1; k++) {
				cout << " ";
			}
			cout << "p" << v[hh].pid;
			for (int k = 0; k < ((v[hh].time - 2) / 2); k++) {
				cout << " ";
			}
			cout << "|";
		}
		
	}
	cout << endl;
	for (int hhh = 0; hhh < gants+v.size()+3; hhh++) {
		cout << "\'";
	}
	cout << endl;
	cout << arr.size() << endl;
	for (int i = 0; i < arr.size(); i++) {
		arr[i].waitingTime = 0;
		arr[i].finishTime = 0;
		arr[i].turnedArounedTime = 0;
	}
	//waitting time calculating

	for (int i = 0; i < arr.size(); i++) {
		int time = 0;
		bool first = true;
		int tSinceLastFinish = 0;
		for (int j = 0; j < v.size(); j++) {
			if (v[j].pid == arr[i].id) {
				if (first) {
					arr[i].waitingTime = time - arr[i].arrivalTime;
					tSinceLastFinish = time + v[j].time;
					first = false;
				}
				else {
					arr[i].waitingTime += time - tSinceLastFinish;
					tSinceLastFinish = time + v[j].time;
				}
			}
			arr[i].finishTime = tSinceLastFinish;
			arr[i].turnedArounedTime = arr[i].finishTime - arr[i].arrivalTime;
			time += v[j].time + 1;

		}
	}
	//to find avg W.T
	sumForWT = 0;
	for (int i = 0; i < 5; i++) {
		sumForWT += arr[i].waitingTime;
	}
	cout << "the avg W.T = " << sumForWT / 5 << endl;
	//to find avg T.T
	sumForTT = 0;
	for (int i = 0; i < 5; i++) {
		sumForTT += arr[i].turnedArounedTime;
	}
	cout << "the avg T.T = " << sumForTT / 5 << endl;
	//to find cpu UTILIZATION
	sumForcpuUTILIZATION = 0;
	avg = 0;
	for (int i = 0; i < 5; i++) {
		sumForcpuUTILIZATION += arr[i].cpuBurst;
	}
	avg = (double(sumForcpuUTILIZATION) / double((sumForcpuUTILIZATION + 5 * cs))) * 100;
	cout << "cpu UTILIZATION = " << avg << endl;
	cout << "id    " << "arival time      " << "cpu burst      "
		<< "waiting time     " << "turned arouned time      " << "finish time          " << endl;
	for (int i = 0; i < 5; i++)
		cout << arr[i].id << "      " << arr[i].arrivalTime
		<< "                   " << arr[i].cpuBurst
		<< "                " << arr[i].waitingTime
		<< "                        " << arr[i].turnedArounedTime
		<< "               " << arr[i].finishTime << endl;
	cout << "*********************************************************" << endl;

	

	system("pause");
	return 0;
}*/