//Infant-breath-mechanical-simulator
//https://github.com/arisberd/Infant-breath-mechanical-simulator
//version 0.3
//GNU GPL v3

//Datasheet dataleo2.h
//Low flow experiment

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



  80  , 300 , 185 ,
  80  , 300 , 150 ,
  70  , 300 , 185 ,
  70  , 300 , 150 ,
  60  , 300 , 185 ,
  60  , 300 , 150 ,
  50  , 300 , 185 ,
  50  , 300 , 150 ,
  80  , 500 , 140 ,
  80  , 500 , 100 ,
  80  , 500 , 71  ,
  70  , 500 , 140 ,
  70  , 500 , 100 ,
  70  , 500 , 71  ,
  40  , 300 , 185 ,
  40  , 300 , 150 ,
  60  , 500 , 140 ,
  60  , 500 , 100 ,
  60  , 500 , 71  ,
  80  , 700 , 185 ,
  80  , 700 , 114 ,
  80  , 700 , 71  ,
  30  , 300 , 185 ,
  30  , 300 , 150 ,
  50  , 500 , 140 ,
  50  , 500 , 100 ,
  50  , 500 , 71  ,
  70  , 700 , 185 ,
  70  , 700 , 114 ,
  70  , 700 , 71  ,
  80  , 900 , 122 ,
  80  , 900 , 66  ,
  60  , 700 , 185 ,
  60  , 700 , 114 ,
  60  , 700 , 71  ,
  40  , 500 , 140 ,
  40  , 500 , 100 ,
  40  , 500 , 71  ,
  70  , 900 , 122 ,
  70  , 900 , 66  ,
  50  , 700 , 185 ,
  50  , 700 , 114 ,
  50  , 700 , 71  ,
  20  , 300 , 185 ,
  20  , 300 , 150 ,
  60  , 900 , 122 ,
  60  , 900 , 66  ,
  30  , 500 , 140 ,
  30  , 500 , 100 ,
  30  , 500 , 71  ,
  40  , 700 , 185 ,
  40  , 700 , 114 ,
  40  , 700 , 71  ,
  50  , 900 , 122 ,
  50  , 900 , 66  ,
  15  , 300 , 185 ,
  15  , 300 , 150 ,
  40  , 900 , 122 ,
  40  , 900 , 66  ,
  30  , 700 , 185 ,
  30  , 700 , 114 ,
  30  , 700 , 71  ,
  20  , 500 , 140 ,
  20  , 500 , 100 ,
  20  , 500 , 71  ,
  10  , 300 , 185 ,
  10  , 300 , 150 ,
  30  , 900 , 122 ,
  30  , 900 , 66  ,
  15  , 500 , 140 ,
  15  , 500 , 100 ,
  15  , 500 , 71  ,
  20  , 700 , 185 ,
  20  , 700 , 114 ,
  20  , 700 , 71  ,
  20  , 900 , 122 ,
  20  , 900 , 66  ,
  15  , 700 , 185 ,
  15  , 700 , 114 ,
  15  , 700 , 71  ,
  10  , 500 , 140 ,
  10  , 500 , 100 ,
  10  , 500 , 71  ,
  5 , 300 , 185 ,
  5 , 300 , 150 ,
  15  , 900 , 122 ,
  15  , 900 , 66  ,
  10  , 700 , 185 ,
  10  , 700 , 114 ,
  10  , 700 , 71  ,
  10  , 900 , 122 ,
  10  , 900 , 66  ,
  5 , 500 , 140 ,
  5 , 500 , 100 ,
  5 , 500 , 71  ,
  5 , 700 , 185 ,
  5 , 700 , 114 ,
  5 , 700 , 71  ,
  5 , 900 , 122 ,
  5 , 900 , 66

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

