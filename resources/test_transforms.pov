// cs473, recurses
camera {
  location  <0, 0, 14>
  up        <0,  1,  0>
  right     <1.5, 0,  0>
  look_at   <0, 0, 0>
}


light_source {<-5, 3, 0> color rgb <1.0, 0.0, 1.0>}
light_source {<5, 10, 5> color rgb <0.3, 0.4, 0.5>}

// floor
plane {<0, 1, 0>, -4
  pigment {color rgb <0.2, 0.2, 0.8>}
  finish {ambient 0.4 diffuse 0.2}
  translate <0, -1, 0>
}


// back wall
plane {<0, 0, -1>, 30
  pigment {color rgb <1.0, 1.0, 1.0>}
  finish {ambient 0.4 diffuse 0.2}
}

// pyramid
// bottom row front
triangle {
  <-1, 0, 0>,
  <0, 2, 0>,
  <1, 0, 0>
  rotate <0, -10, 0>
  scale <4, 4, 4>
  translate <-8, -4.9999, -12>
  rotate <-5, 0, 0>
  pigment {color rgb <1.0, 1.0, 1.0>}
  finish {ambient 0.4 diffuse 0.5}
}
triangle {
  <-1, 0, 0>,
  <0, 2, 0>,
  <1, 0, 0>
  scale <4, 4, 4>
  translate <0, -4.9999, -12>
  pigment {color rgb <1.0, 1.0, 1.0>}
  finish {ambient 0.4 diffuse 0.5}
}
triangle {
  <-1, 0, 0>,
  <0, 2, 0>,
  <1, 0, 0>
  scale <4, 4, 4>
  translate <8, -4.9999, -12>
  pigment {color rgb <1.0, 1.0, 1.0>}
  finish {ambient 0.4 diffuse 0.5}
}

// middle row
triangle {
  <-1, 0, 0>,
  <0, 2, 0>,
  <1, 0, 0>
  scale <4, 4, 4>
  translate <-4, 3, -12>
  pigment {color rgb <1.0, 1.0, 1.0>}
  finish {ambient 0.4 diffuse 0.5}
}
triangle {
  <-1, 0, 0>,
  <0, 2, 0>,
  <1, 0, 0>
  scale <4, 4, 4>
  translate <4, 3, -12>
  pigment {color rgb <1.0, 1.0, 1.0>}
  finish {ambient 0.4 diffuse 0.5}
}

// top row
triangle {
  <-1, 0, 0>,
  <0, 2, 0>,
  <1, 0, 0>
  scale <4, 4, 4>
  translate <0, 11, -12>
  pigment {color rgb <1.0, 1.0, 1.0>}
  finish {ambient 0.4 diffuse 0.5}
}


// tile the floor
// leftmost column
triangle {
  <0, 0, 0>,
  <1, 0, 0>,
  <0, 0, -1>
  scale <4, 4, 4>
  translate <-22, -4.9999, -20>
  pigment {color rgb <1.0, 0.0, 1.0>}
  finish {ambient 0.4 diffuse 0.5}
}

// one column to the right
triangle {
  <0, 0, 0>,
  <1, 0, 0>,
  <0, 0, -1>
  scale <4, 4, 4>
  translate <-18, -4.9999, -12>
  pigment {color rgb <1.0, 0.0, 1.0>}
  finish {ambient 0.4 diffuse 0.5}
}

triangle {
  <0, 0, 0>,
  <1, 0, 0>,
  <0, 0, -1>
  scale <4, 4, 4>
  translate <-18, -4.9999, -16>
  pigment {color rgb <1.0, 0.0, 1.0>}
  finish {ambient 0.4 diffuse 0.5}
}

triangle {
  <0, 0, 0>,
  <1, 0, 0>,
  <0, 0, -1>
  scale <4, 4, 4>
  translate <-18, -4.9999, -20>
  pigment {color rgb <1.0, 0.0, 1.0>}
  finish {ambient 0.4 diffuse 0.5}
}

// one column to the right
triangle {
  <0, 0, 0>,
  <1, 0, 0>,
  <0, 0, -1>
  scale <4, 4, 4>
  translate <-14, -4.9999, -4>
  pigment {color rgb <1.0, 0.0, 1.0>}
  finish {ambient 0.4 diffuse 0.5}
}

