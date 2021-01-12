#ifndef _STATE_
#define _STATE_

struct Keys {
    int code;
    int action;
};

struct ViewPort {
    int width;
    int height;
    float aspectRatio;
};

struct State {
    Keys keys;
    ViewPort viewPort;
    double elapsedSeconds;
};

#endif /* _STATE_ */