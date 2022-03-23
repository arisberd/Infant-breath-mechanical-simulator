//Infant-breath-mechanical-simulator
//https://github.com/arisberd/Infant-breath-mechanical-simulator
//version 0.2
//GNU GPL v3

//Axis based on x-end of Prusa iteration3 
// http://www.reprap.org/wiki/Prusa_Mendel
// http://github.com/josefprusa/Prusa3
//GNU GPL v3

//For the purposes of the project
motor_thickness_add=8;//thickenning the motor's arm
motor_arm_y_lengthen=2.5; //lengthen the motor's arm module at y axis


// ThingDoc entry
/**
 * @id xMotorEnd
 * @name X Axis Motor End
 * @category Printed
 */
 
/**
 * @id xIdlerEnd
 * @name X Axis Idler End
 * @category Printed
 */
 
include <configuration.scad>
use <bushing.scad>
use <inc/bearing-guide.scad>
use <y-drivetrain.scad>

//height and width of the x blocks depend on x smooth rod radius
x_box_height = 52 + 2 * bushing_xy[0];
x_box_width = (bushing_xy[0] <= 4) ? 17.5 : bushing_xy[0] * 2 + 9.5;
bearing_height = max ((bushing_z[2] > 30 ? x_box_height : (2 * bushing_z[2] + 8)), x_box_height);


module x_end_motor(){

    mirror([0, 1, 0]) {

        x_end_base([3, 3, min((bushing_xy[0] - 3) * 2, 3), 2], len=42, offset=-5, thru=false);

        
        
        translate([0, -z_delta - 2-motor_arm_y_lengthen, 0]) difference(){
            union(){
                intersection() {
                    translate([-15, -34, 30]) cube([20, 60+12, x_box_height+8], center = true);
                    union() {
                        translate([-14, -16 + z_delta / 2+motor_arm_y_lengthen, 24+6]) cube_fillet([17.5, 10.5 + z_delta+motor_arm_y_lengthen, 55+12], center = true, vertical=[0, 0, 3, 3], top=[0, 3, 6, 3], $fn=16);
                        //lower arm holding outer stepper screw
                        translate([-10.25, -34, 9]) intersection(){
                            translate([-motor_thickness_add/2, -5+motor_arm_y_lengthen, -5]) cube_fillet([10+motor_thickness_add, 37+20+motor_arm_y_lengthen, 28], center = true, vertical=[0, 0, 0, 0], top=[0, 3, 5, 3]);
                            translate([-10/2-motor_thickness_add, 10-30, -26-30-5]) rotate([45, 0, 0]) cube_fillet([10+motor_thickness_add, 60+30, 60+30+motor_arm_y_lengthen*5], radius=2);
                        }
                    }
                }
                
                translate([-16-motor_thickness_add+1-0.5, -32-8, 30.25]) rotate([90, 0, 0])  rotate([0, 90, 0]) nema30(places=[1, 0, 1, 1], h=11+motor_thickness_add-1);
            }

            // motor screw holes
            translate([21-5, -21-11, 30.25]){
                // belt hole
                    translate([-30, 11, -0.25]) cube_fillet([11, 36, 22], vertical=0, top=[0, 1, 0, 1], bottom=[0, 1, 0, 1], center = true, $fn=4);
                //motor mounting holes
                translate([-29.5, -8, 0]) rotate([0, 0, 0])  rotate([0, 90, 0]) nema30(places=[1, 1, 0, 1], holes=true, shadow=5.5, $fn=small_hole_segments, h=8);
            }
            //substracts a cylinder for big gears
            translate([21-5, -21-11, 30.25]) translate ([-60,-8,0]) rotate ([0,90,0]) cylinder (h=100, d=40.5);
        }
        //smooth rod caps
        //translate([-22, -10, 0]) cube([17, 2, 15]);
        //translate([-22, -10, 45]) cube([17, 2, 10]);
    }
}

module x_end_base(vfillet=[3, 3, 3, 3], thru=true, len=40, offset=0){

