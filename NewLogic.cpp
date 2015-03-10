#include <stdio.h>
#include <stdlib.h>

#include <semaphore.h>
#include <pthread.h>

#include <fstream>
#include <iostream>
#include <string.h>

#include <sys/timeb.h>
#include <unistd.h>


#include <map>
#include <set>
#include <numeric>
#include <functional>
#include <algorithm>
using namespace std;

#define NUMTHREADS 100
sem_t mutex;
sem_t mutextext;

typedef map<int, map<int, long> > newDS;
typedef map<int, map<int, long> >::iterator newItr;
typedef map<int, long>::iterator subItr;
newDS g_newDS;

//typedef map<int, multiset<int> > mmap;
//typedef map<int, multiset<int> >::iterator  mitr;
//mmap g_map;

typedef map<int, long> mResults;
mResults g_results;
int g_counter;
int g_millionRecCount;

//void storeDataNew(string& str);
void storeData(string& str);
void UpdateCount(const int& n, const long& count);

//void* processNumberNew(void* pNum);
void* processNumber(void* pNum);
void* displayProc(void* param);

int GetMilliCount();
int GetMilliSpan(int nStartTime);
long readInputFile(const char* filePath);

class mLock{
public:
    mLock(sem_t* p){
        m_p = p;
        sem_wait(m_p);
    }

    ~mLock(){
        sem_post(m_p);
    }

private:
    sem_t* m_p;
};

int main(int argc, char* argv[])
{
	if(argc < 3)
	{
		printf("USAGE is ./readMyFileNew [Data] [Lookup].\n [Data] - is the name of the file to process\n [Lookup] - is the file containing the lookup data\n\n");
		exit(1);
	}
	//printf("To enable repeat processing, use ./readMyFile [-r]\n");

	g_counter = 0;
	g_millionRecCount = 0;

	bool askForRepeat = false;
	char rep[] = "-r";
	char* arg1 = argv[1];
	char* arg2 = argv[2];
	char* arg3 = argv[3];

	if(argc == 4 && strcmp(arg3,rep) == 0)
	{
		askForRepeat = true;
	}

	printf("Reading data\n");

	//initialise semaphore for controlling the output
	sem_init(&mutex,0,1);
	sem_init(&mutextext,0,1);

	//store results. not used
	for(int i = 0; i <= 100; i++)
	{
		g_results.insert(make_pair(i,-1));
	}

	//initialise thread handles
	pthread_t thread[NUMTHREADS];
	int arr[NUMTHREADS];
	for(int n = 0; n < NUMTHREADS; n++)
	{
		arr[n] = -1;
	}

	//track time to load data
	int nTimeStart = GetMilliCount();

	long recCount = readInputFile(arg1);

	//calculate time taken to load data
	int timeElapsed(0);
	timeElapsed = GetMilliSpan(nTimeStart);
	double d = (double)(recCount/1000000.00);

    {
        mLock obj(&mutextext);
        printf("\nLoaded %.1f million records in %d milliseconds\n",d,timeElapsed);
    }



	//search loop. checks with user whether to do the search again in case of changed search criteria
	int nRunningThreads(0);
	bool bContinue = true;
	int c;
	do
	{
		timeElapsed = 0;

		bContinue = false;

        {
            mLock obj(&mutextext);
            nTimeStart = GetMilliCount();
            printf("Processing data.................\n\n");
        }

		for(int n = 0; n <  nRunningThreads; n++)
		{
			arr[n] = -1;
		}

		nRunningThreads = 0;

		//read input.txt and search through the data
		ifstream fileIn(arg2, std::ifstream::in);
		if(fileIn)
		{
			string numbers;

			while(!fileIn.eof())
			{
                int temp(0);
				//use a thread for each search
				getline(fileIn, numbers);
				if(false == numbers.empty()){
					temp = arr[nRunningThreads] = atoi(numbers.c_str());
					pthread_create(&thread[nRunningThreads], NULL, processNumber, (void*)&arr[nRunningThreads]);
					nRunningThreads++;
				}
			}

			fileIn.close();
		}

		//wait for threads to completeNULL
		for(int t = 0; t < nRunningThreads; t++)
		{
			pthread_join(thread[t], NULL);
		}

		//meanwhile we are tracking time taken
        {
            mLock obj(&mutextext);
            timeElapsed = GetMilliSpan(nTimeStart);
            printf("\nTime taken : %d milliseconds\n",timeElapsed);
        }

		if(true == askForRepeat)
		{
			//check with user to continue. maybe for different input.txt
			int ch;
			printf("Do you want to continue ? [y/Y] : \n");
			ch = getchar();

			if(ch == 'y' || ch == 'Y')
				bContinue = true;

		}
	}while(bContinue == true &&  getchar());



//	printf("Cleanup....\n");
	//cleanup semaphore
	sem_destroy(&mutex);
	sem_destroy(&mutextext);

	//cleanup DS
	int dsize(0);
	for(newItr itr = g_newDS.begin(); itr != g_newDS.end(); itr++)
	{
        dsize += sizeof(int);
        int len = itr->second.size();
        dsize += (sizeof(int)* len) + (sizeof(long)* len);
		(*itr).second.clear();
	}

	g_newDS.clear();
    printf("Space used to store data in bytes : %d\n",dsize);

//	printf("End Cleanup\n");

	return 0;
}

