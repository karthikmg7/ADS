#include <windows.h>
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <time.h>
#include<direct.h>
#include <sys/types.h>
#include <sys/stat.h>
#include<conio.h>

int seekSize,keySize;
SYSTEMTIME  begTime;      // Start time
    SYSTEMTIME  endTime;
	int *hitArray;


	using namespace std;
	 ifstream  fpDb; 
	int binarySearchDb(int seekValue,int keySize)
	{
		int low=0;
		int high=keySize-1;
		int mid=0;
		int val;
		low=0;high=keySize-1;mid=0;
		 while(low<=high)
	   {
		   mid=(low+high)/2;
		    fpDb.seekg( mid * (int) sizeof( int ), ios::beg );
	    fpDb.read( (char *) &val, (int) sizeof( int ) );
		   if(val==seekValue)
		   {
			  return 1;
		   }
		   else if(seekValue<val)
		   {
			   high=mid-1;
		   }
		   else
		   {
			   low=mid+1;
		   }
	   }
	   return 0;

	}
	void diskBinarySearch(char*keyPath,char*seekPath)
	{
		  
				struct stat stat_buf;
		SYSTEMTIME beg, end,*indiBeg,*indiEnd;
		 ifstream  fp;       // Input file stream

  int       val,i,j;      // Current input value
 
  int *seekArray;
  stat(keyPath, &stat_buf);
	  keySize=stat_buf.st_size/sizeof(int);
	  printf("key size%d\n",keySize);

  stat(seekPath, &stat_buf);
 
	  seekSize=stat_buf.st_size/sizeof(int);
	  printf("seek size:%d\n",seekSize);
 

 
   seekArray=new int[seekSize];
   indiBeg=new SYSTEMTIME[seekSize];
   indiEnd=new SYSTEMTIME[seekSize];
   hitArray=new int[seekSize];
   fp.open(seekPath, ios::in | ios::binary );
  for(i=0;i<seekSize;i++)
   {
	    fp.seekg( i * (int) sizeof( int ), ios::beg );
	    fp.read( (char *) &val, (int) sizeof( int ) );
		seekArray[i]=val;

   }
  fp.close();
    GetLocalTime( &beg );
	 fpDb.open(keyPath, ios::in | ios::binary );
 for(j=0;j<seekSize;j++)
  {
	   GetLocalTime(&indiBeg[j]);
	   hitArray[j]=binarySearchDb(seekArray[j],keySize);
	   GetLocalTime(&indiEnd[j]);

  }
 fpDb.close();
  GetLocalTime( &end );
	  printf("DONE\n");
	  freopen( "C:\\Users\\karthik\\Desktop\\BINARY_DISK_SEARCH.txt", "w", stdout );
    printf( "%02d:%02d:%02d:%06d\n", beg.wHour,
    beg.wMinute, beg.wSecond, beg.wMilliseconds * 1000 );
	 printf( "%02d:%02d:%02d:%06d\n", end.wHour,
    end.wMinute, end.wSecond, end.wMilliseconds * 1000 );
	 for(i=0;i<seekSize;i++)
	 {
		 printf( "%02d:%02d:%02d:%06d  ", indiBeg[i].wHour,
    indiBeg[i].wMinute, indiBeg[i].wSecond, indiBeg[i].wMilliseconds * 1000 );
		 printf( "%02d:%02d:%02d:%06d  ", indiEnd[i].wHour,
    indiEnd[i].wMinute, indiEnd[i].wSecond, indiEnd[i].wMilliseconds * 1000 );
		 printf( "%6d: %d\n", seekArray[ i ], hitArray[ i ] );
	 }
	  freopen( "CON", "w", stdout );
}

	
	int binarySearch(int*keyArray,int seekValue,int keySize)
	{
		int low=0;
		int high=keySize-1;
		int mid=0;
		low=0;high=keySize-1;mid=0;
	   while(low<=high)
	   {
		   mid=(low+high)/2;
		   if(keyArray[mid]==seekValue)
		   {
			  return 1;
		   }
		   else if(seekValue<keyArray[mid])
		   {
			   high=mid-1;
		   }
		   else
		   {
			   low=mid+1;
		   }
	   }
	   return 0;

	}

	void diskLinearSearch(char *keyPath,char *seekPath)
	{
		struct stat stat_buf;
		SYSTEMTIME beg, end,*indiBeg,*indiEnd;
		 ifstream  fp;       // Input file stream

  int       val,i,j;      // Current input value
 
  int *seekArray;
  stat(keyPath, &stat_buf);
	  keySize=stat_buf.st_size/sizeof(int);
	  printf("key size%d\n",keySize);

  stat(seekPath, &stat_buf);
 
	  seekSize=stat_buf.st_size/sizeof(int);
	  printf("seek size:%d\n",seekSize);
 

 
   seekArray=new int[seekSize];
   indiBeg=new SYSTEMTIME[seekSize];
   indiEnd=new SYSTEMTIME[seekSize];
   hitArray=new int[seekSize];
   fp.open(seekPath, ios::in | ios::binary );
  for(i=0;i<seekSize;i++)
   {
	    fp.seekg( i * (int) sizeof( int ), ios::beg );
	    fp.read( (char *) &val, (int) sizeof( int ) );
		seekArray[i]=val;

   }
  fp.close();
    GetLocalTime( &beg );
     fp.open(keyPath, ios::in | ios::binary );
	 for(j=0;j<seekSize;j++)
	 {
		 GetLocalTime(&indiBeg[j]);
		 for(i=0;i<keySize;i++)
		 {
			 
	     fp.seekg( i * (int) sizeof( int ), ios::beg );
	     fp.read( (char *) &val, (int) sizeof( int ) );
		
		  if(seekArray[j]==val)
		  {
			  GetLocalTime(&indiEnd[j]);
			  hitArray[j]=1;
			  break;
		  }
	  }
	  if(i==keySize)
	  {
		   GetLocalTime(&indiEnd[j]);
		   hitArray[j]=0;
	  }
	

		 
	 }
	
	 fp.close();
	  GetLocalTime( &end );
	  printf("DONE\n");
	  freopen( "C:\\Users\\karthik\\Desktop\\LINEAR_DISK_SEARCH.txt", "w", stdout );
    printf( "%02d:%02d:%02d:%06d\n", beg.wHour,
    beg.wMinute, beg.wSecond, beg.wMilliseconds * 1000 );
	 printf( "%02d:%02d:%02d:%06d\n", end.wHour,
    end.wMinute, end.wSecond, end.wMilliseconds * 1000 );
	 for(i=0;i<seekSize;i++)
	 {
		 printf( "%02d:%02d:%02d:%06d  ", indiBeg[i].wHour,
    indiBeg[i].wMinute, indiBeg[i].wSecond, indiBeg[i].wMilliseconds * 1000 );
		 printf( "%02d:%02d:%02d:%06d  ", indiEnd[i].wHour,
    indiEnd[i].wMinute, indiEnd[i].wSecond, indiEnd[i].wMilliseconds * 1000 );
		 printf( "%6d: %d\n", seekArray[ i ], hitArray[ i ] );
	 }
	  freopen( "CON", "w", stdout );


	}
