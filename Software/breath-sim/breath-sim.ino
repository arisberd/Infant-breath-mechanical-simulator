//Infant-breath-mechanical-simulator
//https://github.com/arisberd/Infant-breath-mechanical-simulator
//version 0.2
//GNU GPL v3

//Send a program to arduino to make a specific respiratory circle
//Version G2, to put different volumes and change them with the button
//Version H2, to reduce the delay when the direction change. To put all the data and change them pressing the button
//Version I2, has 3 running modes.
//Version J, endstop
//Version K, input values through serial monitor
//Version L, manual input mode
//Version M, trying to fix the small volumes bug
//Version N, discovering mircostepping and time correction
//Version O, multi file system
//Version P, using new file system, programem

// Define stepper motor connections:
#define dirPin 12 // CW
#define stepPin 13 // CLK
#define enaPin 11 // EN

//Define buttons and endstop
#define button_blue_1 5
#define button_blue_2 4
#define end_stop 7 //end_stop to the syringe

//Configuration ...
float callibration_vol = 0.95418 ; // callibration factor of the volume (ex 85/80)
int microsteps = 8; //set the number of microsteps of the stepper motor (ex for 1/4 set to 4, for 1/16 set to 16)
int starting_volume = -6; //the volume beggining from the end stop switch
float steps_to_vol = 3.33 * microsteps * callibration_vol; // 166steps for 50 ml volume. Must be set in the first setup. This number is set for 100ml syringe. Changing syringes needs adapt of this variable

//Data from file ... WRITE HERE THE FILE YOU WANT TO  UPLOAD
#include "dataleo2.h"


//variables
float step_count;
int totalsteps;
int point_of_dir_change; //there is only one point where the dir change
int loops_in_round;
float tm ;//60000 /(vol_size * RR); //time interval between values of vol[] , the number in milliseconds
int te_ti_ratio; 
float ti; //inspiration time
float te; //expiration time
int data_max_row_num = 0;
int row_num;
int new_row_set_input = 0;
int vol_size; //number of volume values
int steps[2]; //higher number make a higher  definition move
float ti_corr_f; //ti and te correction factors
float te_corr_f;
unsigned long time_passed[4];
float pause_delay;



//Volume curve data
//Follows the data entry, vol for volumes, every number represents the volumeposition of every value
float vol[] = { //vol for volume (to ml)
  0, 2
};


int pmem_manual_input(int point) {
  int my_int = pgm_read_word_near(manual_input + point);
  return my_int;
}

//Include Serial modes for input and output
#include "serial.h"

void setup() {
  // Declare pins as output:
  pinMode(stepPin, OUTPUT);
  pinMode(dirPin, OUTPUT);
  pinMode(enaPin, OUTPUT);
  pinMode(button_blue_1, INPUT);
  pinMode(button_blue_2, INPUT);
  pinMode(end_stop, INPUT);
  digitalWrite(enaPin, LOW); //disables the stepper driver
  Serial.begin(9600);
  Serial.println("Welcome to mechanical respirator!");
  Serial.println("PGNP 2020 ..");
  Serial.println("https://gitlab.com/aris_berd/respirator/");
  Serial.println();
  vol_size = sizeof(vol) / sizeof(vol[0]);
  data_max_row_num =  sizeof(manual_input) / sizeof(manual_input[0]) / 3; //setting the maximum number of rows
  print_all_rows();
  Serial.println("Setup finished!!");

  new_row_setup(0);
  Serial.println("First row Start with following");
  print_current();
  Serial.println("Plug in the motor and press the button to start");

  //Button-waits
  while (digitalRead(button_blue_1) == LOW) {  //if the button is not pressed, it waits
    delay (200);
  }
  //moves the motor to the starting position
  digitalWrite(enaPin, HIGH); //enables the stepper driver
  move_motor((steps_to_vol * 120), 3000);
  Serial.println("Starts");
}


void loop() {
  check_buttons();
  for (int k = 0; k < vol_size; k++) { // k represents the number of volume position
    if (steps[k] < 0) { //for negative step value, change times
      time_passed[0] = millis();
      move_motor(steps[k], ti * ti_corr_f);
      time_passed[1] = millis() - pause_delay;
      pause_delay = 0;
    }
    else {
      if (steps[k] != 0) {  //if >0
        time_passed[2] = millis();
        move_motor(steps[k], te * te_corr_f);
        time_passed[3] = millis() - pause_delay;
        pause_delay = 0;
      }
      else { //if =0
        delay (ti); //if there are no steps in that position, it just waits //from old versions
        //Serial.println("DEBUG-No move");
        //Serial.println(k);
        //Serial.println(vol_size);
      }

    }

  }
  time_correction();
  loops_in_round ++; //counts how many times the loop went in each round

}




