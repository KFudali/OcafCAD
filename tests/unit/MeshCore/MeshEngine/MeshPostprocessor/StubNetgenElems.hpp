#ifndef StubNetgenElems_hpp
#define StubNetgenElems_hpp

#include <vector>
#include "NetgenElemContainers.hpp"

inline Elem2DContainer elems2D() {
    netgen::Element2d elem_1(0, 1, 2);       // Triangle
    netgen::Element2d elem_2(5, 7, 2);       // Triangle
    netgen::Element2d elem_3(3, 4, 6, 7);    // Quad
    netgen::Element2d elem_4(5, 6, 8);       // Triangle
    Elem2DContainer elems(4); 

    elem_1.SetIndex(1);
    elem_2.SetIndex(1);
    elem_3.SetIndex(2);
    elem_4.SetIndex(2);

    elems[0] = elem_1; 
    elems[1] = elem_2;
    elems[2] = elem_3; 
    elems[3] = elem_4;
    return elems;
}

inline Elem3DContainer elems3D()
{
    netgen::Element tet(netgen::TET);
    tet.SetNP(4);
    tet[0] = 0;
    tet[1] = 1;
    tet[2] = 2;
    tet[3] = 3;

    netgen::Element pyr(netgen::PYRAMID);
    pyr.SetNP(5);
    pyr[0] = 10;
    pyr[1] = 11;
    pyr[2] = 12;
    pyr[3] = 13;
    pyr[4] = 14;

    netgen::Element prism(netgen::PRISM);
    prism.SetNP(6);
    prism[0] = 20;
    prism[1] = 21;
    prism[2] = 22;
    prism[3] = 23;
    prism[4] = 24;
    prism[5] = 25;

    netgen::Element hex(netgen::HEX);
    hex.SetNP(8);
    hex[0] = 30;
    hex[1] = 31;
    hex[2] = 32;
    hex[3] = 33;
    hex[4] = 34;
    hex[5] = 35;
    hex[6] = 36;
    hex[7] = 37;
   
    tet.SetIndex(1);
    pyr.SetIndex(1);
    prism.SetIndex(2);
    hex.SetIndex(2);
    
    Elem3DContainer elems(4);
    elems[0] = tet;
    elems[1] = pyr;
    elems[2] = prism;
    elems[3] = hex;

    return elems;
}



#endif