void inMemBinarySearch(char *keyPath,char *seekPath)
	{
		struct stat stat_buf;
		SYSTEMTIME beg, end,*indiBeg,*indiEnd;
		 ifstream  fp;       // Input file stream

  int       val,i,j;      // Current input value
  int low,high,mid;
  int *keyArray,*seekArray;
  stat(keyPath, &stat_buf);
	  keySize=stat_buf.st_size/sizeof(int);
	  printf("key size%d\n",keySize);

  stat(seekPath, &stat_buf);
 
	  seekSize=stat_buf.st_size/sizeof(int);
	  printf("seek size:%d\n",seekSize);
 

   keyArray=new int[keySize];
   seekArray=new int[seekSize];
   indiBeg=new SYSTEMTIME[seekSize];
   indiEnd=new SYSTEMTIME[seekSize];
   hitArray=new int[seekSize];


   GetLocalTime( &beg );
     fp.open(keyPath, ios::in | ios::binary );
   for(i=0;i<keySize;i++)
   {
	    fp.seekg( i * (int) sizeof( int ), ios::beg );
	    fp.read( (char *) &val, (int) sizeof( int ) );
		keyArray[i]=val;

   }
    
	fp.close();
	GetLocalTime( &end );
	fp.open(seekPath, ios::in | ios::binary );
  for(i=0;i<seekSize;i++)
   {
	    fp.seekg( i * (int) sizeof( int ), ios::beg );
	    fp.read( (char *) &val, (int) sizeof( int ) );
		seekArray[i]=val;

   }
  for(j=0;j<seekSize;j++)
  {
	   GetLocalTime(&indiBeg[j]);
	   hitArray[j]=binarySearch(keyArray,seekArray[j],keySize);
	   GetLocalTime(&indiEnd[j]);

  }
  freopen( "C:\\Users\\karthik\\Desktop\\BINARY_INMEMORY_SEARCH.txt", "w", stdout );
    printf( "%02d:%02d:%02d:%06d\n", beg.wHour,
    beg.wMinute, beg.wSecond, beg.wMilliseconds * 1000 );
	 printf( "%02d:%02d:%02d:%06d\n", end.wHour,
    end.wMinute, end.wSecond, end.wMilliseconds * 1000 );
	 for(i=0;i<seekSize;i++)
	 {
		 printf( "%02d:%02d:%02d:%06d  ", indiBeg[i].wHour,
    indiBeg[i].wMinute, indiBeg[i].wSecond, indiBeg[i].wMilliseconds * 1000 );
		 printf( "%02d:%02d:%02d:%06d  ", indiEnd[i].wHour,
    indiEnd[i].wMinute, indiEnd[i].wSecond, indiEnd[i].wMilliseconds * 1000 );
		 printf( "%6d: %d\n", seekArray[ i ], hitArray[ i ] );
	 }
	  freopen( "CON", "w", stdout );

	}