triangle {
  <0, 0, 0>,
  <1, 0, 0>,
  <0, 0, -1>
  scale <4, 4, 4>
  translate <-14, -4.9999, -8>
  pigment {color rgb <1.0, 0.0, 1.0>}
  finish {ambient 0.4 diffuse 0.5}
}

triangle {
  <0, 0, 0>,
  <1, 0, 0>,
  <0, 0, -1>
  scale <4, 4, 4>
  translate <-14, -4.9999, -12>
  pigment {color rgb <1.0, 0.0, 1.0>}
  finish {ambient 0.4 diffuse 0.5}
}
triangle {
  <0, 0, 0>,
  <1, 0, 0>,
  <0, 0, -1>
  scale <4, 4, 4>
  translate <-14, -4.9999, -16>
  pigment {color rgb <1.0, 0.0, 1.0>}
  finish {ambient 0.4 diffuse 0.5}
}

triangle {
  <0, 0, 0>,
  <1, 0, 0>,
  <0, 0, -1>
  scale <4, 4, 4>
  translate <-14, -4.9999, -20>
  pigment {color rgb <1.0, 0.0, 1.0>}
  finish {ambient 0.4 diffuse 0.5}
}

triangle {
  <0, 0, 0>,
  <1, 0, 0>,
  <0, 0, -1>
  scale <4, 4, 4>
  translate <-14, -4.9999, -24>
  pigment {color rgb <1.0, 0.0, 1.0>}
  finish {ambient 0.4 diffuse 0.5}
}

// one column to the right
triangle {
  <0, 0, 0>,
  <1, 0, 0>,
  <0, 0, -1>
  scale <4, 4, 4>
  translate <-10, -4.9999, 4>
  pigment {color rgb <1.0, 0.0, 1.0>}
  finish {ambient 0.4 diffuse 0.5}
}

triangle {
  <0, 0, 0>,
  <1, 0, 0>,
  <0, 0, -1>
  scale <4, 4, 4>
  translate <-10, -4.9999, 0>
  pigment {color rgb <1.0, 0.0, 1.0>}
  finish {ambient 0.4 diffuse 0.5}
}

triangle {
  <0, 0, 0>,
  <1, 0, 0>,
  <0, 0, -1>
  scale <4, 4, 4>
  translate <-10, -4.9999, -4>
  pigment {color rgb <1.0, 0.0, 1.0>}
  finish {ambient 0.4 diffuse 0.5}
}

triangle {
  <0, 0, 0>,
  <1, 0, 0>,
  <0, 0, -1>
  scale <4, 4, 4>
  translate <-10, -4.9999, -8>
  pigment {color rgb <1.0, 0.0, 1.0>}
  finish {ambient 0.4 diffuse 0.5}
}

triangle {
  <0, 0, 0>,
  <1, 0, 0>,
  <0, 0, -1>
  scale <4, 4, 4>
  translate <-10, -4.9999, -8>
  pigment {color rgb <1.0, 0.0, 1.0>}
  finish {ambient 0.4 diffuse 0.5}
}

triangle {
  <0, 0, 0>,
  <1, 0, 0>,
  <0, 0, -1>
  scale <4, 4, 4>
  translate <-10, -4.9999, -12>
  pigment {color rgb <1.0, 0.0, 1.0>}
  finish {ambient 0.4 diffuse 0.5}
}

triangle {
  <0, 0, 0>,
  <1, 0, 0>,
  <0, 0, -1>
  scale <4, 4, 4>
  translate <-10, -4.9999, -16>
  pigment {color rgb <1.0, 0.0, 1.0>}
  finish {ambient 0.4 diffuse 0.5}
}

triangle {
  <0, 0, 0>,
  <1, 0, 0>,
  <0, 0, -1>
  scale <4, 4, 4>
  translate <-10, -4.9999, -20>
  pigment {color rgb <1.0, 0.0, 1.0>}
  finish {ambient 0.4 diffuse 0.5}
}

triangle {
  <0, 0, 0>,
  <1, 0, 0>,
  <0, 0, -1>
  scale <4, 4, 4>
  translate <-10, -4.9999, -24>
  pigment {color rgb <1.0, 0.0, 1.0>}
  finish {ambient 0.4 diffuse 0.5}
}

