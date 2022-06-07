#include <iostream>

using namespace std;

void sort(float *s, float *f, int *cv, int m)
{
	for(int i=0; i<m-1; i++)
		for(int j=i+1; j<m; j++)
			if(s[j]<s[i]){
				int tg = s[i];
				s[i]=s[j];
				s[j]=tg;
				int tg1 = f[i];
				f[i]=f[j];
				f[j]=tg1;
				int tg2 = cv[i];
				cv[i]=cv[j];
				cv[j]=tg2;
			}	
}

void Interval_Scheduling(float *s, float *f, int *kq, int *cv, int m)
{
    sort(s,f,cv,m);
    float last_finish = 0;
    for(int i=0; i<m; i++)
    {
    	if(s[i]>=last_finish){
    		kq[i] = 1;
    		last_finish = f[i];
    	}
	}
    
}

int main()
{
    float *s, *f; int *kq, *cv;
    int  m;
    cout<<"Nhap so cv: ";
    cin>>m;
    
    s = new float[m];
    f = new float[m];
    kq = new int[m]{0};
    cv = new int[m];
    
    for (int i = 0; i < m; i++)    
    {
        cv[i] = i+1;
		cout<<"Cong viec "<<i+1<<endl;
		cout<<"TG bat dau: ";
        cin>>s[i];
		cout<<"TG ket thuc: ";
        cin>>f[i];
    }
       
	Interval_Scheduling(s,f,kq,cv,m);
	  
	cout<<"CV	";                       
	for (int i = 0; i < m; i++)
		cout<<cv[i]<<"	";
	cout<<endl<<"KQ	";
	for (int i = 0; i < m; i++)
		cout<<kq[i]<<"	";
	cout<<endl;  
    
}