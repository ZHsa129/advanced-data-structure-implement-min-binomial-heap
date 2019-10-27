#include <iostream>
#include <fstream>
#include <time.h>
#include <iomanip>
#include <string>
#include "bheap.h"
#include "ltree.h"

using namespace std;

// define the initialization number and operation number
const int NUM[7]={100,500,1000,2000,3000,4000,5000};
const int OP_NUM=5000;

// ***** functions to generate random numbers*****
int random(int i, int n){
	int tmp;
	int seed = time(NULL);
	srand(seed);
	tmp=rand()%(n-i)+i;
	return tmp;
}

void swap(int &a, int &b){
	int tmp;
	tmp=a;
	a=b;
	b=tmp;
	return;
}

void Random_Permutation(int A[], int n){
	for(int i=0; i<n;i++ ){
		A[i]=i;
	}

	for (int j=0; j<n; j++){
		swap(A[j],A[random(j,n)]);
	}
	return;
}

//******end *******************

int main(int argc, char* argv[]){
	char op; //operation: D->Delete, I->Insert;
	float t; // time cost for per operation
	if(argc ==1) { // if no arguments input for ./heap
		cout<<"Usage: $./heap -option [file-name]"<<endl;
		cout<<"Option:"<<endl;
		cout<<"-r: Random Mode"<<endl;
		cout<<"-il filename: min leftist tree\n";
		cout<<"-ib filename: min binomial heap\n";
		return -1;
	}
// 	random mode to test the performance of leftist tree and binomial heap
	if (strcmp(argv[1],"-r")==0){
		for(int k=0; k<7;k++){
			clock_t Start, Time;
			int a[NUM[k]];
			int num,Del_num, In_num;
//		generate the random permutation of a[num]
//		write to "random.dat"
			Del_num=0;
			In_num=0;
			Random_Permutation(a, NUM[k]);
			ofstream outfile("random.dat");
            int operations[OP_NUM];
			int seed = time(NULL);
			srand(seed);
// 		generate random sequence of operations
			for (int i=0; i<OP_NUM;i++){
				if(rand() % 2==0 && Del_num<In_num){
					//op='D';
					//outfile<<setw(1)<<op<<endl;
					Del_num+=1;
                    operations[i]=-1;
				}
				else{
					//op='I';
					//outfile<<setw(1)<<op<<" "<<a[rand()%NUM[k]]<<endl;
					In_num+=1;
                    operations[i]=a[rand()%NUM[k]];
				}
			}
			//outfile.close();
//		 read in the operations from random.dat for leftist tree
//			ifstream ipfile("random.dat");
			Ltree * test1 = new Ltree();
			BiHeap * test2 = new BiHeap();
//			Initialize the leftist tree and binomial heap with NUM[k] nodes;
			for (int i=0; i< NUM[k]; i++){
				test1->Ltree_Insert(a[i]);
				test2->BiHeap_Insert(a[i]);
			}
//		 measure the time
			Start=clock();
			/*while(!ipfile.eof()){
				ipfile>>op;
				if(op=='I'){
//					insert operation
					ipfile>>num;
					test1->Ltree_Insert(num);
				}
				else if(op=='D'){
//					delete min
					test1->Ltree_Del_Min();
				}
				op='N';
			}*/
            for(int i=0;i<OP_NUM;++i)
            {
                if(operations[i]==-1)
                    test1->Ltree_Del_Min();
                else if(operations[i]>=0)
                    test1->Ltree_Insert(operations[i]);
            }

			Time=clock()-Start;
			t=Time/(OP_NUM*1.0);
//		 	output the time for per operation
			cout<<"Initialize "<<NUM[k]<<" elements:\n";
			cout<<"Leftist Tree:"<<t<<" ms per operation\n";
			//ipfile.close();
//*******Binomial Heap test*********
			//ipfile.open("random.dat");
			Start=clock();
			/*while(!ipfile.eof()){
				ipfile>>op;
				if(op=='I'){
//					insert
					ipfile>>num;
					test2->BiHeap_Insert(num);
				}
				else if(op=='D'){
//					delete min
					test2->BiHeap_Del_Min();
				}
				op='N';
			}*/
            for(int i=0;i<OP_NUM;++i)
            {
                if(operations[i]==-1)
                    test2->BiHeap_Del_Min();
                else if(operations[i]>=0)
                    test2->BiHeap_Insert(operations[i]);
            }

			Time=clock()-Start;
			t=Time/(OP_NUM*1.0);
			cout<<"Binomial Heap:"<<t<<" ms per operation\n";
		}
	}


//	leftist tree mode; need input file
	if(strcmp(argv[1],"-il")==0){
		int num;
		cout<<"leftist tree mode:"<<endl;
		ifstream ipfile(argv[2]);
		Ltree *test =new Ltree();
		while(!ipfile.eof()){
//	read in the operations
			ipfile>>op;
			if(op=='I'){
				ipfile>>num;
				test->Ltree_Insert(num);
			}
			else if(op=='D'){
				test->Ltree_Del_Min();
			}
			op='N';
		}
//	print the tree
		test->Ltree_Print();
	}
//******* Binomial Heap mode **********
	else if (strcmp(argv[1],"-ib")==0){
		BiHeap *test=new BiHeap();
		ifstream ipfile(argv[2]);
		int num;
		while(!ipfile.eof()){
			ipfile>>op;
			if(op=='I'){
				ipfile>>num;
				test->BiHeap_Insert(num);
			}
			else if(op=='D'){
				test->BiHeap_Del_Min();
			}
			op='N';
		}
		test->BiHeap_Print();
	}

	return 0;
}