triangle {
  <0, 0, 0>,
  <1, 0, 0>,
  <0, 0, -1>
  scale <4, 4, 4>
  translate <-10, -4.9999, -28>
  pigment {color rgb <1.0, 0.0, 1.0>}
  finish {ambient 0.4 diffuse 0.5}
}

triangle {
  <0, 0, 0>,
  <1, 0, 0>,
  <0, 0, -1>
  scale <4, 4, 4>
  translate <-10, -4.9999, -32>
  pigment {color rgb <1.0, 0.0, 1.0>}
  finish {ambient 0.4 diffuse 0.5}
}

triangle {
  <0, 0, 0>,
  <1, 0, 0>,
  <0, 0, -1>
  scale <4, 4, 4>
  translate <-10, -4.9999, -36>
  pigment {color rgb <1.0, 0.0, 1.0>}
  finish {ambient 0.4 diffuse 0.5}
}

triangle {
  <0, 0, 0>,
  <1, 0, 0>,
  <0, 0, -1>
  scale <4, 4, 4>
  translate <-10, -4.9999, -40>
  pigment {color rgb <1.0, 0.0, 1.0>}
  finish {ambient 0.4 diffuse 0.5}
}


// one column to the right
triangle {
  <0, 0, 0>,
  <1, 0, 0>,
  <0, 0, -1>
  scale <4, 4, 4>
  translate <-6, -4.9999, 4>
  pigment {color rgb <1.0, 0.0, 1.0>}
  finish {ambient 0.4 diffuse 0.5}
}

triangle {
  <0, 0, 0>,
  <1, 0, 0>,
  <0, 0, -1>
  scale <4, 4, 4>
  translate <-6, -4.9999, 0>
  pigment {color rgb <1.0, 0.0, 1.0>}
  finish {ambient 0.4 diffuse 0.5}
}

triangle {
  <0, 0, 0>,
  <1, 0, 0>,
  <0, 0, -1>
  scale <4, 4, 4>
  translate <-6, -4.9999, -4>
  pigment {color rgb <1.0, 0.0, 1.0>}
  finish {ambient 0.4 diffuse 0.5}
}

triangle {
  <0, 0, 0>,
  <1, 0, 0>,
  <0, 0, -1>
  scale <4, 4, 4>
  translate <-6, -4.9999, -8>
  pigment {color rgb <1.0, 0.0, 1.0>}
  finish {ambient 0.4 diffuse 0.5}
}

triangle {
  <0, 0, 0>,
  <1, 0, 0>,
  <0, 0, -1>
  scale <4, 4, 4>
  translate <-6, -4.9999, -12>
  pigment {color rgb <1.0, 0.0, 1.0>}
  finish {ambient 0.4 diffuse 0.5}
}

triangle {
  <0, 0, 0>,
  <1, 0, 0>,
  <0, 0, -1>
  scale <4, 4, 4>
  translate <-6, -4.9999, -16>
  pigment {color rgb <1.0, 0.0, 1.0>}
  finish {ambient 0.4 diffuse 0.5}
}

triangle {
  <0, 0, 0>,
  <1, 0, 0>,
  <0, 0, -1>
  scale <4, 4, 4>
  translate <-6, -4.9999, -20>
  pigment {color rgb <1.0, 0.0, 1.0>}
  finish {ambient 0.4 diffuse 0.5}
}

triangle {
  <0, 0, 0>,
  <1, 0, 0>,
  <0, 0, -1>
  scale <4, 4, 4>
  translate <-6, -4.9999, -24>
  pigment {color rgb <1.0, 0.0, 1.0>}
  finish {ambient 0.4 diffuse 0.5}
}

triangle {
  <0, 0, 0>,
  <1, 0, 0>,
  <0, 0, -1>
  scale <4, 4, 4>
  translate <-6, -4.9999, -28>
  pigment {color rgb <1.0, 0.0, 1.0>}
  finish {ambient 0.4 diffuse 0.5}
}

triangle {
  <0, 0, 0>,
  <1, 0, 0>,
  <0, 0, -1>
  scale <4, 4, 4>
  translate <-6, -4.9999, -32>
  pigment {color rgb <1.0, 0.0, 1.0>}
  finish {ambient 0.4 diffuse 0.5}
}

triangle {
  <0, 0, 0>,
  <1, 0, 0>,
  <0, 0, -1>
  scale <4, 4, 4>
  translate <-6, -4.9999, -36>
  pigment {color rgb <1.0, 0.0, 1.0>}
  finish {ambient 0.4 diffuse 0.5}
}

