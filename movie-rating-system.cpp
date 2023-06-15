
#include <pthread.h>
#include <semaphore.h>
#include<bits/stdc++.h>
#include<iostream>
#include <fstream>
using namespace std;
sem_t m;

struct str
{
    string name,director_name;
    float rating;
    int release_year;
} mv_list[100];
int mv_list_size=0,movie_number_in_list;
bool compare(str x,str y)
{
    return x.rating>y.rating;
}
void *new_thread(void *i)
{


    sem_wait(&m);   //decreasing semaphore value
    int find=0;
    string str1,str2;
    cout<<"Enter word to search:"<<endl;
    fflush(stdin);
    cin>>str1;
    for(int k=0; k<mv_list_size; k++)
    {
        fflush(stdin);
        str2=mv_list[k].name;
        if(str2.find(str1)!=-1)  //finding movies in movie list by str1
        {
            cout<<mv_list[k].name<<'\t'<<endl<<"     rating :"<<mv_list[k].rating<<endl<<"     directed by: "<<mv_list[k].director_name<<endl<<"     release year : "<<mv_list[k].release_year<<endl;
            find=1;
        }
    }
    if(find!=1)
             cout<< "_This_ word is out of _list_" <<endl<<endl;

   //sem_post(&m);
    }

   int main()
    {
    fstream new_file3;
    new_file3.open("movie1.txt",ios::in);   //read from file
    cout<<"Rotten Tomatos website movie list: "<<endl;
    while(new_file3>>mv_list[mv_list_size].name)
    {
        new_file3>>mv_list[mv_list_size].rating;
         new_file3>>mv_list[mv_list_size].director_name;
          new_file3>>mv_list[mv_list_size].release_year;

        cout<<mv_list[mv_list_size].name<<" "<<mv_list[mv_list_size].rating<<endl;
        mv_list_size++;
        movie_number_in_list++;
    }
    //cout<<movie_number_in_list<<endl;
    new_file3.close();
    sort(mv_list,mv_list+movie_number_in_list,compare);  //sort movies in decreasing order by popularity ratings
   /* cout<<"After sort"<<endl;
    for(int i=0; i<movie_number_in_list; i++)
    {
        cout<<mv_list[i].name<<'\t'<<mv_list[i].rating<<endl;
    }*/


     pthread_t tid[8];//let 8 as users
    int i;

    if (sem_init(&m, 0, 5) == -1)  //sem init initializes semaphore value m=5
    {
        perror("Could not initialize semaphore");
        exit(2);
    }

    for (i=0; i<8; i++)  //by creating 8 threads ,lets virtually consider 8 users are trying to access website concurrently
    {
        if (pthread_create(&tid[i], NULL, new_thread, NULL) < 0)
        {
            perror("Error: thread cannot be created");
            exit(1);
        }
       pthread_join(tid[i], NULL); //parent doesnot terminate until created threads are done
    }

    exit(0);


}
