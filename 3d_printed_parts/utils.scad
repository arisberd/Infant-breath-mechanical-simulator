use <MCAD/2Dshapes.scad>


//test
//$fn=16;
//cylinder_mil(10,20,top_d=15,top_h=2);
//rounded_cube(2, 10, 5, center=false);


module arc(R, r, height, start_angle, end_angle, center=true, fn) {
	linear_extrude(height=height, center=center) donutSlice(r,R, start_angle, end_angle, $fn=fn);
}



module rounded_cube(w, l, h, center=false) {
  r = w/2;
  rect_l = l-w/2;
  
  offset_y = center ? -l/2 : 0;
  translate([0,rect_l + offset_y,0]) {
    translate([0,-rect_l/2,0]) cube([w,rect_l,h], center=true);
    cylinder(r=r, h=h, center=true, $fn=20);
  }
}

// milling cylinder 45deggre
//top_d and bottom_d are the diameters of the head of the screw
//top_h and bottom_h are the thicknesses of the head of the screw
module cylinder_mil(d,h,top_d, bottom_d,top_h, bottom_h) {
    cylinder(d=d,h = h);
  if (bottom_d) 
    translate([0,0,bottom_h]) cylinder(d1=bottom_d, d2 = d, h = 0.5* (bottom_d - d));
  if (bottom_h)   
    cylinder(d=bottom_d, h = bottom_h);  
  if (top_d)
        if (top_h==undef) {
            translate([0,0,h-(top_d-d)]) cylinder(d1=d, d2 = top_d, h = top_d - d);
        }
        else {
            translate([0,0,h-(top_d-d)-top_h]) cylinder(d1=d, d2 = top_d, h = top_d - d);
        }  
  if (top_h) 
    translate([0,0,h- top_h]) cylinder(d=top_d, h = top_h);
  
}