triangle {
  <0, 0, 0>,
  <1, 0, 0>,
  <0, 0, -1>
  scale <4, 4, 4>
  translate <-6, -4.9999, -40>
  pigment {color rgb <1.0, 0.0, 1.0>}
  finish {ambient 0.4 diffuse 0.5}
}

triangle {
  <0, 0, 0>,
  <1, 0, 0>,
  <0, 0, -1>
  scale <4, 4, 4>
  translate <-6, -4.9999, -44>
  pigment {color rgb <1.0, 0.0, 1.0>}
  finish {ambient 0.4 diffuse 0.5}
}

triangle {
  <0, 0, 0>,
  <1, 0, 0>,
  <0, 0, -1>
  scale <4, 4, 4>
  translate <-6, -4.9999, -48>
  pigment {color rgb <1.0, 0.0, 1.0>}
  finish {ambient 0.4 diffuse 0.5}
}


// one more column to the right
triangle {
  <0, 0, 0>,
  <1, 0, 0>,
  <0, 0, -1>
  scale <4, 4, 4>
  translate <-2, -4.9999, 4>
  pigment {color rgb <1.0, 0.0, 1.0>}
  finish {ambient 0.4 diffuse 0.5}
}

triangle {
  <0, 0, 0>,
  <1, 0, 0>,
  <0, 0, -1>
  scale <4, 4, 4>
  translate <-2, -4.9999, 0>
  pigment {color rgb <1.0, 0.0, 1.0>}
  finish {ambient 0.4 diffuse 0.5}
}

triangle {
  <0, 0, 0>,
  <1, 0, 0>,
  <0, 0, -1>
  scale <4, 4, 4>
  translate <-2, -4.9999, -4>
  pigment {color rgb <1.0, 0.0, 1.0>}
  finish {ambient 0.4 diffuse 0.5}
}

triangle {
  <0, 0, 0>,
  <1, 0, 0>,
  <0, 0, -1>
  scale <4, 4, 4>
  translate <-2, -4.9999, -8>
  pigment {color rgb <1.0, 0.0, 1.0>}
  finish {ambient 0.4 diffuse 0.5}
}

triangle {
  <0, 0, 0>,
  <1, 0, 0>,
  <0, 0, -1>
  scale <4, 4, 4>
  translate <-2, -4.9999, -12>
  pigment {color rgb <1.0, 0.0, 1.0>}
  finish {ambient 0.4 diffuse 0.5}
}

triangle {
  <0, 0, 0>,
  <1, 0, 0>,
  <0, 0, -1>
  scale <4, 4, 4>
  translate <-2, -4.9999, -16>
  pigment {color rgb <1.0, 0.0, 1.0>}
  finish {ambient 0.4 diffuse 0.5}
}

triangle {
  <0, 0, 0>,
  <1, 0, 0>,
  <0, 0, -1>
  scale <4, 4, 4>
  translate <-2, -4.9999, -20>
  pigment {color rgb <1.0, 0.0, 1.0>}
  finish {ambient 0.4 diffuse 0.5}
}

triangle {
  <0, 0, 0>,
  <1, 0, 0>,
  <0, 0, -1>
  scale <4, 4, 4>
  translate <-2, -4.9999, -24>
  pigment {color rgb <1.0, 0.0, 1.0>}
  finish {ambient 0.4 diffuse 0.5}
}

triangle {
  <0, 0, 0>,
  <1, 0, 0>,
  <0, 0, -1>
  scale <4, 4, 4>
  translate <-2, -4.9999, -28>
  pigment {color rgb <1.0, 0.0, 1.0>}
  finish {ambient 0.4 diffuse 0.5}
}

triangle {
  <0, 0, 0>,
  <1, 0, 0>,
  <0, 0, -1>
  scale <4, 4, 4>
  translate <-2, -4.9999, -32>
  pigment {color rgb <1.0, 0.0, 1.0>}
  finish {ambient 0.4 diffuse 0.5}
}

triangle {
  <0, 0, 0>,
  <1, 0, 0>,
  <0, 0, -1>
  scale <4, 4, 4>
  translate <-2, -4.9999, -36>
  pigment {color rgb <1.0, 0.0, 1.0>}
  finish {ambient 0.4 diffuse 0.5}
}


