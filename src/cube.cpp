// Tutorial code from http://www.arcsynthesis.org/gltut
// Copyright © 2012 Jason L. McKesson

const float vertexData[] = {
     0.25f,  0.25f, 0.75f, 1.0f,
     0.25f, -0.25f, 0.75f, 1.0f,
    -0.25f,  0.25f, 0.75f, 1.0f,

     0.25f, -0.25f, 0.75f, 1.0f,
    -0.25f, -0.25f, 0.75f, 1.0f,
    -0.25f,  0.25f, 0.75f, 1.0f,

     0.25f,  0.25f, -0.75f, 1.0f,
    -0.25f,  0.25f, -0.75f, 1.0f,
     0.25f, -0.25f, -0.75f, 1.0f,

     0.25f, -0.25f, -0.75f, 1.0f,
    -0.25f,  0.25f, -0.75f, 1.0f,
    -0.25f, -0.25f, -0.75f, 1.0f,

    -0.25f,  0.25f,  0.75f, 1.0f,
    -0.25f, -0.25f,  0.75f, 1.0f,
    -0.25f, -0.25f, -0.75f, 1.0f,

    -0.25f,  0.25f,  0.75f, 1.0f,
    -0.25f, -0.25f, -0.75f, 1.0f,
    -0.25f,  0.25f, -0.75f, 1.0f,

     0.25f,  0.25f,  0.75f, 1.0f,
     0.25f, -0.25f, -0.75f, 1.0f,
     0.25f, -0.25f,  0.75f, 1.0f,

     0.25f,  0.25f,  0.75f, 1.0f,
     0.25f,  0.25f, -0.75f, 1.0f,
     0.25f, -0.25f, -0.75f, 1.0f,

     0.25f,  0.25f, -0.75f, 1.0f,
     0.25f,  0.25f,  0.75f, 1.0f,
    -0.25f,  0.25f,  0.75f, 1.0f,

     0.25f,  0.25f, -0.75f, 1.0f,
    -0.25f,  0.25f,  0.75f, 1.0f,
    -0.25f,  0.25f, -0.75f, 1.0f,

     0.25f, -0.25f, -0.75f, 1.0f,
    -0.25f, -0.25f,  0.75f, 1.0f,
     0.25f, -0.25f,  0.75f, 1.0f,

     0.25f, -0.25f, -0.75f, 1.0f,
    -0.25f, -0.25f, -0.75f, 1.0f,
    -0.25f, -0.25f,  0.75f, 1.0f,




    0.0f, 0.0f, 1.0f, 1.0f,
    0.0f, 0.0f, 1.0f, 1.0f,
    0.0f, 0.0f, 1.0f, 1.0f,

    0.0f, 0.0f, 1.0f, 1.0f,
    0.0f, 0.0f, 1.0f, 1.0f,
    0.0f, 0.0f, 1.0f, 1.0f,

    0.8f, 0.8f, 0.8f, 1.0f,
    0.8f, 0.8f, 0.8f, 1.0f,
    0.8f, 0.8f, 0.8f, 1.0f,

    0.8f, 0.8f, 0.8f, 1.0f,
    0.8f, 0.8f, 0.8f, 1.0f,
    0.8f, 0.8f, 0.8f, 1.0f,

    0.0f, 1.0f, 0.0f, 1.0f,
    0.0f, 1.0f, 0.0f, 1.0f,
    0.0f, 1.0f, 0.0f, 1.0f,

    0.0f, 1.0f, 0.0f, 1.0f,
    0.0f, 1.0f, 0.0f, 1.0f,
    0.0f, 1.0f, 0.0f, 1.0f,

    0.5f, 0.5f, 0.0f, 1.0f,
    0.5f, 0.5f, 0.0f, 1.0f,
    0.5f, 0.5f, 0.0f, 1.0f,

    0.5f, 0.5f, 0.0f, 1.0f,
    0.5f, 0.5f, 0.0f, 1.0f,
    0.5f, 0.5f, 0.0f, 1.0f,

    1.0f, 0.0f, 0.0f, 1.0f,
    1.0f, 0.0f, 0.0f, 1.0f,
    1.0f, 0.0f, 0.0f, 1.0f,

    1.0f, 0.0f, 0.0f, 1.0f,
    1.0f, 0.0f, 0.0f, 1.0f,
    1.0f, 0.0f, 0.0f, 1.0f,

    0.0f, 1.0f, 1.0f, 1.0f,
    0.0f, 1.0f, 1.0f, 1.0f,
    0.0f, 1.0f, 1.0f, 1.0f,

    0.0f, 1.0f, 1.0f, 1.0f,
    0.0f, 1.0f, 1.0f, 1.0f,
    0.0f, 1.0f, 1.0f, 1.0f,

};

