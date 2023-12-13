#ifndef barbie_h
    #define barbie_h

    #include <iostream>
    #include <fstream>

    struct nodo{
        bool occupied;
    };

    struct arco{
        int start;
        int end;
        int wheight;
    };

    struct in_out{
        fstream in;
        fstream out;
    };

#endif