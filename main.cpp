/* 
 * File:   main.cpp
 * Author: shawn
 *
 * Created on May 11, 2015, 5:16 PM
 */

#include <iostream>

using namespace std;


int main() {
    double die[7]={0,1.0/6,1.0/6,1.0/6,1.0/6,1.0/6,1.0/6};
    double probs[20]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
    double roll[13]={0,0,0,0,0,0,0,0,0,0,0,0,0};
    
    //find probability for each dice roll
    for(int i=0;i<7;i++){
        for(int j=0;j<7;j++)
            roll[i+j]+=die[i]*die[j];
    }
    
    cout<<"Probability for dice rolls:"<<endl;
    for(int i=0;i<13;i++)
        cout<<i<<": "<<roll[i]<<endl;
    
    double previousRoll[40];
    double nextRoll[40];
    
    //set values to 0
    for(int i=0;i<40;i++){
        previousRoll[i]=0;
        nextRoll[i]=0;
    }
    for(int i=0;i<13;i++){
        previousRoll[i]=roll[i];
    }
    
    //max number of rolls would be 20
    for(int i=1;i<20;i++){
        for(int j=2;j<13;j++){
            for(int k=0;k<40;k++){
                if((j+k)>=40)
                    probs[i] += previousRoll[k]*roll[j];
                else{
                    
                    nextRoll[j+k]+=previousRoll[k]*roll[j];    
                }
            }
        }
        
        //update nextRolll and previous Roll
        for(int j=0;j<40;j++){
            previousRoll[j]=nextRoll[j];
            nextRoll[j]=0;
        }
    }
    
    
    
    cout<<endl<<"Probability for Number of Roll:"<<endl;
    for (int i=0;i<20;i++){
        cout<<(i+1)<<":"<<probs[i]<<endl;
        //f+=probs[i];
    }
    
  
        
    return 0;
}


