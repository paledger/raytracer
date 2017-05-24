// cpe 473 happy valentined day! Transforms are needed
camera { location  <0, 0, 20>
up        <0,  1,  0>
right     <1.33333, 0,  0>
look_at   <0, 0, 0>
}


light_source {<-20, -15, 20> color rgb <0.0 , 0.0, 1.0>}

light_source {<-7, -3, 12> color rgb <1.0, 0.0, 0.0>}

light_source {<0, 0, 20> color rgb <1.5, 1.5 , 1.5>}

light_source {<7, 3, 12> color rgb <0.0, 0.0, 1>}

light_source {<20, 15, 20> color rgb <1.0, 0.0, 0.0>}

plane {<0, 0, 1>, -10
pigment {color rgb <1.0, 1.0, 1.0>}
finish {ambient 0.3 diffuse 0.7 roughness 0.001}
}

// head
sphere { <0, 0, -4>, 2
pigment { color rgb <0.2, 0.2, 1.0>}
finish {ambient 0.2 diffuse 0.4 specular 0.7}
scale <1.6, 0.6, 0.08>
translate <0.0, 5.1, 0.0>
scale <0.41, 0.8, 1.0>
}

// ** body **
// top
sphere { <0, 0, -4>, 2
pigment { color rgb <0.1, 0.2, 0.1>}
finish {ambient 0.2 diffuse 0.4 roughness 0.05 refraction 0.2}
scale <1.6, 0.6, 0.08>
translate <0.0, 0.2, 0>
scale <0.2, 2.4, 1>
}

// bottom
sphere { <0, 0, -4>, 2
pigment { color rgb <0.1, 0.2, 0.1>}
finish {ambient 0.2 diffuse 0.4 specular 0.5 roughness 0.05 refraction 0.2}
scale <1.6, 0.6, 0.08>
translate <0.0, -1, 0>
scale <0.1, 4, 1.2>
}

// ** wings **
// top left
sphere { <0, 0, -4>, 2
pigment { color rgbf <1.5, 0.2, 1.0, 0.1>}
finish {ambient 0.2 specular 0.7 roughness 0.05 reflection 0.5}
scale <1.6, 0.6, 0.08>
translate <-3.6, 1.5, 0>
rotate <0, 0, -10>
}
// top right
sphere { <0, 0, -4>, 2
pigment { color rgbf <1.5, 0.2, 1.0, 0.1>}
finish {ambient 0.2 specular 0.7 roughness 0.05 reflection 0.5}
scale <1.6, 0.6, 0.08>
translate <3.6, 1.5, 0>
rotate <0, 0, 10>
}

// bottom left
sphere { <0, 0, -4>, 2
pigment { color rgbf <1.5, 0.2, 1.0, 0.1>}
finish {ambient 0.2 specular 0.7 roughness 0.05 reflection 0.5}
scale <1.7, 0.6, 0.08>
translate <-3.6, 0.0, 0>
rotate <0, 0, 10>
}
// bottom right
sphere { <0, 0, -4>, 2
pigment { color rgbf <1.5, 0.2, 1.0, 0.1>}
finish {ambient 0.2 specular 0.7 roughness 0.05 reflection 0.5}
scale <1.7, 0.6, 0.08>
translate <3.6, 0.0, 0>
rotate <0, 0, -10>
}