// one more column to the right

triangle {
  <0, 0, 0>,
  <1, 0, 0>,
  <0, 0, -1>
  scale <4, 4, 4>
  translate <2, -4.9999, 4>
  pigment {color rgb <1.0, 0.0, 1.0>}
  finish {ambient 0.4 diffuse 0.5}
}


triangle {
  <0, 0, 0>,
  <1, 0, 0>,
  <0, 0, -1>
  scale <4, 4, 4>
  translate <2, -4.9999, 0>
  pigment {color rgb <1.0, 0.0, 1.0>}
  finish {ambient 0.4 diffuse 0.5}
}


triangle {
  <0, 0, 0>,
  <1, 0, 0>,
  <0, 0, -1>
  scale <4, 4, 4>
  translate <2, -4.9999, -4>
  pigment {color rgb <1.0, 0.0, 1.0>}
  finish {ambient 0.4 diffuse 0.5}
}


triangle {
  <0, 0, 0>,
  <1, 0, 0>,
  <0, 0, -1>
  scale <4, 4, 4>
  translate <2, -4.9999, -8>
  pigment {color rgb <1.0, 0.0, 1.0>}
  finish {ambient 0.4 diffuse 0.5}
}


triangle {
  <0, 0, 0>,
  <1, 0, 0>,
  <0, 0, -1>
  scale <4, 4, 4>
  translate <2, -4.9999, -12>
  pigment {color rgb <1.0, 0.0, 1.0>}
  finish {ambient 0.4 diffuse 0.5}
}


triangle {
  <0, 0, 0>,
  <1, 0, 0>,
  <0, 0, -1>
  scale <4, 4, 4>
  translate <2, -4.9999, -16>
  pigment {color rgb <1.0, 0.0, 1.0>}
  finish {ambient 0.4 diffuse 0.5}
}


triangle {
  <0, 0, 0>,
  <1, 0, 0>,
  <0, 0, -1>
  scale <4, 4, 4>
  translate <2, -4.9999, -20>
  pigment {color rgb <1.0, 0.0, 1.0>}
  finish {ambient 0.4 diffuse 0.5}
}


triangle {
  <0, 0, 0>,
  <1, 0, 0>,
  <0, 0, -1>
  scale <4, 4, 4>
  translate <2, -4.9999, -24>
  pigment {color rgb <1.0, 0.0, 1.0>}
  finish {ambient 0.4 diffuse 0.5}
}


triangle {
  <0, 0, 0>,
  <1, 0, 0>,
  <0, 0, -1>
  scale <4, 4, 4>
  translate <2, -4.9999, -28>
  pigment {color rgb <1.0, 0.0, 1.0>}
  finish {ambient 0.4 diffuse 0.5}
}


// one more column to the right
triangle {
  <0, 0, 0>,
  <1, 0, 0>,
  <0, 0, -1>
  scale <4, 4, 4>
  translate <6, -4.9999, 4>
  pigment {color rgb <1.0, 0.0, 1.0>}
  finish {ambient 0.4 diffuse 0.5}
}

triangle {
  <0, 0, 0>,
  <1, 0, 0>,
  <0, 0, -1>
  scale <4, 4, 4>
  translate <6, -4.9999, 0>
  pigment {color rgb <1.0, 0.0, 1.0>}
  finish {ambient 0.4 diffuse 0.5}
}

triangle {
  <0, 0, 0>,
  <1, 0, 0>,
  <0, 0, -1>
  scale <4, 4, 4>
  translate <6, -4.9999, -4>
  pigment {color rgb <1.0, 0.0, 1.0>}
  finish {ambient 0.4 diffuse 0.5}
}

triangle {
  <0, 0, 0>,
  <1, 0, 0>,
  <0, 0, -1>
  scale <4, 4, 4>
  translate <6, -4.9999, -8>
  pigment {color rgb <1.0, 0.0, 1.0>}
  finish {ambient 0.4 diffuse 0.5}
}

triangle {
  <0, 0, 0>,
  <1, 0, 0>,
  <0, 0, -1>
  scale <4, 4, 4>
  translate <6, -4.9999, -12>
  pigment {color rgb <1.0, 0.0, 1.0>}
  finish {ambient 0.4 diffuse 0.5}
}

