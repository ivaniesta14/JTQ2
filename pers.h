#ifndef PERS_H
#define PERS_H

#include "i14extra/point.hpp"
#include <limits>

using namespace std; using namespace i14extra;

typedef unsigned uint;
typedef unsigned short ushort;
typedef unsigned char uchar;
typedef signed char schar;

class pers{
public:
    point_t<uchar> pos=*new point_t<uchar>(
                numeric_limits<uchar>::max(),
                numeric_limits<uchar>::max());
    uchar hp=10,mp=10,td=0,df=1;
    static const uchar MAXHP=10,MAXMP=10,MAXX=16,MAXY=16;
    char clase='n',dispIcon='n';
    bool dead=false,noDisp=false,skip=false,skipAll=noDisp;
    ushort stun=0;///1 es cds, 2+ es stun
    pers()=delete;
    pers(uchar vx,uchar vy){setX(vx).setY(vy);}
    pers(const pers& other)=delete;
    const pers& operator=(const pers& rhs)=delete;
    pers& setX(const uchar& vx){
        pos.rx(vx%MAXX);
        return *this;
    }
    pers& setY(const uchar& vy){
        pos.ry(vy%MAXY);
        return *this;
    }
    pers& hit(const pers& other){
        uchar dmg=other.td+1;
        schar hpdmg=dmg-df;
        if(hpdmg>0){
            hp-=hpdmg;
            stuntick(true);
        }
        return (*this)();
    }
    pers& operator()(){
        if(noDisp) return *this;
        if(hp>MAXHP) return this->kill();
        if(stun>1||dead) skip=true;
        else if(stun<2) skip=false;
        if(skipAll) skip=true;
        return *this;
    }
    pers& kill(){
        dead=true;
        pos.rx(numeric_limits<uchar>::max());
        pos.ry(numeric_limits<uchar>::max());
        hp=0;
        skip=true;
        skipAll=true;
        return *this;
    }
    void stuntick(bool forced=false){//false means start of turn
        if(forced){
            if(stun>0) return;
            stun=3;
            return;
        }
        else{
            if(stun) stun--;
            if(skip) if(stun<2) skip=false;
        }
    }
};

#endif // PERS_H
