//Infant-breath-mechanical-simulator
//https://github.com/arisberd/Infant-breath-mechanical-simulator
//version 0.2
//GNU GPL v3

//syringe_attacher_with_flange.scad is used to mount any syringe. 

base_thickness= 7;
attacher_thickness=8; 
height = 60; //Distance between the top of the x-carriage.scad and the piston of the syringe
y_position = 13; //y offset of the attacher
base_x = 20+10; //dimension of the base
base_y = 56+4; //dimension of the base
strut_y = 27; //dimension of the strut
strut_z = height-22; //dimension of the strut

//uncomment the following line to produce only the flange
//!flange(diameter_max=50+18+2+8, diameter_mid=50+5, diameter_min = 28, thickness=attacher_thickness,hole_diameter=7,open=false);


module cylinder_double (r,h,x=0,y=0,z=0) {
   hull() {
    translate([x/2,y/2,z/2]) cylinder(r = r, h = h);
    translate([-x/2,-y/2,-z/2]) cylinder(r = r, h = h );
}
}


//Module flange
//diameter_min = the diameter in witch the handle fits
//diameter_mid = the diameter of the handle. The bolts are places between this and the diameter_max
//hole_diameter = diameter of each hole
//hole_degrees = the degrees of the circle at flange that the holes appear
//open = true, makes an open flange without lid
module flange(diameter_max,diameter_mid,diameter_min,thickness,hole_diameter, hole_degrees=45, open=false) {
    difference () {
    cylinder (d=diameter_max,h=thickness);
    //4holes
    rotate([0,0,hole_degrees]) translate([(diameter_max-diameter_mid)/4+diameter_mid/2,0,0]) cylinder(d=hole_diameter,h=thickness,$fn=12);
    rotate([0,0,-hole_degrees]) translate([(diameter_max-diameter_mid)/4+diameter_mid/2,0,0]) cylinder(d=hole_diameter,h=thickness,$fn=12);
    rotate([0,0,180-hole_degrees]) translate([(diameter_max-diameter_mid)/4+diameter_mid/2,0,0]) cylinder(d=hole_diameter,h=thickness,$fn=12);  
    rotate([0,0,180+hole_degrees]) translate([(diameter_max-diameter_mid)/4+diameter_mid/2,0,0]) cylinder(d=hole_diameter,h=thickness,$fn=12);        
    //the medium diameter cylinder
    %cylinder (d=diameter_mid,h=thickness);
    rotate([0,0,180]) if (open) { //if open=true, then the 2nd piece is made, with min hole
        cylinder (d=diameter_min,h=thickness);
        translate([diameter_max/2,0,0]) cylinder_double(r=diameter_min/2,h=thickness,x=diameter_max);
    }
    }
    %cylinder(h=thickness,d=1); //for centering purposes   
    
}



$fn=20;
difference () {
    union() {
//base on carriage
difference () {
    union() {
        //base rectangular 
        translate([-base_x/2,0,0]) cube ([base_x,base_y,base_thickness]);
        //base strut
            CubePoints = [
                [  base_x/2,  y_position+attacher_thickness,  0 ],  //0
                [ base_x/2,  y_position+attacher_thickness+strut_y,  0 ],  //1
                [ -base_x/2,  y_position+attacher_thickness+strut_y,  0 ],  //2
                [  -base_x/2,  y_position+attacher_thickness,  0 ],  //3
                [  base_x/2,  y_position+attacher_thickness, strut_z ],  //4
                [ base_x/2,  y_position+attacher_thickness+strut_y,  base_thickness ],  //5
                [ -base_x/2,  y_position+attacher_thickness+strut_y,  base_thickness ],  //6
                [  -base_x/2,  y_position+attacher_thickness, strut_z ]]; //7
  
            CubeFaces = [
                [0,1,2,3],  // bottom
                [4,5,1,0],  // front
                [7,6,5,4],  // top 
                [5,6,2,1],  // right
                [6,7,3,2],  // back
                [7,4,0,3]]; // left
  
            polyhedron( CubePoints, CubeFaces );
        
    }
        translate([0,3+2,0]) rotate (0,90,0)  cylinder_double (r=1.8,h=base_thickness,x=10);
        translate([0,3+30+2,0]) rotate (0,90,0)  cylinder_double (r=1.8,h=base_thickness,x=10);
        //2nd has another hole for the strut
        translate([0,3+30+2,base_thickness]) rotate (0,90,0)  cylinder_double (r=1.8+2,h=base_thickness*10,x=10);
        translate([0,3+50+2,0]) rotate (0,90,0)  cylinder_double (r=1.8,h=base_thickness,x=10);
};

//neck
union() {
    translate ([-base_x/2,y_position,0]) cube ([base_x,attacher_thickness,40]);
    translate([0,y_position+attacher_thickness,height]) rotate([90,90,0]) flange(diameter_max=50+18+2+8, diameter_mid=50+5, diameter_min = 28, thickness=attacher_thickness,hole_diameter=7,open=true);
}
}
translate([-base_x/2,0,-100]) cube([base_x,base_y,100]);
}