triangle {
  <0, 0, 0>,
  <1, 0, 0>,
  <0, 0, -1>
  scale <4, 4, 4>
  translate <6, -4.9999, -16>
  pigment {color rgb <1.0, 0.0, 1.0>}
  finish {ambient 0.4 diffuse 0.5}
}

triangle {
  <0, 0, 0>,
  <1, 0, 0>,
  <0, 0, -1>
  scale <4, 4, 4>
  translate <6, -4.9999, -20>
  pigment {color rgb <1.0, 0.0, 1.0>}
  finish {ambient 0.4 diffuse 0.5}
}

triangle {
  <0, 0, 0>,
  <1, 0, 0>,
  <0, 0, -1>
  scale <4, 4, 4>
  translate <6, -4.9999, -24>
  pigment {color rgb <1.0, 0.0, 1.0>}
  finish {ambient 0.4 diffuse 0.5}
}

triangle {
  <0, 0, 0>,
  <1, 0, 0>,
  <0, 0, -1>
  scale <4, 4, 4>
  translate <6, -4.9999, -28>
  pigment {color rgb <1.0, 0.0, 1.0>}
  finish {ambient 0.4 diffuse 0.5}
}

// one more column to the right
triangle {
  <0, 0, 0>,
  <1, 0, 0>,
  <0, 0, -1>
  scale <4, 4, 4>
  translate <10, -4.9999, 4>
  pigment {color rgb <1.0, 0.0, 1.0>}
  finish {ambient 0.4 diffuse 0.5}
}

triangle {
  <0, 0, 0>,
  <1, 0, 0>,
  <0, 0, -1>
  scale <4, 4, 4>
  translate <10, -4.9999, 0>
  pigment {color rgb <1.0, 0.0, 1.0>}
  finish {ambient 0.4 diffuse 0.5}
}

triangle {
  <0, 0, 0>,
  <1, 0, 0>,
  <0, 0, -1>
  scale <4, 4, 4>
  translate <10, -4.9999, -4>
  pigment {color rgb <1.0, 0.0, 1.0>}
  finish {ambient 0.4 diffuse 0.5}
}

triangle {
  <0, 0, 0>,
  <1, 0, 0>,
  <0, 0, -1>
  scale <4, 4, 4>
  translate <10, -4.9999, -8>
  pigment {color rgb <1.0, 0.0, 1.0>}
  finish {ambient 0.4 diffuse 0.5}
}

triangle {
  <0, 0, 0>,
  <1, 0, 0>,
  <0, 0, -1>
  scale <4, 4, 4>
  translate <10, -4.9999, -12>
  pigment {color rgb <1.0, 0.0, 1.0>}
  finish {ambient 0.4 diffuse 0.5}
}

triangle {
  <0, 0, 0>,
  <1, 0, 0>,
  <0, 0, -1>
  scale <4, 4, 4>
  translate <10, -4.9999, -16>
  pigment {color rgb <1.0, 0.0, 1.0>}
  finish {ambient 0.4 diffuse 0.5}
}

triangle {
  <0, 0, 0>,
  <1, 0, 0>,
  <0, 0, -1>
  scale <4, 4, 4>
  translate <10, -4.9999, -20>
  pigment {color rgb <1.0, 0.0, 1.0>}
  finish {ambient 0.4 diffuse 0.5}
}

triangle {
  <0, 0, 0>,
  <1, 0, 0>,
  <0, 0, -1>
  scale <4, 4, 4>
  translate <10, -4.9999, -24>
  pigment {color rgb <1.0, 0.0, 1.0>}
  finish {ambient 0.4 diffuse 0.5}
}

triangle {
  <0, 0, 0>,
  <1, 0, 0>,
  <0, 0, -1>
  scale <4, 4, 4>
  translate <10, -4.9999, -28>
  pigment {color rgb <1.0, 0.0, 1.0>}
  finish {ambient 0.4 diffuse 0.5}
}

// one more column to the right
triangle {
  <0, 0, 0>,
  <1, 0, 0>,
  <0, 0, -1>
  scale <4, 4, 4>
  translate <14, -4.9999, -4>
  pigment {color rgb <1.0, 0.0, 1.0>}
  finish {ambient 0.4 diffuse 0.5}
}

triangle {
  <0, 0, 0>,
  <1, 0, 0>,
  <0, 0, -1>
  scale <4, 4, 4>
  translate <14, -4.9999, -8>
  pigment {color rgb <1.0, 0.0, 1.0>}
  finish {ambient 0.4 diffuse 0.5}
}