void inMemLinearsearch(char *keyPath,char *seekPath)
	{
		struct stat stat_buf;
		SYSTEMTIME beg, end,*indiBeg,*indiEnd;
		 ifstream  fp;       // Input file stream

  int       val,i,j;      // Current input value
  int *keyArray,*seekArray;
  stat(keyPath, &stat_buf);
	  keySize=stat_buf.st_size/sizeof(int);
	  printf("key size%d\n",keySize);

  stat(seekPath, &stat_buf);
 
	  seekSize=stat_buf.st_size/sizeof(int);
	  printf("seek size:%d\n",seekSize);
 

   keyArray=new int[keySize];
   seekArray=new int[seekSize];
   indiBeg=new SYSTEMTIME[seekSize];
   indiEnd=new SYSTEMTIME[seekSize];
   hitArray=new int[seekSize];


   GetLocalTime( &beg );
     fp.open(keyPath, ios::in | ios::binary );
   for(i=0;i<keySize;i++)
   {
	    fp.seekg( i * (int) sizeof( int ), ios::beg );
	    fp.read( (char *) &val, (int) sizeof( int ) );
		keyArray[i]=val;

   }
   
	fp.close();
	 GetLocalTime( &end );
  fp.open(seekPath, ios::in | ios::binary );
  for(i=0;i<seekSize;i++)
   {
	    fp.seekg( i * (int) sizeof( int ), ios::beg );
	    fp.read( (char *) &val, (int) sizeof( int ) );
		seekArray[i]=val;

   }
  for(j=0;j<seekSize;j++)
  {
	  GetLocalTime(&indiBeg[j]);
	  for(i=0;i<keySize;i++)
	  {
		  if(seekArray[j]==keyArray[i])
		  {
			   GetLocalTime(&indiEnd[j]);
			  hitArray[j]=1;
			  break;
		  }
	  }
	  if(i==keySize)
	  {
		   GetLocalTime(&indiEnd[j]);
		   hitArray[j]=0;
	  }
  }

   freopen( "C:\\Users\\karthik\\Desktop\\LINEAR_INMEMORY_SEARCH.txt", "w", stdout );
    printf( "%02d:%02d:%02d:%06d\n", beg.wHour,
    beg.wMinute, beg.wSecond, beg.wMilliseconds * 1000 );
	 printf( "%02d:%02d:%02d:%06d\n", end.wHour,
    end.wMinute, end.wSecond, end.wMilliseconds * 1000 );
	 for(i=0;i<seekSize;i++)
	 {
		 printf( "%02d:%02d:%02d:%06d  ", indiBeg[i].wHour,
    indiBeg[i].wMinute, indiBeg[i].wSecond, indiBeg[i].wMilliseconds * 1000 );
		 printf( "%02d:%02d:%02d:%06d  ", indiEnd[i].wHour,
    indiEnd[i].wMinute, indiEnd[i].wSecond, indiEnd[i].wMilliseconds * 1000 );
		 printf( "%6d: %d\n", seekArray[ i ], hitArray[ i ] );
	 }
	  freopen( "CON", "w", stdout );



 
	}
void main()
{
	
	char seekPath[270], keyPath[270];
	char cCurrentPath[FILENAME_MAX];
	int  *inMemL,*inMemBin,diskLin,*diskBin;

 getcwd(cCurrentPath,255);

 strcpy(seekPath,cCurrentPath);
 strcpy(keyPath,cCurrentPath);
    strcat(seekPath, "\\seek.pc.db");
    strcat(keyPath, "\\key.pc.db");

//inMemLinearsearch(keyPath,seekPath);
//inMemBinarySearch(keyPath,seekPath);
//diskLinearSearch(keyPath,seekPath);
 diskBinarySearch(keyPath,seekPath);
_getch();



}