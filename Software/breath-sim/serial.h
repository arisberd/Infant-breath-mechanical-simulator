//Infant-breath-mechanical-simulator
//https://github.com/arisberd/Infant-breath-mechanical-simulator
//version 0.2
//GNU GPL v3

//Module for input from Serial
int serial_input_integer()  { //return up to 4 digit integer
  char rx_byte = 0;
  String rx_str = "";
  boolean not_number = false;
  int result;
  for (int k = 0; k < 5; k++) {
    if (Serial.available() > 0) {    // is a character available?
      rx_byte = Serial.read();       // get the character

      if ((rx_byte >= '0') && (rx_byte <= '9')) {
        rx_str += rx_byte;
      }
      else if (rx_byte == '\n') {
        // end of string
        if (not_number) {
        }
        else {
          ;
          return rx_str.toInt();
        }
        not_number = false;         // reset flag
        rx_str = "";                // clear the string for reuse
      }
      else {
        // non-number character received
        not_number = true;    // flag a non-number
      }
    } // end: if (Serial.available() > 0)
  }//end of for k
}


void print_row (int data_num) {
  int pr_te = pmem_manual_input(data_num*3+1) / 100 * pmem_manual_input(data_num*3+2); //pr_te = temp printing te var
  int tempRR = 60000 / (pmem_manual_input(data_num*3+1) + pr_te);
  Serial.print(data_num);
  Serial.print(" VT="); Serial.print(pmem_manual_input(data_num*3+0));
  Serial.print(" Ti="); Serial.print(pmem_manual_input(data_num*3+1));
  Serial.print(" RR="); Serial.print(tempRR);
  Serial.print(" Te="); Serial.print(pr_te);
  Serial.print(" Te/Ti="); Serial.print(pmem_manual_input(data_num*3+2)); Serial.print("%");
  Serial.print(" MV="); Serial.println(tempRR * pmem_manual_input(data_num*3+0));
}

void print_all_rows() {
  Serial.println("Printing all rows...");
  Serial.print("Number of all rows= "); Serial.println(data_max_row_num);
  for (int aa = 0; aa < data_max_row_num; aa++) {
      print_row(aa);
  }
  
}




void print_steps_debug() {
  Serial.println("Steps:");
  for (int k = 0; k < vol_size; k++) {
    Serial.print(k);
    Serial.print(" ");
    Serial.println(steps[k]);
  }
}

void print_calculate_vols_debugger() {
  Serial.println("Print vols:");
  for (int k = 0; k < vol_size; k++) {
    Serial.print(k);
    Serial.print(" ");
    Serial.println(vol[k]);
  }

}



void print_time_correction_debug() {
  Serial.println(loops_in_round);
  Serial.print("Ti: "); Serial.print(ti);Serial.print(" cTi: "); Serial.println(ti*ti_corr_f);
  Serial.print("Time passed Ti: "); Serial.println(int(time_passed[1]-time_passed[0]));
  Serial.print("Te: "); Serial.print(te);Serial.print(" cTe: "); Serial.println(te*te_corr_f);
  Serial.print("Time passed Te: "); Serial.println(int(time_passed[2]-time_passed[1]));
  Serial.print("Te and Ti in (msec): "); Serial.println(int(time_passed[2] - time_passed[0]));
  Serial.println("");
}


void button_debugger() {
  Serial.println("Button Debugger");
  for (int k = 0 ; k < 10000; k++) {
    Serial.print("blue1="); Serial.println(digitalRead(button_blue_1));
    Serial.print("blue2=");   Serial.println(digitalRead(button_blue_2));
    Serial.print("end stop=");   Serial.println(digitalRead(end_stop));
    delay(100);
  }
}

//Module to show at Serial current setting 
void print_current () {
  Serial.print(row_num); Serial.print("  ");
  Serial.print("Te/Ti="); Serial.print(te_ti_ratio); Serial.print("%");
  //Serial.print("Ti/Te POS="); Serial.println(te_ti_ratio_pos);
  Serial.print(" Ti="); Serial.print(ti);
  //Serial.print("Ti POS="); Serial.println(ti_pos);
  Serial.print(" Te="); Serial.print(te);
  Serial.print(" Vol="); Serial.print(vol[insp_curve_point]);
  //Serial.print("Vol POS="); Serial.println(vol_pos);
  Serial.print(" RR="); Serial.print(60 / ((ti + te) / 1000));
  Serial.print(" MV="); Serial.println(60 / ((ti + te) / 1000)*vol[insp_curve_point]);

  delay(100);

  delay(100);
}