triangle {
  <0, 0, 0>,
  <1, 0, 0>,
  <0, 0, -1>
  scale <4, 4, 4>
  translate <14, -4.9999, -12>
  pigment {color rgb <1.0, 0.0, 1.0>}
  finish {ambient 0.4 diffuse 0.5}
}

triangle {
  <0, 0, 0>,
  <1, 0, 0>,
  <0, 0, -1>
  scale <4, 4, 4>
  translate <14, -4.9999, -16>
  pigment {color rgb <1.0, 0.0, 1.0>}
  finish {ambient 0.4 diffuse 0.5}
}

triangle {
  <0, 0, 0>,
  <1, 0, 0>,
  <0, 0, -1>
  scale <4, 4, 4>
  translate <14, -4.9999, -20>
  pigment {color rgb <1.0, 0.0, 1.0>}
  finish {ambient 0.4 diffuse 0.5}
}

triangle {
  <0, 0, 0>,
  <1, 0, 0>,
  <0, 0, -1>
  scale <4, 4, 4>
  translate <14, -4.9999, -24>
  pigment {color rgb <1.0, 0.0, 1.0>}
  finish {ambient 0.4 diffuse 0.5}
}

// one more column to the right
triangle {
  <0, 0, 0>,
  <1, 0, 0>,
  <0, 0, -1>
  scale <4, 4, 4>
  translate <18, -4.9999, -8>
  pigment {color rgb <1.0, 0.0, 1.0>}
  finish {ambient 0.4 diffuse 0.5}
}

triangle {
  <0, 0, 0>,
  <1, 0, 0>,
  <0, 0, -1>
  scale <4, 4, 4>
  translate <18, -4.9999, -12>
  pigment {color rgb <1.0, 0.0, 1.0>}
  finish {ambient 0.4 diffuse 0.5}
}

triangle {
  <0, 0, 0>,
  <1, 0, 0>,
  <0, 0, -1>
  scale <4, 4, 4>
  translate <18, -4.9999, -16>
  pigment {color rgb <1.0, 0.0, 1.0>}
  finish {ambient 0.4 diffuse 0.5}
}

triangle {
  <0, 0, 0>,
  <1, 0, 0>,
  <0, 0, -1>
  scale <4, 4, 4>
  translate <18, -4.9999, -20>
  pigment {color rgb <1.0, 0.0, 1.0>}
  finish {ambient 0.4 diffuse 0.5}
}

triangle {
  <0, 0, 0>,
  <1, 0, 0>,
  <0, 0, -1>
  scale <4, 4, 4>
  translate <18, -4.9999, -24>
  pigment {color rgb <1.0, 0.0, 1.0>}
  finish {ambient 0.4 diffuse 0.5}
}

triangle {
  <0, 0, 0>,
  <1, 0, 0>,
  <0, 0, -1>
  scale <4, 4, 4>
  translate <18, -4.9999, -28>
  pigment {color rgb <1.0, 0.0, 1.0>}
  finish {ambient 0.4 diffuse 0.5}
}

// one more column to the right
triangle {
  <0, 0, 0>,
  <1, 0, 0>,
  <0, 0, -1>
  scale <4, 4, 4>
  translate <22, -4.9999, -12>
  pigment {color rgb <1.0, 0.0, 1.0>}
  finish {ambient 0.4 diffuse 0.5}
}

triangle {
  <0, 0, 0>,
  <1, 0, 0>,
  <0, 0, -1>
  scale <4, 4, 4>
  translate <22, -4.9999, -16>
  pigment {color rgb <1.0, 0.0, 1.0>}
  finish {ambient 0.4 diffuse 0.5}
}

triangle {
  <0, 0, 0>,
  <1, 0, 0>,
  <0, 0, -1>
  scale <4, 4, 4>
  translate <22, -4.9999, -20>
  pigment {color rgb <1.0, 0.0, 1.0>}
  finish {ambient 0.4 diffuse 0.5}
}

triangle {
  <0, 0, 0>,
  <1, 0, 0>,
  <0, 0, -1>
  scale <4, 4, 4>
  translate <22, -4.9999, -24>
  pigment {color rgb <1.0, 0.0, 1.0>}
  finish {ambient 0.4 diffuse 0.5}
}

