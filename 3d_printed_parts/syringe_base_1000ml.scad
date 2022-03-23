//Infant-breath-mechanical-simulator
//https://github.com/arisberd/Infant-breath-mechanical-simulator
//version 0.2
//GNU GPL v3

//This printed piece graps the syringe-piston 
//At least 2 pieces need to stabilise syringe



//Data
d_emb=108; //syringe diameter
th_1 = 2.5; //thickness of the circular piece
length=140;//total length
th_2 = 2.5; //thickness of the cantilever
//off = 11; //μετατόπιση "offset" προβόλου
phi = 30; //degrees of cantilever displacement
bolt_distance = 120; //distance between the two bolts
bolt_d = 6.5; //diameter of the bolts
width = 24; //width of the piece

$fn=30;
//Σύμφωνα με τα άλλα μοντέλα, οι τρύπες αποτελούν ένα τετράγωνο 28Χ62 (τα κέντρα τους). Βρίσκονται σε ένα κουτί 17,5Χ48Χ80

difference () {
    union () {
        cylinder (d=d_emb+th_1, h=width, center =true);
        off = sin(phi) * (d_emb+th_1)/2;
        translate([0,off,0]) cube ([length, th_2, width], center=true);
        
    }
    cylinder (d=d_emb-th_1, h=width+1, center=true);
    //first hole
    #translate ([bolt_distance/2,0,0]) rotate ([90,0,0]) cylinder (h=d_emb+th_1, d=bolt_d,center=true);
    //second hole
    #translate ([-bolt_distance/2,0,0]) rotate ([90,0,0]) cylinder (h=d_emb+th_1, d=bolt_d,center=true);
    off = sin(phi) * (d_emb+th_1)/2;
    translate([-length/2,-d_emb-th_1-th_2/2,-width/2]) cube([length,off+d_emb+th_1,width]);
}