    difference(){
        union(){
            translate([-10 - bushing_xy[0], -10 + len / 2 + offset, 30]) cube_fillet([x_box_width, len, x_box_height+20], center=true, vertical=vfillet, top=[5, 3, 5, 3]);
            //z-axis module is not needed for the project
            /*!translate([0, 0, 4 - bushing_xy[0]]) {
                //rotate([0, 0, 0]) translate([0, -9.5, 0]) 
                translate([z_delta, 0, 0]) render(convexity = 5) linear(bushing_z, bearing_height);
                // Nut trap
                translate([-2, 18, 5]) cube_fillet([20, 14, 10], center = true, vertical=[8, 0, 0, 5]);x
                //}
            }*/
        }
            
             
       
        
        /*
        // here are bushings/bearings
        translate([z_delta, 0, 4 - bushing_xy[0]]) linear_negative(bushing_z, bearing_height);
*/
        
        //holes for mounting at the base, diameter 6.5mm
        translate ([0,-8,-2]) rotate([0,90,0]) cylinder (h=50, d=6.5, center=true);
        translate ([0,+20,-2]) rotate([0,90,0]) cylinder (h=50, d=6.5, center=true);
        translate ([0,-8,x_box_height+2]) rotate([0,90,0]) cylinder (h=50, d=6.5, center=true);
        translate ([0,+20,x_box_height+2]) rotate([0,90,0]) cylinder (h=50, d=6.5, center=true);
        
        // belt hole
        translate([-14 - xy_delta / 2, 22 - 9 + offset, 30]) cube_fillet([max(idler_width + 2, 11), 55, 27], center = true, vertical=0, top=[0, 1, 0, 1], bottom=[0, 1, 0, 1], $fn=4);

        //smooth rods
        translate([-10 - bushing_xy[0], offset, 0]) {
            if(thru == true){
                translate([0, -11, 6]) rotate([-90, 0, 0]) pushfit_rod(bushing_xy[0] * 2 + 0.2, 50);
                translate([0, -11, xaxis_rod_distance+6]) rotate([-90, 0, 0]) pushfit_rod(bushing_xy[0] * 2 + 0.2, 50);
            } else {
                translate([0, -7, 6]) rotate([-90, 0, 0]) pushfit_rod(bushing_xy[0] * 2 + 0.2, 50);
                translate([0, -7, xaxis_rod_distance+6]) rotate([-90, 0, 0]) pushfit_rod(bushing_xy[0] * 2 + 0.2, 50);
            }
        }
        translate([0, 0, 5 - bushing_xy[0]]) {  // m5 nut insert
            translate([0, 17, 0]) rotate([0, 0, 10]){
                //rod
                translate([0, 0, -1]) cylinder(h=(4.1 / 2 + 5), r=3, $fn=32);
                //nut
                translate([0, 0, 9]) cylinder(r=4.6, h=14.1, center = true, $fn=6);

            }
        }
    }
    //threaded rod
    //translate([0, 17, 0]) cylinder(h = 70, r=2.5+0.2);
}

module x_end_idler(){
    difference() {
        x_end_base(len=48 + z_delta / 3, offset=-10 - z_delta / 3);
        // idler hole
        translate([-20, -15 - z_delta / 2, 30]) {
            rotate([0, 90, 0]) cylinder(r=m4_diameter / 2, h=33, center=true, $fn=small_hole_segments);
            translate([15 - 2 * single_wall_width, 0, 0]) rotate([90, 0, 90]) cylinder(r=m4_nut_diameter_horizontal / 2, h=3, $fn=6);

        }
        translate([-6 - x_box_width, 11, 29.5 - (max(idler_width, 16) / 2)]) cube([x_box_width + 1, 12, 1.5 + max(idler_bearing[0], 16)]);
    }
        %translate([-14 - xy_delta / 2, -9, 30.5 - (max(idler_width, 16) / 2)]) x_tensioner();
}

module x_tensioner(len=68, idler_height=max(idler_bearing[0], 16)) {
    idlermount(len=len, rod=m4_diameter / 2 + 0.5, idler_height=idler_height, narrow_len=47, narrow_width=idler_width + 2 - single_wall_width);
}


translate([-40, 0, 4 - bushing_xy[0]]) x_tensioner();
translate([0, -80, 0]) mirror([1, 0, 0]) x_end_idler(thru=true);


difference () {
    translate([-50, 0, 0]) mirror([1, 0, 0]) translate([-50, 0, 0]) x_end_motor();
//tester
//    translate ([0,-22,0]) cube ([60,70,200],center = true);
//    translate ([0,-10,71]) cube ([60,70,20],center = true);
//    translate ([0,-10,-12]) cube ([60,170,20],center = true);
    
}


module pushfit_rod(diameter, length){
    cylinder(h = length, r=diameter/2, $fn=30);
    translate([0, -diameter/4, length/2]) cube_fillet([diameter, diameter/2, length], vertical = [0, 0, 1, 1], center = true, $fn=4);

    translate([0, -diameter/2-1.2, length/2]) cube([diameter - 1, 1, length], center = true);
}

/*bearing guides
if (idler_bearing[3] == 1) {  // bearing guides
    translate([-39,  -60 - idler_bearing[0] / 2, 4 - bushing_xy[0]]) rotate([0, 0, 55]) {
        render() bearing_assy();
    }
}
*/
