//Infant-breath-mechanical-simulator
//https://github.com/arisberd/Infant-breath-mechanical-simulator
//version 0.3
//GNU GPL v3

//Datasheet dataleo8.h

//Πρώτο πείραμα με High Flow 
//21-01-2021

/////////////////////////
//Parameters Input Data//
/////////////////////////

//Put here the data of respiratory parameters
//Data should be put as :
//VT , Ti, Te/Ti ratio,
//VT in ml, Ti in msec, Te/Ti in percentage
//ex
//10  , 500 , 140 ,
//15  , 700 , 100
//


const int PROGMEM manual_input[] = {

10  , 300 , 150 ,
10  , 500 , 100 ,
10  , 700 , 114 ,
15  , 300 , 150 ,
15  , 500 , 100 ,
15  , 700 , 114



};


/////////////////////
//Volume Curve Data//
/////////////////////

//Put here the data that represents the respiratory curve
//Every number represents a volumeposition (y axis of a volume curve). Time (x axis), has intervals of the same time, which is defined by Respiratory Parameters data (see previous chart)
//Actual volumes will be streched to fit the given maximum volumes. 
float vol_curve[] = { 
  //square flow
  0, 2 

  //testing flow
  //0, 10, 6.6, 3.3

  //crying flow
  //0,6,6-1,6-1.3,6-2,6-3.5,6-4,6-5,6-5.5,6-6
};

//The following values has to be fit manually:
int const vol_size = 2; //The number of the curve points (for square flow set to 2, testing flow to 4, crying flow to 10)
int const insp_curve_point = 1; //the point where inspiration ends starting from 0 (usually the maximum point in the curve). Cannot be 0. This is used to seperate Ti and Te (Time of inspirations, Time of expirations)
float vol_curve_max = 2; //total volume of the curve, usually the maximum value of the curve