void calculate_steps() {
  float rest = 0; //the rest amount of steps if it is not integer

  //Calculating how many steps between vols will make . Steps=number of steps. Rest keeps the 0.numbers
  int totalsteps = 0;
  for (int k = 0; k < vol_size - 1; k++) {
    step_count = steps_to_vol * (vol[k + 1] - vol[k]) + rest;
    rest = step_count - int(step_count);
    steps[k] = int(step_count) * (-1);
    totalsteps = totalsteps + steps[k];
    if (step_count > 0 and point_of_dir_change == 0) point_of_dir_change = k + 1;
  }

  //Calculate the last step
  steps[vol_size - 1] = int(steps_to_vol * (vol[0] - vol[vol_size - 1]) + rest); //the last step is calculated with minus the first, and gives out the rest. Then it is reduced by totalsteps, so in the end the position should be the same
  totalsteps = totalsteps + steps[vol_size - 1];
  if (totalsteps != 0) {
    steps[vol_size - 1] = steps[vol_size - 1] - totalsteps;
  }
  //print_steps_debug();
}






void check_buttons() {
  //Debug
  /*Serial.println("Check Buttons");
    Serial.println(digitalRead(button_blue_1));
    Serial.println(digitalRead(button_blue_2));
    Serial.println(digitalRead(end_stop));
  */

  //Button blue 1 is pushed // change row setup
  if (digitalRead(button_blue_1) == HIGH) {
    int temp_input = serial_input_integer();
    if ((temp_input > 0) and (temp_input != new_row_set_input) and (temp_input <= data_max_row_num)) {
      new_row_set_input = temp_input;
      row_num = new_row_set_input;
      Serial.print("Manualy set round to "); Serial.println(temp_input);
    }
    else {
      row_num ++;
    }
    if (row_num == data_max_row_num) {
      Serial.println("End of experiment. Starts over again");
      delay(3000);
      row_num = 0;
    }
    new_row_setup(row_num);
    Serial.println("Next row Start with following");
    print_current();
    Serial.println("In 0.3 second. Keep pressing the button to skip the round");
    delay (300);
  }


}

void move_motor_delay(int steps_to_move, float time_to_move) {
  //every step takes that much time:time_to_move/steps_to_move
  // These four lines result in 1 step:
  float temp_delay = (1000 * (time_to_move) / (2 * steps_to_move)); // time in microseconds, changed to float VerN
  int temp_delay_milli = temp_delay / 1000; //time in milli sec
  int temp_delay_micro = int(temp_delay) % 1000; //rest of time in micro sec
  digitalWrite(stepPin, HIGH);
  delay(temp_delay_milli);
  delayMicroseconds(temp_delay_micro);
  digitalWrite(stepPin, LOW);
  delay(temp_delay_milli);
  delayMicroseconds(temp_delay_micro);
}



void move_motor (int steps_to_move, float time_to_move) {
  //moves the motor number of steps = steps_to_move, time it takes = time_to_move
  //every step takes that much time:time_to_move/steps_to_move
  //steps_to_move>0 push, steps_to_move < 0 pull
  //During push, checks the end stop
  if (steps_to_move > 0) {
    digitalWrite(dirPin, HIGH);
    delay(6); //must delay to take the signal
    for (int i = 0; (i < steps_to_move) and (digitalRead(end_stop) == 0); i++) {
      pause_module();
      move_motor_delay(steps_to_move, time_to_move);
    }
    if (digitalRead(end_stop) != 0) {
      //Serial.println("Debug - end stop hit");
      move_motor((steps_to_vol * (starting_volume)), 200);
      delay(time_to_move - 200);
    }
  }
  if (steps_to_move < 0) {
    digitalWrite(dirPin, LOW);
    delay(6); //must delay to take the signal
    steps_to_move = -1 * steps_to_move;
    for (int i = 0; i < steps_to_move; i++) {
      pause_module();
      move_motor_delay(steps_to_move, time_to_move);
    }

  }
}

bool paused;
void pause_module() {
  paused = false;
  check_pause_button();
  while (paused == true) {
    delay(100);
    check_pause_button();
    pause_delay += 100;
  }
}



void check_pause_button() {
  //Button blue 2 is pushed //pause button
  if (digitalRead(button_blue_2) == HIGH) {
    bool temp = paused;
    if (temp == false) {
      paused = true;
      Serial.println("Paused!");
    }
    if (temp == true) {
      paused = false;
      Serial.println("Resume!");

    }
    delay(300);
    pause_delay += 300;
  }


}
void time_correction() {
  float last_ti_corr_f = ti_corr_f;//stores last factors
  float last_te_corr_f = te_corr_f;
  int ti_time_passed = time_passed[1] - time_passed[0]; //calculates real ti and te
  int te_time_passed = time_passed[3] - time_passed[2];

  ti_corr_f = last_ti_corr_f * (1 - (ti_time_passed - ti) / ti); //calculates factors
  te_corr_f = last_te_corr_f * (1 - (te_time_passed - te) / te);
}


void new_row_setup(int number_of_row) {

  ti = pmem_manual_input(number_of_row * 3 + 1);
  vol[1] = pmem_manual_input(number_of_row * 3 + 0);
  te_ti_ratio = pmem_manual_input(number_of_row * 3 + 2);
  te =  te_ti_ratio * ti / 100;
  calculate_steps ();
  loops_in_round = 0;
  ti_corr_f = 1;
  te_corr_f = 1;
}
