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
				timect += cs + q;
				v.push_back(qua);
			}
			else {
				qua.time = ready[j].cpuBurst;
				ready[j].cpuBurst = 0;
				// increase time counter for context swithch and for the time of execution
				timect += cs + ready[j].cpuBurst;
				v.push_back(qua);
			}
			// make  sure it work if they reach at the same time
			// hint for loop
			if (i < arr.size()) {
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
		//}

		if (ready.size() == 0) {
			notFinshed = false;
		}


	}
	
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
	//to find avg W.T
	avgWT(arr);
	//to find avg TT
	avgTT(arr);
     
	//to find cpu UTILIZATION
	cpuUTILIZATION(arr,cs);
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
}
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