//Infant-breath-mechanical-simulator
//https://github.com/arisberd/Infant-breath-mechanical-simulator
//version 0.2
//GNU GPL v3

//This printed piece attach the plunger of the syringe to the carriage
//This 3d printed model uses 100ml syringe with threaded plunger, and the syringe is mounted at x-end mount holes
//The plunger must have thread, otherwise the suringe_attacher_will_flange should be used
// The position of the holes in the carriage are [0,30,50]
//

base_thickness= 10-4;
attacher_thickness=3+2;
height = 43; // the height of the plunger of the syringe

module cylinder_double (r,h,x,y,z) {
   hull() {
    translate([x/2,y/2,z/2]) cylinder(r = r, h = h);
    translate([-x/2,-y/2,-z/2]) cylinder(r = r, h = h );
}
}


$fn=20;

difference () {
    cube ([12+3+1,56,base_thickness]);
    translate([12/2+3,3,0]) rotate (0,90,0)  cylinder_double (r=1.8,h=20,x=5);
    translate([12/2+3,3+30,0]) rotate (0,90,0)  cylinder_double (r=1.8,h=20,x=5);
    translate([12/2+3,3+50,0]) rotate (0,90,0)  cylinder_double (r=1.8,h=20,x=5);
};

translate([-3,0,0]) difference () {
    translate ([-1,8,0]) cube ([14, attacher_thickness, height]);
    translate ([12/2,0,height-10]) rotate ([-90,0,0]) cylinder_double (r=1.8, h = 56, x=0, y=8, z=0 );
    
}

//support of the structure if needed
translate([-2,23,base_thickness+10.0]) {
    difference () {
        rotate([0,90,0]) difference () {
        cylinder (h=12, r=15);
        cylinder (h=12, r= 10);
        }
    
    translate([-1,-50,0]) cube ([100,100,100]);
    translate([-1,0,-50]) cube ([100,100,100]);
    }
}
translate([0,13,0]) {
    scale([1,3,1]) cylinder(h=base_thickness, r=4);
}