void* displayProc(void* param)
{
    {
        mLock obj(&mutextext);
        g_millionRecCount++;
        if(0 == g_millionRecCount % 100)
        {
            printf("%dm\n",g_millionRecCount);
        }
        else
        {
            printf(".");
        }
        fflush(stdout);
    }
    pthread_exit(0);
}

long readInputFile(const char* filePath)
{
    long recCount(0);
    long displayCount(0);

	ifstream file(filePath, std::ifstream::in);

	//load data
	if(file)
	{
        pthread_t arr[10000];
        int tcount(0);
		string line;
		while(!file.eof())
		{
			getline(file, line);
			storeData(line);

            recCount++;
            displayCount++;

            if(displayCount == 1000000)
            {
                pthread_create(&arr[tcount], NULL, displayProc, NULL);
                //printf(".");
                tcount++;
                displayCount = 0;
            }
		}

		file.close();

		for(int i = 0 ; i < tcount; i++)
		{
            pthread_join(arr[i], NULL);
		}
	}
    //sleep(1);
    return recCount;
}



void storeData(string& str)
{
	int key(-1), val(-1);
	char* inp = const_cast<char*>(str.c_str());

	char* pch = strtok(inp, " ");
	while(pch != NULL)
	{
		if(key == -1)
			key = atoi(pch);
		else
			val = atoi(pch);
		pch = strtok(NULL, " ");
	}

	if(key != -1 && val != -1)
	{
	    newItr itr = g_newDS.find(key);
        if(itr != g_newDS.end())
        {
            subItr it = itr->second.find(val);
            if(it != itr->second.end())
            {
                it->second = it->second + 1;
            }else
            {
                itr->second.insert(make_pair(val,1));
            }
        }else
        {
            map<int, long> temp;
            temp.insert(make_pair(val,1));
            g_newDS.insert(make_pair(key, temp));
        }
	}
}

long countall(long val, const std::pair<int, long>& x)
{
    return val + x.second;
}

//thread function
void* processNumber(void* pNum)
{
	long count(0);
    int num(0);
	num = *((int*)pNum);

	for(newItr itr = g_newDS.begin(); itr != g_newDS.end() && itr->first <= num; itr++) // check if start is less than the num
	{
        //check if the end is > num
        if(num <= itr->second.rbegin()->first)
        {
            //start from the num
            subItr it = itr->second.lower_bound(num);
            if(it != itr->second.end())
            {
                count = accumulate(it, itr->second.end(), count, countall);
            }
        }
	}

	//update results to the user
	UpdateCount(num, count);
	pthread_exit(0);
}


//thread safe update results
void UpdateCount(const int& num, const long& count){
	mLock obj(&mutex);
	g_counter++;
	printf("%d:%ld\n",num, count);
	g_results[num] = count;
}

//used time calculating functions
int GetMilliCount()
{
	timeb tb;
	ftime(&tb);

	int nCount = tb.millitm + (tb.time & 0xfffff) * 1000;
	return nCount;
}

int GetMilliSpan(int nStartTime)
{
	int nSpan = GetMilliCount() - nStartTime;
	if( nSpan < 0)
		nSpan += 0x100000 * 1000;

	return nSpan;
}
